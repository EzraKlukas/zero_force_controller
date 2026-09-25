#pragma once
#include "count_command.hpp"
#include <ethercat_system.hpp>
namespace zfc_zero_force_controller {
struct CalibrationParameters {
  bool do_calibrate_ = true;
  std::int32_t center_zone_half_width_ = 1000;
  std::int32_t base_velocity_ = 500;
  std::int32_t jerk_step_ = 5;
  std::int32_t max_acceleration_limit_ = 20;
  std::int32_t cycles_per_acceleration_increase_ = 10;
};

// Each accepted update updates position and internal variables, without heap
// storage or time integration.
class CalibrationSequencer {
public:
  static bool valid(const CalibrationParameters &p) noexcept {
    return p.center_zone_half_width_ > 0 &&
           p.center_zone_half_width_ <= 10000 && p.jerk_step_ > 0 &&
           p.base_velocity_ > 0 && p.base_velocity_ <= zfc::kMaximumVelocity &&
           p.jerk_step_ > 0 && p.jerk_step_ <= zfc::kMaximumJerk &&
           p.max_acceleration_limit_ <= zfc::kMaximumAcceleration &&
           p.cycles_per_acceleration_increase_ >= 1;
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
    std::int32_t start;
    if (!configured_ || !zfc::ToCounts(actual, start))
      return false;
    start_position_ = commanded_position_ = start;
    acceleration_limit_ = 1;
    active_ = true;
    return true;
  }
  void reset() noexcept {
    active_ = false;
    aborting_ = false;
    finished_ = false;
    update_count_ = 0;
    start_position_ = commanded_position_ = 0;
    excessive_periods_ = 0;
  }
  bool update(std::int64_t period_ns) noexcept {
    if (!active_ || period_ns <= 0)
      return false;
    // Observe jitter without changing the requested cycle-count sequence.
    // A gap beyond 10 ms faults; it is never compensated by a larger step.
    if (period_ns > 1500000)
      ++excessive_periods_;
    if (period_ns > 10000000)
      return false;
    if (finished_ || !p_.do_calibrate_)
      return true;

    const auto displacement_from_start = commanded_position_ - start_position_;

    const std::int32_t direction_sign = displacement_from_start >= 0 ? 1 : -1;

    if (aborting_) {
      if (std::abs(displacement_from_start) < p_.base_velocity_) {
        finished_ = true;
        return true;
      }
      commanded_position_ -= direction_sign * p_.base_velocity_;
      return true;
    }

    const bool in_center_zone =
        std::abs(displacement_from_start) < p_.center_zone_half_width_;

    if (in_center_zone) {
      if (velocity_ == 0) { // starting condition.
        velocity_ = p_.base_velocity_;
      }

      velocity_ = std::clamp(velocity_, -p_.base_velocity_, p_.base_velocity_);

      if (!positive_center_pass_counted_ && velocity_ > 0) {
        ++completed_shuttle_cycles_;

        if (completed_shuttle_cycles_ >= p_.cycles_per_acceleration_increase_) {
          completed_shuttle_cycles_ = 0;
          ++acceleration_limit_;

          if (acceleration_limit_ >= p_.max_acceleration_limit_) {
            finished_ = true;
          }
        }

        positive_center_pass_counted_ = true;
      }
    } else {
      positive_center_pass_counted_ = false;

      acceleration_ -= direction_sign * p_.jerk_step_;

      acceleration_ =
          std::clamp(acceleration_, -acceleration_limit_, acceleration_limit_);

      velocity_ += acceleration_;
    }

    commanded_position_ += velocity_;

    return true;
  }
  void limit_hit() noexcept { aborting_ = true; }
  std::int32_t target() const noexcept { return commanded_position_; }
  std::uint64_t excessive_periods() const noexcept {
    return excessive_periods_;
  }
  bool finished_calibration() noexcept { return finished_; }

private:
  CalibrationParameters p_{};
  // function specific parameters included
  bool configured_ = false;
  bool active_ = false;
  bool aborting_ = false;
  bool finished_ = false;

  std::int64_t update_count_ = 0;

  // Motion state
  std::int32_t start_position_ = 0;
  std::int32_t commanded_position_ = 0;
  std::int32_t velocity_ = 0;
  std::int32_t acceleration_ = 0;

  // Acceleration ramp state
  std::int32_t acceleration_limit_ = 0;
  std::int32_t completed_shuttle_cycles_ = 0;
  bool positive_center_pass_counted_ = true;

  std::uint64_t excessive_periods_ = 0;
};
} // namespace zfc_zero_force_controller
