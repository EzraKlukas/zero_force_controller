// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from zfc_interfaces:msg/AnalysisState.idl
// generated code does not contain a copyright notice
#include "zfc_interfaces/msg/detail/analysis_state__rosidl_typesupport_fastrtps_cpp.hpp"
#include "zfc_interfaces/msg/detail/analysis_state__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace std_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const std_msgs::msg::Header &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  std_msgs::msg::Header &);
size_t get_serialized_size(
  const std_msgs::msg::Header &,
  size_t current_alignment);
size_t
max_serialized_size_Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace std_msgs

namespace zfc_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const zfc_interfaces::msg::CalibrationResult &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  zfc_interfaces::msg::CalibrationResult &);
size_t get_serialized_size(
  const zfc_interfaces::msg::CalibrationResult &,
  size_t current_alignment);
size_t
max_serialized_size_CalibrationResult(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace zfc_interfaces


namespace zfc_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_zfc_interfaces
cdr_serialize(
  const zfc_interfaces::msg::AnalysisState & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.header,
    cdr);
  // Member: trial_id
  cdr << ros_message.trial_id;
  // Member: stage
  cdr << ros_message.stage;
  // Member: stage_code
  cdr << ros_message.stage_code;
  // Member: progress
  cdr << ros_message.progress;
  // Member: recorded_samples
  cdr << ros_message.recorded_samples;
  // Member: dropped_samples
  cdr << ros_message.dropped_samples;
  // Member: final_sequence
  cdr << ros_message.final_sequence;
  // Member: stop_acknowledged
  cdr << (ros_message.stop_acknowledged ? true : false);
  // Member: detail
  cdr << ros_message.detail;
  // Member: fit
  zfc_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.fit,
    cdr);
  // Member: backend
  cdr << ros_message.backend;
  // Member: operation_pending
  cdr << (ros_message.operation_pending ? true : false);
  // Member: trial_directory
  cdr << ros_message.trial_directory;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_zfc_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  zfc_interfaces::msg::AnalysisState & ros_message)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.header);

  // Member: trial_id
  cdr >> ros_message.trial_id;

  // Member: stage
  cdr >> ros_message.stage;

  // Member: stage_code
  cdr >> ros_message.stage_code;

  // Member: progress
  cdr >> ros_message.progress;

  // Member: recorded_samples
  cdr >> ros_message.recorded_samples;

  // Member: dropped_samples
  cdr >> ros_message.dropped_samples;

  // Member: final_sequence
  cdr >> ros_message.final_sequence;

  // Member: stop_acknowledged
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.stop_acknowledged = tmp ? true : false;
  }

  // Member: detail
  cdr >> ros_message.detail;

  // Member: fit
  zfc_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.fit);

  // Member: backend
  cdr >> ros_message.backend;

  // Member: operation_pending
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.operation_pending = tmp ? true : false;
  }

  // Member: trial_directory
  cdr >> ros_message.trial_directory;

  return true;
}  // NOLINT(readability/fn_size)

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_zfc_interfaces
get_serialized_size(
  const zfc_interfaces::msg::AnalysisState & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: header

  current_alignment +=
    std_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.header, current_alignment);
  // Member: trial_id
  {
    size_t item_size = sizeof(ros_message.trial_id);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: stage
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.stage.size() + 1);
  // Member: stage_code
  {
    size_t item_size = sizeof(ros_message.stage_code);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: progress
  {
    size_t item_size = sizeof(ros_message.progress);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: recorded_samples
  {
    size_t item_size = sizeof(ros_message.recorded_samples);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: dropped_samples
  {
    size_t item_size = sizeof(ros_message.dropped_samples);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: final_sequence
  {
    size_t item_size = sizeof(ros_message.final_sequence);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: stop_acknowledged
  {
    size_t item_size = sizeof(ros_message.stop_acknowledged);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: detail
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.detail.size() + 1);
  // Member: fit

  current_alignment +=
    zfc_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.fit, current_alignment);
  // Member: backend
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.backend.size() + 1);
  // Member: operation_pending
  {
    size_t item_size = sizeof(ros_message.operation_pending);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: trial_directory
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.trial_directory.size() + 1);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_zfc_interfaces
max_serialized_size_AnalysisState(
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


  // Member: header
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        std_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: trial_id
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: stage
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

  // Member: stage_code
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: progress
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: recorded_samples
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: dropped_samples
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: final_sequence
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: stop_acknowledged
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: detail
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

  // Member: fit
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        zfc_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_CalibrationResult(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: backend
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

  // Member: operation_pending
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: trial_directory
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
    using DataType = zfc_interfaces::msg::AnalysisState;
    is_plain =
      (
      offsetof(DataType, trial_directory) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _AnalysisState__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const zfc_interfaces::msg::AnalysisState *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _AnalysisState__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<zfc_interfaces::msg::AnalysisState *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _AnalysisState__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const zfc_interfaces::msg::AnalysisState *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _AnalysisState__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_AnalysisState(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _AnalysisState__callbacks = {
  "zfc_interfaces::msg",
  "AnalysisState",
  _AnalysisState__cdr_serialize,
  _AnalysisState__cdr_deserialize,
  _AnalysisState__get_serialized_size,
  _AnalysisState__max_serialized_size
};

static rosidl_message_type_support_t _AnalysisState__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_AnalysisState__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace zfc_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_zfc_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<zfc_interfaces::msg::AnalysisState>()
{
  return &zfc_interfaces::msg::typesupport_fastrtps_cpp::_AnalysisState__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, zfc_interfaces, msg, AnalysisState)() {
  return &zfc_interfaces::msg::typesupport_fastrtps_cpp::_AnalysisState__handle;
}

#ifdef __cplusplus
}
#endif
