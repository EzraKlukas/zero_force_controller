#pragma once

#include <cstdint>

#include "clearpath_pdo.hpp"
#include "elm3604_pdo.hpp"

struct CycleInputs {
  Elm3604::Feedback force;
  Clearpath::PDO::TxPDOs motor;
  std::uint64_t sample_index = 0;
  std::uint64_t scheduled_time_ns = 0;
  std::int64_t wakeup_latency_ns = 0;
};

class DriveLogic {
public:
  explicit DriveLogic(std::int32_t position_step_per_cycle);

  void ResetHoldPosition(std::int32_t actual_position);
  void CalculateNextCommand(const CycleInputs &inputs,
                            Clearpath::Command *command);

private:
  std::int32_t position_step_per_cycle_ = 0;
  std::int32_t target_position_ = 0;

  bool negative_limit_latched_ = false;
  bool positive_limit_latched_ = false;
};
