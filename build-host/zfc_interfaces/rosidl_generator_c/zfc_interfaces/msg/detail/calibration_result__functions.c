// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from zfc_interfaces:msg/CalibrationResult.idl
// generated code does not contain a copyright notice
#include "zfc_interfaces/msg/detail/calibration_result__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `reason`
// Member `acceleration_source`
#include "rosidl_runtime_c/string_functions.h"

bool
zfc_interfaces__msg__CalibrationResult__init(zfc_interfaces__msg__CalibrationResult * msg)
{
  if (!msg) {
    return false;
  }
  // valid
  // reason
  if (!rosidl_runtime_c__String__init(&msg->reason)) {
    zfc_interfaces__msg__CalibrationResult__fini(msg);
    return false;
  }
  // inertial_force_coefficient_kg
  // intercept_n
  // r_squared
  // residual_rms_n
  // uncertainty_kg
  // sample_count
  // plateau_count
  // positive_slope_kg
  // negative_slope_kg
  // tracking_rms_m
  // acceleration_source
  if (!rosidl_runtime_c__String__init(&msg->acceleration_source)) {
    zfc_interfaces__msg__CalibrationResult__fini(msg);
    return false;
  }
  return true;
}

void
zfc_interfaces__msg__CalibrationResult__fini(zfc_interfaces__msg__CalibrationResult * msg)
{
  if (!msg) {
    return;
  }
  // valid
  // reason
  rosidl_runtime_c__String__fini(&msg->reason);
  // inertial_force_coefficient_kg
  // intercept_n
  // r_squared
  // residual_rms_n
  // uncertainty_kg
  // sample_count
  // plateau_count
  // positive_slope_kg
  // negative_slope_kg
  // tracking_rms_m
  // acceleration_source
  rosidl_runtime_c__String__fini(&msg->acceleration_source);
}

bool
zfc_interfaces__msg__CalibrationResult__are_equal(const zfc_interfaces__msg__CalibrationResult * lhs, const zfc_interfaces__msg__CalibrationResult * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // valid
  if (lhs->valid != rhs->valid) {
    return false;
  }
  // reason
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->reason), &(rhs->reason)))
  {
    return false;
  }
  // inertial_force_coefficient_kg
  if (lhs->inertial_force_coefficient_kg != rhs->inertial_force_coefficient_kg) {
    return false;
  }
  // intercept_n
  if (lhs->intercept_n != rhs->intercept_n) {
    return false;
  }
  // r_squared
  if (lhs->r_squared != rhs->r_squared) {
    return false;
  }
  // residual_rms_n
  if (lhs->residual_rms_n != rhs->residual_rms_n) {
    return false;
  }
  // uncertainty_kg
  if (lhs->uncertainty_kg != rhs->uncertainty_kg) {
    return false;
  }
  // sample_count
  if (lhs->sample_count != rhs->sample_count) {
    return false;
  }
  // plateau_count
  if (lhs->plateau_count != rhs->plateau_count) {
    return false;
  }
  // positive_slope_kg
  if (lhs->positive_slope_kg != rhs->positive_slope_kg) {
    return false;
  }
  // negative_slope_kg
  if (lhs->negative_slope_kg != rhs->negative_slope_kg) {
    return false;
  }
  // tracking_rms_m
  if (lhs->tracking_rms_m != rhs->tracking_rms_m) {
    return false;
  }
  // acceleration_source
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->acceleration_source), &(rhs->acceleration_source)))
  {
    return false;
  }
  return true;
}

bool
zfc_interfaces__msg__CalibrationResult__copy(
  const zfc_interfaces__msg__CalibrationResult * input,
  zfc_interfaces__msg__CalibrationResult * output)
{
  if (!input || !output) {
    return false;
  }
  // valid
  output->valid = input->valid;
  // reason
  if (!rosidl_runtime_c__String__copy(
      &(input->reason), &(output->reason)))
  {
    return false;
  }
  // inertial_force_coefficient_kg
  output->inertial_force_coefficient_kg = input->inertial_force_coefficient_kg;
  // intercept_n
  output->intercept_n = input->intercept_n;
  // r_squared
  output->r_squared = input->r_squared;
  // residual_rms_n
  output->residual_rms_n = input->residual_rms_n;
  // uncertainty_kg
  output->uncertainty_kg = input->uncertainty_kg;
  // sample_count
  output->sample_count = input->sample_count;
  // plateau_count
  output->plateau_count = input->plateau_count;
  // positive_slope_kg
  output->positive_slope_kg = input->positive_slope_kg;
  // negative_slope_kg
  output->negative_slope_kg = input->negative_slope_kg;
  // tracking_rms_m
  output->tracking_rms_m = input->tracking_rms_m;
  // acceleration_source
  if (!rosidl_runtime_c__String__copy(
      &(input->acceleration_source), &(output->acceleration_source)))
  {
    return false;
  }
  return true;
}

zfc_interfaces__msg__CalibrationResult *
zfc_interfaces__msg__CalibrationResult__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__CalibrationResult * msg = (zfc_interfaces__msg__CalibrationResult *)allocator.allocate(sizeof(zfc_interfaces__msg__CalibrationResult), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__msg__CalibrationResult));
  bool success = zfc_interfaces__msg__CalibrationResult__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__msg__CalibrationResult__destroy(zfc_interfaces__msg__CalibrationResult * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__msg__CalibrationResult__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__msg__CalibrationResult__Sequence__init(zfc_interfaces__msg__CalibrationResult__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__CalibrationResult * data = NULL;

  if (size) {
    data = (zfc_interfaces__msg__CalibrationResult *)allocator.zero_allocate(size, sizeof(zfc_interfaces__msg__CalibrationResult), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__msg__CalibrationResult__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__msg__CalibrationResult__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
zfc_interfaces__msg__CalibrationResult__Sequence__fini(zfc_interfaces__msg__CalibrationResult__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      zfc_interfaces__msg__CalibrationResult__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

zfc_interfaces__msg__CalibrationResult__Sequence *
zfc_interfaces__msg__CalibrationResult__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__CalibrationResult__Sequence * array = (zfc_interfaces__msg__CalibrationResult__Sequence *)allocator.allocate(sizeof(zfc_interfaces__msg__CalibrationResult__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__msg__CalibrationResult__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__msg__CalibrationResult__Sequence__destroy(zfc_interfaces__msg__CalibrationResult__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__msg__CalibrationResult__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__msg__CalibrationResult__Sequence__are_equal(const zfc_interfaces__msg__CalibrationResult__Sequence * lhs, const zfc_interfaces__msg__CalibrationResult__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__msg__CalibrationResult__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__msg__CalibrationResult__Sequence__copy(
  const zfc_interfaces__msg__CalibrationResult__Sequence * input,
  zfc_interfaces__msg__CalibrationResult__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__msg__CalibrationResult);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__msg__CalibrationResult * data =
      (zfc_interfaces__msg__CalibrationResult *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__msg__CalibrationResult__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__msg__CalibrationResult__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__msg__CalibrationResult__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
