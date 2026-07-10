#pragma once

#include <cstdint>

#include "clearpath_pdo.hpp"

namespace CiA402 {

constexpr std::int8_t kModeCsp = 8;
constexpr std::uint16_t kControlwordDisableVoltage = 0x0000;
constexpr std::uint16_t kControlwordShutdown = 0x0006;
constexpr std::uint16_t kControlwordSwitchOn = 0x0007;
constexpr std::uint16_t kControlwordEnableOperation = 0x000F;
constexpr std::uint16_t kControlwordFaultReset = 0x0080;

enum class DriveState {
  EnablingCSP,
  RunningCSP,
  Fault,
};

enum class State {
  NotReadyToSwitchOn,
  SwitchOnDisabled,
  ReadyToSwitchOn,
  SwitchedOn,
  OperationEnabled,
  QuickStopActive,
  FaultReactionActive,
  Fault,
  Unknown,
};

State DecodeStatusword(std::uint16_t statusword);
bool IsOperationEnabled(std::uint16_t statusword);
bool IsOperationEnabledCSP(const Clearpath::PDO::TxPDOs &feedback);

// Advances the CiA 402 state machine toward Operation Enabled.
// Returns true once the drive is Operation Enabled.
bool ReachOp(const Clearpath::PDO::TxPDOs &feedback,
             Clearpath::Command *command);

// Sets CSP mode and advances the drive to Operation Enabled.
// Seeds target_position from actual_position while enabling to avoid a jump.
// Returns true once Operation Enabled and mode display == CSP.
bool UpdateCSPEnableState(const Clearpath::PDO::TxPDOs &feedback,
                          Clearpath::Command *command);

} // namespace CiA402
