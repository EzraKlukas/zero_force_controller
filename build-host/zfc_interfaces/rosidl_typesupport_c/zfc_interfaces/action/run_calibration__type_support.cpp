// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from zfc_interfaces:action/RunCalibration.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "zfc_interfaces/action/detail/run_calibration__struct.h"
#include "zfc_interfaces/action/detail/run_calibration__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace zfc_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _RunCalibration_Goal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunCalibration_Goal_type_support_ids_t;

static const _RunCalibration_Goal_type_support_ids_t _RunCalibration_Goal_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _RunCalibration_Goal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _RunCalibration_Goal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _RunCalibration_Goal_type_support_symbol_names_t _RunCalibration_Goal_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, zfc_interfaces, action, RunCalibration_Goal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_Goal)),
  }
};

typedef struct _RunCalibration_Goal_type_support_data_t
{
  void * data[2];
} _RunCalibration_Goal_type_support_data_t;

static _RunCalibration_Goal_type_support_data_t _RunCalibration_Goal_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _RunCalibration_Goal_message_typesupport_map = {
  2,
  "zfc_interfaces",
  &_RunCalibration_Goal_message_typesupport_ids.typesupport_identifier[0],
  &_RunCalibration_Goal_message_typesupport_symbol_names.symbol_name[0],
  &_RunCalibration_Goal_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t RunCalibration_Goal_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunCalibration_Goal_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace zfc_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, zfc_interfaces, action, RunCalibration_Goal)() {
  return &::zfc_interfaces::action::rosidl_typesupport_c::RunCalibration_Goal_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace zfc_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _RunCalibration_Result_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunCalibration_Result_type_support_ids_t;

static const _RunCalibration_Result_type_support_ids_t _RunCalibration_Result_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _RunCalibration_Result_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _RunCalibration_Result_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _RunCalibration_Result_type_support_symbol_names_t _RunCalibration_Result_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, zfc_interfaces, action, RunCalibration_Result)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_Result)),
  }
};

typedef struct _RunCalibration_Result_type_support_data_t
{
  void * data[2];
} _RunCalibration_Result_type_support_data_t;

static _RunCalibration_Result_type_support_data_t _RunCalibration_Result_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _RunCalibration_Result_message_typesupport_map = {
  2,
  "zfc_interfaces",
  &_RunCalibration_Result_message_typesupport_ids.typesupport_identifier[0],
  &_RunCalibration_Result_message_typesupport_symbol_names.symbol_name[0],
  &_RunCalibration_Result_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t RunCalibration_Result_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunCalibration_Result_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace zfc_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, zfc_interfaces, action, RunCalibration_Result)() {
  return &::zfc_interfaces::action::rosidl_typesupport_c::RunCalibration_Result_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace zfc_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _RunCalibration_Feedback_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunCalibration_Feedback_type_support_ids_t;

static const _RunCalibration_Feedback_type_support_ids_t _RunCalibration_Feedback_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _RunCalibration_Feedback_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _RunCalibration_Feedback_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _RunCalibration_Feedback_type_support_symbol_names_t _RunCalibration_Feedback_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, zfc_interfaces, action, RunCalibration_Feedback)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_Feedback)),
  }
};

typedef struct _RunCalibration_Feedback_type_support_data_t
{
  void * data[2];
} _RunCalibration_Feedback_type_support_data_t;

static _RunCalibration_Feedback_type_support_data_t _RunCalibration_Feedback_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _RunCalibration_Feedback_message_typesupport_map = {
  2,
  "zfc_interfaces",
  &_RunCalibration_Feedback_message_typesupport_ids.typesupport_identifier[0],
  &_RunCalibration_Feedback_message_typesupport_symbol_names.symbol_name[0],
  &_RunCalibration_Feedback_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t RunCalibration_Feedback_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunCalibration_Feedback_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace zfc_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, zfc_interfaces, action, RunCalibration_Feedback)() {
  return &::zfc_interfaces::action::rosidl_typesupport_c::RunCalibration_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace zfc_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _RunCalibration_SendGoal_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunCalibration_SendGoal_Request_type_support_ids_t;

static const _RunCalibration_SendGoal_Request_type_support_ids_t _RunCalibration_SendGoal_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _RunCalibration_SendGoal_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _RunCalibration_SendGoal_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _RunCalibration_SendGoal_Request_type_support_symbol_names_t _RunCalibration_SendGoal_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, zfc_interfaces, action, RunCalibration_SendGoal_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_SendGoal_Request)),
  }
};

typedef struct _RunCalibration_SendGoal_Request_type_support_data_t
{
  void * data[2];
} _RunCalibration_SendGoal_Request_type_support_data_t;

