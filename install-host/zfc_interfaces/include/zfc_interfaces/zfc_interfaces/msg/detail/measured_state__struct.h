// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from zfc_interfaces:msg/MeasuredState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__MEASURED_STATE__STRUCT_H_
#define ZFC_INTERFACES__MSG__DETAIL__MEASURED_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'force_stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'detail'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/MeasuredState in the package zfc_interfaces.
/**
  * Visualization only: independent broadcaster samples, NOT synchronized capture.
  * Header is the joint source time. Force retains its own source time.
 */
typedef struct zfc_interfaces__msg__MeasuredState
{
  std_msgs__msg__Header header;
  builtin_interfaces__msg__Time force_stamp;
  double position_m;
  double velocity_mps;
  double force_n;
  bool joint_fresh;
  bool force_fresh;
  bool valid;
  rosidl_runtime_c__String detail;
} zfc_interfaces__msg__MeasuredState;

// Struct for a sequence of zfc_interfaces__msg__MeasuredState.
typedef struct zfc_interfaces__msg__MeasuredState__Sequence
{
  zfc_interfaces__msg__MeasuredState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__msg__MeasuredState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ZFC_INTERFACES__MSG__DETAIL__MEASURED_STATE__STRUCT_H_
