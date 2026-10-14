// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from zfc_interfaces:msg/ControllerState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__CONTROLLER_STATE__TRAITS_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__CONTROLLER_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "zfc_interfaces/msg/detail/controller_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace zfc_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ControllerState & msg,
  std::ostream & out)
{
  out << "{";
  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: trial_id
  {
    out << "trial_id: ";
    rosidl_generator_traits::value_to_yaml(msg.trial_id, out);
    out << ", ";
  }

  // member: sequence
  {
    out << "sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.sequence, out);
    out << ", ";
  }

  // member: phase
  {
    out << "phase: ";
    rosidl_generator_traits::value_to_yaml(msg.phase, out);
    out << ", ";
  }

  // member: fault_code
  {
    out << "fault_code: ";
    rosidl_generator_traits::value_to_yaml(msg.fault_code, out);
    out << ", ";
  }

  // member: valid
  {
    out << "valid: ";
    rosidl_generator_traits::value_to_yaml(msg.valid, out);
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

  // member: reference_position_m
  {
    out << "reference_position_m: ";
    rosidl_generator_traits::value_to_yaml(msg.reference_position_m, out);
    out << ", ";
  }

  // member: reference_velocity_mps
  {
    out << "reference_velocity_mps: ";
    rosidl_generator_traits::value_to_yaml(msg.reference_velocity_mps, out);
    out << ", ";
  }

  // member: reference_acceleration_mps2
  {
    out << "reference_acceleration_mps2: ";
    rosidl_generator_traits::value_to_yaml(msg.reference_acceleration_mps2, out);
    out << ", ";
  }

  // member: baseline_force_n
  {
    out << "baseline_force_n: ";
    rosidl_generator_traits::value_to_yaml(msg.baseline_force_n, out);
    out << ", ";
  }

  // member: noise_rms_n
  {
    out << "noise_rms_n: ";
    rosidl_generator_traits::value_to_yaml(msg.noise_rms_n, out);
    out << ", ";
  }

  // member: residual_force_n
  {
    out << "residual_force_n: ";
    rosidl_generator_traits::value_to_yaml(msg.residual_force_n, out);
    out << ", ";
  }

  // member: progress
  {
    out << "progress: ";
    rosidl_generator_traits::value_to_yaml(msg.progress, out);
    out << ", ";
  }

  // member: excessive_periods
  {
    out << "excessive_periods: ";
    rosidl_generator_traits::value_to_yaml(msg.excessive_periods, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ControllerState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }

  // member: trial_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "trial_id: ";
    rosidl_generator_traits::value_to_yaml(msg.trial_id, out);
    out << "\n";
  }

  // member: sequence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.sequence, out);
    out << "\n";
  }

  // member: phase
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "phase: ";
    rosidl_generator_traits::value_to_yaml(msg.phase, out);
    out << "\n";
  }

  // member: fault_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fault_code: ";
    rosidl_generator_traits::value_to_yaml(msg.fault_code, out);
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

  // member: reference_position_m
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reference_position_m: ";
    rosidl_generator_traits::value_to_yaml(msg.reference_position_m, out);
    out << "\n";
  }

  // member: reference_velocity_mps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reference_velocity_mps: ";
    rosidl_generator_traits::value_to_yaml(msg.reference_velocity_mps, out);
    out << "\n";
  }

  // member: reference_acceleration_mps2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reference_acceleration_mps2: ";
    rosidl_generator_traits::value_to_yaml(msg.reference_acceleration_mps2, out);
    out << "\n";
  }

  // member: baseline_force_n
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "baseline_force_n: ";
    rosidl_generator_traits::value_to_yaml(msg.baseline_force_n, out);
    out << "\n";
  }

  // member: noise_rms_n
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "noise_rms_n: ";
    rosidl_generator_traits::value_to_yaml(msg.noise_rms_n, out);
    out << "\n";
  }

  // member: residual_force_n
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "residual_force_n: ";
    rosidl_generator_traits::value_to_yaml(msg.residual_force_n, out);
    out << "\n";
  }

  // member: progress
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "progress: ";
    rosidl_generator_traits::value_to_yaml(msg.progress, out);
    out << "\n";
  }

  // member: excessive_periods
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "excessive_periods: ";
    rosidl_generator_traits::value_to_yaml(msg.excessive_periods, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ControllerState & msg, bool use_flow_style = false)
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
  const zfc_interfaces::msg::ControllerState & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::msg::ControllerState & msg)
{
  return zfc_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::msg::ControllerState>()
{
  return "zfc_interfaces::msg::ControllerState";
}

template<>
inline const char * name<zfc_interfaces::msg::ControllerState>()
{
  return "zfc_interfaces/msg/ControllerState";
}

template<>
struct has_fixed_size<zfc_interfaces::msg::ControllerState>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<zfc_interfaces::msg::ControllerState>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<zfc_interfaces::msg::ControllerState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ZFC_INTERFACES__MSG__DETAIL__CONTROLLER_STATE__TRAITS_HPP_
