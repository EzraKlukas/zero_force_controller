// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from zfc_interfaces:action/RunCalibration.idl
// generated code does not contain a copyright notice
#include "zfc_interfaces/action/detail/run_calibration__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
zfc_interfaces__action__RunCalibration_Goal__init(zfc_interfaces__action__RunCalibration_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // activate_zero_force_after
  // external_contact_clear
  return true;
}

void
zfc_interfaces__action__RunCalibration_Goal__fini(zfc_interfaces__action__RunCalibration_Goal * msg)
{
  if (!msg) {
    return;
  }
  // activate_zero_force_after
  // external_contact_clear
}

bool
zfc_interfaces__action__RunCalibration_Goal__are_equal(const zfc_interfaces__action__RunCalibration_Goal * lhs, const zfc_interfaces__action__RunCalibration_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // activate_zero_force_after
  if (lhs->activate_zero_force_after != rhs->activate_zero_force_after) {
    return false;
  }
  // external_contact_clear
  if (lhs->external_contact_clear != rhs->external_contact_clear) {
    return false;
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_Goal__copy(
  const zfc_interfaces__action__RunCalibration_Goal * input,
  zfc_interfaces__action__RunCalibration_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // activate_zero_force_after
  output->activate_zero_force_after = input->activate_zero_force_after;
  // external_contact_clear
  output->external_contact_clear = input->external_contact_clear;
  return true;
}

zfc_interfaces__action__RunCalibration_Goal *
zfc_interfaces__action__RunCalibration_Goal__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_Goal * msg = (zfc_interfaces__action__RunCalibration_Goal *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__action__RunCalibration_Goal));
  bool success = zfc_interfaces__action__RunCalibration_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__action__RunCalibration_Goal__destroy(zfc_interfaces__action__RunCalibration_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__action__RunCalibration_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__action__RunCalibration_Goal__Sequence__init(zfc_interfaces__action__RunCalibration_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_Goal * data = NULL;

  if (size) {
    data = (zfc_interfaces__action__RunCalibration_Goal *)allocator.zero_allocate(size, sizeof(zfc_interfaces__action__RunCalibration_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__action__RunCalibration_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__action__RunCalibration_Goal__fini(&data[i - 1]);
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
zfc_interfaces__action__RunCalibration_Goal__Sequence__fini(zfc_interfaces__action__RunCalibration_Goal__Sequence * array)
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
      zfc_interfaces__action__RunCalibration_Goal__fini(&array->data[i]);
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

zfc_interfaces__action__RunCalibration_Goal__Sequence *
zfc_interfaces__action__RunCalibration_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_Goal__Sequence * array = (zfc_interfaces__action__RunCalibration_Goal__Sequence *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__action__RunCalibration_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__action__RunCalibration_Goal__Sequence__destroy(zfc_interfaces__action__RunCalibration_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__action__RunCalibration_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__action__RunCalibration_Goal__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_Goal__Sequence * lhs, const zfc_interfaces__action__RunCalibration_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_Goal__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_Goal__Sequence * input,
  zfc_interfaces__action__RunCalibration_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__action__RunCalibration_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__action__RunCalibration_Goal * data =
      (zfc_interfaces__action__RunCalibration_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__action__RunCalibration_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__action__RunCalibration_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `trial_directory`
// Member `message`
#include "rosidl_runtime_c/string_functions.h"
// Member `fit`
#include "zfc_interfaces/msg/detail/calibration_result__functions.h"

bool
zfc_interfaces__action__RunCalibration_Result__init(zfc_interfaces__action__RunCalibration_Result * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // trial_id
  // trial_directory
  if (!rosidl_runtime_c__String__init(&msg->trial_directory)) {
    zfc_interfaces__action__RunCalibration_Result__fini(msg);
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    zfc_interfaces__action__RunCalibration_Result__fini(msg);
    return false;
  }
  // applied
  // zero_force_active
  // stop_acknowledged
  // fit
  if (!zfc_interfaces__msg__CalibrationResult__init(&msg->fit)) {
    zfc_interfaces__action__RunCalibration_Result__fini(msg);
    return false;
  }
  return true;
}

void
zfc_interfaces__action__RunCalibration_Result__fini(zfc_interfaces__action__RunCalibration_Result * msg)
{
  if (!msg) {
    return;
  }
  // success
  // trial_id
  // trial_directory
  rosidl_runtime_c__String__fini(&msg->trial_directory);
  // message
  rosidl_runtime_c__String__fini(&msg->message);
  // applied
  // zero_force_active
  // stop_acknowledged
  // fit
  zfc_interfaces__msg__CalibrationResult__fini(&msg->fit);
}

bool
zfc_interfaces__action__RunCalibration_Result__are_equal(const zfc_interfaces__action__RunCalibration_Result * lhs, const zfc_interfaces__action__RunCalibration_Result * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // trial_id
  if (lhs->trial_id != rhs->trial_id) {
    return false;
  }
  // trial_directory
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->trial_directory), &(rhs->trial_directory)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  // applied
  if (lhs->applied != rhs->applied) {
    return false;
  }
  // zero_force_active
  if (lhs->zero_force_active != rhs->zero_force_active) {
    return false;
  }
  // stop_acknowledged
  if (lhs->stop_acknowledged != rhs->stop_acknowledged) {
    return false;
  }
  // fit
  if (!zfc_interfaces__msg__CalibrationResult__are_equal(
      &(lhs->fit), &(rhs->fit)))
  {
    return false;
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_Result__copy(
  const zfc_interfaces__action__RunCalibration_Result * input,
  zfc_interfaces__action__RunCalibration_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // trial_id
  output->trial_id = input->trial_id;
  // trial_directory
  if (!rosidl_runtime_c__String__copy(
      &(input->trial_directory), &(output->trial_directory)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  // applied
  output->applied = input->applied;
  // zero_force_active
  output->zero_force_active = input->zero_force_active;
  // stop_acknowledged
  output->stop_acknowledged = input->stop_acknowledged;
  // fit
  if (!zfc_interfaces__msg__CalibrationResult__copy(
      &(input->fit), &(output->fit)))
  {
    return false;
  }
  return true;
}

zfc_interfaces__action__RunCalibration_Result *
zfc_interfaces__action__RunCalibration_Result__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_Result * msg = (zfc_interfaces__action__RunCalibration_Result *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__action__RunCalibration_Result));
  bool success = zfc_interfaces__action__RunCalibration_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__action__RunCalibration_Result__destroy(zfc_interfaces__action__RunCalibration_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__action__RunCalibration_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__action__RunCalibration_Result__Sequence__init(zfc_interfaces__action__RunCalibration_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_Result * data = NULL;

  if (size) {
    data = (zfc_interfaces__action__RunCalibration_Result *)allocator.zero_allocate(size, sizeof(zfc_interfaces__action__RunCalibration_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__action__RunCalibration_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__action__RunCalibration_Result__fini(&data[i - 1]);
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
zfc_interfaces__action__RunCalibration_Result__Sequence__fini(zfc_interfaces__action__RunCalibration_Result__Sequence * array)
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
      zfc_interfaces__action__RunCalibration_Result__fini(&array->data[i]);
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

zfc_interfaces__action__RunCalibration_Result__Sequence *
zfc_interfaces__action__RunCalibration_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_Result__Sequence * array = (zfc_interfaces__action__RunCalibration_Result__Sequence *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__action__RunCalibration_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__action__RunCalibration_Result__Sequence__destroy(zfc_interfaces__action__RunCalibration_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__action__RunCalibration_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__action__RunCalibration_Result__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_Result__Sequence * lhs, const zfc_interfaces__action__RunCalibration_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_Result__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_Result__Sequence * input,
  zfc_interfaces__action__RunCalibration_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__action__RunCalibration_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__action__RunCalibration_Result * data =
      (zfc_interfaces__action__RunCalibration_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__action__RunCalibration_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__action__RunCalibration_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `state`
#include "zfc_interfaces/msg/detail/analysis_state__functions.h"

bool
zfc_interfaces__action__RunCalibration_Feedback__init(zfc_interfaces__action__RunCalibration_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // state
  if (!zfc_interfaces__msg__AnalysisState__init(&msg->state)) {
    zfc_interfaces__action__RunCalibration_Feedback__fini(msg);
    return false;
  }
  return true;
}

void
zfc_interfaces__action__RunCalibration_Feedback__fini(zfc_interfaces__action__RunCalibration_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // state
  zfc_interfaces__msg__AnalysisState__fini(&msg->state);
}

bool
zfc_interfaces__action__RunCalibration_Feedback__are_equal(const zfc_interfaces__action__RunCalibration_Feedback * lhs, const zfc_interfaces__action__RunCalibration_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // state
  if (!zfc_interfaces__msg__AnalysisState__are_equal(
      &(lhs->state), &(rhs->state)))
  {
    return false;
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_Feedback__copy(
  const zfc_interfaces__action__RunCalibration_Feedback * input,
  zfc_interfaces__action__RunCalibration_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // state
  if (!zfc_interfaces__msg__AnalysisState__copy(
      &(input->state), &(output->state)))
  {
    return false;
  }
  return true;
}

zfc_interfaces__action__RunCalibration_Feedback *
zfc_interfaces__action__RunCalibration_Feedback__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_Feedback * msg = (zfc_interfaces__action__RunCalibration_Feedback *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__action__RunCalibration_Feedback));
  bool success = zfc_interfaces__action__RunCalibration_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__action__RunCalibration_Feedback__destroy(zfc_interfaces__action__RunCalibration_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__action__RunCalibration_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__action__RunCalibration_Feedback__Sequence__init(zfc_interfaces__action__RunCalibration_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_Feedback * data = NULL;

  if (size) {
    data = (zfc_interfaces__action__RunCalibration_Feedback *)allocator.zero_allocate(size, sizeof(zfc_interfaces__action__RunCalibration_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__action__RunCalibration_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__action__RunCalibration_Feedback__fini(&data[i - 1]);
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
zfc_interfaces__action__RunCalibration_Feedback__Sequence__fini(zfc_interfaces__action__RunCalibration_Feedback__Sequence * array)
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
      zfc_interfaces__action__RunCalibration_Feedback__fini(&array->data[i]);
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

zfc_interfaces__action__RunCalibration_Feedback__Sequence *
zfc_interfaces__action__RunCalibration_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_Feedback__Sequence * array = (zfc_interfaces__action__RunCalibration_Feedback__Sequence *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__action__RunCalibration_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__action__RunCalibration_Feedback__Sequence__destroy(zfc_interfaces__action__RunCalibration_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__action__RunCalibration_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__action__RunCalibration_Feedback__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_Feedback__Sequence * lhs, const zfc_interfaces__action__RunCalibration_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_Feedback__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_Feedback__Sequence * input,
  zfc_interfaces__action__RunCalibration_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__action__RunCalibration_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__action__RunCalibration_Feedback * data =
      (zfc_interfaces__action__RunCalibration_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__action__RunCalibration_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__action__RunCalibration_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__functions.h"

bool
zfc_interfaces__action__RunCalibration_SendGoal_Request__init(zfc_interfaces__action__RunCalibration_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    zfc_interfaces__action__RunCalibration_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!zfc_interfaces__action__RunCalibration_Goal__init(&msg->goal)) {
    zfc_interfaces__action__RunCalibration_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
zfc_interfaces__action__RunCalibration_SendGoal_Request__fini(zfc_interfaces__action__RunCalibration_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  zfc_interfaces__action__RunCalibration_Goal__fini(&msg->goal);
}

bool
zfc_interfaces__action__RunCalibration_SendGoal_Request__are_equal(const zfc_interfaces__action__RunCalibration_SendGoal_Request * lhs, const zfc_interfaces__action__RunCalibration_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!zfc_interfaces__action__RunCalibration_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_SendGoal_Request__copy(
  const zfc_interfaces__action__RunCalibration_SendGoal_Request * input,
  zfc_interfaces__action__RunCalibration_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!zfc_interfaces__action__RunCalibration_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

zfc_interfaces__action__RunCalibration_SendGoal_Request *
zfc_interfaces__action__RunCalibration_SendGoal_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_SendGoal_Request * msg = (zfc_interfaces__action__RunCalibration_SendGoal_Request *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__action__RunCalibration_SendGoal_Request));
  bool success = zfc_interfaces__action__RunCalibration_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__action__RunCalibration_SendGoal_Request__destroy(zfc_interfaces__action__RunCalibration_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__action__RunCalibration_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__init(zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_SendGoal_Request * data = NULL;

  if (size) {
    data = (zfc_interfaces__action__RunCalibration_SendGoal_Request *)allocator.zero_allocate(size, sizeof(zfc_interfaces__action__RunCalibration_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__action__RunCalibration_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__action__RunCalibration_SendGoal_Request__fini(&data[i - 1]);
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
zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__fini(zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * array)
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
      zfc_interfaces__action__RunCalibration_SendGoal_Request__fini(&array->data[i]);
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

zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence *
zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * array = (zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__destroy(zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * lhs, const zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * input,
  zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__action__RunCalibration_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__action__RunCalibration_SendGoal_Request * data =
      (zfc_interfaces__action__RunCalibration_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__action__RunCalibration_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__action__RunCalibration_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
zfc_interfaces__action__RunCalibration_SendGoal_Response__init(zfc_interfaces__action__RunCalibration_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    zfc_interfaces__action__RunCalibration_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
zfc_interfaces__action__RunCalibration_SendGoal_Response__fini(zfc_interfaces__action__RunCalibration_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
zfc_interfaces__action__RunCalibration_SendGoal_Response__are_equal(const zfc_interfaces__action__RunCalibration_SendGoal_Response * lhs, const zfc_interfaces__action__RunCalibration_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_SendGoal_Response__copy(
  const zfc_interfaces__action__RunCalibration_SendGoal_Response * input,
  zfc_interfaces__action__RunCalibration_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

zfc_interfaces__action__RunCalibration_SendGoal_Response *
zfc_interfaces__action__RunCalibration_SendGoal_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_SendGoal_Response * msg = (zfc_interfaces__action__RunCalibration_SendGoal_Response *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__action__RunCalibration_SendGoal_Response));
  bool success = zfc_interfaces__action__RunCalibration_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__action__RunCalibration_SendGoal_Response__destroy(zfc_interfaces__action__RunCalibration_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__action__RunCalibration_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__init(zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_SendGoal_Response * data = NULL;

  if (size) {
    data = (zfc_interfaces__action__RunCalibration_SendGoal_Response *)allocator.zero_allocate(size, sizeof(zfc_interfaces__action__RunCalibration_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__action__RunCalibration_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__action__RunCalibration_SendGoal_Response__fini(&data[i - 1]);
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
zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__fini(zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * array)
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
      zfc_interfaces__action__RunCalibration_SendGoal_Response__fini(&array->data[i]);
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

zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence *
zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * array = (zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__destroy(zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * lhs, const zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * input,
  zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__action__RunCalibration_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__action__RunCalibration_SendGoal_Response * data =
      (zfc_interfaces__action__RunCalibration_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__action__RunCalibration_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__action__RunCalibration_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
zfc_interfaces__action__RunCalibration_GetResult_Request__init(zfc_interfaces__action__RunCalibration_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    zfc_interfaces__action__RunCalibration_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
zfc_interfaces__action__RunCalibration_GetResult_Request__fini(zfc_interfaces__action__RunCalibration_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
zfc_interfaces__action__RunCalibration_GetResult_Request__are_equal(const zfc_interfaces__action__RunCalibration_GetResult_Request * lhs, const zfc_interfaces__action__RunCalibration_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_GetResult_Request__copy(
  const zfc_interfaces__action__RunCalibration_GetResult_Request * input,
  zfc_interfaces__action__RunCalibration_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

zfc_interfaces__action__RunCalibration_GetResult_Request *
zfc_interfaces__action__RunCalibration_GetResult_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_GetResult_Request * msg = (zfc_interfaces__action__RunCalibration_GetResult_Request *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__action__RunCalibration_GetResult_Request));
  bool success = zfc_interfaces__action__RunCalibration_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__action__RunCalibration_GetResult_Request__destroy(zfc_interfaces__action__RunCalibration_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__action__RunCalibration_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__init(zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_GetResult_Request * data = NULL;

  if (size) {
    data = (zfc_interfaces__action__RunCalibration_GetResult_Request *)allocator.zero_allocate(size, sizeof(zfc_interfaces__action__RunCalibration_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__action__RunCalibration_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__action__RunCalibration_GetResult_Request__fini(&data[i - 1]);
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
zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__fini(zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * array)
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
      zfc_interfaces__action__RunCalibration_GetResult_Request__fini(&array->data[i]);
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

zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence *
zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * array = (zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__destroy(zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * lhs, const zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * input,
  zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__action__RunCalibration_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__action__RunCalibration_GetResult_Request * data =
      (zfc_interfaces__action__RunCalibration_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__action__RunCalibration_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__action__RunCalibration_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__functions.h"

bool
zfc_interfaces__action__RunCalibration_GetResult_Response__init(zfc_interfaces__action__RunCalibration_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!zfc_interfaces__action__RunCalibration_Result__init(&msg->result)) {
    zfc_interfaces__action__RunCalibration_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
zfc_interfaces__action__RunCalibration_GetResult_Response__fini(zfc_interfaces__action__RunCalibration_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  zfc_interfaces__action__RunCalibration_Result__fini(&msg->result);
}

bool
zfc_interfaces__action__RunCalibration_GetResult_Response__are_equal(const zfc_interfaces__action__RunCalibration_GetResult_Response * lhs, const zfc_interfaces__action__RunCalibration_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!zfc_interfaces__action__RunCalibration_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_GetResult_Response__copy(
  const zfc_interfaces__action__RunCalibration_GetResult_Response * input,
  zfc_interfaces__action__RunCalibration_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!zfc_interfaces__action__RunCalibration_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

zfc_interfaces__action__RunCalibration_GetResult_Response *
zfc_interfaces__action__RunCalibration_GetResult_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_GetResult_Response * msg = (zfc_interfaces__action__RunCalibration_GetResult_Response *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__action__RunCalibration_GetResult_Response));
  bool success = zfc_interfaces__action__RunCalibration_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__action__RunCalibration_GetResult_Response__destroy(zfc_interfaces__action__RunCalibration_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__action__RunCalibration_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__init(zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_GetResult_Response * data = NULL;

  if (size) {
    data = (zfc_interfaces__action__RunCalibration_GetResult_Response *)allocator.zero_allocate(size, sizeof(zfc_interfaces__action__RunCalibration_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__action__RunCalibration_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__action__RunCalibration_GetResult_Response__fini(&data[i - 1]);
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
zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__fini(zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * array)
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
      zfc_interfaces__action__RunCalibration_GetResult_Response__fini(&array->data[i]);
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

zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence *
zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * array = (zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__destroy(zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * lhs, const zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * input,
  zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__action__RunCalibration_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__action__RunCalibration_GetResult_Response * data =
      (zfc_interfaces__action__RunCalibration_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__action__RunCalibration_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__action__RunCalibration_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__functions.h"

bool
zfc_interfaces__action__RunCalibration_FeedbackMessage__init(zfc_interfaces__action__RunCalibration_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    zfc_interfaces__action__RunCalibration_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!zfc_interfaces__action__RunCalibration_Feedback__init(&msg->feedback)) {
    zfc_interfaces__action__RunCalibration_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
zfc_interfaces__action__RunCalibration_FeedbackMessage__fini(zfc_interfaces__action__RunCalibration_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  zfc_interfaces__action__RunCalibration_Feedback__fini(&msg->feedback);
}

bool
zfc_interfaces__action__RunCalibration_FeedbackMessage__are_equal(const zfc_interfaces__action__RunCalibration_FeedbackMessage * lhs, const zfc_interfaces__action__RunCalibration_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!zfc_interfaces__action__RunCalibration_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_FeedbackMessage__copy(
  const zfc_interfaces__action__RunCalibration_FeedbackMessage * input,
  zfc_interfaces__action__RunCalibration_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!zfc_interfaces__action__RunCalibration_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

zfc_interfaces__action__RunCalibration_FeedbackMessage *
zfc_interfaces__action__RunCalibration_FeedbackMessage__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_FeedbackMessage * msg = (zfc_interfaces__action__RunCalibration_FeedbackMessage *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__action__RunCalibration_FeedbackMessage));
  bool success = zfc_interfaces__action__RunCalibration_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__action__RunCalibration_FeedbackMessage__destroy(zfc_interfaces__action__RunCalibration_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__action__RunCalibration_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__init(zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_FeedbackMessage * data = NULL;

  if (size) {
    data = (zfc_interfaces__action__RunCalibration_FeedbackMessage *)allocator.zero_allocate(size, sizeof(zfc_interfaces__action__RunCalibration_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__action__RunCalibration_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__action__RunCalibration_FeedbackMessage__fini(&data[i - 1]);
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
zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__fini(zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * array)
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
      zfc_interfaces__action__RunCalibration_FeedbackMessage__fini(&array->data[i]);
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

zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence *
zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * array = (zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence *)allocator.allocate(sizeof(zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__destroy(zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * lhs, const zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * input,
  zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__action__RunCalibration_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__action__RunCalibration_FeedbackMessage * data =
      (zfc_interfaces__action__RunCalibration_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__action__RunCalibration_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__action__RunCalibration_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__action__RunCalibration_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
