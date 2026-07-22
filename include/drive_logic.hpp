// Raw-count zero-force control policy.
//
// This header defines the typed boundary between the EtherCAT loop and the
// controller. DriveLogic consumes already-decoded ELM3604 feedback plus
// ClearPath feedback and emits a ClearPath command. It deliberately does not
// know about IgH masters, domains, PDO offsets, or process-data memory.

#pragma once

#include <cstdint>

#include "clearpath_pdo.hpp"
#include "elm3604_pdo.hpp"

inline constexpr std::size_t setpoint_sample_size = 1000;

// Per-cycle inputs passed from the EtherCAT loop into DriveLogic. Force samples
// are ELM3604 raw signed counts; motor positions and velocities are ClearPath
// drive counts.
struct CycleInputs {
  Elm3604::Feedback force;
  Clearpath::PDO::TxPDOs motor;
  std::uint64_t sample_index = 0;
  std::uint64_t scheduled_time_ns = 0;
  std::int64_t wakeup_latency_ns = 0;
};

enum class ControlPhase : std::uint8_t {
  enabling,
  baseline_capture,
  noise_estimation,
  balancing,
  returning_home,
  stopped,
  fault
};

struct ControllerTelemetry {
  ControlPhase phase{};

  std::int32_t target_x_raw{};
  std::int32_t noise_rms_raw{};
  std::int32_t force_error_x_raw{};

  std::int32_t velocity_step_counts{};
  std::int32_t position_step_counts{};
  std::int32_t target_position_counts{};

  double kp{};
  double drag{};

  bool negative_limit_latched{};
  bool positive_limit_latched{};
};

struct TelemetryFrame {
  std::uint64_t sequence{};
  std::uint64_t sample_index{};
  std::uint64_t source_monotonic_ns{};
  std::int64_t wakeup_latency_ns{};
  std::uint64_t timing_overruns{};
  std::uint64_t queue_drop_count{};

  Elm3604::Feedback analog{};
  Clearpath::PDO::TxPDOs motor{};
  Clearpath::Command command{};
  ControllerTelemetry telemetry{};

  bool ethercat_ready{};
  bool communication_lost{};

  std::uint64_t last_applied_command_id{};
  std::int32_t last_command_result{};
};

// Implements the current physical checkpoint controller:
// 1. learn a raw X-axis baseline,
// 2. estimate raw X-axis noise,
// 3. convert raw-count error into motor-count acceleration with an empirical
//    gain,
// 4. damp and accumulate that into target-position increments,
// 5. return home after a logical limit hit.
class DriveLogic {
public:
  explicit DriveLogic(double kp, double drag);

  // Seeds the target position from the actual position once CSP is enabled.
  void ResetHoldPosition(std::int32_t actual_position);
  // Returns true after the baseline and noise windows have completed.
  bool FindSetPoint(const CycleInputs &inputs);
  // Handles logical ClearPath limit bits and latches each assertion once.
  bool LimitSwitchCheck(const CycleInputs &inputs);
  // Calculates the next normal balancing command in raw-count/motor-count
  // units. No SI-unit conversion is performed here.
  void CalculateNextCommand(const CycleInputs &inputs,
                            Clearpath::Command *command);
  // Commands motion back toward the post-setpoint initial position.
  bool ReturnHome(const CycleInputs &inputs, Clearpath::Command *command);

  // emitter for ROS2 to buffer and publish at lower priority and frequency.
  TelemetryFrame GetTelemetry(const CycleInputs &inputs) const noexcept;

private:
  // Accumulated motor-count step, treated like velocity in the raw-count
  // controller model.
  std::int32_t next_position_step_ = 0;
  // Per-cycle change in next_position_step_, treated like acceleration.
  std::int32_t next_velocity_step_ = 0;
  std::int32_t target_position_ = 0;
  // Raw ELM X-axis baseline and RMS raw-count noise estimate.
  std::int32_t target_x_ = 0;
  std::int32_t rms_delta_x_ = 0;
  // Empirical tuning parameters, not physical SI gains.
  double kp_ = 0.0;
  double drag_ = 0.0;

  bool negative_limit_latched_ = false;
  bool positive_limit_latched_ = false;

  std::int32_t initial_position_ = 0;
};
