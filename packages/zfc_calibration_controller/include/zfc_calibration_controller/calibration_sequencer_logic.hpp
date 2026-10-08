#pragma once
#include "zfc_calibration_controller/calibration_sequencer.hpp"
#include "zfc_interfaces/control_types.hpp"
namespace zfc_calibration_controller {
struct CalibrationSettings {
  CalibrationParameters trajectory{};
  zfc::MotionBounds bounds{};
  double settling_acceleration_mps2=0.2, settling_timeout_s=5;
  double stationary_velocity_mps=0.001, tracking_tolerance_m=0.0001;
  double stationary_duration_s=0.1;
  bool valid() const noexcept {
    return CalibrationSequencer::valid(trajectory) && bounds.valid() &&
      std::isfinite(settling_acceleration_mps2) && settling_acceleration_mps2>0 &&
      settling_acceleration_mps2<=100 && std::isfinite(settling_timeout_s) &&
      settling_timeout_s>0 && settling_timeout_s<=60 &&
      std::isfinite(stationary_velocity_mps) && stationary_velocity_mps>0 &&
      stationary_velocity_mps<=0.1 && std::isfinite(tracking_tolerance_m) &&
      tracking_tolerance_m>0 && tracking_tolerance_m<=0.01 &&
      std::isfinite(stationary_duration_s) && stationary_duration_s>=zfc::dt &&
      stationary_duration_s<=10 &&
      trajectory.center_zone_half_width_m<=0.1 &&
      std::abs(trajectory.base_velocity_mps)<=1 && trajectory.jerk_mps3<=1e6 &&
      trajectory.max_acceleration_mps2<=100 &&
      trajectory.cycles_per_acceleration_increase<=1000;
  }
  // Conservative discrete turning + settling envelope. A jerk ramp to the
  // initial opposing acceleration must not prolong the first turn indefinitely.
  double required_excursion() const noexcept {
    const double speed=std::abs(trajectory.base_velocity_mps);
    const double a=trajectory.max_acceleration_mps2;
    const double peak=speed+a*a/(2*trajectory.jerk_mps3)+a*zfc::dt;
    const double ramp_time=2*a/trajectory.jerk_mps3;
    return trajectory.center_zone_half_width_m + peak*(ramp_time+3*zfc::dt) +
      peak*peak/(2*trajectory.initial_acceleration_mps2) +
      peak*peak/(2*settling_acceleration_mps2) + tracking_tolerance_m;
  }
};
class CalibrationSequencerLogic {
public:
  bool activate(const CalibrationSettings &p, const zfc::Inputs &in) noexcept {
    reset();
    if (!p.valid() || !zfc::finite(in) ||
        std::abs(in.velocity_mps)>p.stationary_velocity_mps ||
        p.required_excursion()>p.bounds.excursion_limit_m ||
        !p.bounds.contains(in.position_m-p.required_excursion(),in.position_m) ||
        !p.bounds.contains(in.position_m+p.required_excursion(),in.position_m) ||
        !sequencer_.configure(p.trajectory) || !sequencer_.activate(in.position_m))
      return false;
    p_=p; origin_=in.position_m; active_=true;
    state_.measured=in; state_.phase=zfc::Phase::trajectory;
    state_.reference_position_m=in.position_m;
    return true;
  }
  void reset() noexcept {
    sequencer_.reset(); state_={}; active_=false; origin_=0;
    settling_cycles_=stationary_cycles_=0;
  }
  zfc::Snapshot update(const zfc::Inputs &in) noexcept {
    if (!active_ || !state_.valid) return zfc::fail(state_,in,state_.fault);
    if (!zfc::finite(in)) return zfc::fail(state_,in,zfc::Fault::feedback);
    if (!zfc::period_valid(in,state_)) return zfc::fail(state_,in,zfc::Fault::period);
    if (!p_.bounds.contains(in.position_m,origin_))
      return zfc::fail(state_,in,zfc::Fault::bounds);
    state_.measured=in;
    if (state_.phase==zfc::Phase::complete) {
      // Completion remains stationary; unexpected motion invalidates handoff.
      if (std::abs(in.velocity_mps)>p_.stationary_velocity_mps ||
          std::abs(in.position_m-state_.reference_position_m)>p_.tracking_tolerance_m)
        return zfc::fail(state_,in,zfc::Fault::feedback);
      return state_;
    }
    const double previous_position=state_.reference_position_m;
    const double previous_velocity=state_.reference_velocity_mps;
    if (state_.phase==zfc::Phase::trajectory) {
      if (!sequencer_.update(in.period_ns))
        return zfc::fail(state_,in,zfc::Fault::period);
      state_.reference_position_m=sequencer_.target();
      // Includes the effective acceleration of center-zone velocity clipping.
      state_.reference_velocity_mps=(sequencer_.target()-previous_position)/zfc::dt;
      state_.progress=sequencer_.finished_calibration() ? 0.9 : sequencer_.progress()*0.9;
      if (sequencer_.finished_calibration()) state_.phase=zfc::Phase::settling;
    } else {
      ++settling_cycles_;
      if (settling_cycles_*zfc::dt>p_.settling_timeout_s)
        return zfc::fail(state_,in,zfc::Fault::settling_timeout);
      const double velocity=std::copysign(std::max(0.0,
        std::abs(previous_velocity)-p_.settling_acceleration_mps2*zfc::dt),
        previous_velocity);
      state_.reference_velocity_mps=velocity;
      state_.reference_position_m+=velocity*zfc::dt;
      if (velocity==0 && std::abs(in.velocity_mps)<=p_.stationary_velocity_mps &&
          std::abs(in.position_m-state_.reference_position_m)<=p_.tracking_tolerance_m)
        ++stationary_cycles_;
      else stationary_cycles_=0;
      if (stationary_cycles_*zfc::dt>=p_.stationary_duration_s) {
        state_.phase=zfc::Phase::complete; state_.progress=1;
      }
    }
    state_.reference_acceleration_mps2=
      (state_.reference_velocity_mps-previous_velocity)/zfc::dt;
    if (!std::isfinite(state_.reference_velocity_mps) ||
        !std::isfinite(state_.reference_acceleration_mps2) ||
        !p_.bounds.contains(state_.reference_position_m,origin_))
      return zfc::fail(state_,in,zfc::Fault::bounds);
    return state_;
  }
  const zfc::Snapshot &snapshot() const noexcept { return state_; }
private:
  CalibrationSettings p_{};
  CalibrationSequencer sequencer_;
  zfc::Snapshot state_{};
  bool active_=false;
  double origin_=0;
  std::uint64_t settling_cycles_=0, stationary_cycles_=0;
};
} // namespace zfc_calibration_controller
