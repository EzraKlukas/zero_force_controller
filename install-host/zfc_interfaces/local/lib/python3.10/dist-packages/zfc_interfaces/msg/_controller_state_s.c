// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from zfc_interfaces:msg/ControllerState.idl
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
#include "zfc_interfaces/msg/detail/controller_state__struct.h"
#include "zfc_interfaces/msg/detail/controller_state__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool builtin_interfaces__msg__time__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * builtin_interfaces__msg__time__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool zfc_interfaces__msg__controller_state__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[53];
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
    assert(strncmp("zfc_interfaces.msg._controller_state.ControllerState", full_classname_dest, 52) == 0);
  }
  zfc_interfaces__msg__ControllerState * ros_message = _ros_message;
  {  // stamp
    PyObject * field = PyObject_GetAttrString(_pymsg, "stamp");
    if (!field) {
      return false;
    }
    if (!builtin_interfaces__msg__time__convert_from_py(field, &ros_message->stamp)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // trial_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "trial_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->trial_id = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // sequence
    PyObject * field = PyObject_GetAttrString(_pymsg, "sequence");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->sequence = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // phase
    PyObject * field = PyObject_GetAttrString(_pymsg, "phase");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->phase = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // fault_code
    PyObject * field = PyObject_GetAttrString(_pymsg, "fault_code");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->fault_code = (uint8_t)PyLong_AsUnsignedLong(field);
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
  {  // reference_position_m
    PyObject * field = PyObject_GetAttrString(_pymsg, "reference_position_m");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->reference_position_m = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // reference_velocity_mps
    PyObject * field = PyObject_GetAttrString(_pymsg, "reference_velocity_mps");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->reference_velocity_mps = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // reference_acceleration_mps2
    PyObject * field = PyObject_GetAttrString(_pymsg, "reference_acceleration_mps2");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->reference_acceleration_mps2 = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // baseline_force_n
    PyObject * field = PyObject_GetAttrString(_pymsg, "baseline_force_n");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->baseline_force_n = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // noise_rms_n
    PyObject * field = PyObject_GetAttrString(_pymsg, "noise_rms_n");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->noise_rms_n = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // residual_force_n
    PyObject * field = PyObject_GetAttrString(_pymsg, "residual_force_n");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->residual_force_n = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // progress
    PyObject * field = PyObject_GetAttrString(_pymsg, "progress");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->progress = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // excessive_periods
    PyObject * field = PyObject_GetAttrString(_pymsg, "excessive_periods");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->excessive_periods = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * zfc_interfaces__msg__controller_state__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of ControllerState */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("zfc_interfaces.msg._controller_state");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "ControllerState");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  zfc_interfaces__msg__ControllerState * ros_message = (zfc_interfaces__msg__ControllerState *)raw_ros_message;
  {  // stamp
    PyObject * field = NULL;
    field = builtin_interfaces__msg__time__convert_to_py(&ros_message->stamp);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "stamp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // trial_id
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->trial_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "trial_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // sequence
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->sequence);
    {
      int rc = PyObject_SetAttrString(_pymessage, "sequence", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // phase
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->phase);
    {
      int rc = PyObject_SetAttrString(_pymessage, "phase", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // fault_code
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->fault_code);
    {
      int rc = PyObject_SetAttrString(_pymessage, "fault_code", field);
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
  {  // reference_position_m
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->reference_position_m);
    {
      int rc = PyObject_SetAttrString(_pymessage, "reference_position_m", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // reference_velocity_mps
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->reference_velocity_mps);
    {
      int rc = PyObject_SetAttrString(_pymessage, "reference_velocity_mps", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // reference_acceleration_mps2
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->reference_acceleration_mps2);
    {
      int rc = PyObject_SetAttrString(_pymessage, "reference_acceleration_mps2", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // baseline_force_n
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->baseline_force_n);
    {
      int rc = PyObject_SetAttrString(_pymessage, "baseline_force_n", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // noise_rms_n
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->noise_rms_n);
    {
      int rc = PyObject_SetAttrString(_pymessage, "noise_rms_n", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // residual_force_n
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->residual_force_n);
    {
      int rc = PyObject_SetAttrString(_pymessage, "residual_force_n", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // progress
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->progress);
    {
      int rc = PyObject_SetAttrString(_pymessage, "progress", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // excessive_periods
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->excessive_periods);
    {
      int rc = PyObject_SetAttrString(_pymessage, "excessive_periods", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
