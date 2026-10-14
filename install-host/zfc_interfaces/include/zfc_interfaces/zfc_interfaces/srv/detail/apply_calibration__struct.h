// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from zfc_interfaces:srv/ApplyCalibration.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__SRV__DETAIL__APPLY_CALIBRATION__STRUCT_H_
#define ZFC_INTERFACES__SRV__DETAIL__APPLY_CALIBRATION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'result_file'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ApplyCalibration in the package zfc_interfaces.
typedef struct zfc_interfaces__srv__ApplyCalibration_Request
{
  rosidl_runtime_c__String result_file;
} zfc_interfaces__srv__ApplyCalibration_Request;

// Struct for a sequence of zfc_interfaces__srv__ApplyCalibration_Request.
typedef struct zfc_interfaces__srv__ApplyCalibration_Request__Sequence
{
  zfc_interfaces__srv__ApplyCalibration_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__srv__ApplyCalibration_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'fit'
#include "zfc_interfaces/msg/detail/calibration_result__struct.h"

/// Struct defined in srv/ApplyCalibration in the package zfc_interfaces.
typedef struct zfc_interfaces__srv__ApplyCalibration_Response
{
  bool success;
  rosidl_runtime_c__String message;
  zfc_interfaces__msg__CalibrationResult fit;
} zfc_interfaces__srv__ApplyCalibration_Response;

// Struct for a sequence of zfc_interfaces__srv__ApplyCalibration_Response.
typedef struct zfc_interfaces__srv__ApplyCalibration_Response__Sequence
{
  zfc_interfaces__srv__ApplyCalibration_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__srv__ApplyCalibration_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ZFC_INTERFACES__SRV__DETAIL__APPLY_CALIBRATION__STRUCT_H_
