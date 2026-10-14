// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from zfc_interfaces:srv/OperatorCommand.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__STRUCT_H_
#define ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'command'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/OperatorCommand in the package zfc_interfaces.
typedef struct zfc_interfaces__srv__OperatorCommand_Request
{
  rosidl_runtime_c__String command;
  /// Physical operator affirmation for THIS request; sensors cannot prove no contact.
  bool external_contact_clear;
} zfc_interfaces__srv__OperatorCommand_Request;

// Struct for a sequence of zfc_interfaces__srv__OperatorCommand_Request.
typedef struct zfc_interfaces__srv__OperatorCommand_Request__Sequence
{
  zfc_interfaces__srv__OperatorCommand_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__srv__OperatorCommand_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/OperatorCommand in the package zfc_interfaces.
typedef struct zfc_interfaces__srv__OperatorCommand_Response
{
  bool success;
  bool stop_acknowledged;
  rosidl_runtime_c__String message;
} zfc_interfaces__srv__OperatorCommand_Response;

// Struct for a sequence of zfc_interfaces__srv__OperatorCommand_Response.
typedef struct zfc_interfaces__srv__OperatorCommand_Response__Sequence
{
  zfc_interfaces__srv__OperatorCommand_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__srv__OperatorCommand_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__STRUCT_H_
