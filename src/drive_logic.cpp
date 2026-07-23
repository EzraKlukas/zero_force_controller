// Raw-count zero-force control implementation.
//
// The controller intentionally works in the units presently available from the
// hardware path: ELM3604 raw signed counts and ClearPath motor counts. It is a
// physical-control checkpoint, not a calibrated SI-unit force controller.

#include "drive_logic.hpp"
#include <cmath>
#include <format>
#include <iostream>

#include "cia402.hpp"

DriveLogic::DriveLogic(double kp, double drag) : kp_(kp), drag_(drag) {}

void DriveLogic::ResetHoldPosition(std::int32_t actual_position) {
  target_position_ = actual_position;
}

bool DriveLogic::FindSetPoint(const CycleInputs &inputs) {
  if (inputs.sample_index < setpoint_sample_size) {
    // First window: average raw X counts to define the "zero force" target for
    // the current fixture and load-cell electronics.
    target_x_ += inputs.force.x.raw_sample;
    return false;
  } else if (inputs.sample_index == setpoint_sample_size) {
    target_x_ /= setpoint_sample_size;
    return false;
  } else if (inputs.sample_index < 2 * setpoint_sample_size) {
    // Second window: estimate raw-count noise so small deviations near the
    // baseline do not drive motor motion.
    int32_t delta = inputs.force.x.raw_sample - target_x_;
    rms_delta_x_ += delta * delta;
    return false;
  } else if (inputs.sample_index == 2 * setpoint_sample_size) {
    rms_delta_x_ /= setpoint_sample_size;
    rms_delta_x_ = std::sqrt((double)rms_delta_x_);
    std::cout << std::format("target_x_: {}, rms_delta_x: {}\n", target_x_,
                             rms_delta_x_);
    initial_position_ = inputs.motor.actual_position;
  }
  return true;
}

bool DriveLogic::ReturnHome(const CycleInputs &inputs,
                            Clearpath::Command *command) {
  bool done = false;
  // Move away from the asserted limit until the motor reaches the position
  // captured immediately after the setpoint/noise windows.
  if (negative_limit_latched_) {
    if (inputs.motor.actual_position < initial_position_) {
      target_position_ += 500;
    } else {
      done = true;
    }
  } else {
    if (inputs.motor.actual_position > initial_position_) {
      target_position_ -= 500;
    } else {
      done = true;
    }
  }
  command->controlword = CiA402::kControlwordEnableOperation;
  command->mode_op = CiA402::kModeCsp;
  command->target_position = target_position_;
  command->target_velocity = 0;
  command->target_torque = 0;

  return done;
}

bool DriveLogic::LimitSwitchCheck(const CycleInputs &inputs) {
  const bool negative_limit = inputs.motor.negative_limit_reached();
  const bool positive_limit = inputs.motor.positive_limit_reached();

  /* trying something, to make ROS be the latch resetting agent, rather than the
  current switch state, once a switch has been hit.
  // Rearm each limit after the switch is released.
  if (!negative_limit) {
    negative_limit_latched_ = false;
  }
  if (!positive_limit) {
    positive_limit_latched_ = false;
  }
  */

  // Reverse only when moving into the asserted limit, and only once
  // per assertion. Note that positive position_step_per_cycle corresponds to
  // downward motion of the load cell.
  if (next_position_step_ < 0 && negative_limit && !negative_limit_latched_) {
    next_position_step_ = -next_position_step_;
    negative_limit_latched_ = true;
    return true;
  }

  if (next_position_step_ > 0 && positive_limit && !positive_limit_latched_) {
    next_position_step_ = -next_position_step_;
    positive_limit_latched_ = true;
    return true;
  }
  return false;
}

void DriveLogic::CalculateNextCommand(const CycleInputs &inputs,
                                      Clearpath::Command *command) {
  if (!LimitSwitchCheck(inputs)) {
    const auto delta_x = inputs.force.x.raw_sample - target_x_;
    // Convert raw X-count error into an empirical motor-count acceleration.
    // The 1000 factor keeps useful command-line gain values in a manageable
    // range; it is not a physical unit conversion.
    if (std::abs(delta_x) > rms_delta_x_) {
      next_velocity_step_ = -static_cast<int32_t>(kp_ / 1000.0 * delta_x);
    } else {
      next_velocity_step_ = 0;
    }
  }

  // next_position_step_ is a globally accruing motor-count step.
  // next_velocity_step_ is treated like acceleration proportional to raw
  // load-cell error, then damped by drag_ before integration into position.
  next_position_step_ += next_velocity_step_;
  next_position_step_ =
      static_cast<int32_t>((1.0 - drag_) * next_position_step_);
  target_position_ += next_position_step_;

  command->controlword = CiA402::kControlwordEnableOperation;
  command->mode_op = CiA402::kModeCsp;
  command->target_position = target_position_;
  command->target_velocity = 0;
  command->target_torque = 0;
}

void DriveLogic::InertiaCalibrationNextCommand(const CycleInputs &inputs,
                                               Clearpath::Command *command) {
  if (!LimitSwitchCheck(inputs)) {
    const int32_t displacement = target_position_ - initial_position_;
    const int32_t direction = displacement >= 0 ? 1 : -1;

    if (std::abs(displacement) < zero_accel_position_range) {
      next_position_step_ = direction * base_position_step;
    } else {
      next_velocity_step_ -= direction * accel_step_;

      next_velocity_step_ = std::clamp(next_velocity_step_, -const_accel_target,
                                       const_accel_target);
    }

    next_position_step_ += next_velocity_step_;
  }

  target_position_ += next_position_step_;

  command->controlword = CiA402::kControlwordEnableOperation;
  command->mode_op = CiA402::kModeCsp;
  command->target_position = target_position_;
  command->target_velocity = 0;
  command->target_torque = 0;
}

TelemetryFrame
DriveLogic::GetTelemetry(const CycleInputs &inputs) const noexcept {
  TelemetryFrame frame{};
  frame.sample_index = inputs.sample_index;
  frame.source_monotonic_ns = inputs.scheduled_time_ns;
  frame.wakeup_latency_ns = inputs.wakeup_latency_ns;
  frame.analog = inputs.force;
  frame.motor = inputs.motor;

  ControllerTelemetry &telemetry = frame.telemetry;
  if (negative_limit_latched_ || positive_limit_latched_) {
    telemetry.phase = ControlPhase::returning_home;
  } else if (inputs.sample_index < setpoint_sample_size) {
    telemetry.phase = ControlPhase::baseline_capture;
  } else if (inputs.sample_index < 2U * setpoint_sample_size) {
    telemetry.phase = ControlPhase::noise_estimation;
  } else {
    telemetry.phase = ControlPhase::balancing;
  }

  telemetry.target_x_raw = target_x_;
  telemetry.noise_rms_raw = rms_delta_x_;
  telemetry.force_error_x_raw = inputs.force.x.raw_sample - target_x_;
  telemetry.velocity_step_counts = next_velocity_step_;
  telemetry.position_step_counts = next_position_step_;
  telemetry.target_position_counts = target_position_;
  telemetry.kp = kp_;
  telemetry.drag = drag_;
  telemetry.negative_limit_latched = negative_limit_latched_;
  telemetry.positive_limit_latched = positive_limit_latched_;

  return frame;
}
