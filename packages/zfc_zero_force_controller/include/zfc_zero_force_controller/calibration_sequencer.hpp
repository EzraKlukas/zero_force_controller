#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
namespace zfc_zero_force_controller {
struct CalibrationParameters {
  bool do_calibrate = false;
  double center_zone_half_width_m = NAN;
  // Signed SI velocity permits preserving the original first-leg direction.
  double base_velocity_mps = NAN;
  double jerk_mps3 = NAN;
  double initial_acceleration_mps2 = NAN;
  double acceleration_increment_mps2 = NAN;
  double max_acceleration_mps2 = NAN;
  std::int64_t cycles_per_acceleration_increase = 5;
};

// Nominal 1 kHz discrete recurrence; measured period only validates scheduling.
class CalibrationSequencer {
public:
  static constexpr double dt = 0.001;
  static bool valid(const CalibrationParameters &p) noexcept {
    if (!p.do_calibrate)
      return true;
    return std::isfinite(p.center_zone_half_width_m) &&
           p.center_zone_half_width_m > 0 &&
           std::isfinite(p.base_velocity_mps) && p.base_velocity_mps != 0 &&
           std::isfinite(p.jerk_mps3) && p.jerk_mps3 > 0 &&
           std::isfinite(p.initial_acceleration_mps2) &&
           p.initial_acceleration_mps2 > 0 &&
           std::isfinite(p.acceleration_increment_mps2) &&
           p.acceleration_increment_mps2 > 0 &&
           std::isfinite(p.max_acceleration_mps2) &&
           p.max_acceleration_mps2 >= p.initial_acceleration_mps2 &&
           p.cycles_per_acceleration_increase >= 1;
  }
  bool configure(const CalibrationParameters &p) noexcept {
    reset();
    configured_ = valid(p);
    if (configured_)
      p_ = p;
    return configured_;
  }
  bool activate(double actual) noexcept {
    reset();
    if (!configured_ || !std::isfinite(actual))
      return false;
    start_position_ = commanded_position_ = actual;
    acceleration_limit_ = p_.initial_acceleration_mps2;
    active_ = true;
    return true;
  }
  void reset() noexcept {
    active_ = finished_ = false;
    start_position_ = commanded_position_ = 0;
    displacement_ = displacement_error_ = velocity_error_ = 0;
    velocity_ = acceleration_ = acceleration_limit_ = 0;
    completed_shuttle_cycles_ = 0;
    positive_center_pass_counted_ = true;
    excessive_periods_ = 0;
  }
  bool update(std::int64_t period_ns) noexcept {
    if (!active_ || period_ns <= 0)
      return false;
    if (period_ns > 1500000)
      ++excessive_periods_;
    if (period_ns > 10000000)
      return false;
    if (finished_ || !p_.do_calibrate)
      return true;

    const double displacement = displacement_;
    const double direction = displacement >= 0 ? 1 : -1;
    // Avoid a different branch at an exact count-equivalent center boundary
    // solely from floating point roundoff after conversion to SI.
    const double epsilon = 1e-9 * p_.center_zone_half_width_m;
    const bool in_center =
        std::abs(displacement) < p_.center_zone_half_width_m - epsilon;
    const double speed = std::abs(p_.base_velocity_mps);
    if (in_center) {
      if (velocity_ == 0)
        velocity_ = p_.base_velocity_mps;
      const double clamped = std::clamp(velocity_, -speed, speed);
      if (clamped != velocity_)
        velocity_error_ = 0;
      velocity_ = clamped;
      if (!positive_center_pass_counted_ &&
          velocity_ * p_.base_velocity_mps > 0) {
        ++completed_shuttle_cycles_;
        if (completed_shuttle_cycles_ >= p_.cycles_per_acceleration_increase) {
          completed_shuttle_cycles_ = 0;
          acceleration_limit_ += p_.acceleration_increment_mps2;
          const double tolerance = 64 * std::numeric_limits<double>::epsilon() *
                                   p_.max_acceleration_mps2;
          if (acceleration_limit_ >= p_.max_acceleration_mps2 - tolerance)
            finished_ = true;
        }
        positive_center_pass_counted_ = true;
      }
    } else {
      positive_center_pass_counted_ = false;
      acceleration_ -= direction * p_.jerk_mps3 * dt;
      acceleration_ = std::clamp(acceleration_, -acceleration_limit_,
                                  acceleration_limit_);
      accumulate(velocity_, velocity_error_, acceleration_ * dt);
    }
    // Preserve the last accepted step on the completion cycle.
    accumulate(displacement_, displacement_error_, velocity_ * dt);
    commanded_position_ = start_position_ + displacement_;
    return std::isfinite(commanded_position_) && std::isfinite(velocity_) &&
           std::isfinite(acceleration_);
  }
  double target() const noexcept { return commanded_position_; }
  std::uint64_t excessive_periods() const noexcept { return excessive_periods_; }
  bool finished_calibration() const noexcept { return finished_; }
private:
  // Compensated sums keep SI roundoff from moving exact legacy center crossings.
  static void accumulate(double &sum, double &error, double step) noexcept {
    const double corrected = step - error;
    const double next = sum + corrected;
    error = (next - sum) - corrected;
    sum = next;
  }
  CalibrationParameters p_{};
  bool configured_ = false, active_ = false, finished_ = false;
  double start_position_ = 0, commanded_position_ = 0;
  double displacement_ = 0, displacement_error_ = 0, velocity_error_ = 0;
  double velocity_ = 0, acceleration_ = 0, acceleration_limit_ = 0;
  std::int64_t completed_shuttle_cycles_ = 0;
  bool positive_center_pass_counted_ = true;
  std::uint64_t excessive_periods_ = 0;
};
} // namespace zfc_zero_force_controller
