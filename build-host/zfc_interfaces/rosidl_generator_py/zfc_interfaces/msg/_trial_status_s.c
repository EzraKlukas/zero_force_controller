// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from zfc_interfaces:msg/TrialStatus.idl
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
#include "zfc_interfaces/msg/detail/trial_status__struct.h"
#include "zfc_interfaces/msg/detail/trial_status__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool builtin_interfaces__msg__time__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * builtin_interfaces__msg__time__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool zfc_interfaces__msg__trial_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[45];
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
    assert(strncmp("zfc_interfaces.msg._trial_status.TrialStatus", full_classname_dest, 44) == 0);
  }
  zfc_interfaces__msg__TrialStatus * ros_message = _ros_message;
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
  {  // final_sequence
    PyObject * field = PyObject_GetAttrString(_pymsg, "final_sequence");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->final_sequence = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // dropped_samples
    PyObject * field = PyObject_GetAttrString(_pymsg, "dropped_samples");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->dropped_samples = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // failed_publication_samples
    PyObject * field = PyObject_GetAttrString(_pymsg, "failed_publication_samples");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->failed_publication_samples = PyLong_AsUnsignedLongLong(field);
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
  {  // completed
    PyObject * field = PyObject_GetAttrString(_pymsg, "completed");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->completed = (Py_True == field);
    Py_DECREF(field);
  }
  {  // successful
    PyObject * field = PyObject_GetAttrString(_pymsg, "successful");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->successful = (Py_True == field);
    Py_DECREF(field);
  }
  {  // capture_complete
    PyObject * field = PyObject_GetAttrString(_pymsg, "capture_complete");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->capture_complete = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * zfc_interfaces__msg__trial_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of TrialStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("zfc_interfaces.msg._trial_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "TrialStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  zfc_interfaces__msg__TrialStatus * ros_message = (zfc_interfaces__msg__TrialStatus *)raw_ros_message;
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
  {  // final_sequence
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->final_sequence);
    {
      int rc = PyObject_SetAttrString(_pymessage, "final_sequence", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // dropped_samples
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->dropped_samples);
    {
      int rc = PyObject_SetAttrString(_pymessage, "dropped_samples", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // failed_publication_samples
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->failed_publication_samples);
    {
      int rc = PyObject_SetAttrString(_pymessage, "failed_publication_samples", field);
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
  {  // completed
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->completed ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "completed", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // successful
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->successful ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "successful", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // capture_complete
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->capture_complete ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "capture_complete", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
