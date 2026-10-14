// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from zfc_interfaces:msg/CalibrationResult.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__CALIBRATION_RESULT__STRUCT_H_
#define ZFC_INTERFACES__MSG__DETAIL__CALIBRATION_RESULT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'reason'
// Member 'acceleration_source'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/CalibrationResult in the package zfc_interfaces.
/**
  * Signed slope of force.x against effective commanded acceleration; NOT total mass.
 */
typedef struct zfc_interfaces__msg__CalibrationResult
{
  bool valid;
  rosidl_runtime_c__String reason;
  double inertial_force_coefficient_kg;
  double intercept_n;
  double r_squared;
  double residual_rms_n;
  double uncertainty_kg;
  uint64_t sample_count;
  uint64_t plateau_count;
  double positive_slope_kg;
  double negative_slope_kg;
  double tracking_rms_m;
  rosidl_runtime_c__String acceleration_source;
} zfc_interfaces__msg__CalibrationResult;

// Struct for a sequence of zfc_interfaces__msg__CalibrationResult.
typedef struct zfc_interfaces__msg__CalibrationResult__Sequence
{
  zfc_interfaces__msg__CalibrationResult * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__msg__CalibrationResult__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ZFC_INTERFACES__MSG__DETAIL__CALIBRATION_RESULT__STRUCT_H_
