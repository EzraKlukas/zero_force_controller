// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from zfc_interfaces:msg/AnalysisState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__TRAITS_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "zfc_interfaces/msg/detail/analysis_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'fit'
#include "zfc_interfaces/msg/detail/calibration_result__traits.hpp"

namespace zfc_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const AnalysisState & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: trial_id
  {
    out << "trial_id: ";
    rosidl_generator_traits::value_to_yaml(msg.trial_id, out);
    out << ", ";
  }

  // member: stage
  {
    out << "stage: ";
    rosidl_generator_traits::value_to_yaml(msg.stage, out);
    out << ", ";
  }

  // member: stage_code
  {
    out << "stage_code: ";
    rosidl_generator_traits::value_to_yaml(msg.stage_code, out);
    out << ", ";
  }

  // member: progress
  {
    out << "progress: ";
    rosidl_generator_traits::value_to_yaml(msg.progress, out);
    out << ", ";
  }

  // member: recorded_samples
  {
    out << "recorded_samples: ";
    rosidl_generator_traits::value_to_yaml(msg.recorded_samples, out);
    out << ", ";
  }

  // member: dropped_samples
  {
    out << "dropped_samples: ";
    rosidl_generator_traits::value_to_yaml(msg.dropped_samples, out);
    out << ", ";
  }

  // member: final_sequence
  {
    out << "final_sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.final_sequence, out);
    out << ", ";
  }

  // member: stop_acknowledged
  {
    out << "stop_acknowledged: ";
    rosidl_generator_traits::value_to_yaml(msg.stop_acknowledged, out);
    out << ", ";
  }

  // member: detail
  {
    out << "detail: ";
    rosidl_generator_traits::value_to_yaml(msg.detail, out);
    out << ", ";
  }

  // member: fit
  {
    out << "fit: ";
    to_flow_style_yaml(msg.fit, out);
    out << ", ";
  }

  // member: backend
  {
    out << "backend: ";
    rosidl_generator_traits::value_to_yaml(msg.backend, out);
    out << ", ";
  }

  // member: operation_pending
  {
    out << "operation_pending: ";
    rosidl_generator_traits::value_to_yaml(msg.operation_pending, out);
    out << ", ";
  }

  // member: trial_directory
  {
    out << "trial_directory: ";
    rosidl_generator_traits::value_to_yaml(msg.trial_directory, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AnalysisState & msg,
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

  // member: trial_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "trial_id: ";
    rosidl_generator_traits::value_to_yaml(msg.trial_id, out);
    out << "\n";
  }

  // member: stage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stage: ";
    rosidl_generator_traits::value_to_yaml(msg.stage, out);
    out << "\n";
  }

  // member: stage_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stage_code: ";
    rosidl_generator_traits::value_to_yaml(msg.stage_code, out);
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

  // member: recorded_samples
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "recorded_samples: ";
    rosidl_generator_traits::value_to_yaml(msg.recorded_samples, out);
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

  // member: final_sequence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "final_sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.final_sequence, out);
    out << "\n";
  }

  // member: stop_acknowledged
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stop_acknowledged: ";
    rosidl_generator_traits::value_to_yaml(msg.stop_acknowledged, out);
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

  // member: fit
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fit:\n";
    to_block_style_yaml(msg.fit, out, indentation + 2);
  }

  // member: backend
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "backend: ";
    rosidl_generator_traits::value_to_yaml(msg.backend, out);
    out << "\n";
  }

  // member: operation_pending
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "operation_pending: ";
    rosidl_generator_traits::value_to_yaml(msg.operation_pending, out);
    out << "\n";
  }

  // member: trial_directory
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "trial_directory: ";
    rosidl_generator_traits::value_to_yaml(msg.trial_directory, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AnalysisState & msg, bool use_flow_style = false)
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
  const zfc_interfaces::msg::AnalysisState & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::msg::AnalysisState & msg)
{
  return zfc_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::msg::AnalysisState>()
{
  return "zfc_interfaces::msg::AnalysisState";
}

template<>
inline const char * name<zfc_interfaces::msg::AnalysisState>()
{
  return "zfc_interfaces/msg/AnalysisState";
}

template<>
struct has_fixed_size<zfc_interfaces::msg::AnalysisState>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<zfc_interfaces::msg::AnalysisState>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<zfc_interfaces::msg::AnalysisState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__TRAITS_HPP_
