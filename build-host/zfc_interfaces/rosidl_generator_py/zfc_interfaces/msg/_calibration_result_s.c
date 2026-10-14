// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from zfc_interfaces:msg/CalibrationResult.idl
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
#include "zfc_interfaces/msg/detail/calibration_result__struct.h"
#include "zfc_interfaces/msg/detail/calibration_result__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool zfc_interfaces__msg__calibration_result__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[57];
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
    assert(strncmp("zfc_interfaces.msg._calibration_result.CalibrationResult", full_classname_dest, 56) == 0);
  }
  zfc_interfaces__msg__CalibrationResult * ros_message = _ros_message;
  {  // valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // reason
    PyObject * field = PyObject_GetAttrString(_pymsg, "reason");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->reason, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // inertial_force_coefficient_kg
    PyObject * field = PyObject_GetAttrString(_pymsg, "inertial_force_coefficient_kg");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->inertial_force_coefficient_kg = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // intercept_n
    PyObject * field = PyObject_GetAttrString(_pymsg, "intercept_n");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->intercept_n = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // r_squared
    PyObject * field = PyObject_GetAttrString(_pymsg, "r_squared");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->r_squared = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // residual_rms_n
    PyObject * field = PyObject_GetAttrString(_pymsg, "residual_rms_n");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->residual_rms_n = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // uncertainty_kg
    PyObject * field = PyObject_GetAttrString(_pymsg, "uncertainty_kg");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->uncertainty_kg = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // sample_count
    PyObject * field = PyObject_GetAttrString(_pymsg, "sample_count");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->sample_count = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // plateau_count
    PyObject * field = PyObject_GetAttrString(_pymsg, "plateau_count");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->plateau_count = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // positive_slope_kg
    PyObject * field = PyObject_GetAttrString(_pymsg, "positive_slope_kg");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->positive_slope_kg = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // negative_slope_kg
    PyObject * field = PyObject_GetAttrString(_pymsg, "negative_slope_kg");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->negative_slope_kg = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // tracking_rms_m
    PyObject * field = PyObject_GetAttrString(_pymsg, "tracking_rms_m");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->tracking_rms_m = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // acceleration_source
    PyObject * field = PyObject_GetAttrString(_pymsg, "acceleration_source");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->acceleration_source, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * zfc_interfaces__msg__calibration_result__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of CalibrationResult */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("zfc_interfaces.msg._calibration_result");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "CalibrationResult");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  zfc_interfaces__msg__CalibrationResult * ros_message = (zfc_interfaces__msg__CalibrationResult *)raw_ros_message;
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
  {  // reason
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->reason.data,
      strlen(ros_message->reason.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "reason", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // inertial_force_coefficient_kg
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->inertial_force_coefficient_kg);
    {
      int rc = PyObject_SetAttrString(_pymessage, "inertial_force_coefficient_kg", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // intercept_n
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->intercept_n);
    {
      int rc = PyObject_SetAttrString(_pymessage, "intercept_n", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // r_squared
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->r_squared);
    {
      int rc = PyObject_SetAttrString(_pymessage, "r_squared", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // residual_rms_n
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->residual_rms_n);
    {
      int rc = PyObject_SetAttrString(_pymessage, "residual_rms_n", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // uncertainty_kg
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->uncertainty_kg);
    {
      int rc = PyObject_SetAttrString(_pymessage, "uncertainty_kg", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // sample_count
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->sample_count);
    {
      int rc = PyObject_SetAttrString(_pymessage, "sample_count", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // plateau_count
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->plateau_count);
    {
      int rc = PyObject_SetAttrString(_pymessage, "plateau_count", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // positive_slope_kg
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->positive_slope_kg);
    {
      int rc = PyObject_SetAttrString(_pymessage, "positive_slope_kg", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // negative_slope_kg
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->negative_slope_kg);
    {
      int rc = PyObject_SetAttrString(_pymessage, "negative_slope_kg", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // tracking_rms_m
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->tracking_rms_m);
    {
      int rc = PyObject_SetAttrString(_pymessage, "tracking_rms_m", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // acceleration_source
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->acceleration_source.data,
      strlen(ros_message->acceleration_source.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "acceleration_source", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
