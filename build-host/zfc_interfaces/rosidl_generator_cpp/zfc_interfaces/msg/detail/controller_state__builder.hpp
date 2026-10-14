// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from zfc_interfaces:msg/ControllerState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__CONTROLLER_STATE__BUILDER_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__CONTROLLER_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "zfc_interfaces/msg/detail/controller_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace zfc_interfaces
{

namespace msg
{

namespace builder
{

class Init_ControllerState_excessive_periods
{
public:
  explicit Init_ControllerState_excessive_periods(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::msg::ControllerState excessive_periods(::zfc_interfaces::msg::ControllerState::_excessive_periods_type arg)
  {
    msg_.excessive_periods = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_progress
{
public:
  explicit Init_ControllerState_progress(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_excessive_periods progress(::zfc_interfaces::msg::ControllerState::_progress_type arg)
  {
    msg_.progress = std::move(arg);
    return Init_ControllerState_excessive_periods(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_residual_force_n
{
public:
  explicit Init_ControllerState_residual_force_n(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_progress residual_force_n(::zfc_interfaces::msg::ControllerState::_residual_force_n_type arg)
  {
    msg_.residual_force_n = std::move(arg);
    return Init_ControllerState_progress(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_noise_rms_n
{
public:
  explicit Init_ControllerState_noise_rms_n(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_residual_force_n noise_rms_n(::zfc_interfaces::msg::ControllerState::_noise_rms_n_type arg)
  {
    msg_.noise_rms_n = std::move(arg);
    return Init_ControllerState_residual_force_n(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_baseline_force_n
{
public:
  explicit Init_ControllerState_baseline_force_n(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_noise_rms_n baseline_force_n(::zfc_interfaces::msg::ControllerState::_baseline_force_n_type arg)
  {
    msg_.baseline_force_n = std::move(arg);
    return Init_ControllerState_noise_rms_n(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_reference_acceleration_mps2
{
public:
  explicit Init_ControllerState_reference_acceleration_mps2(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_baseline_force_n reference_acceleration_mps2(::zfc_interfaces::msg::ControllerState::_reference_acceleration_mps2_type arg)
  {
    msg_.reference_acceleration_mps2 = std::move(arg);
    return Init_ControllerState_baseline_force_n(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_reference_velocity_mps
{
public:
  explicit Init_ControllerState_reference_velocity_mps(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_reference_acceleration_mps2 reference_velocity_mps(::zfc_interfaces::msg::ControllerState::_reference_velocity_mps_type arg)
  {
    msg_.reference_velocity_mps = std::move(arg);
    return Init_ControllerState_reference_acceleration_mps2(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_reference_position_m
{
public:
  explicit Init_ControllerState_reference_position_m(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_reference_velocity_mps reference_position_m(::zfc_interfaces::msg::ControllerState::_reference_position_m_type arg)
  {
    msg_.reference_position_m = std::move(arg);
    return Init_ControllerState_reference_velocity_mps(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_force_n
{
public:
  explicit Init_ControllerState_force_n(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_reference_position_m force_n(::zfc_interfaces::msg::ControllerState::_force_n_type arg)
  {
    msg_.force_n = std::move(arg);
    return Init_ControllerState_reference_position_m(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_velocity_mps
{
public:
  explicit Init_ControllerState_velocity_mps(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_force_n velocity_mps(::zfc_interfaces::msg::ControllerState::_velocity_mps_type arg)
  {
    msg_.velocity_mps = std::move(arg);
    return Init_ControllerState_force_n(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_position_m
{
public:
  explicit Init_ControllerState_position_m(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_velocity_mps position_m(::zfc_interfaces::msg::ControllerState::_position_m_type arg)
  {
    msg_.position_m = std::move(arg);
    return Init_ControllerState_velocity_mps(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_valid
{
public:
  explicit Init_ControllerState_valid(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_position_m valid(::zfc_interfaces::msg::ControllerState::_valid_type arg)
  {
    msg_.valid = std::move(arg);
    return Init_ControllerState_position_m(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_fault_code
{
public:
  explicit Init_ControllerState_fault_code(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_valid fault_code(::zfc_interfaces::msg::ControllerState::_fault_code_type arg)
  {
    msg_.fault_code = std::move(arg);
    return Init_ControllerState_valid(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_phase
{
public:
  explicit Init_ControllerState_phase(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_fault_code phase(::zfc_interfaces::msg::ControllerState::_phase_type arg)
  {
    msg_.phase = std::move(arg);
    return Init_ControllerState_fault_code(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_sequence
{
public:
  explicit Init_ControllerState_sequence(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_phase sequence(::zfc_interfaces::msg::ControllerState::_sequence_type arg)
  {
    msg_.sequence = std::move(arg);
    return Init_ControllerState_phase(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_trial_id
{
public:
  explicit Init_ControllerState_trial_id(::zfc_interfaces::msg::ControllerState & msg)
  : msg_(msg)
  {}
  Init_ControllerState_sequence trial_id(::zfc_interfaces::msg::ControllerState::_trial_id_type arg)
  {
    msg_.trial_id = std::move(arg);
    return Init_ControllerState_sequence(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

class Init_ControllerState_stamp
{
public:
  Init_ControllerState_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ControllerState_trial_id stamp(::zfc_interfaces::msg::ControllerState::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_ControllerState_trial_id(msg_);
  }

private:
  ::zfc_interfaces::msg::ControllerState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::msg::ControllerState>()
{
  return zfc_interfaces::msg::builder::Init_ControllerState_stamp();
}

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__MSG__DETAIL__CONTROLLER_STATE__BUILDER_HPP_
