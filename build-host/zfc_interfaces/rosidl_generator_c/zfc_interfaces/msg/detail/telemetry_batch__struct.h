// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from zfc_interfaces:msg/TelemetryBatch.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__TELEMETRY_BATCH__STRUCT_H_
#define ZFC_INTERFACES__MSG__DETAIL__TELEMETRY_BATCH__STRUCT_H_

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
// Member 'samples'
#include "zfc_interfaces/msg/detail/controller_state__struct.h"

// constants for array fields with an upper bound
// samples
enum
{
  zfc_interfaces__msg__TelemetryBatch__samples__MAX_SIZE = 256
};

/// Struct defined in msg/TelemetryBatch in the package zfc_interfaces.
/**
  * Reliable capture stream; consumers must verify sequence continuity.
 */
typedef struct zfc_interfaces__msg__TelemetryBatch
{
  builtin_interfaces__msg__Time stamp;
  zfc_interfaces__msg__ControllerState__Sequence samples;
  uint64_t dropped_samples;
  uint64_t failed_publication_samples;
} zfc_interfaces__msg__TelemetryBatch;

// Struct for a sequence of zfc_interfaces__msg__TelemetryBatch.
typedef struct zfc_interfaces__msg__TelemetryBatch__Sequence
{
  zfc_interfaces__msg__TelemetryBatch * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__msg__TelemetryBatch__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ZFC_INTERFACES__MSG__DETAIL__TELEMETRY_BATCH__STRUCT_H_
