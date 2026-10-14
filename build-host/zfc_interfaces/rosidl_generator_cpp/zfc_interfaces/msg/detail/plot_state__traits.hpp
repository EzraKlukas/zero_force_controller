// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from zfc_interfaces:msg/PlotState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__PLOT_STATE__TRAITS_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__PLOT_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "zfc_interfaces/msg/detail/plot_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'state'
#include "zfc_interfaces/msg/detail/controller_state__traits.hpp"

namespace zfc_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const PlotState & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    to_flow_style_yaml(msg.state, out);
    out << ", ";
  }

  // member: inertial_compensation_n
  {
    out << "inertial_compensation_n: ";
    rosidl_generator_traits::value_to_yaml(msg.inertial_compensation_n, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PlotState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state:\n";
    to_block_style_yaml(msg.state, out, indentation + 2);
  }

  // member: inertial_compensation_n
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "inertial_compensation_n: ";
    rosidl_generator_traits::value_to_yaml(msg.inertial_compensation_n, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PlotState & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace zfc_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use zfc_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const zfc_interfaces::msg::PlotState & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::msg::PlotState & msg)
{
  return zfc_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::msg::PlotState>()
{
  return "zfc_interfaces::msg::PlotState";
}

template<>
inline const char * name<zfc_interfaces::msg::PlotState>()
{
  return "zfc_interfaces/msg/PlotState";
}

template<>
struct has_fixed_size<zfc_interfaces::msg::PlotState>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value && has_fixed_size<zfc_interfaces::msg::ControllerState>::value> {};

template<>
struct has_bounded_size<zfc_interfaces::msg::PlotState>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value && has_bounded_size<zfc_interfaces::msg::ControllerState>::value> {};

template<>
struct is_message<zfc_interfaces::msg::PlotState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ZFC_INTERFACES__MSG__DETAIL__PLOT_STATE__TRAITS_HPP_
