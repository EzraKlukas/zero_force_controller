// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from zfc_interfaces:msg/CalibrationResult.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__CALIBRATION_RESULT__TRAITS_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__CALIBRATION_RESULT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "zfc_interfaces/msg/detail/calibration_result__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace zfc_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const CalibrationResult & msg,
  std::ostream & out)
{
  out << "{";
  // member: valid
  {
    out << "valid: ";
    rosidl_generator_traits::value_to_yaml(msg.valid, out);
    out << ", ";
  }

  // member: reason
  {
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
    out << ", ";
  }

  // member: inertial_force_coefficient_kg
  {
    out << "inertial_force_coefficient_kg: ";
    rosidl_generator_traits::value_to_yaml(msg.inertial_force_coefficient_kg, out);
    out << ", ";
  }

  // member: intercept_n
  {
    out << "intercept_n: ";
    rosidl_generator_traits::value_to_yaml(msg.intercept_n, out);
    out << ", ";
  }

  // member: r_squared
  {
    out << "r_squared: ";
    rosidl_generator_traits::value_to_yaml(msg.r_squared, out);
    out << ", ";
  }

  // member: residual_rms_n
  {
    out << "residual_rms_n: ";
    rosidl_generator_traits::value_to_yaml(msg.residual_rms_n, out);
    out << ", ";
  }

  // member: uncertainty_kg
  {
    out << "uncertainty_kg: ";
    rosidl_generator_traits::value_to_yaml(msg.uncertainty_kg, out);
    out << ", ";
  }

  // member: sample_count
  {
    out << "sample_count: ";
    rosidl_generator_traits::value_to_yaml(msg.sample_count, out);
    out << ", ";
  }

  // member: plateau_count
  {
    out << "plateau_count: ";
    rosidl_generator_traits::value_to_yaml(msg.plateau_count, out);
    out << ", ";
  }

  // member: positive_slope_kg
  {
    out << "positive_slope_kg: ";
    rosidl_generator_traits::value_to_yaml(msg.positive_slope_kg, out);
    out << ", ";
  }

  // member: negative_slope_kg
  {
    out << "negative_slope_kg: ";
    rosidl_generator_traits::value_to_yaml(msg.negative_slope_kg, out);
    out << ", ";
  }

  // member: tracking_rms_m
  {
    out << "tracking_rms_m: ";
    rosidl_generator_traits::value_to_yaml(msg.tracking_rms_m, out);
    out << ", ";
  }

  // member: acceleration_source
  {
    out << "acceleration_source: ";
    rosidl_generator_traits::value_to_yaml(msg.acceleration_source, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CalibrationResult & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "valid: ";
    rosidl_generator_traits::value_to_yaml(msg.valid, out);
    out << "\n";
  }

  // member: reason
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
    out << "\n";
  }

  // member: inertial_force_coefficient_kg
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "inertial_force_coefficient_kg: ";
    rosidl_generator_traits::value_to_yaml(msg.inertial_force_coefficient_kg, out);
    out << "\n";
  }

  // member: intercept_n
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "intercept_n: ";
    rosidl_generator_traits::value_to_yaml(msg.intercept_n, out);
    out << "\n";
  }

  // member: r_squared
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "r_squared: ";
    rosidl_generator_traits::value_to_yaml(msg.r_squared, out);
    out << "\n";
  }

  // member: residual_rms_n
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "residual_rms_n: ";
    rosidl_generator_traits::value_to_yaml(msg.residual_rms_n, out);
    out << "\n";
  }

  // member: uncertainty_kg
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "uncertainty_kg: ";
    rosidl_generator_traits::value_to_yaml(msg.uncertainty_kg, out);
    out << "\n";
  }

  // member: sample_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sample_count: ";
    rosidl_generator_traits::value_to_yaml(msg.sample_count, out);
    out << "\n";
  }

  // member: plateau_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "plateau_count: ";
    rosidl_generator_traits::value_to_yaml(msg.plateau_count, out);
    out << "\n";
  }

  // member: positive_slope_kg
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "positive_slope_kg: ";
    rosidl_generator_traits::value_to_yaml(msg.positive_slope_kg, out);
    out << "\n";
  }

  // member: negative_slope_kg
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "negative_slope_kg: ";
    rosidl_generator_traits::value_to_yaml(msg.negative_slope_kg, out);
    out << "\n";
  }

  // member: tracking_rms_m
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tracking_rms_m: ";
    rosidl_generator_traits::value_to_yaml(msg.tracking_rms_m, out);
    out << "\n";
  }

  // member: acceleration_source
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "acceleration_source: ";
    rosidl_generator_traits::value_to_yaml(msg.acceleration_source, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CalibrationResult & msg, bool use_flow_style = false)
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
  const zfc_interfaces::msg::CalibrationResult & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::msg::CalibrationResult & msg)
{
  return zfc_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::msg::CalibrationResult>()
{
  return "zfc_interfaces::msg::CalibrationResult";
}

template<>
inline const char * name<zfc_interfaces::msg::CalibrationResult>()
{
  return "zfc_interfaces/msg/CalibrationResult";
}

template<>
struct has_fixed_size<zfc_interfaces::msg::CalibrationResult>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<zfc_interfaces::msg::CalibrationResult>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<zfc_interfaces::msg::CalibrationResult>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ZFC_INTERFACES__MSG__DETAIL__CALIBRATION_RESULT__TRAITS_HPP_
