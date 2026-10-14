// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from zfc_interfaces:msg/MeasuredState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__MEASURED_STATE__BUILDER_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__MEASURED_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "zfc_interfaces/msg/detail/measured_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace zfc_interfaces
{

namespace msg
{

namespace builder
{

class Init_MeasuredState_detail
{
public:
  explicit Init_MeasuredState_detail(::zfc_interfaces::msg::MeasuredState & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::msg::MeasuredState detail(::zfc_interfaces::msg::MeasuredState::_detail_type arg)
  {
    msg_.detail = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::msg::MeasuredState msg_;
};

class Init_MeasuredState_valid
{
public:
  explicit Init_MeasuredState_valid(::zfc_interfaces::msg::MeasuredState & msg)
  : msg_(msg)
  {}
  Init_MeasuredState_detail valid(::zfc_interfaces::msg::MeasuredState::_valid_type arg)
  {
    msg_.valid = std::move(arg);
    return Init_MeasuredState_detail(msg_);
  }

private:
  ::zfc_interfaces::msg::MeasuredState msg_;
};

class Init_MeasuredState_force_fresh
{
public:
  explicit Init_MeasuredState_force_fresh(::zfc_interfaces::msg::MeasuredState & msg)
  : msg_(msg)
  {}
  Init_MeasuredState_valid force_fresh(::zfc_interfaces::msg::MeasuredState::_force_fresh_type arg)
  {
    msg_.force_fresh = std::move(arg);
    return Init_MeasuredState_valid(msg_);
  }

private:
  ::zfc_interfaces::msg::MeasuredState msg_;
};

class Init_MeasuredState_joint_fresh
{
public:
  explicit Init_MeasuredState_joint_fresh(::zfc_interfaces::msg::MeasuredState & msg)
  : msg_(msg)
  {}
  Init_MeasuredState_force_fresh joint_fresh(::zfc_interfaces::msg::MeasuredState::_joint_fresh_type arg)
  {
    msg_.joint_fresh = std::move(arg);
    return Init_MeasuredState_force_fresh(msg_);
  }

private:
  ::zfc_interfaces::msg::MeasuredState msg_;
};

class Init_MeasuredState_force_n
{
public:
  explicit Init_MeasuredState_force_n(::zfc_interfaces::msg::MeasuredState & msg)
  : msg_(msg)
  {}
  Init_MeasuredState_joint_fresh force_n(::zfc_interfaces::msg::MeasuredState::_force_n_type arg)
  {
    msg_.force_n = std::move(arg);
    return Init_MeasuredState_joint_fresh(msg_);
  }

private:
  ::zfc_interfaces::msg::MeasuredState msg_;
};

class Init_MeasuredState_velocity_mps
{
public:
  explicit Init_MeasuredState_velocity_mps(::zfc_interfaces::msg::MeasuredState & msg)
  : msg_(msg)
  {}
  Init_MeasuredState_force_n velocity_mps(::zfc_interfaces::msg::MeasuredState::_velocity_mps_type arg)
  {
    msg_.velocity_mps = std::move(arg);
    return Init_MeasuredState_force_n(msg_);
  }

private:
  ::zfc_interfaces::msg::MeasuredState msg_;
};

class Init_MeasuredState_position_m
{
public:
  explicit Init_MeasuredState_position_m(::zfc_interfaces::msg::MeasuredState & msg)
  : msg_(msg)
  {}
  Init_MeasuredState_velocity_mps position_m(::zfc_interfaces::msg::MeasuredState::_position_m_type arg)
  {
    msg_.position_m = std::move(arg);
    return Init_MeasuredState_velocity_mps(msg_);
  }

private:
  ::zfc_interfaces::msg::MeasuredState msg_;
};

class Init_MeasuredState_force_stamp
{
public:
  explicit Init_MeasuredState_force_stamp(::zfc_interfaces::msg::MeasuredState & msg)
  : msg_(msg)
  {}
  Init_MeasuredState_position_m force_stamp(::zfc_interfaces::msg::MeasuredState::_force_stamp_type arg)
  {
    msg_.force_stamp = std::move(arg);
    return Init_MeasuredState_position_m(msg_);
  }

private:
  ::zfc_interfaces::msg::MeasuredState msg_;
};

class Init_MeasuredState_header
{
public:
  Init_MeasuredState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MeasuredState_force_stamp header(::zfc_interfaces::msg::MeasuredState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_MeasuredState_force_stamp(msg_);
  }

private:
  ::zfc_interfaces::msg::MeasuredState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::msg::MeasuredState>()
{
  return zfc_interfaces::msg::builder::Init_MeasuredState_header();
}

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__MSG__DETAIL__MEASURED_STATE__BUILDER_HPP_
