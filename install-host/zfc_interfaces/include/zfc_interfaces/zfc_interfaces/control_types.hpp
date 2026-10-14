#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
namespace zfc {
constexpr double dt = 0.001;
enum class Phase : std::uint8_t {
  idle=0, baseline=1, noise=2, compliant=3, hold=4, fault=5,
  trajectory=10, settling=11, complete=12
};
enum class Fault : std::uint8_t {
  none=0, feedback=1, period=2, bounds=3, settings=4, settling_timeout=5
};
struct Inputs {
  double position_m=0, velocity_mps=0, force_n=0;
  std::int64_t time_ns=0, period_ns=1000000;
};
struct Snapshot {
  Inputs measured{};
  Phase phase=Phase::idle;
  Fault fault=Fault::none;
  bool valid=true;
  double reference_position_m=0, reference_velocity_mps=0,
         reference_acceleration_mps2=0;
  double baseline_force_n=0, noise_rms_n=0, residual_force_n=0, progress=0;
  std::uint64_t excessive_periods=0;
};
struct MotionBounds {
  double excursion_limit_m=0.06;
  bool use_position_bounds=false;
  double lower_position_m=0, upper_position_m=0.5;
  bool valid() const noexcept {
    return std::isfinite(excursion_limit_m) && excursion_limit_m>0 &&
      excursion_limit_m<=1 &&
      (!use_position_bounds || (std::isfinite(lower_position_m) &&
        std::isfinite(upper_position_m) && lower_position_m<upper_position_m));
  }
  bool contains(double q, double origin) const noexcept {
    return std::isfinite(q) && std::abs(q-origin)<=excursion_limit_m &&
      (!use_position_bounds || (q>=lower_position_m && q<=upper_position_m));
  }
};
inline bool finite(const Inputs &in) noexcept {
  return std::isfinite(in.position_m) && std::isfinite(in.velocity_mps) &&
         std::isfinite(in.force_n) && in.time_ns>=0;
}
inline bool period_valid(const Inputs &in, Snapshot &out) noexcept {
  if (in.period_ns>1500000) ++out.excessive_periods;
  return in.period_ns>0 && in.period_ns<=10000000 &&
         in.time_ns>=out.measured.time_ns;
}
inline Snapshot fail(Snapshot &out, const Inputs &in, Fault reason) noexcept {
  out.measured=in;
  out.phase=Phase::fault;
  out.fault=reason;
  out.valid=false;
  out.reference_position_m=std::numeric_limits<double>::quiet_NaN();
  return out;
}
} // namespace zfc
