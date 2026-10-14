// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from zfc_interfaces:msg/TelemetryBatch.idl
// generated code does not contain a copyright notice
#include "zfc_interfaces/msg/detail/telemetry_batch__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `samples`
#include "zfc_interfaces/msg/detail/controller_state__functions.h"

bool
zfc_interfaces__msg__TelemetryBatch__init(zfc_interfaces__msg__TelemetryBatch * msg)
{
  if (!msg) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    zfc_interfaces__msg__TelemetryBatch__fini(msg);
    return false;
  }
  // samples
  if (!zfc_interfaces__msg__ControllerState__Sequence__init(&msg->samples, 0)) {
    zfc_interfaces__msg__TelemetryBatch__fini(msg);
    return false;
  }
  // dropped_samples
  // failed_publication_samples
  return true;
}

void
zfc_interfaces__msg__TelemetryBatch__fini(zfc_interfaces__msg__TelemetryBatch * msg)
{
  if (!msg) {
    return;
  }
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // samples
  zfc_interfaces__msg__ControllerState__Sequence__fini(&msg->samples);
  // dropped_samples
  // failed_publication_samples
}

bool
zfc_interfaces__msg__TelemetryBatch__are_equal(const zfc_interfaces__msg__TelemetryBatch * lhs, const zfc_interfaces__msg__TelemetryBatch * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  // samples
  if (!zfc_interfaces__msg__ControllerState__Sequence__are_equal(
      &(lhs->samples), &(rhs->samples)))
  {
    return false;
  }
  // dropped_samples
  if (lhs->dropped_samples != rhs->dropped_samples) {
    return false;
  }
  // failed_publication_samples
  if (lhs->failed_publication_samples != rhs->failed_publication_samples) {
    return false;
  }
  return true;
}

bool
zfc_interfaces__msg__TelemetryBatch__copy(
  const zfc_interfaces__msg__TelemetryBatch * input,
  zfc_interfaces__msg__TelemetryBatch * output)
{
  if (!input || !output) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  // samples
  if (!zfc_interfaces__msg__ControllerState__Sequence__copy(
      &(input->samples), &(output->samples)))
  {
    return false;
  }
  // dropped_samples
  output->dropped_samples = input->dropped_samples;
  // failed_publication_samples
  output->failed_publication_samples = input->failed_publication_samples;
  return true;
}

zfc_interfaces__msg__TelemetryBatch *
zfc_interfaces__msg__TelemetryBatch__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__TelemetryBatch * msg = (zfc_interfaces__msg__TelemetryBatch *)allocator.allocate(sizeof(zfc_interfaces__msg__TelemetryBatch), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__msg__TelemetryBatch));
  bool success = zfc_interfaces__msg__TelemetryBatch__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__msg__TelemetryBatch__destroy(zfc_interfaces__msg__TelemetryBatch * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__msg__TelemetryBatch__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__msg__TelemetryBatch__Sequence__init(zfc_interfaces__msg__TelemetryBatch__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__TelemetryBatch * data = NULL;

  if (size) {
    data = (zfc_interfaces__msg__TelemetryBatch *)allocator.zero_allocate(size, sizeof(zfc_interfaces__msg__TelemetryBatch), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__msg__TelemetryBatch__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__msg__TelemetryBatch__fini(&data[i - 1]);
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
zfc_interfaces__msg__TelemetryBatch__Sequence__fini(zfc_interfaces__msg__TelemetryBatch__Sequence * array)
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
      zfc_interfaces__msg__TelemetryBatch__fini(&array->data[i]);
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

zfc_interfaces__msg__TelemetryBatch__Sequence *
zfc_interfaces__msg__TelemetryBatch__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__TelemetryBatch__Sequence * array = (zfc_interfaces__msg__TelemetryBatch__Sequence *)allocator.allocate(sizeof(zfc_interfaces__msg__TelemetryBatch__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__msg__TelemetryBatch__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__msg__TelemetryBatch__Sequence__destroy(zfc_interfaces__msg__TelemetryBatch__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__msg__TelemetryBatch__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__msg__TelemetryBatch__Sequence__are_equal(const zfc_interfaces__msg__TelemetryBatch__Sequence * lhs, const zfc_interfaces__msg__TelemetryBatch__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__msg__TelemetryBatch__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__msg__TelemetryBatch__Sequence__copy(
  const zfc_interfaces__msg__TelemetryBatch__Sequence * input,
  zfc_interfaces__msg__TelemetryBatch__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__msg__TelemetryBatch);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__msg__TelemetryBatch * data =
      (zfc_interfaces__msg__TelemetryBatch *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__msg__TelemetryBatch__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__msg__TelemetryBatch__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__msg__TelemetryBatch__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
