// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from zfc_interfaces:msg/TrialStatus.idl
// generated code does not contain a copyright notice
#include "zfc_interfaces/msg/detail/trial_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
zfc_interfaces__msg__TrialStatus__init(zfc_interfaces__msg__TrialStatus * msg)
{
  if (!msg) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    zfc_interfaces__msg__TrialStatus__fini(msg);
    return false;
  }
  // trial_id
  // final_sequence
  // dropped_samples
  // failed_publication_samples
  // phase
  // fault_code
  // completed
  // successful
  // capture_complete
  return true;
}

void
zfc_interfaces__msg__TrialStatus__fini(zfc_interfaces__msg__TrialStatus * msg)
{
  if (!msg) {
    return;
  }
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // trial_id
  // final_sequence
  // dropped_samples
  // failed_publication_samples
  // phase
  // fault_code
  // completed
  // successful
  // capture_complete
}

bool
zfc_interfaces__msg__TrialStatus__are_equal(const zfc_interfaces__msg__TrialStatus * lhs, const zfc_interfaces__msg__TrialStatus * rhs)
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
  // trial_id
  if (lhs->trial_id != rhs->trial_id) {
    return false;
  }
  // final_sequence
  if (lhs->final_sequence != rhs->final_sequence) {
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
  // phase
  if (lhs->phase != rhs->phase) {
    return false;
  }
  // fault_code
  if (lhs->fault_code != rhs->fault_code) {
    return false;
  }
  // completed
  if (lhs->completed != rhs->completed) {
    return false;
  }
  // successful
  if (lhs->successful != rhs->successful) {
    return false;
  }
  // capture_complete
  if (lhs->capture_complete != rhs->capture_complete) {
    return false;
  }
  return true;
}

bool
zfc_interfaces__msg__TrialStatus__copy(
  const zfc_interfaces__msg__TrialStatus * input,
  zfc_interfaces__msg__TrialStatus * output)
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
  // trial_id
  output->trial_id = input->trial_id;
  // final_sequence
  output->final_sequence = input->final_sequence;
  // dropped_samples
  output->dropped_samples = input->dropped_samples;
  // failed_publication_samples
  output->failed_publication_samples = input->failed_publication_samples;
  // phase
  output->phase = input->phase;
  // fault_code
  output->fault_code = input->fault_code;
  // completed
  output->completed = input->completed;
  // successful
  output->successful = input->successful;
  // capture_complete
  output->capture_complete = input->capture_complete;
  return true;
}

zfc_interfaces__msg__TrialStatus *
zfc_interfaces__msg__TrialStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__TrialStatus * msg = (zfc_interfaces__msg__TrialStatus *)allocator.allocate(sizeof(zfc_interfaces__msg__TrialStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__msg__TrialStatus));
  bool success = zfc_interfaces__msg__TrialStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__msg__TrialStatus__destroy(zfc_interfaces__msg__TrialStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__msg__TrialStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__msg__TrialStatus__Sequence__init(zfc_interfaces__msg__TrialStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__TrialStatus * data = NULL;

  if (size) {
    data = (zfc_interfaces__msg__TrialStatus *)allocator.zero_allocate(size, sizeof(zfc_interfaces__msg__TrialStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__msg__TrialStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__msg__TrialStatus__fini(&data[i - 1]);
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
zfc_interfaces__msg__TrialStatus__Sequence__fini(zfc_interfaces__msg__TrialStatus__Sequence * array)
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
      zfc_interfaces__msg__TrialStatus__fini(&array->data[i]);
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

zfc_interfaces__msg__TrialStatus__Sequence *
zfc_interfaces__msg__TrialStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__TrialStatus__Sequence * array = (zfc_interfaces__msg__TrialStatus__Sequence *)allocator.allocate(sizeof(zfc_interfaces__msg__TrialStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__msg__TrialStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__msg__TrialStatus__Sequence__destroy(zfc_interfaces__msg__TrialStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__msg__TrialStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__msg__TrialStatus__Sequence__are_equal(const zfc_interfaces__msg__TrialStatus__Sequence * lhs, const zfc_interfaces__msg__TrialStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__msg__TrialStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__msg__TrialStatus__Sequence__copy(
  const zfc_interfaces__msg__TrialStatus__Sequence * input,
  zfc_interfaces__msg__TrialStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__msg__TrialStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__msg__TrialStatus * data =
      (zfc_interfaces__msg__TrialStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__msg__TrialStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__msg__TrialStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__msg__TrialStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
