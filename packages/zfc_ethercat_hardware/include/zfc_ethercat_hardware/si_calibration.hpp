#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>
namespace zfc_ethercat_hardware {
struct SiCalibration {
  double m_per_count=NAN;
  bool velocity_from_encoder=true, soft_bounds_enabled=false;
  double velocity_mps_per_raw_unit=NAN;
  std::array<double,3> force_scale{NAN,NAN,NAN}, force_zero{0,0,0};
  double lower=NAN, upper=NAN;
  std::int32_t reference_counts=0;
  bool reference_valid=false;
  static bool parameter(std::string_view key) noexcept {
    return key=="m_per_count" || key=="velocity_from_encoder" ||
      key=="velocity_mps_per_raw_unit" || key=="soft_bounds_enabled" ||
      key=="soft_lower_m" || key=="soft_upper_m" ||
      key=="conventions_confirmed" || key=="force_frame" ||
      key=="force_channel_mapping" || key=="force_x_newtons_per_count" ||
      key=="force_y_newtons_per_count" || key=="force_z_newtons_per_count" ||
      key=="force_x_zero_counts" || key=="force_y_zero_counts" || key=="force_z_zero_counts";
  }
  template<class Parameters> static SiCalibration load(const Parameters &params) {
    auto text=[&](const std::string &key) {
      const auto it=params.find(key);
      if (it==params.end()) throw std::runtime_error("Missing installation calibration: "+key);
      return it->second;
    };
    auto number=[&](const std::string &key,bool nonzero) {
      const auto value=text(key);
      std::size_t used=0;
      double result=NAN;
      try { result=std::stod(value,&used); }
      catch (...) { throw std::runtime_error("Invalid installation calibration: "+key); }
      if (used!=value.size() || !std::isfinite(result) || (nonzero && result==0))
        throw std::runtime_error("Installation calibration "+key+" must be finite"+
                                 (nonzero ? " and nonzero" : ""));
      return result;
    };
    auto boolean=[&](const std::string &key,bool fallback) {
      const auto it=params.find(key);
      if (it==params.end()) return fallback;
      if (it->second!="true" && it->second!="false")
        throw std::runtime_error(key+" must be true or false");
      return it->second=="true";
    };
    SiCalibration c;
    c.m_per_count=number("m_per_count",true);
    c.velocity_from_encoder=boolean("velocity_from_encoder",true);
    if (!c.velocity_from_encoder)
      c.velocity_mps_per_raw_unit=number("velocity_mps_per_raw_unit",true);
    const std::array<std::string,3> axes{"x","y","z"};
    for (unsigned i=0;i<3;++i) {
      c.force_scale[i]=number("force_"+axes[i]+"_newtons_per_count",true);
      const auto key="force_"+axes[i]+"_zero_counts";
      if (params.find(key)!=params.end()) c.force_zero[i]=number(key,false);
      for (const auto raw:{std::numeric_limits<std::int32_t>::min(),
                          std::numeric_limits<std::int32_t>::max()})
        if (!std::isfinite(c.force(i,raw)))
          throw std::runtime_error("Force installation calibration overflows: "+axes[i]);
    }
    if (!boolean("conventions_confirmed",false) || text("force_frame")!="load_cell_link" ||
        text("force_channel_mapping")!="x,y,z")
      throw std::runtime_error("Confirm position scale polarity and force X/Y/Z signs in "
        "load_cell_link (+X upward); conventions_confirmed must be true. Raw velocity "
        "requires independent unit/sign verification if velocity_from_encoder=false.");
    if (!std::isfinite(c.m_per_count*4294967295.0) ||
        (!c.velocity_from_encoder && !std::isfinite(c.velocity_mps_per_raw_unit*2147483648.0)))
      throw std::runtime_error("Position/velocity calibration overflows native feedback");
    c.soft_bounds_enabled=boolean("soft_bounds_enabled",false);
    if (c.soft_bounds_enabled) {
      c.lower=number("soft_lower_m",false); c.upper=number("soft_upper_m",false);
      if (c.lower>=c.upper)
        throw std::runtime_error("Measured session-relative soft bounds require lower < upper");
    }
    return c;
  }
  bool set_reference(std::int32_t counts) noexcept {
    if (reference_valid) return reference_counts==counts; // never re-zero
    reference_counts=counts; reference_valid=true; return true;
  }
  void clear_reference() noexcept { reference_valid=false; }
  double position(std::int32_t counts) const noexcept {
    return reference_valid ? m_per_count*(double(counts)-reference_counts) : NAN;
  }
  double velocity(std::int32_t raw) const noexcept {
    return velocity_mps_per_raw_unit*double(raw);
  }
  double force(unsigned axis,std::int32_t raw) const noexcept {
    return force_scale[axis]*(double(raw)-force_zero[axis]);
  }
  bool in_bounds(double q) const noexcept {
    return std::isfinite(q) && (!soft_bounds_enabled || (q>=lower && q<=upper));
  }
  bool to_counts(double q,std::int32_t &out) const noexcept {
    if (!reference_valid || !in_bounds(q) || !std::isfinite(m_per_count) || m_per_count==0)
      return false;
    const double raw=double(reference_counts)+q/m_per_count;
    if (!std::isfinite(raw) || raw<std::numeric_limits<std::int32_t>::min() ||
        raw>std::numeric_limits<std::int32_t>::max()) return false;
    const double rounded=std::round(raw);
    if (rounded<std::numeric_limits<std::int32_t>::min() ||
        rounded>std::numeric_limits<std::int32_t>::max()) return false;
    const auto counts=static_cast<std::int32_t>(rounded);
    if (!in_bounds(position(counts))) return false;
    out=counts; return true;
  }
};
class EncoderSession {
public:
  void end() noexcept { *this=EncoderSession{}; }
  void suspend() noexcept { suspended_=true; }
  bool observe(std::int32_t counts,std::uint64_t now,bool raw_stationary,
               double scale,std::int32_t count_bound) noexcept {
    if (have_read_) {
      if (now<=last_ns_) return false;
      const auto elapsed=now-last_ns_;
      const auto delta=std::int64_t(counts)-previous_;
      // Native per-cycle bound supplies a conservative discontinuity check.
      // No PDO velocity unit is assumed. Unobserved movement after deactivation
      // exceeding one native bound requires explicit session reinitialization.
      const double allowed=suspended_ ? count_bound :
        count_bound*std::max(1.0,double(elapsed)/1000000.0);
      if (std::abs(double(delta))>allowed) return false;
      velocity_=scale*double(delta)/(double(elapsed)*1e-9);
      if (!std::isfinite(velocity_)) return false;
      if (!reference_valid_ && raw_stationary && previous_stationary_ && delta==0) {
        reference_=previous_; reference_valid_=true;
      }
    }
    previous_=counts; last_ns_=now; have_read_=true;
    previous_stationary_=raw_stationary; suspended_=false;
    return true;
  }
  bool valid() const noexcept { return reference_valid_; }
  std::int32_t reference() const noexcept { return reference_; }
  double velocity() const noexcept { return velocity_; }
private:
  bool have_read_=false, reference_valid_=false, previous_stationary_=false, suspended_=false;
  std::int32_t reference_=0, previous_=0;
  std::uint64_t last_ns_=0;
  double velocity_=NAN;
};
} // namespace zfc_ethercat_hardware