static _RunCalibration_SendGoal_Request_type_support_data_t _RunCalibration_SendGoal_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _RunCalibration_SendGoal_Request_message_typesupport_map = {
  2,
  "zfc_interfaces",
  &_RunCalibration_SendGoal_Request_message_typesupport_ids.typesupport_identifier[0],
  &_RunCalibration_SendGoal_Request_message_typesupport_symbol_names.symbol_name[0],
  &_RunCalibration_SendGoal_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t RunCalibration_SendGoal_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunCalibration_SendGoal_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace zfc_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, zfc_interfaces, action, RunCalibration_SendGoal_Request)() {
  return &::zfc_interfaces::action::rosidl_typesupport_c::RunCalibration_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace zfc_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _RunCalibration_SendGoal_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunCalibration_SendGoal_Response_type_support_ids_t;

static const _RunCalibration_SendGoal_Response_type_support_ids_t _RunCalibration_SendGoal_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _RunCalibration_SendGoal_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _RunCalibration_SendGoal_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _RunCalibration_SendGoal_Response_type_support_symbol_names_t _RunCalibration_SendGoal_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, zfc_interfaces, action, RunCalibration_SendGoal_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_SendGoal_Response)),
  }
};

typedef struct _RunCalibration_SendGoal_Response_type_support_data_t
{
  void * data[2];
} _RunCalibration_SendGoal_Response_type_support_data_t;

static _RunCalibration_SendGoal_Response_type_support_data_t _RunCalibration_SendGoal_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _RunCalibration_SendGoal_Response_message_typesupport_map = {
  2,
  "zfc_interfaces",
  &_RunCalibration_SendGoal_Response_message_typesupport_ids.typesupport_identifier[0],
  &_RunCalibration_SendGoal_Response_message_typesupport_symbol_names.symbol_name[0],
  &_RunCalibration_SendGoal_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t RunCalibration_SendGoal_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunCalibration_SendGoal_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace zfc_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, zfc_interfaces, action, RunCalibration_SendGoal_Response)() {
  return &::zfc_interfaces::action::rosidl_typesupport_c::RunCalibration_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace zfc_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _RunCalibration_SendGoal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunCalibration_SendGoal_type_support_ids_t;

static const _RunCalibration_SendGoal_type_support_ids_t _RunCalibration_SendGoal_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _RunCalibration_SendGoal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _RunCalibration_SendGoal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _RunCalibration_SendGoal_type_support_symbol_names_t _RunCalibration_SendGoal_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, zfc_interfaces, action, RunCalibration_SendGoal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_SendGoal)),
  }
};

typedef struct _RunCalibration_SendGoal_type_support_data_t
{
  void * data[2];
} _RunCalibration_SendGoal_type_support_data_t;

static _RunCalibration_SendGoal_type_support_data_t _RunCalibration_SendGoal_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _RunCalibration_SendGoal_service_typesupport_map = {
  2,
  "zfc_interfaces",
  &_RunCalibration_SendGoal_service_typesupport_ids.typesupport_identifier[0],
  &_RunCalibration_SendGoal_service_typesupport_symbol_names.symbol_name[0],
  &_RunCalibration_SendGoal_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t RunCalibration_SendGoal_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunCalibration_SendGoal_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace zfc_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, zfc_interfaces, action, RunCalibration_SendGoal)() {
  return &::zfc_interfaces::action::rosidl_typesupport_c::RunCalibration_SendGoal_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace zfc_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _RunCalibration_GetResult_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunCalibration_GetResult_Request_type_support_ids_t;

static const _RunCalibration_GetResult_Request_type_support_ids_t _RunCalibration_GetResult_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _RunCalibration_GetResult_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _RunCalibration_GetResult_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _RunCalibration_GetResult_Request_type_support_symbol_names_t _RunCalibration_GetResult_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, zfc_interfaces, action, RunCalibration_GetResult_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_GetResult_Request)),
  }
};

typedef struct _RunCalibration_GetResult_Request_type_support_data_t
{
  void * data[2];
} _RunCalibration_GetResult_Request_type_support_data_t;

static _RunCalibration_GetResult_Request_type_support_data_t _RunCalibration_GetResult_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _RunCalibration_GetResult_Request_message_typesupport_map = {
  2,
  "zfc_interfaces",
  &_RunCalibration_GetResult_Request_message_typesupport_ids.typesupport_identifier[0],
  &_RunCalibration_GetResult_Request_message_typesupport_symbol_names.symbol_name[0],
  &_RunCalibration_GetResult_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t RunCalibration_GetResult_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunCalibration_GetResult_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace zfc_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, zfc_interfaces, action, RunCalibration_GetResult_Request)() {
  return &::zfc_interfaces::action::rosidl_typesupport_c::RunCalibration_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace zfc_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _RunCalibration_GetResult_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunCalibration_GetResult_Response_type_support_ids_t;

static const _RunCalibration_GetResult_Response_type_support_ids_t _RunCalibration_GetResult_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _RunCalibration_GetResult_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _RunCalibration_GetResult_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _RunCalibration_GetResult_Response_type_support_symbol_names_t _RunCalibration_GetResult_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, zfc_interfaces, action, RunCalibration_GetResult_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_GetResult_Response)),
  }
};

