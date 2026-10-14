// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from zfc_interfaces:msg/TrialStatus.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__TRIAL_STATUS__TRAITS_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__TRIAL_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "zfc_interfaces/msg/detail/trial_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace zfc_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const TrialStatus & msg,
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

  // member: final_sequence
  {
    out << "final_sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.final_sequence, out);
    out << ", ";
  }

  // member: dropped_samples
  {
    out << "dropped_samples: ";
    rosidl_generator_traits::value_to_yaml(msg.dropped_samples, out);
    out << ", ";
  }

  // member: failed_publication_samples
  {
    out << "failed_publication_samples: ";
    rosidl_generator_traits::value_to_yaml(msg.failed_publication_samples, out);
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

  // member: completed
  {
    out << "completed: ";
    rosidl_generator_traits::value_to_yaml(msg.completed, out);
    out << ", ";
  }

  // member: successful
  {
    out << "successful: ";
    rosidl_generator_traits::value_to_yaml(msg.successful, out);
    out << ", ";
  }

  // member: capture_complete
  {
    out << "capture_complete: ";
    rosidl_generator_traits::value_to_yaml(msg.capture_complete, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TrialStatus & msg,
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

  // member: final_sequence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "final_sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.final_sequence, out);
    out << "\n";
  }

  // member: dropped_samples
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dropped_samples: ";
    rosidl_generator_traits::value_to_yaml(msg.dropped_samples, out);
    out << "\n";
  }

  // member: failed_publication_samples
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "failed_publication_samples: ";
    rosidl_generator_traits::value_to_yaml(msg.failed_publication_samples, out);
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

  // member: completed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "completed: ";
    rosidl_generator_traits::value_to_yaml(msg.completed, out);
    out << "\n";
  }

  // member: successful
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "successful: ";
    rosidl_generator_traits::value_to_yaml(msg.successful, out);
    out << "\n";
  }

  // member: capture_complete
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "capture_complete: ";
    rosidl_generator_traits::value_to_yaml(msg.capture_complete, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TrialStatus & msg, bool use_flow_style = false)
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
  const zfc_interfaces::msg::TrialStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::msg::TrialStatus & msg)
{
  return zfc_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::msg::TrialStatus>()
{
  return "zfc_interfaces::msg::TrialStatus";
}

template<>
inline const char * name<zfc_interfaces::msg::TrialStatus>()
{
  return "zfc_interfaces/msg/TrialStatus";
}

template<>
struct has_fixed_size<zfc_interfaces::msg::TrialStatus>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<zfc_interfaces::msg::TrialStatus>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<zfc_interfaces::msg::TrialStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ZFC_INTERFACES__MSG__DETAIL__TRIAL_STATUS__TRAITS_HPP_
