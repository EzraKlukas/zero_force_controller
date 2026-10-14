// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from zfc_interfaces:msg/ControllerState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__CONTROLLER_STATE__STRUCT_H_
#define ZFC_INTERFACES__MSG__DETAIL__CONTROLLER_STATE__STRUCT_H_

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

/// Struct defined in msg/ControllerState in the package zfc_interfaces.
typedef struct zfc_interfaces__msg__ControllerState
{
  builtin_interfaces__msg__Time stamp;
  uint64_t trial_id;
  uint64_t sequence;
  uint8_t phase;
  uint8_t fault_code;
  bool valid;
  double position_m;
  double velocity_mps;
  double force_n;
  double reference_position_m;
  double reference_velocity_mps;
  double reference_acceleration_mps2;
  double baseline_force_n;
  double noise_rms_n;
  double residual_force_n;
  double progress;
  uint64_t excessive_periods;
} zfc_interfaces__msg__ControllerState;

// Struct for a sequence of zfc_interfaces__msg__ControllerState.
typedef struct zfc_interfaces__msg__ControllerState__Sequence
{
  zfc_interfaces__msg__ControllerState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__msg__ControllerState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ZFC_INTERFACES__MSG__DETAIL__CONTROLLER_STATE__STRUCT_H_
