// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from zfc_interfaces:srv/OperatorCommand.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__TRAITS_HPP_
#define ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "zfc_interfaces/srv/detail/operator_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace zfc_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const OperatorCommand_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: command
  {
    out << "command: ";
    rosidl_generator_traits::value_to_yaml(msg.command, out);
    out << ", ";
  }

  // member: external_contact_clear
  {
    out << "external_contact_clear: ";
    rosidl_generator_traits::value_to_yaml(msg.external_contact_clear, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const OperatorCommand_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "command: ";
    rosidl_generator_traits::value_to_yaml(msg.command, out);
    out << "\n";
  }

  // member: external_contact_clear
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "external_contact_clear: ";
    rosidl_generator_traits::value_to_yaml(msg.external_contact_clear, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const OperatorCommand_Request & msg, bool use_flow_style = false)
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
  const zfc_interfaces::srv::OperatorCommand_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::srv::OperatorCommand_Request & msg)
{
  return zfc_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::srv::OperatorCommand_Request>()
{
  return "zfc_interfaces::srv::OperatorCommand_Request";
}

template<>
inline const char * name<zfc_interfaces::srv::OperatorCommand_Request>()
{
  return "zfc_interfaces/srv/OperatorCommand_Request";
}

template<>
struct has_fixed_size<zfc_interfaces::srv::OperatorCommand_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<zfc_interfaces::srv::OperatorCommand_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<zfc_interfaces::srv::OperatorCommand_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace zfc_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const OperatorCommand_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: stop_acknowledged
  {
    out << "stop_acknowledged: ";
    rosidl_generator_traits::value_to_yaml(msg.stop_acknowledged, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const OperatorCommand_Response & msg,
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

  // member: stop_acknowledged
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stop_acknowledged: ";
    rosidl_generator_traits::value_to_yaml(msg.stop_acknowledged, out);
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const OperatorCommand_Response & msg, bool use_flow_style = false)
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
  const zfc_interfaces::srv::OperatorCommand_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::srv::OperatorCommand_Response & msg)
{
  return zfc_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::srv::OperatorCommand_Response>()
{
  return "zfc_interfaces::srv::OperatorCommand_Response";
}

template<>
inline const char * name<zfc_interfaces::srv::OperatorCommand_Response>()
{
  return "zfc_interfaces/srv/OperatorCommand_Response";
}

template<>
struct has_fixed_size<zfc_interfaces::srv::OperatorCommand_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<zfc_interfaces::srv::OperatorCommand_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<zfc_interfaces::srv::OperatorCommand_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<zfc_interfaces::srv::OperatorCommand>()
{
  return "zfc_interfaces::srv::OperatorCommand";
}

template<>
inline const char * name<zfc_interfaces::srv::OperatorCommand>()
{
  return "zfc_interfaces/srv/OperatorCommand";
}

template<>
struct has_fixed_size<zfc_interfaces::srv::OperatorCommand>
  : std::integral_constant<
    bool,
    has_fixed_size<zfc_interfaces::srv::OperatorCommand_Request>::value &&
    has_fixed_size<zfc_interfaces::srv::OperatorCommand_Response>::value
  >
{
};

template<>
struct has_bounded_size<zfc_interfaces::srv::OperatorCommand>
  : std::integral_constant<
    bool,
    has_bounded_size<zfc_interfaces::srv::OperatorCommand_Request>::value &&
    has_bounded_size<zfc_interfaces::srv::OperatorCommand_Response>::value
  >
{
};

template<>
struct is_service<zfc_interfaces::srv::OperatorCommand>
  : std::true_type
{
};

template<>
struct is_service_request<zfc_interfaces::srv::OperatorCommand_Request>
  : std::true_type
{
};

template<>
struct is_service_response<zfc_interfaces::srv::OperatorCommand_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__TRAITS_HPP_
