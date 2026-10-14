// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from zfc_interfaces:msg/PlotState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__PLOT_STATE__STRUCT_H_
#define ZFC_INTERFACES__MSG__DETAIL__PLOT_STATE__STRUCT_H_

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
// Member 'state'
#include "zfc_interfaces/msg/detail/controller_state__struct.h"

/// Struct defined in msg/PlotState in the package zfc_interfaces.
/**
  * Decimated visualization only. Original full-rate batches remain authoritative.
 */
typedef struct zfc_interfaces__msg__PlotState
{
  std_msgs__msg__Header header;
  zfc_interfaces__msg__ControllerState state;
  /// Reconstructed outside update from force - frozen baseline - residual.
  /// Meaningful only in compliant phase; zero in capture/calibration phases.
  double inertial_compensation_n;
} zfc_interfaces__msg__PlotState;

// Struct for a sequence of zfc_interfaces__msg__PlotState.
typedef struct zfc_interfaces__msg__PlotState__Sequence
{
  zfc_interfaces__msg__PlotState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__msg__PlotState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ZFC_INTERFACES__MSG__DETAIL__PLOT_STATE__STRUCT_H_
