// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from zfc_interfaces:msg/TelemetryBatch.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "zfc_interfaces/msg/detail/telemetry_batch__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace zfc_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void TelemetryBatch_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) zfc_interfaces::msg::TelemetryBatch(_init);
}

void TelemetryBatch_fini_function(void * message_memory)
{
  auto typed_message = static_cast<zfc_interfaces::msg::TelemetryBatch *>(message_memory);
  typed_message->~TelemetryBatch();
}

size_t size_function__TelemetryBatch__samples(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<zfc_interfaces::msg::ControllerState> *>(untyped_member);
  return member->size();
}

const void * get_const_function__TelemetryBatch__samples(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<zfc_interfaces::msg::ControllerState> *>(untyped_member);
  return &member[index];
}

void * get_function__TelemetryBatch__samples(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<zfc_interfaces::msg::ControllerState> *>(untyped_member);
  return &member[index];
}

void fetch_function__TelemetryBatch__samples(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const zfc_interfaces::msg::ControllerState *>(
    get_const_function__TelemetryBatch__samples(untyped_member, index));
  auto & value = *reinterpret_cast<zfc_interfaces::msg::ControllerState *>(untyped_value);
  value = item;
}

void assign_function__TelemetryBatch__samples(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<zfc_interfaces::msg::ControllerState *>(
    get_function__TelemetryBatch__samples(untyped_member, index));
  const auto & value = *reinterpret_cast<const zfc_interfaces::msg::ControllerState *>(untyped_value);
  item = value;
}

void resize_function__TelemetryBatch__samples(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<zfc_interfaces::msg::ControllerState> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember TelemetryBatch_message_member_array[4] = {
  {
    "stamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces::msg::TelemetryBatch, stamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "samples",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<zfc_interfaces::msg::ControllerState>(),  // members of sub message
    true,  // is array
    256,  // array size
    true,  // is upper bound
    offsetof(zfc_interfaces::msg::TelemetryBatch, samples),  // bytes offset in struct
    nullptr,  // default value
    size_function__TelemetryBatch__samples,  // size() function pointer
    get_const_function__TelemetryBatch__samples,  // get_const(index) function pointer
    get_function__TelemetryBatch__samples,  // get(index) function pointer
    fetch_function__TelemetryBatch__samples,  // fetch(index, &value) function pointer
    assign_function__TelemetryBatch__samples,  // assign(index, value) function pointer
    resize_function__TelemetryBatch__samples  // resize(index) function pointer
  },
  {
    "dropped_samples",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces::msg::TelemetryBatch, dropped_samples),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "failed_publication_samples",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces::msg::TelemetryBatch, failed_publication_samples),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers TelemetryBatch_message_members = {
  "zfc_interfaces::msg",  // message namespace
  "TelemetryBatch",  // message name
  4,  // number of fields
  sizeof(zfc_interfaces::msg::TelemetryBatch),
  TelemetryBatch_message_member_array,  // message members
  TelemetryBatch_init_function,  // function to initialize message memory (memory has to be allocated)
  TelemetryBatch_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t TelemetryBatch_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &TelemetryBatch_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace zfc_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<zfc_interfaces::msg::TelemetryBatch>()
{
  return &::zfc_interfaces::msg::rosidl_typesupport_introspection_cpp::TelemetryBatch_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, zfc_interfaces, msg, TelemetryBatch)() {
  return &::zfc_interfaces::msg::rosidl_typesupport_introspection_cpp::TelemetryBatch_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
