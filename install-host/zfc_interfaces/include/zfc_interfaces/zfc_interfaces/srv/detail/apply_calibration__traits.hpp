// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from zfc_interfaces:srv/ApplyCalibration.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__SRV__DETAIL__APPLY_CALIBRATION__TRAITS_HPP_
#define ZFC_INTERFACES__SRV__DETAIL__APPLY_CALIBRATION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "zfc_interfaces/srv/detail/apply_calibration__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace zfc_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ApplyCalibration_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: result_file
  {
    out << "result_file: ";
    rosidl_generator_traits::value_to_yaml(msg.result_file, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ApplyCalibration_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: result_file
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result_file: ";
    rosidl_generator_traits::value_to_yaml(msg.result_file, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ApplyCalibration_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace zfc_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use zfc_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const zfc_interfaces::srv::ApplyCalibration_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::srv::ApplyCalibration_Request & msg)
{
  return zfc_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::srv::ApplyCalibration_Request>()
{
  return "zfc_interfaces::srv::ApplyCalibration_Request";
}

template<>
inline const char * name<zfc_interfaces::srv::ApplyCalibration_Request>()
{
  return "zfc_interfaces/srv/ApplyCalibration_Request";
}

template<>
struct has_fixed_size<zfc_interfaces::srv::ApplyCalibration_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<zfc_interfaces::srv::ApplyCalibration_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<zfc_interfaces::srv::ApplyCalibration_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'fit'
#include "zfc_interfaces/msg/detail/calibration_result__traits.hpp"

namespace zfc_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ApplyCalibration_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: fit
  {
    out << "fit: ";
    to_flow_style_yaml(msg.fit, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ApplyCalibration_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ApplyCalibration_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace zfc_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use zfc_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const zfc_interfaces::srv::ApplyCalibration_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::srv::ApplyCalibration_Response & msg)
{
  return zfc_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::srv::ApplyCalibration_Response>()
{
  return "zfc_interfaces::srv::ApplyCalibration_Response";
}

template<>
inline const char * name<zfc_interfaces::srv::ApplyCalibration_Response>()
{
  return "zfc_interfaces/srv/ApplyCalibration_Response";
}

template<>
struct has_fixed_size<zfc_interfaces::srv::ApplyCalibration_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<zfc_interfaces::srv::ApplyCalibration_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<zfc_interfaces::srv::ApplyCalibration_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<zfc_interfaces::srv::ApplyCalibration>()
{
  return "zfc_interfaces::srv::ApplyCalibration";
}

template<>
inline const char * name<zfc_interfaces::srv::ApplyCalibration>()
{
  return "zfc_interfaces/srv/ApplyCalibration";
}

template<>
struct has_fixed_size<zfc_interfaces::srv::ApplyCalibration>
  : std::integral_constant<
    bool,
    has_fixed_size<zfc_interfaces::srv::ApplyCalibration_Request>::value &&
    has_fixed_size<zfc_interfaces::srv::ApplyCalibration_Response>::value
  >
{
};

template<>
struct has_bounded_size<zfc_interfaces::srv::ApplyCalibration>
  : std::integral_constant<
    bool,
    has_bounded_size<zfc_interfaces::srv::ApplyCalibration_Request>::value &&
    has_bounded_size<zfc_interfaces::srv::ApplyCalibration_Response>::value
  >
{
};

template<>
struct is_service<zfc_interfaces::srv::ApplyCalibration>
  : std::true_type
{
};

template<>
struct is_service_request<zfc_interfaces::srv::ApplyCalibration_Request>
  : std::true_type
{
};

template<>
struct is_service_response<zfc_interfaces::srv::ApplyCalibration_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ZFC_INTERFACES__SRV__DETAIL__APPLY_CALIBRATION__TRAITS_HPP_
