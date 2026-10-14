// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from zfc_interfaces:action/RunCalibration.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "zfc_interfaces/action/detail/run_calibration__rosidl_typesupport_introspection_c.h"
#include "zfc_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "zfc_interfaces/action/detail/run_calibration__functions.h"
#include "zfc_interfaces/action/detail/run_calibration__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void zfc_interfaces__action__RunCalibration_Goal__rosidl_typesupport_introspection_c__RunCalibration_Goal_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  zfc_interfaces__action__RunCalibration_Goal__init(message_memory);
}

void zfc_interfaces__action__RunCalibration_Goal__rosidl_typesupport_introspection_c__RunCalibration_Goal_fini_function(void * message_memory)
{
  zfc_interfaces__action__RunCalibration_Goal__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember zfc_interfaces__action__RunCalibration_Goal__rosidl_typesupport_introspection_c__RunCalibration_Goal_message_member_array[2] = {
  {
    "activate_zero_force_after",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_Goal, activate_zero_force_after),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "external_contact_clear",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_Goal, external_contact_clear),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers zfc_interfaces__action__RunCalibration_Goal__rosidl_typesupport_introspection_c__RunCalibration_Goal_message_members = {
  "zfc_interfaces__action",  // message namespace
  "RunCalibration_Goal",  // message name
  2,  // number of fields
  sizeof(zfc_interfaces__action__RunCalibration_Goal),
  zfc_interfaces__action__RunCalibration_Goal__rosidl_typesupport_introspection_c__RunCalibration_Goal_message_member_array,  // message members
  zfc_interfaces__action__RunCalibration_Goal__rosidl_typesupport_introspection_c__RunCalibration_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  zfc_interfaces__action__RunCalibration_Goal__rosidl_typesupport_introspection_c__RunCalibration_Goal_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t zfc_interfaces__action__RunCalibration_Goal__rosidl_typesupport_introspection_c__RunCalibration_Goal_message_type_support_handle = {
  0,
  &zfc_interfaces__action__RunCalibration_Goal__rosidl_typesupport_introspection_c__RunCalibration_Goal_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_zfc_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_Goal)() {
  if (!zfc_interfaces__action__RunCalibration_Goal__rosidl_typesupport_introspection_c__RunCalibration_Goal_message_type_support_handle.typesupport_identifier) {
    zfc_interfaces__action__RunCalibration_Goal__rosidl_typesupport_introspection_c__RunCalibration_Goal_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &zfc_interfaces__action__RunCalibration_Goal__rosidl_typesupport_introspection_c__RunCalibration_Goal_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__rosidl_typesupport_introspection_c.h"
// already included above
// #include "zfc_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__functions.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"


// Include directives for member types
// Member `trial_directory`
// Member `message`
#include "rosidl_runtime_c/string_functions.h"
// Member `fit`
#include "zfc_interfaces/msg/calibration_result.h"
// Member `fit`
#include "zfc_interfaces/msg/detail/calibration_result__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void zfc_interfaces__action__RunCalibration_Result__rosidl_typesupport_introspection_c__RunCalibration_Result_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  zfc_interfaces__action__RunCalibration_Result__init(message_memory);
}

void zfc_interfaces__action__RunCalibration_Result__rosidl_typesupport_introspection_c__RunCalibration_Result_fini_function(void * message_memory)
{
  zfc_interfaces__action__RunCalibration_Result__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember zfc_interfaces__action__RunCalibration_Result__rosidl_typesupport_introspection_c__RunCalibration_Result_message_member_array[8] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_Result, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "trial_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_Result, trial_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "trial_directory",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_Result, trial_directory),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_Result, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "applied",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_Result, applied),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "zero_force_active",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_Result, zero_force_active),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stop_acknowledged",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_Result, stop_acknowledged),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "fit",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_Result, fit),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers zfc_interfaces__action__RunCalibration_Result__rosidl_typesupport_introspection_c__RunCalibration_Result_message_members = {
  "zfc_interfaces__action",  // message namespace
  "RunCalibration_Result",  // message name
  8,  // number of fields
  sizeof(zfc_interfaces__action__RunCalibration_Result),
  zfc_interfaces__action__RunCalibration_Result__rosidl_typesupport_introspection_c__RunCalibration_Result_message_member_array,  // message members
  zfc_interfaces__action__RunCalibration_Result__rosidl_typesupport_introspection_c__RunCalibration_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  zfc_interfaces__action__RunCalibration_Result__rosidl_typesupport_introspection_c__RunCalibration_Result_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t zfc_interfaces__action__RunCalibration_Result__rosidl_typesupport_introspection_c__RunCalibration_Result_message_type_support_handle = {
  0,
  &zfc_interfaces__action__RunCalibration_Result__rosidl_typesupport_introspection_c__RunCalibration_Result_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_zfc_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_Result)() {
  zfc_interfaces__action__RunCalibration_Result__rosidl_typesupport_introspection_c__RunCalibration_Result_message_member_array[7].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, msg, CalibrationResult)();
  if (!zfc_interfaces__action__RunCalibration_Result__rosidl_typesupport_introspection_c__RunCalibration_Result_message_type_support_handle.typesupport_identifier) {
    zfc_interfaces__action__RunCalibration_Result__rosidl_typesupport_introspection_c__RunCalibration_Result_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &zfc_interfaces__action__RunCalibration_Result__rosidl_typesupport_introspection_c__RunCalibration_Result_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__rosidl_typesupport_introspection_c.h"
// already included above
// #include "zfc_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__functions.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"


// Include directives for member types
// Member `state`
#include "zfc_interfaces/msg/analysis_state.h"
// Member `state`
#include "zfc_interfaces/msg/detail/analysis_state__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void zfc_interfaces__action__RunCalibration_Feedback__rosidl_typesupport_introspection_c__RunCalibration_Feedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  zfc_interfaces__action__RunCalibration_Feedback__init(message_memory);
}

void zfc_interfaces__action__RunCalibration_Feedback__rosidl_typesupport_introspection_c__RunCalibration_Feedback_fini_function(void * message_memory)
{
  zfc_interfaces__action__RunCalibration_Feedback__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember zfc_interfaces__action__RunCalibration_Feedback__rosidl_typesupport_introspection_c__RunCalibration_Feedback_message_member_array[1] = {
  {
    "state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_Feedback, state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers zfc_interfaces__action__RunCalibration_Feedback__rosidl_typesupport_introspection_c__RunCalibration_Feedback_message_members = {
  "zfc_interfaces__action",  // message namespace
  "RunCalibration_Feedback",  // message name
  1,  // number of fields
  sizeof(zfc_interfaces__action__RunCalibration_Feedback),
  zfc_interfaces__action__RunCalibration_Feedback__rosidl_typesupport_introspection_c__RunCalibration_Feedback_message_member_array,  // message members
  zfc_interfaces__action__RunCalibration_Feedback__rosidl_typesupport_introspection_c__RunCalibration_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  zfc_interfaces__action__RunCalibration_Feedback__rosidl_typesupport_introspection_c__RunCalibration_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t zfc_interfaces__action__RunCalibration_Feedback__rosidl_typesupport_introspection_c__RunCalibration_Feedback_message_type_support_handle = {
  0,
  &zfc_interfaces__action__RunCalibration_Feedback__rosidl_typesupport_introspection_c__RunCalibration_Feedback_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_zfc_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_Feedback)() {
  zfc_interfaces__action__RunCalibration_Feedback__rosidl_typesupport_introspection_c__RunCalibration_Feedback_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, msg, AnalysisState)();
  if (!zfc_interfaces__action__RunCalibration_Feedback__rosidl_typesupport_introspection_c__RunCalibration_Feedback_message_type_support_handle.typesupport_identifier) {
    zfc_interfaces__action__RunCalibration_Feedback__rosidl_typesupport_introspection_c__RunCalibration_Feedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &zfc_interfaces__action__RunCalibration_Feedback__rosidl_typesupport_introspection_c__RunCalibration_Feedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__rosidl_typesupport_introspection_c.h"
// already included above
// #include "zfc_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__functions.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `goal`
#include "zfc_interfaces/action/run_calibration.h"
// Member `goal`
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void zfc_interfaces__action__RunCalibration_SendGoal_Request__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  zfc_interfaces__action__RunCalibration_SendGoal_Request__init(message_memory);
}

void zfc_interfaces__action__RunCalibration_SendGoal_Request__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_fini_function(void * message_memory)
{
  zfc_interfaces__action__RunCalibration_SendGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember zfc_interfaces__action__RunCalibration_SendGoal_Request__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_SendGoal_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_SendGoal_Request, goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers zfc_interfaces__action__RunCalibration_SendGoal_Request__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_message_members = {
  "zfc_interfaces__action",  // message namespace
  "RunCalibration_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(zfc_interfaces__action__RunCalibration_SendGoal_Request),
  zfc_interfaces__action__RunCalibration_SendGoal_Request__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_message_member_array,  // message members
  zfc_interfaces__action__RunCalibration_SendGoal_Request__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  zfc_interfaces__action__RunCalibration_SendGoal_Request__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t zfc_interfaces__action__RunCalibration_SendGoal_Request__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_message_type_support_handle = {
  0,
  &zfc_interfaces__action__RunCalibration_SendGoal_Request__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_zfc_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_SendGoal_Request)() {
  zfc_interfaces__action__RunCalibration_SendGoal_Request__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  zfc_interfaces__action__RunCalibration_SendGoal_Request__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_Goal)();
  if (!zfc_interfaces__action__RunCalibration_SendGoal_Request__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_message_type_support_handle.typesupport_identifier) {
    zfc_interfaces__action__RunCalibration_SendGoal_Request__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &zfc_interfaces__action__RunCalibration_SendGoal_Request__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__rosidl_typesupport_introspection_c.h"
// already included above
// #include "zfc_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__functions.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void zfc_interfaces__action__RunCalibration_SendGoal_Response__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  zfc_interfaces__action__RunCalibration_SendGoal_Response__init(message_memory);
}

void zfc_interfaces__action__RunCalibration_SendGoal_Response__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Response_fini_function(void * message_memory)
{
  zfc_interfaces__action__RunCalibration_SendGoal_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember zfc_interfaces__action__RunCalibration_SendGoal_Response__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_SendGoal_Response, accepted),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_SendGoal_Response, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers zfc_interfaces__action__RunCalibration_SendGoal_Response__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Response_message_members = {
  "zfc_interfaces__action",  // message namespace
  "RunCalibration_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(zfc_interfaces__action__RunCalibration_SendGoal_Response),
  zfc_interfaces__action__RunCalibration_SendGoal_Response__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Response_message_member_array,  // message members
  zfc_interfaces__action__RunCalibration_SendGoal_Response__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  zfc_interfaces__action__RunCalibration_SendGoal_Response__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t zfc_interfaces__action__RunCalibration_SendGoal_Response__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Response_message_type_support_handle = {
  0,
  &zfc_interfaces__action__RunCalibration_SendGoal_Response__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_zfc_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_SendGoal_Response)() {
  zfc_interfaces__action__RunCalibration_SendGoal_Response__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!zfc_interfaces__action__RunCalibration_SendGoal_Response__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Response_message_type_support_handle.typesupport_identifier) {
    zfc_interfaces__action__RunCalibration_SendGoal_Response__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &zfc_interfaces__action__RunCalibration_SendGoal_Response__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "zfc_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_service_members = {
  "zfc_interfaces__action",  // service namespace
  "RunCalibration_SendGoal",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Request_message_type_support_handle,
  NULL  // response message
  // zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_Response_message_type_support_handle
};

static rosidl_service_type_support_t zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_service_type_support_handle = {
  0,
  &zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_SendGoal_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_SendGoal_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_zfc_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_SendGoal)() {
  if (!zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_service_type_support_handle.typesupport_identifier) {
    zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_SendGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_SendGoal_Response)()->data;
  }

  return &zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_SendGoal_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__rosidl_typesupport_introspection_c.h"
// already included above
// #include "zfc_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__functions.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void zfc_interfaces__action__RunCalibration_GetResult_Request__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  zfc_interfaces__action__RunCalibration_GetResult_Request__init(message_memory);
}

void zfc_interfaces__action__RunCalibration_GetResult_Request__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Request_fini_function(void * message_memory)
{
  zfc_interfaces__action__RunCalibration_GetResult_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember zfc_interfaces__action__RunCalibration_GetResult_Request__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_GetResult_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers zfc_interfaces__action__RunCalibration_GetResult_Request__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Request_message_members = {
  "zfc_interfaces__action",  // message namespace
  "RunCalibration_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(zfc_interfaces__action__RunCalibration_GetResult_Request),
  zfc_interfaces__action__RunCalibration_GetResult_Request__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Request_message_member_array,  // message members
  zfc_interfaces__action__RunCalibration_GetResult_Request__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  zfc_interfaces__action__RunCalibration_GetResult_Request__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t zfc_interfaces__action__RunCalibration_GetResult_Request__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Request_message_type_support_handle = {
  0,
  &zfc_interfaces__action__RunCalibration_GetResult_Request__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_zfc_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_GetResult_Request)() {
  zfc_interfaces__action__RunCalibration_GetResult_Request__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  if (!zfc_interfaces__action__RunCalibration_GetResult_Request__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Request_message_type_support_handle.typesupport_identifier) {
    zfc_interfaces__action__RunCalibration_GetResult_Request__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &zfc_interfaces__action__RunCalibration_GetResult_Request__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__rosidl_typesupport_introspection_c.h"
// already included above
// #include "zfc_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__functions.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"


// Include directives for member types
// Member `result`
// already included above
// #include "zfc_interfaces/action/run_calibration.h"
// Member `result`
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void zfc_interfaces__action__RunCalibration_GetResult_Response__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  zfc_interfaces__action__RunCalibration_GetResult_Response__init(message_memory);
}

void zfc_interfaces__action__RunCalibration_GetResult_Response__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Response_fini_function(void * message_memory)
{
  zfc_interfaces__action__RunCalibration_GetResult_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember zfc_interfaces__action__RunCalibration_GetResult_Response__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_GetResult_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_GetResult_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers zfc_interfaces__action__RunCalibration_GetResult_Response__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Response_message_members = {
  "zfc_interfaces__action",  // message namespace
  "RunCalibration_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(zfc_interfaces__action__RunCalibration_GetResult_Response),
  zfc_interfaces__action__RunCalibration_GetResult_Response__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Response_message_member_array,  // message members
  zfc_interfaces__action__RunCalibration_GetResult_Response__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  zfc_interfaces__action__RunCalibration_GetResult_Response__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t zfc_interfaces__action__RunCalibration_GetResult_Response__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Response_message_type_support_handle = {
  0,
  &zfc_interfaces__action__RunCalibration_GetResult_Response__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_zfc_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_GetResult_Response)() {
  zfc_interfaces__action__RunCalibration_GetResult_Response__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_Result)();
  if (!zfc_interfaces__action__RunCalibration_GetResult_Response__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Response_message_type_support_handle.typesupport_identifier) {
    zfc_interfaces__action__RunCalibration_GetResult_Response__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &zfc_interfaces__action__RunCalibration_GetResult_Response__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "zfc_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_GetResult_service_members = {
  "zfc_interfaces__action",  // service namespace
  "RunCalibration_GetResult",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Request_message_type_support_handle,
  NULL  // response message
  // zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_GetResult_Response_message_type_support_handle
};

static rosidl_service_type_support_t zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_GetResult_service_type_support_handle = {
  0,
  &zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_GetResult_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_GetResult_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_GetResult_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_zfc_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_GetResult)() {
  if (!zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_GetResult_service_type_support_handle.typesupport_identifier) {
    zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_GetResult_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_GetResult_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_GetResult_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_GetResult_Response)()->data;
  }

  return &zfc_interfaces__action__detail__run_calibration__rosidl_typesupport_introspection_c__RunCalibration_GetResult_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__rosidl_typesupport_introspection_c.h"
// already included above
// #include "zfc_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__functions.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `feedback`
// already included above
// #include "zfc_interfaces/action/run_calibration.h"
// Member `feedback`
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void zfc_interfaces__action__RunCalibration_FeedbackMessage__rosidl_typesupport_introspection_c__RunCalibration_FeedbackMessage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  zfc_interfaces__action__RunCalibration_FeedbackMessage__init(message_memory);
}

void zfc_interfaces__action__RunCalibration_FeedbackMessage__rosidl_typesupport_introspection_c__RunCalibration_FeedbackMessage_fini_function(void * message_memory)
{
  zfc_interfaces__action__RunCalibration_FeedbackMessage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember zfc_interfaces__action__RunCalibration_FeedbackMessage__rosidl_typesupport_introspection_c__RunCalibration_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_FeedbackMessage, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "feedback",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zfc_interfaces__action__RunCalibration_FeedbackMessage, feedback),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers zfc_interfaces__action__RunCalibration_FeedbackMessage__rosidl_typesupport_introspection_c__RunCalibration_FeedbackMessage_message_members = {
  "zfc_interfaces__action",  // message namespace
  "RunCalibration_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(zfc_interfaces__action__RunCalibration_FeedbackMessage),
  zfc_interfaces__action__RunCalibration_FeedbackMessage__rosidl_typesupport_introspection_c__RunCalibration_FeedbackMessage_message_member_array,  // message members
  zfc_interfaces__action__RunCalibration_FeedbackMessage__rosidl_typesupport_introspection_c__RunCalibration_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  zfc_interfaces__action__RunCalibration_FeedbackMessage__rosidl_typesupport_introspection_c__RunCalibration_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t zfc_interfaces__action__RunCalibration_FeedbackMessage__rosidl_typesupport_introspection_c__RunCalibration_FeedbackMessage_message_type_support_handle = {
  0,
  &zfc_interfaces__action__RunCalibration_FeedbackMessage__rosidl_typesupport_introspection_c__RunCalibration_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_zfc_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_FeedbackMessage)() {
  zfc_interfaces__action__RunCalibration_FeedbackMessage__rosidl_typesupport_introspection_c__RunCalibration_FeedbackMessage_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  zfc_interfaces__action__RunCalibration_FeedbackMessage__rosidl_typesupport_introspection_c__RunCalibration_FeedbackMessage_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_Feedback)();
  if (!zfc_interfaces__action__RunCalibration_FeedbackMessage__rosidl_typesupport_introspection_c__RunCalibration_FeedbackMessage_message_type_support_handle.typesupport_identifier) {
    zfc_interfaces__action__RunCalibration_FeedbackMessage__rosidl_typesupport_introspection_c__RunCalibration_FeedbackMessage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &zfc_interfaces__action__RunCalibration_FeedbackMessage__rosidl_typesupport_introspection_c__RunCalibration_FeedbackMessage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
