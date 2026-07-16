#include "drive_logic.hpp"
#include <cmath>
#include <format>
#include <iostream>

#include "cia402.hpp"

DriveLogic::DriveLogic(std::int32_t position_step_per_cycle)
    : default_step_per_cycle_(position_step_per_cycle) {}

void DriveLogic::ResetHoldPosition(std::int32_t actual_position) {
  target_position_ = actual_position;
}

bool DriveLogic::FindSetPoint(const CycleInputs &inputs) {
  if (inputs.sample_index < setpoint_sample_size) {
    target_x_ += inputs.force.x.raw_sample;
    return false;
  } else if (inputs.sample_index == setpoint_sample_size) {
    target_x_ /= setpoint_sample_size;
    return false;
  } else if (inputs.sample_index < 2 * setpoint_sample_size) {
    // measuring variance
    int32_t delta = inputs.force.x.raw_sample - target_x_;
    rms_delta_x_ += delta * delta;
    return false;
  } else if (inputs.sample_index == 2 * setpoint_sample_size) {
    rms_delta_x_ /= setpoint_sample_size;
    rms_delta_x_ = std::sqrt((double)rms_delta_x_);
    std::cout << std::format("target_x_: {}, rms_delta_x: {}\n", target_x_,
                             rms_delta_x_);
  }
  return true;
}

bool DriveLogic::LimitSwitchCheck(const CycleInputs &inputs) {
  const bool negative_limit = inputs.motor.negative_limit_reached();
  const bool positive_limit = inputs.motor.positive_limit_reached();

  // Rearm each limit after the switch is released.
  if (!negative_limit) {
    negative_limit_latched_ = false;
  }
  if (!positive_limit) {
    positive_limit_latched_ = false;
  }

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
    if (std::abs(delta_x) > (5 * rms_delta_x_)) {
      next_position_step_ = std::signbit(delta_x) ? default_step_per_cycle_
                                                  : -default_step_per_cycle_;
    } else {
      next_position_step_ = 0;
    }
  }

  target_position_ += next_position_step_;

  command->controlword = CiA402::kControlwordEnableOperation;
  command->mode_op = CiA402::kModeCsp;
  command->target_position = target_position_;
  command->target_velocity = 0;
  command->target_torque = 0;
}
