// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from zfc_interfaces:msg/PlotState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__PLOT_STATE__BUILDER_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__PLOT_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "zfc_interfaces/msg/detail/plot_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace zfc_interfaces
{

namespace msg
{

namespace builder
{

class Init_PlotState_inertial_compensation_n
{
public:
  explicit Init_PlotState_inertial_compensation_n(::zfc_interfaces::msg::PlotState & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::msg::PlotState inertial_compensation_n(::zfc_interfaces::msg::PlotState::_inertial_compensation_n_type arg)
  {
    msg_.inertial_compensation_n = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::msg::PlotState msg_;
};

class Init_PlotState_state
{
public:
  explicit Init_PlotState_state(::zfc_interfaces::msg::PlotState & msg)
  : msg_(msg)
  {}
  Init_PlotState_inertial_compensation_n state(::zfc_interfaces::msg::PlotState::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_PlotState_inertial_compensation_n(msg_);
  }

private:
  ::zfc_interfaces::msg::PlotState msg_;
};

class Init_PlotState_header
{
public:
  Init_PlotState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlotState_state header(::zfc_interfaces::msg::PlotState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_PlotState_state(msg_);
  }

private:
  ::zfc_interfaces::msg::PlotState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::msg::PlotState>()
{
  return zfc_interfaces::msg::builder::Init_PlotState_header();
}

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__MSG__DETAIL__PLOT_STATE__BUILDER_HPP_
