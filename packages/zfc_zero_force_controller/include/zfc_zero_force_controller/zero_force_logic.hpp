#pragma once
#include "zfc_interfaces/control_types.hpp"
namespace zfc_zero_force_controller {
struct ZeroForceSettings {
  zfc::MotionBounds bounds{};
  bool hold_only=false;
  double baseline_duration_s=1, noise_duration_s=1;
  double acceleration_per_force=0.1; // (m/s^2)/N, simulation tuning only
  double damping_per_s=5, inertial_force_coefficient_kg=0;
  double noise_multiplier=3, minimum_deadband_n=0.05;
  double max_acceleration_mps2=0.5, max_velocity_mps=0.02;
  double stationary_velocity_mps=0.001, max_force_n=1000;
  int force_response_sign=-1;
  bool valid() const noexcept {
    const double values[]={baseline_duration_s,noise_duration_s,acceleration_per_force,
      damping_per_s,inertial_force_coefficient_kg,noise_multiplier,minimum_deadband_n,
      max_acceleration_mps2,max_velocity_mps,stationary_velocity_mps,max_force_n};
    for (double v:values) if (!std::isfinite(v)) return false;
    return bounds.valid() && baseline_duration_s>=zfc::dt && baseline_duration_s<=60 &&
      noise_duration_s>=zfc::dt && noise_duration_s<=60 &&
      acceleration_per_force>=0 && acceleration_per_force<=100 &&
      damping_per_s>=0 && damping_per_s<=1000 &&
      std::abs(inertial_force_coefficient_kg)<=1000 &&
      noise_multiplier>=0 && noise_multiplier<=20 && minimum_deadband_n>=0 &&
      minimum_deadband_n<=1000 && max_acceleration_mps2>0 && max_acceleration_mps2<=100 &&
      max_velocity_mps>0 && max_velocity_mps<=1 &&
      stationary_velocity_mps>0 && stationary_velocity_mps<=0.1 &&
      max_force_n>0 && max_force_n<=1e6 &&
      (force_response_sign==-1 || force_response_sign==1);
  }
};
class ZeroForceLogic {
public:
  bool activate(const ZeroForceSettings &settings, const zfc::Inputs &in) noexcept {
    reset();
    if (!settings.valid() || !zfc::finite(in) ||
        std::abs(in.velocity_mps)>settings.stationary_velocity_mps ||
        std::abs(in.force_n)>settings.max_force_n ||
        !settings.bounds.contains(in.position_m,in.position_m))
      return false;
    p_=settings;
    origin_=in.position_m;
    state_.measured=in;
    state_.reference_position_m=in.position_m;
    state_.phase=p_.hold_only ? zfc::Phase::hold : zfc::Phase::baseline;
    active_=true;
    return true;
  }
  void reset() noexcept {
    state_={}; active_=false; count_=0; origin_=mean_=noise_scale_=noise_sum_=0;
  }
  zfc::Snapshot update(const zfc::Inputs &in) noexcept {
    if (!active_ || !state_.valid) return zfc::fail(state_,in,state_.fault);
    if (!zfc::finite(in) || std::abs(in.force_n)>p_.max_force_n)
      return zfc::fail(state_,in,zfc::Fault::feedback);
    if (!zfc::period_valid(in,state_))
      return zfc::fail(state_,in,zfc::Fault::period);
    if (!p_.bounds.contains(in.position_m,origin_))
      return zfc::fail(state_,in,zfc::Fault::bounds);
    state_.measured=in;
    if (state_.phase==zfc::Phase::hold) {
      state_.reference_position_m=in.position_m;
      return state_;
    }
    if (state_.phase==zfc::Phase::baseline || state_.phase==zfc::Phase::noise) {
      if (std::abs(in.velocity_mps)>p_.stationary_velocity_mps)
        return zfc::fail(state_,in,zfc::Fault::feedback);
      state_.reference_position_m=in.position_m; // capture holds measured position
      if (state_.phase==zfc::Phase::baseline) {
        ++count_;
        mean_ += (in.force_n-mean_)/double(count_);
        state_.baseline_force_n=mean_;
        if (count_>=static_cast<std::uint64_t>(std::ceil(p_.baseline_duration_s/zfc::dt))) {
          state_.phase=zfc::Phase::noise; count_=0;
        }
      } else {
        const double deviation=std::abs(in.force_n-state_.baseline_force_n);
        // Scaled sum of squared deviations: stable RMS about the FROZEN baseline,
        // including DC drift. This is not standard deviation around a second mean.
        if (deviation>0) {
          if (deviation>noise_scale_) {
            const double ratio=noise_scale_/deviation;
            noise_sum_=1+noise_sum_*ratio*ratio;
            noise_scale_=deviation;
          } else {
            const double ratio=deviation/noise_scale_;
            noise_sum_+=ratio*ratio;
          }
        }
        ++count_;
        state_.noise_rms_n=noise_scale_*std::sqrt(noise_sum_/double(count_));
        if (count_>=static_cast<std::uint64_t>(std::ceil(p_.noise_duration_s/zfc::dt))) {
          state_.phase=zfc::Phase::compliant;
          state_.progress=1;
        }
      }
      return state_;
    }
    state_.residual_force_n=in.force_n-state_.baseline_force_n -
      p_.inertial_force_coefficient_kg*state_.reference_acceleration_mps2;
    const double threshold=std::max(p_.minimum_deadband_n,
                                   p_.noise_multiplier*state_.noise_rms_n);
    const double error=std::copysign(std::max(0.0,
                              std::abs(state_.residual_force_n)-threshold),
                              state_.residual_force_n);
    const double old_velocity=state_.reference_velocity_mps;
    const double response=std::clamp(p_.force_response_sign*p_.acceleration_per_force*error,
                                    -p_.max_acceleration_mps2,p_.max_acceleration_mps2);
    const double damped=(old_velocity+response*zfc::dt)*std::exp(-p_.damping_per_s*zfc::dt);
    const double velocity=std::clamp(
      std::clamp(damped,old_velocity-p_.max_acceleration_mps2*zfc::dt,
                        old_velocity+p_.max_acceleration_mps2*zfc::dt),
      -p_.max_velocity_mps,p_.max_velocity_mps);
    const double command=state_.reference_position_m+velocity*zfc::dt;
    if (!std::isfinite(state_.residual_force_n) || !std::isfinite(command) ||
        !p_.bounds.contains(command,origin_))
      return zfc::fail(state_,in,zfc::Fault::bounds);
    state_.reference_acceleration_mps2=(velocity-old_velocity)/zfc::dt;
    state_.reference_velocity_mps=velocity;
    state_.reference_position_m=command;
    return state_;
  }
  const zfc::Snapshot &snapshot() const noexcept { return state_; }
private:
  ZeroForceSettings p_{};
  zfc::Snapshot state_{};
  bool active_=false;
  std::uint64_t count_=0;
  double origin_=0, mean_=0, noise_scale_=0, noise_sum_=0;
};
} // namespace zfc_zero_force_controller
