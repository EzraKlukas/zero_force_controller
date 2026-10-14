// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from zfc_interfaces:msg/CalibrationResult.idl
// generated code does not contain a copyright notice
#include "zfc_interfaces/msg/detail/calibration_result__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "zfc_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "zfc_interfaces/msg/detail/calibration_result__struct.h"
#include "zfc_interfaces/msg/detail/calibration_result__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // acceleration_source, reason
#include "rosidl_runtime_c/string_functions.h"  // acceleration_source, reason

// forward declare type support functions


using _CalibrationResult__ros_msg_type = zfc_interfaces__msg__CalibrationResult;

static bool _CalibrationResult__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _CalibrationResult__ros_msg_type * ros_message = static_cast<const _CalibrationResult__ros_msg_type *>(untyped_ros_message);
  // Field name: valid
  {
    cdr << (ros_message->valid ? true : false);
  }

  // Field name: reason
  {
    const rosidl_runtime_c__String * str = &ros_message->reason;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: inertial_force_coefficient_kg
  {
    cdr << ros_message->inertial_force_coefficient_kg;
  }

  // Field name: intercept_n
  {
    cdr << ros_message->intercept_n;
  }

  // Field name: r_squared
  {
    cdr << ros_message->r_squared;
  }

  // Field name: residual_rms_n
  {
    cdr << ros_message->residual_rms_n;
  }

  // Field name: uncertainty_kg
  {
    cdr << ros_message->uncertainty_kg;
  }

  // Field name: sample_count
  {
    cdr << ros_message->sample_count;
  }

  // Field name: plateau_count
  {
    cdr << ros_message->plateau_count;
  }

  // Field name: positive_slope_kg
  {
    cdr << ros_message->positive_slope_kg;
  }

  // Field name: negative_slope_kg
  {
    cdr << ros_message->negative_slope_kg;
  }

  // Field name: tracking_rms_m
  {
    cdr << ros_message->tracking_rms_m;
  }

  // Field name: acceleration_source
  {
    const rosidl_runtime_c__String * str = &ros_message->acceleration_source;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

static bool _CalibrationResult__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _CalibrationResult__ros_msg_type * ros_message = static_cast<_CalibrationResult__ros_msg_type *>(untyped_ros_message);
  // Field name: valid
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->valid = tmp ? true : false;
  }

  // Field name: reason
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->reason.data) {
      rosidl_runtime_c__String__init(&ros_message->reason);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->reason,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'reason'\n");
      return false;
    }
  }

  // Field name: inertial_force_coefficient_kg
  {
    cdr >> ros_message->inertial_force_coefficient_kg;
  }

  // Field name: intercept_n
  {
    cdr >> ros_message->intercept_n;
  }

  // Field name: r_squared
  {
    cdr >> ros_message->r_squared;
  }

  // Field name: residual_rms_n
  {
    cdr >> ros_message->residual_rms_n;
  }

  // Field name: uncertainty_kg
  {
    cdr >> ros_message->uncertainty_kg;
  }

  // Field name: sample_count
  {
    cdr >> ros_message->sample_count;
  }

  // Field name: plateau_count
  {
    cdr >> ros_message->plateau_count;
  }

  // Field name: positive_slope_kg
  {
    cdr >> ros_message->positive_slope_kg;
  }

  // Field name: negative_slope_kg
  {
    cdr >> ros_message->negative_slope_kg;
  }

  // Field name: tracking_rms_m
  {
    cdr >> ros_message->tracking_rms_m;
  }

  // Field name: acceleration_source
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->acceleration_source.data) {
      rosidl_runtime_c__String__init(&ros_message->acceleration_source);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->acceleration_source,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'acceleration_source'\n");
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_zfc_interfaces
size_t get_serialized_size_zfc_interfaces__msg__CalibrationResult(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _CalibrationResult__ros_msg_type * ros_message = static_cast<const _CalibrationResult__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name valid
  {
    size_t item_size = sizeof(ros_message->valid);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name reason
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->reason.size + 1);
  // field.name inertial_force_coefficient_kg
  {
    size_t item_size = sizeof(ros_message->inertial_force_coefficient_kg);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name intercept_n
  {
    size_t item_size = sizeof(ros_message->intercept_n);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name r_squared
  {
    size_t item_size = sizeof(ros_message->r_squared);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name residual_rms_n
  {
    size_t item_size = sizeof(ros_message->residual_rms_n);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name uncertainty_kg
  {
    size_t item_size = sizeof(ros_message->uncertainty_kg);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name sample_count
  {
    size_t item_size = sizeof(ros_message->sample_count);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name plateau_count
  {
    size_t item_size = sizeof(ros_message->plateau_count);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name positive_slope_kg
  {
    size_t item_size = sizeof(ros_message->positive_slope_kg);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name negative_slope_kg
  {
    size_t item_size = sizeof(ros_message->negative_slope_kg);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name tracking_rms_m
  {
    size_t item_size = sizeof(ros_message->tracking_rms_m);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name acceleration_source
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->acceleration_source.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _CalibrationResult__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_zfc_interfaces__msg__CalibrationResult(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_zfc_interfaces
size_t max_serialized_size_zfc_interfaces__msg__CalibrationResult(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: valid
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: reason
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: inertial_force_coefficient_kg
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: intercept_n
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: r_squared
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: residual_rms_n
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: uncertainty_kg
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: sample_count
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: plateau_count
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: positive_slope_kg
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: negative_slope_kg
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: tracking_rms_m
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: acceleration_source
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = zfc_interfaces__msg__CalibrationResult;
    is_plain =
      (
      offsetof(DataType, acceleration_source) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _CalibrationResult__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_zfc_interfaces__msg__CalibrationResult(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_CalibrationResult = {
  "zfc_interfaces::msg",
  "CalibrationResult",
  _CalibrationResult__cdr_serialize,
  _CalibrationResult__cdr_deserialize,
  _CalibrationResult__get_serialized_size,
  _CalibrationResult__max_serialized_size
};

static rosidl_message_type_support_t _CalibrationResult__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_CalibrationResult,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, zfc_interfaces, msg, CalibrationResult)() {
  return &_CalibrationResult__type_support;
}

#if defined(__cplusplus)
}
#endif
