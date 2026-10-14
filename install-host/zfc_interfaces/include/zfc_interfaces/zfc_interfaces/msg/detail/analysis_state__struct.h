// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from zfc_interfaces:msg/AnalysisState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__STRUCT_H_
#define ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__STRUCT_H_

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
// Member 'stage'
// Member 'detail'
// Member 'backend'
// Member 'trial_directory'
#include "rosidl_runtime_c/string.h"
// Member 'fit'
#include "zfc_interfaces/msg/detail/calibration_result__struct.h"

/// Struct defined in msg/AnalysisState in the package zfc_interfaces.
typedef struct zfc_interfaces__msg__AnalysisState
{
  std_msgs__msg__Header header;
  uint64_t trial_id;
  rosidl_runtime_c__String stage;
  uint8_t stage_code;
  double progress;
  uint64_t recorded_samples;
  uint64_t dropped_samples;
  uint64_t final_sequence;
  bool stop_acknowledged;
  rosidl_runtime_c__String detail;
  zfc_interfaces__msg__CalibrationResult fit;
  rosidl_runtime_c__String backend;
  bool operation_pending;
  rosidl_runtime_c__String trial_directory;
} zfc_interfaces__msg__AnalysisState;

// Struct for a sequence of zfc_interfaces__msg__AnalysisState.
typedef struct zfc_interfaces__msg__AnalysisState__Sequence
{
  zfc_interfaces__msg__AnalysisState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__msg__AnalysisState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__STRUCT_H_
