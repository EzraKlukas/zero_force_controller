// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from zfc_interfaces:msg/MeasuredState.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "zfc_interfaces/msg/detail/measured_state__struct.h"
#include "zfc_interfaces/msg/detail/measured_state__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool builtin_interfaces__msg__time__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * builtin_interfaces__msg__time__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool zfc_interfaces__msg__measured_state__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[49];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("zfc_interfaces.msg._measured_state.MeasuredState", full_classname_dest, 48) == 0);
  }
  zfc_interfaces__msg__MeasuredState * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // force_stamp
    PyObject * field = PyObject_GetAttrString(_pymsg, "force_stamp");
    if (!field) {
      return false;
    }
    if (!builtin_interfaces__msg__time__convert_from_py(field, &ros_message->force_stamp)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // position_m
    PyObject * field = PyObject_GetAttrString(_pymsg, "position_m");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->position_m = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // velocity_mps
    PyObject * field = PyObject_GetAttrString(_pymsg, "velocity_mps");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->velocity_mps = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // force_n
    PyObject * field = PyObject_GetAttrString(_pymsg, "force_n");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->force_n = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // joint_fresh
    PyObject * field = PyObject_GetAttrString(_pymsg, "joint_fresh");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->joint_fresh = (Py_True == field);
    Py_DECREF(field);
  }
  {  // force_fresh
    PyObject * field = PyObject_GetAttrString(_pymsg, "force_fresh");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->force_fresh = (Py_True == field);
    Py_DECREF(field);
  }
  {  // valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // detail
    PyObject * field = PyObject_GetAttrString(_pymsg, "detail");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->detail, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * zfc_interfaces__msg__measured_state__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of MeasuredState */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("zfc_interfaces.msg._measured_state");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "MeasuredState");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  zfc_interfaces__msg__MeasuredState * ros_message = (zfc_interfaces__msg__MeasuredState *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // force_stamp
    PyObject * field = NULL;
    field = builtin_interfaces__msg__time__convert_to_py(&ros_message->force_stamp);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "force_stamp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // position_m
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->position_m);
    {
      int rc = PyObject_SetAttrString(_pymessage, "position_m", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // velocity_mps
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->velocity_mps);
    {
      int rc = PyObject_SetAttrString(_pymessage, "velocity_mps", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // force_n
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->force_n);
    {
      int rc = PyObject_SetAttrString(_pymessage, "force_n", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // joint_fresh
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->joint_fresh ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "joint_fresh", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // force_fresh
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->force_fresh ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "force_fresh", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // detail
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->detail.data,
      strlen(ros_message->detail.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "detail", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
