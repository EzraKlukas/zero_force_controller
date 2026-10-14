// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from zfc_interfaces:action/RunCalibration.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__STRUCT_H_
#define ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in action/RunCalibration in the package zfc_interfaces.
typedef struct zfc_interfaces__action__RunCalibration_Goal
{
  bool activate_zero_force_after;
  /// Physical operator affirmation for this trial and baseline/noise capture.
  bool external_contact_clear;
} zfc_interfaces__action__RunCalibration_Goal;

// Struct for a sequence of zfc_interfaces__action__RunCalibration_Goal.
typedef struct zfc_interfaces__action__RunCalibration_Goal__Sequence
{
  zfc_interfaces__action__RunCalibration_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__action__RunCalibration_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'trial_directory'
// Member 'message'
#include "rosidl_runtime_c/string.h"
// Member 'fit'
#include "zfc_interfaces/msg/detail/calibration_result__struct.h"

/// Struct defined in action/RunCalibration in the package zfc_interfaces.
typedef struct zfc_interfaces__action__RunCalibration_Result
{
  bool success;
  uint64_t trial_id;
  rosidl_runtime_c__String trial_directory;
  rosidl_runtime_c__String message;
  bool applied;
  bool zero_force_active;
  bool stop_acknowledged;
  zfc_interfaces__msg__CalibrationResult fit;
} zfc_interfaces__action__RunCalibration_Result;

// Struct for a sequence of zfc_interfaces__action__RunCalibration_Result.
typedef struct zfc_interfaces__action__RunCalibration_Result__Sequence
{
  zfc_interfaces__action__RunCalibration_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__action__RunCalibration_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'state'
#include "zfc_interfaces/msg/detail/analysis_state__struct.h"

/// Struct defined in action/RunCalibration in the package zfc_interfaces.
typedef struct zfc_interfaces__action__RunCalibration_Feedback
{
  zfc_interfaces__msg__AnalysisState state;
} zfc_interfaces__action__RunCalibration_Feedback;

// Struct for a sequence of zfc_interfaces__action__RunCalibration_Feedback.
typedef struct zfc_interfaces__action__RunCalibration_Feedback__Sequence
{
  zfc_interfaces__action__RunCalibration_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__action__RunCalibration_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "zfc_interfaces/action/detail/run_calibration__struct.h"

/// Struct defined in action/RunCalibration in the package zfc_interfaces.
typedef struct zfc_interfaces__action__RunCalibration_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  zfc_interfaces__action__RunCalibration_Goal goal;
} zfc_interfaces__action__RunCalibration_SendGoal_Request;

// Struct for a sequence of zfc_interfaces__action__RunCalibration_SendGoal_Request.
typedef struct zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence
{
  zfc_interfaces__action__RunCalibration_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/RunCalibration in the package zfc_interfaces.
typedef struct zfc_interfaces__action__RunCalibration_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} zfc_interfaces__action__RunCalibration_SendGoal_Response;

// Struct for a sequence of zfc_interfaces__action__RunCalibration_SendGoal_Response.
typedef struct zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence
{
  zfc_interfaces__action__RunCalibration_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/RunCalibration in the package zfc_interfaces.
typedef struct zfc_interfaces__action__RunCalibration_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} zfc_interfaces__action__RunCalibration_GetResult_Request;

// Struct for a sequence of zfc_interfaces__action__RunCalibration_GetResult_Request.
typedef struct zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence
{
  zfc_interfaces__action__RunCalibration_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"

/// Struct defined in action/RunCalibration in the package zfc_interfaces.
typedef struct zfc_interfaces__action__RunCalibration_GetResult_Response
{
  int8_t status;
  zfc_interfaces__action__RunCalibration_Result result;
} zfc_interfaces__action__RunCalibration_GetResult_Response;

// Struct for a sequence of zfc_interfaces__action__RunCalibration_GetResult_Response.
typedef struct zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence
{
  zfc_interfaces__action__RunCalibration_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"

/// Struct defined in action/RunCalibration in the package zfc_interfaces.
typedef struct zfc_interfaces__action__RunCalibration_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  zfc_interfaces__action__RunCalibration_Feedback feedback;
} zfc_interfaces__action__RunCalibration_FeedbackMessage;

// Struct for a sequence of zfc_interfaces__action__RunCalibration_FeedbackMessage.
typedef struct zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence
{
  zfc_interfaces__action__RunCalibration_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__STRUCT_H_
