// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from zfc_interfaces:msg/TrialStatus.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__TRIAL_STATUS__STRUCT_H_
#define ZFC_INTERFACES__MSG__DETAIL__TRIAL_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/TrialStatus in the package zfc_interfaces.
/**
  * Transient-local terminal status; independent of plotting delivery.
 */
typedef struct zfc_interfaces__msg__TrialStatus
{
  builtin_interfaces__msg__Time stamp;
  uint64_t trial_id;
  uint64_t final_sequence;
  uint64_t dropped_samples;
  uint64_t failed_publication_samples;
  uint8_t phase;
  uint8_t fault_code;
  bool completed;
  bool successful;
  bool capture_complete;
} zfc_interfaces__msg__TrialStatus;

// Struct for a sequence of zfc_interfaces__msg__TrialStatus.
typedef struct zfc_interfaces__msg__TrialStatus__Sequence
{
  zfc_interfaces__msg__TrialStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__msg__TrialStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ZFC_INTERFACES__MSG__DETAIL__TRIAL_STATUS__STRUCT_H_
