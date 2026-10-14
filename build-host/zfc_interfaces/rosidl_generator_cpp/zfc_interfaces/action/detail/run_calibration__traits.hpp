// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from zfc_interfaces:action/RunCalibration.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__TRAITS_HPP_
#define ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "zfc_interfaces/action/detail/run_calibration__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace zfc_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const RunCalibration_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: activate_zero_force_after
  {
    out << "activate_zero_force_after: ";
    rosidl_generator_traits::value_to_yaml(msg.activate_zero_force_after, out);
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
  const RunCalibration_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: activate_zero_force_after
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "activate_zero_force_after: ";
    rosidl_generator_traits::value_to_yaml(msg.activate_zero_force_after, out);
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

inline std::string to_yaml(const RunCalibration_Goal & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace zfc_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use zfc_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const zfc_interfaces::action::RunCalibration_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::action::RunCalibration_Goal & msg)
{
  return zfc_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::action::RunCalibration_Goal>()
{
  return "zfc_interfaces::action::RunCalibration_Goal";
}

template<>
inline const char * name<zfc_interfaces::action::RunCalibration_Goal>()
{
  return "zfc_interfaces/action/RunCalibration_Goal";
}

template<>
struct has_fixed_size<zfc_interfaces::action::RunCalibration_Goal>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<zfc_interfaces::action::RunCalibration_Goal>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<zfc_interfaces::action::RunCalibration_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'fit'
#include "zfc_interfaces/msg/detail/calibration_result__traits.hpp"

namespace zfc_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const RunCalibration_Result & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: trial_id
  {
    out << "trial_id: ";
    rosidl_generator_traits::value_to_yaml(msg.trial_id, out);
    out << ", ";
  }

  // member: trial_directory
  {
    out << "trial_directory: ";
    rosidl_generator_traits::value_to_yaml(msg.trial_directory, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: applied
  {
    out << "applied: ";
    rosidl_generator_traits::value_to_yaml(msg.applied, out);
    out << ", ";
  }

  // member: zero_force_active
  {
    out << "zero_force_active: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_force_active, out);
    out << ", ";
  }

  // member: stop_acknowledged
  {
    out << "stop_acknowledged: ";
    rosidl_generator_traits::value_to_yaml(msg.stop_acknowledged, out);
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
  const RunCalibration_Result & msg,
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

  // member: trial_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "trial_id: ";
    rosidl_generator_traits::value_to_yaml(msg.trial_id, out);
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

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }

  // member: applied
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "applied: ";
    rosidl_generator_traits::value_to_yaml(msg.applied, out);
    out << "\n";
  }

  // member: zero_force_active
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "zero_force_active: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_force_active, out);
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

  // member: fit
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fit:\n";
    to_block_style_yaml(msg.fit, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RunCalibration_Result & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace zfc_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use zfc_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const zfc_interfaces::action::RunCalibration_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::action::RunCalibration_Result & msg)
{
  return zfc_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::action::RunCalibration_Result>()
{
  return "zfc_interfaces::action::RunCalibration_Result";
}

template<>
inline const char * name<zfc_interfaces::action::RunCalibration_Result>()
{
  return "zfc_interfaces/action/RunCalibration_Result";
}

template<>
struct has_fixed_size<zfc_interfaces::action::RunCalibration_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<zfc_interfaces::action::RunCalibration_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<zfc_interfaces::action::RunCalibration_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'state'
#include "zfc_interfaces/msg/detail/analysis_state__traits.hpp"

namespace zfc_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const RunCalibration_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: state
  {
    out << "state: ";
    to_flow_style_yaml(msg.state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RunCalibration_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state:\n";
    to_block_style_yaml(msg.state, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RunCalibration_Feedback & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace zfc_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use zfc_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const zfc_interfaces::action::RunCalibration_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::action::RunCalibration_Feedback & msg)
{
  return zfc_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::action::RunCalibration_Feedback>()
{
  return "zfc_interfaces::action::RunCalibration_Feedback";
}

template<>
inline const char * name<zfc_interfaces::action::RunCalibration_Feedback>()
{
  return "zfc_interfaces/action/RunCalibration_Feedback";
}

template<>
struct has_fixed_size<zfc_interfaces::action::RunCalibration_Feedback>
  : std::integral_constant<bool, has_fixed_size<zfc_interfaces::msg::AnalysisState>::value> {};

template<>
struct has_bounded_size<zfc_interfaces::action::RunCalibration_Feedback>
  : std::integral_constant<bool, has_bounded_size<zfc_interfaces::msg::AnalysisState>::value> {};

template<>
struct is_message<zfc_interfaces::action::RunCalibration_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "zfc_interfaces/action/detail/run_calibration__traits.hpp"

namespace zfc_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const RunCalibration_SendGoal_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: goal
  {
    out << "goal: ";
    to_flow_style_yaml(msg.goal, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RunCalibration_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal:\n";
    to_block_style_yaml(msg.goal, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RunCalibration_SendGoal_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace zfc_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use zfc_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const zfc_interfaces::action::RunCalibration_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::action::RunCalibration_SendGoal_Request & msg)
{
  return zfc_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::action::RunCalibration_SendGoal_Request>()
{
  return "zfc_interfaces::action::RunCalibration_SendGoal_Request";
}

template<>
inline const char * name<zfc_interfaces::action::RunCalibration_SendGoal_Request>()
{
  return "zfc_interfaces/action/RunCalibration_SendGoal_Request";
}

template<>
struct has_fixed_size<zfc_interfaces::action::RunCalibration_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value && has_fixed_size<zfc_interfaces::action::RunCalibration_Goal>::value> {};

template<>
struct has_bounded_size<zfc_interfaces::action::RunCalibration_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value && has_bounded_size<zfc_interfaces::action::RunCalibration_Goal>::value> {};

template<>
struct is_message<zfc_interfaces::action::RunCalibration_SendGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace zfc_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const RunCalibration_SendGoal_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: accepted
  {
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RunCalibration_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: accepted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RunCalibration_SendGoal_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace zfc_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use zfc_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const zfc_interfaces::action::RunCalibration_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::action::RunCalibration_SendGoal_Response & msg)
{
  return zfc_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::action::RunCalibration_SendGoal_Response>()
{
  return "zfc_interfaces::action::RunCalibration_SendGoal_Response";
}

template<>
inline const char * name<zfc_interfaces::action::RunCalibration_SendGoal_Response>()
{
  return "zfc_interfaces/action/RunCalibration_SendGoal_Response";
}

template<>
struct has_fixed_size<zfc_interfaces::action::RunCalibration_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<zfc_interfaces::action::RunCalibration_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<zfc_interfaces::action::RunCalibration_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<zfc_interfaces::action::RunCalibration_SendGoal>()
{
  return "zfc_interfaces::action::RunCalibration_SendGoal";
}

template<>
inline const char * name<zfc_interfaces::action::RunCalibration_SendGoal>()
{
  return "zfc_interfaces/action/RunCalibration_SendGoal";
}

template<>
struct has_fixed_size<zfc_interfaces::action::RunCalibration_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<zfc_interfaces::action::RunCalibration_SendGoal_Request>::value &&
    has_fixed_size<zfc_interfaces::action::RunCalibration_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<zfc_interfaces::action::RunCalibration_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<zfc_interfaces::action::RunCalibration_SendGoal_Request>::value &&
    has_bounded_size<zfc_interfaces::action::RunCalibration_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<zfc_interfaces::action::RunCalibration_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<zfc_interfaces::action::RunCalibration_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<zfc_interfaces::action::RunCalibration_SendGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"

namespace zfc_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const RunCalibration_GetResult_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RunCalibration_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RunCalibration_GetResult_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace zfc_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use zfc_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const zfc_interfaces::action::RunCalibration_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::action::RunCalibration_GetResult_Request & msg)
{
  return zfc_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::action::RunCalibration_GetResult_Request>()
{
  return "zfc_interfaces::action::RunCalibration_GetResult_Request";
}

template<>
inline const char * name<zfc_interfaces::action::RunCalibration_GetResult_Request>()
{
  return "zfc_interfaces/action/RunCalibration_GetResult_Request";
}

template<>
struct has_fixed_size<zfc_interfaces::action::RunCalibration_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<zfc_interfaces::action::RunCalibration_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<zfc_interfaces::action::RunCalibration_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__traits.hpp"

namespace zfc_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const RunCalibration_GetResult_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << ", ";
  }

  // member: result
  {
    out << "result: ";
    to_flow_style_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RunCalibration_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result:\n";
    to_block_style_yaml(msg.result, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RunCalibration_GetResult_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace zfc_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use zfc_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const zfc_interfaces::action::RunCalibration_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::action::RunCalibration_GetResult_Response & msg)
{
  return zfc_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::action::RunCalibration_GetResult_Response>()
{
  return "zfc_interfaces::action::RunCalibration_GetResult_Response";
}

template<>
inline const char * name<zfc_interfaces::action::RunCalibration_GetResult_Response>()
{
  return "zfc_interfaces/action/RunCalibration_GetResult_Response";
}

template<>
struct has_fixed_size<zfc_interfaces::action::RunCalibration_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<zfc_interfaces::action::RunCalibration_Result>::value> {};

template<>
struct has_bounded_size<zfc_interfaces::action::RunCalibration_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<zfc_interfaces::action::RunCalibration_Result>::value> {};

template<>
struct is_message<zfc_interfaces::action::RunCalibration_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<zfc_interfaces::action::RunCalibration_GetResult>()
{
  return "zfc_interfaces::action::RunCalibration_GetResult";
}

template<>
inline const char * name<zfc_interfaces::action::RunCalibration_GetResult>()
{
  return "zfc_interfaces/action/RunCalibration_GetResult";
}

template<>
struct has_fixed_size<zfc_interfaces::action::RunCalibration_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<zfc_interfaces::action::RunCalibration_GetResult_Request>::value &&
    has_fixed_size<zfc_interfaces::action::RunCalibration_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<zfc_interfaces::action::RunCalibration_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<zfc_interfaces::action::RunCalibration_GetResult_Request>::value &&
    has_bounded_size<zfc_interfaces::action::RunCalibration_GetResult_Response>::value
  >
{
};

template<>
struct is_service<zfc_interfaces::action::RunCalibration_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<zfc_interfaces::action::RunCalibration_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<zfc_interfaces::action::RunCalibration_GetResult_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'feedback'
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__traits.hpp"

namespace zfc_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const RunCalibration_FeedbackMessage & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: feedback
  {
    out << "feedback: ";
    to_flow_style_yaml(msg.feedback, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RunCalibration_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: feedback
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "feedback:\n";
    to_block_style_yaml(msg.feedback, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RunCalibration_FeedbackMessage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace zfc_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use zfc_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const zfc_interfaces::action::RunCalibration_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::action::RunCalibration_FeedbackMessage & msg)
{
  return zfc_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::action::RunCalibration_FeedbackMessage>()
{
  return "zfc_interfaces::action::RunCalibration_FeedbackMessage";
}

template<>
inline const char * name<zfc_interfaces::action::RunCalibration_FeedbackMessage>()
{
  return "zfc_interfaces/action/RunCalibration_FeedbackMessage";
}

template<>
struct has_fixed_size<zfc_interfaces::action::RunCalibration_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value && has_fixed_size<zfc_interfaces::action::RunCalibration_Feedback>::value> {};

template<>
struct has_bounded_size<zfc_interfaces::action::RunCalibration_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value && has_bounded_size<zfc_interfaces::action::RunCalibration_Feedback>::value> {};

template<>
struct is_message<zfc_interfaces::action::RunCalibration_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<zfc_interfaces::action::RunCalibration>
  : std::true_type
{
};

template<>
struct is_action_goal<zfc_interfaces::action::RunCalibration_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<zfc_interfaces::action::RunCalibration_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<zfc_interfaces::action::RunCalibration_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__TRAITS_HPP_
