#pragma once

#include <cstdint>

#include "clearpath_pdo.hpp"
#include "elm3604_pdo.hpp"

inline constexpr std::size_t setpoint_sample_size = 1000;

struct CycleInputs {
  Elm3604::Feedback force;
  Clearpath::PDO::TxPDOs motor;
  std::uint64_t sample_index = 0;
  std::uint64_t scheduled_time_ns = 0;
  std::int64_t wakeup_latency_ns = 0;
};

class DriveLogic {
public:
  explicit DriveLogic(double kp, double drag);

  void ResetHoldPosition(std::int32_t actual_position);
  bool FindSetPoint(const CycleInputs &inputs);
  bool LimitSwitchCheck(const CycleInputs &inputs);
  void CalculateNextCommand(const CycleInputs &inputs,
                            Clearpath::Command *command);
  bool ReturnHome(const CycleInputs &inputs, Clearpath::Command *command);

private:
  std::int32_t next_position_step_ = 0;
  std::int32_t next_velocity_step_ = 0;
  std::int32_t target_position_ = 0;
  std::int32_t target_x_ = 0;
  std::int32_t rms_delta_x_ = 0;
  double kp_ = 0.0;
  double drag_ = 0.0;

  bool negative_limit_latched_ = false;
  bool positive_limit_latched_ = false;

  std::int32_t initial_position_ = 0;
};
