#pragma once
#include "count_command.hpp"
#include <ethercat_system.hpp>
namespace zfc_zero_force_controller {
struct ZeroForceParameters {
  double kp_ = 0.0;   // basically the higher the better
  double drag_ = 0.0; // exponential velocity decay emulates drag
  double k_af_ = 0.0; // calculated by ros2 node after calibration
};

enum class ZfState { Idle, FindingForceSetPoint, ZeroForce };

// Each accepted update updates position and internal variables, without heap
// storage or time integration.
class ZeroForceDynamics {
public:
  static bool valid(const ZeroForceParameters &p) noexcept {
    return p.kp_ > 0 && p.kp_ <= 2.0 && p.drag_ >= 0 && p.drag_ <= 0.0000001 &&
           p.k_af_ >= 0.0 && p.k_af_ <= 1.0; // arbitrary!
  }
  bool configure(const ZeroForceParameters &p) noexcept {
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
    active_ = true;
    return true;
  }
  void reset() noexcept {
    active_ = false;
    aborting_ = false;
    finished_ = false;
    update_count_ = 0;
    start_position_ = commanded_position_ = 0;
    velocity_ = acceleration_ = 0;
    acceleration_limit_ = 0;
    completed_shuttle_cycles_ = 0;
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

    switch (state_) {
    case ZfState::Idle:
      return true;
    case ZfState::FindingForceSetPoint:
      if (setpoint_sample_index_ < setpoint_sample_size_) {
        target_force_ += raw_force_;
      } else if (setpoint_sample_index_ == setpoint_sample_size_) {
        target_force_ /= setpoint_sample_size_;
      } else if (setpoint_sample_index_ < 2 * setpoint_sample_size_) {
        const auto delta = raw_force_ - target_force_;
        force_rms_ += delta;
      } else if (setpoint_sample_index_ == 2 * setpoint_sample_size_) {
        force_rms_ /= setpoint_sample_size_;
        force_rms_ = std::sqrt((double)force_rms_);
        state_ = ZfState::ZeroForce;
      }
      break;
    case ZfState::ZeroForce:
      // all the dynamics we need!
      const auto f_delta = raw_force_ - target_force_;
      const auto f_external = f_delta - k_af_ * acceleration_;
      if (std::abs(f_external) > force_rms_) {
        acceleration_ = -static_cast<std::int32_t>(k_p_ / 1000.0 * f_external);
      } else {
        acceleration_ = 0.0;
      }
      break;
    }

    // apply commanded acceleration
    velocity_ += acceleration_;
    // apply drag
    velocity_ = static_cast<std::int32_t>((1.0 - k_drag_) * velocity_);

    commanded_position_ += velocity_;

    return true;
  }
  std::int32_t target() const noexcept { return commanded_position_; }
  bool set_force(std::int32_t &raw_force) { raw_force_ = raw_force; }
  std::uint64_t excessive_periods() const noexcept {
    return excessive_periods_;
  }

private:
  ZeroForceParameters p_{};
  ZfState state_ = ZfState::Idle;

  // implement a state machine
  // function specific parameters included
  bool configured_ = false;
  bool active_ = false;
  bool aborting_ = false;
  bool finished_ = false;

  std::int64_t update_count_ = 0;

  // Force
  std::int32_t raw_force_ = 0;
  std::int32_t target_force_ = 0;

  // Motion state
  std::int32_t start_position_ = 0;
  std::int32_t commanded_position_ = 0;
  std::int32_t velocity_ = 0;
  std::int32_t acceleration_ = 0;

  // Acceleration ramp state
  std::int32_t acceleration_limit_ = 0;
  std::int32_t completed_shuttle_cycles_ = 0;

  // setpoint variables / constants
  const std::int32_t setpoint_sample_size_ = 1000;
  std::int32_t setpoint_sample_index_ = 0;
  std::int32_t force_rms_ = 0;

  // gains
  double k_af_ = 0.0;
  double k_p_ = 1.0;
  double k_drag_ = 0.0000001;

  std::uint64_t excessive_periods_ = 0;
};
} // namespace zfc_zero_force_controller
