#include "cia402.hpp"

namespace CiA402 {

State DecodeStatusword(std::uint16_t sw) {
  if ((sw & 0x004F) == 0x0008) {
    return State::Fault;
  }
  if ((sw & 0x004F) == 0x000F) {
    return State::FaultReactionActive;
  }
  if ((sw & 0x006F) == 0x0007) {
    return State::QuickStopActive;
  }
  if ((sw & 0x006F) == 0x0027) {
    return State::OperationEnabled;
  }
  if ((sw & 0x006F) == 0x0023) {
    return State::SwitchedOn;
  }
  if ((sw & 0x006F) == 0x0021) {
    return State::ReadyToSwitchOn;
  }
  if ((sw & 0x004F) == 0x0040) {
    return State::SwitchOnDisabled;
  }
  if ((sw & 0x004F) == 0x0000) {
    return State::NotReadyToSwitchOn;
  }
  return State::Unknown;
}

bool IsOperationEnabled(std::uint16_t statusword) {
  return (statusword & 0x006F) == 0x0027;
}

bool IsOperationEnabledCSP(const Clearpath::PDO::TxPDOs &feedback) {
  return IsOperationEnabled(feedback.statusword) &&
         feedback.mode_display == kModeCsp;
}

bool ReachOp(const Clearpath::PDO::TxPDOs &feedback,
             Clearpath::Command *command) {
  switch (DecodeStatusword(feedback.statusword)) {
  case State::Fault:
    command->controlword = kControlwordFaultReset;
    return false;

  case State::SwitchOnDisabled:
    command->controlword = kControlwordShutdown;
    return false;

  case State::ReadyToSwitchOn:
    command->controlword = kControlwordSwitchOn;
    return false;

  case State::SwitchedOn:
    command->controlword = kControlwordEnableOperation;
    return false;

  case State::OperationEnabled:
    command->controlword = kControlwordEnableOperation;
    return true;

  case State::QuickStopActive:
    command->controlword = kControlwordEnableOperation;
    return false;

  case State::FaultReactionActive:
  case State::NotReadyToSwitchOn:
  case State::Unknown:
  default:
    command->controlword = kControlwordShutdown;
    return false;
  }
}

bool UpdateCSPEnableState(const Clearpath::PDO::TxPDOs &feedback,
                          Clearpath::Command *command) {
  command->mode_op = kModeCsp;
  command->target_velocity = 0;
  command->target_torque = 0;

  const bool op_enabled = ReachOp(feedback, command);

  if (!op_enabled || feedback.mode_display != kModeCsp) {
    command->target_position = feedback.actual_position;
  }

  return op_enabled && feedback.mode_display == kModeCsp;
}

} // namespace CiA402
