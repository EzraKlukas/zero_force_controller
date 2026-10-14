// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from zfc_interfaces:msg/MeasuredState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__MEASURED_STATE__TRAITS_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__MEASURED_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "zfc_interfaces/msg/detail/measured_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'force_stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace zfc_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const MeasuredState & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: force_stamp
  {
    out << "force_stamp: ";
    to_flow_style_yaml(msg.force_stamp, out);
    out << ", ";
  }

  // member: position_m
  {
    out << "position_m: ";
    rosidl_generator_traits::value_to_yaml(msg.position_m, out);
    out << ", ";
  }

  // member: velocity_mps
  {
    out << "velocity_mps: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity_mps, out);
    out << ", ";
  }

  // member: force_n
  {
    out << "force_n: ";
    rosidl_generator_traits::value_to_yaml(msg.force_n, out);
    out << ", ";
  }

  // member: joint_fresh
  {
    out << "joint_fresh: ";
    rosidl_generator_traits::value_to_yaml(msg.joint_fresh, out);
    out << ", ";
  }

  // member: force_fresh
  {
    out << "force_fresh: ";
    rosidl_generator_traits::value_to_yaml(msg.force_fresh, out);
    out << ", ";
  }

  // member: valid
  {
    out << "valid: ";
    rosidl_generator_traits::value_to_yaml(msg.valid, out);
    out << ", ";
  }

  // member: detail
  {
    out << "detail: ";
    rosidl_generator_traits::value_to_yaml(msg.detail, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MeasuredState & msg,
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

  // member: force_stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "force_stamp:\n";
    to_block_style_yaml(msg.force_stamp, out, indentation + 2);
  }

  // member: position_m
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position_m: ";
    rosidl_generator_traits::value_to_yaml(msg.position_m, out);
    out << "\n";
  }

  // member: velocity_mps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "velocity_mps: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity_mps, out);
    out << "\n";
  }

  // member: force_n
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "force_n: ";
    rosidl_generator_traits::value_to_yaml(msg.force_n, out);
    out << "\n";
  }

  // member: joint_fresh
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "joint_fresh: ";
    rosidl_generator_traits::value_to_yaml(msg.joint_fresh, out);
    out << "\n";
  }

  // member: force_fresh
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "force_fresh: ";
    rosidl_generator_traits::value_to_yaml(msg.force_fresh, out);
    out << "\n";
  }

  // member: valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "valid: ";
    rosidl_generator_traits::value_to_yaml(msg.valid, out);
    out << "\n";
  }

  // member: detail
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "detail: ";
    rosidl_generator_traits::value_to_yaml(msg.detail, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MeasuredState & msg, bool use_flow_style = false)
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
  const zfc_interfaces::msg::MeasuredState & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::msg::MeasuredState & msg)
{
  return zfc_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::msg::MeasuredState>()
{
  return "zfc_interfaces::msg::MeasuredState";
}

template<>
inline const char * name<zfc_interfaces::msg::MeasuredState>()
{
  return "zfc_interfaces/msg/MeasuredState";
}

template<>
struct has_fixed_size<zfc_interfaces::msg::MeasuredState>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<zfc_interfaces::msg::MeasuredState>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<zfc_interfaces::msg::MeasuredState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ZFC_INTERFACES__MSG__DETAIL__MEASURED_STATE__TRAITS_HPP_
