#include "drive_logic.hpp"
#include <cmath>

#include "cia402.hpp"

DriveLogic::DriveLogic(std::int32_t position_step_per_cycle)
    : position_step_per_cycle_(position_step_per_cycle) {}

void DriveLogic::ResetHoldPosition(std::int32_t actual_position) {
  target_position_ = actual_position;
}

void DriveLogic::CalculateNextCommand(const CycleInputs &inputs,
                                      Clearpath::Command *command) {
  (void)inputs.force;
  (void)inputs.sample_index;
  (void)inputs.scheduled_time_ns;
  (void)inputs.wakeup_latency_ns;

  const bool negative_limit =
      inputs.motor.negative_limit_reached();
  const bool positive_limit =
      inputs.motor.positive_limit_reached();

  // Rearm each limit after the switch is released.
  if (!negative_limit) {
      negative_limit_latched_ = false;
  }
  if (!positive_limit) {
      positive_limit_latched_ = false;
  }

  // Reverse only when moving into the asserted limit, and only once
  // per assertion. Note that positive position_step_per_cycle corresponds to downward motion of the load cell.
  if (position_step_per_cycle_ < 0 &&
          negative_limit &&
          !negative_limit_latched_) {
      position_step_per_cycle_ = -position_step_per_cycle_;
      negative_limit_latched_ = true;
  }

  if (position_step_per_cycle_ > 0 &&
          positive_limit &&
          !positive_limit_latched_) {
      position_step_per_cycle_ = -position_step_per_cycle_;
      positive_limit_latched_ = true;
  }

  target_position_ += position_step_per_cycle_;

  command->controlword = CiA402::kControlwordEnableOperation;
  command->mode_op = CiA402::kModeCsp;
  command->target_position = target_position_;
  command->target_velocity = 0;
  command->target_torque = 0;
}