typedef struct _RunCalibration_GetResult_Response_type_support_data_t
{
  void * data[2];
} _RunCalibration_GetResult_Response_type_support_data_t;

static _RunCalibration_GetResult_Response_type_support_data_t _RunCalibration_GetResult_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _RunCalibration_GetResult_Response_message_typesupport_map = {
  2,
  "zfc_interfaces",
  &_RunCalibration_GetResult_Response_message_typesupport_ids.typesupport_identifier[0],
  &_RunCalibration_GetResult_Response_message_typesupport_symbol_names.symbol_name[0],
  &_RunCalibration_GetResult_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t RunCalibration_GetResult_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunCalibration_GetResult_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace zfc_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, zfc_interfaces, action, RunCalibration_GetResult_Response)() {
  return &::zfc_interfaces::action::rosidl_typesupport_c::RunCalibration_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace zfc_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _RunCalibration_GetResult_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunCalibration_GetResult_type_support_ids_t;

static const _RunCalibration_GetResult_type_support_ids_t _RunCalibration_GetResult_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _RunCalibration_GetResult_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _RunCalibration_GetResult_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _RunCalibration_GetResult_type_support_symbol_names_t _RunCalibration_GetResult_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, zfc_interfaces, action, RunCalibration_GetResult)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_GetResult)),
  }
};

typedef struct _RunCalibration_GetResult_type_support_data_t
{
  void * data[2];
} _RunCalibration_GetResult_type_support_data_t;

static _RunCalibration_GetResult_type_support_data_t _RunCalibration_GetResult_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _RunCalibration_GetResult_service_typesupport_map = {
  2,
  "zfc_interfaces",
  &_RunCalibration_GetResult_service_typesupport_ids.typesupport_identifier[0],
  &_RunCalibration_GetResult_service_typesupport_symbol_names.symbol_name[0],
  &_RunCalibration_GetResult_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t RunCalibration_GetResult_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunCalibration_GetResult_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace zfc_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, zfc_interfaces, action, RunCalibration_GetResult)() {
  return &::zfc_interfaces::action::rosidl_typesupport_c::RunCalibration_GetResult_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace zfc_interfaces
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _RunCalibration_FeedbackMessage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunCalibration_FeedbackMessage_type_support_ids_t;

static const _RunCalibration_FeedbackMessage_type_support_ids_t _RunCalibration_FeedbackMessage_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _RunCalibration_FeedbackMessage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _RunCalibration_FeedbackMessage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _RunCalibration_FeedbackMessage_type_support_symbol_names_t _RunCalibration_FeedbackMessage_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, zfc_interfaces, action, RunCalibration_FeedbackMessage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zfc_interfaces, action, RunCalibration_FeedbackMessage)),
  }
};

typedef struct _RunCalibration_FeedbackMessage_type_support_data_t
{
  void * data[2];
} _RunCalibration_FeedbackMessage_type_support_data_t;

static _RunCalibration_FeedbackMessage_type_support_data_t _RunCalibration_FeedbackMessage_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _RunCalibration_FeedbackMessage_message_typesupport_map = {
  2,
  "zfc_interfaces",
  &_RunCalibration_FeedbackMessage_message_typesupport_ids.typesupport_identifier[0],
  &_RunCalibration_FeedbackMessage_message_typesupport_symbol_names.symbol_name[0],
  &_RunCalibration_FeedbackMessage_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t RunCalibration_FeedbackMessage_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunCalibration_FeedbackMessage_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace zfc_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, zfc_interfaces, action, RunCalibration_FeedbackMessage)() {
  return &::zfc_interfaces::action::rosidl_typesupport_c::RunCalibration_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "action_msgs/msg/goal_status_array.h"
#include "action_msgs/srv/cancel_goal.h"
#include "zfc_interfaces/action/run_calibration.h"
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__type_support.h"

static rosidl_action_type_support_t _zfc_interfaces__action__RunCalibration__typesupport_c;

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(
  rosidl_typesupport_c, zfc_interfaces, action, RunCalibration)()
{
  // Thread-safe by always writing the same values to the static struct
  _zfc_interfaces__action__RunCalibration__typesupport_c.goal_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, zfc_interfaces, action, RunCalibration_SendGoal)();
  _zfc_interfaces__action__RunCalibration__typesupport_c.result_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, zfc_interfaces, action, RunCalibration_GetResult)();
  _zfc_interfaces__action__RunCalibration__typesupport_c.cancel_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, action_msgs, srv, CancelGoal)();
  _zfc_interfaces__action__RunCalibration__typesupport_c.feedback_message_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, zfc_interfaces, action, RunCalibration_FeedbackMessage)();
  _zfc_interfaces__action__RunCalibration__typesupport_c.status_message_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, action_msgs, msg, GoalStatusArray)();

  return &_zfc_interfaces__action__RunCalibration__typesupport_c;
}

#ifdef __cplusplus
}
#endif
