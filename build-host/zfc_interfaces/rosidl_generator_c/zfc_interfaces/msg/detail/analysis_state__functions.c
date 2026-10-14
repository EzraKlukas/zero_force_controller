// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from zfc_interfaces:msg/AnalysisState.idl
// generated code does not contain a copyright notice
#include "zfc_interfaces/msg/detail/analysis_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `stage`
// Member `detail`
// Member `backend`
// Member `trial_directory`
#include "rosidl_runtime_c/string_functions.h"
// Member `fit`
#include "zfc_interfaces/msg/detail/calibration_result__functions.h"

bool
zfc_interfaces__msg__AnalysisState__init(zfc_interfaces__msg__AnalysisState * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    zfc_interfaces__msg__AnalysisState__fini(msg);
    return false;
  }
  // trial_id
  // stage
  if (!rosidl_runtime_c__String__init(&msg->stage)) {
    zfc_interfaces__msg__AnalysisState__fini(msg);
    return false;
  }
  // stage_code
  // progress
  // recorded_samples
  // dropped_samples
  // final_sequence
  // stop_acknowledged
  // detail
  if (!rosidl_runtime_c__String__init(&msg->detail)) {
    zfc_interfaces__msg__AnalysisState__fini(msg);
    return false;
  }
  // fit
  if (!zfc_interfaces__msg__CalibrationResult__init(&msg->fit)) {
    zfc_interfaces__msg__AnalysisState__fini(msg);
    return false;
  }
  // backend
  if (!rosidl_runtime_c__String__init(&msg->backend)) {
    zfc_interfaces__msg__AnalysisState__fini(msg);
    return false;
  }
  // operation_pending
  // trial_directory
  if (!rosidl_runtime_c__String__init(&msg->trial_directory)) {
    zfc_interfaces__msg__AnalysisState__fini(msg);
    return false;
  }
  return true;
}

void
zfc_interfaces__msg__AnalysisState__fini(zfc_interfaces__msg__AnalysisState * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // trial_id
  // stage
  rosidl_runtime_c__String__fini(&msg->stage);
  // stage_code
  // progress
  // recorded_samples
  // dropped_samples
  // final_sequence
  // stop_acknowledged
  // detail
  rosidl_runtime_c__String__fini(&msg->detail);
  // fit
  zfc_interfaces__msg__CalibrationResult__fini(&msg->fit);
  // backend
  rosidl_runtime_c__String__fini(&msg->backend);
  // operation_pending
  // trial_directory
  rosidl_runtime_c__String__fini(&msg->trial_directory);
}

bool
zfc_interfaces__msg__AnalysisState__are_equal(const zfc_interfaces__msg__AnalysisState * lhs, const zfc_interfaces__msg__AnalysisState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // trial_id
  if (lhs->trial_id != rhs->trial_id) {
    return false;
  }
  // stage
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->stage), &(rhs->stage)))
  {
    return false;
  }
  // stage_code
  if (lhs->stage_code != rhs->stage_code) {
    return false;
  }
  // progress
  if (lhs->progress != rhs->progress) {
    return false;
  }
  // recorded_samples
  if (lhs->recorded_samples != rhs->recorded_samples) {
    return false;
  }
  // dropped_samples
  if (lhs->dropped_samples != rhs->dropped_samples) {
    return false;
  }
  // final_sequence
  if (lhs->final_sequence != rhs->final_sequence) {
    return false;
  }
  // stop_acknowledged
  if (lhs->stop_acknowledged != rhs->stop_acknowledged) {
    return false;
  }
  // detail
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->detail), &(rhs->detail)))
  {
    return false;
  }
  // fit
  if (!zfc_interfaces__msg__CalibrationResult__are_equal(
      &(lhs->fit), &(rhs->fit)))
  {
    return false;
  }
  // backend
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->backend), &(rhs->backend)))
  {
    return false;
  }
  // operation_pending
  if (lhs->operation_pending != rhs->operation_pending) {
    return false;
  }
  // trial_directory
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->trial_directory), &(rhs->trial_directory)))
  {
    return false;
  }
  return true;
}

bool
zfc_interfaces__msg__AnalysisState__copy(
  const zfc_interfaces__msg__AnalysisState * input,
  zfc_interfaces__msg__AnalysisState * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // trial_id
  output->trial_id = input->trial_id;
  // stage
  if (!rosidl_runtime_c__String__copy(
      &(input->stage), &(output->stage)))
  {
    return false;
  }
  // stage_code
  output->stage_code = input->stage_code;
  // progress
  output->progress = input->progress;
  // recorded_samples
  output->recorded_samples = input->recorded_samples;
  // dropped_samples
  output->dropped_samples = input->dropped_samples;
  // final_sequence
  output->final_sequence = input->final_sequence;
  // stop_acknowledged
  output->stop_acknowledged = input->stop_acknowledged;
  // detail
  if (!rosidl_runtime_c__String__copy(
      &(input->detail), &(output->detail)))
  {
    return false;
  }
  // fit
  if (!zfc_interfaces__msg__CalibrationResult__copy(
      &(input->fit), &(output->fit)))
  {
    return false;
  }
  // backend
  if (!rosidl_runtime_c__String__copy(
      &(input->backend), &(output->backend)))
  {
    return false;
  }
  // operation_pending
  output->operation_pending = input->operation_pending;
  // trial_directory
  if (!rosidl_runtime_c__String__copy(
      &(input->trial_directory), &(output->trial_directory)))
  {
    return false;
  }
  return true;
}

zfc_interfaces__msg__AnalysisState *
zfc_interfaces__msg__AnalysisState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__AnalysisState * msg = (zfc_interfaces__msg__AnalysisState *)allocator.allocate(sizeof(zfc_interfaces__msg__AnalysisState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__msg__AnalysisState));
  bool success = zfc_interfaces__msg__AnalysisState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__msg__AnalysisState__destroy(zfc_interfaces__msg__AnalysisState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__msg__AnalysisState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__msg__AnalysisState__Sequence__init(zfc_interfaces__msg__AnalysisState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__AnalysisState * data = NULL;

  if (size) {
    data = (zfc_interfaces__msg__AnalysisState *)allocator.zero_allocate(size, sizeof(zfc_interfaces__msg__AnalysisState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__msg__AnalysisState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__msg__AnalysisState__fini(&data[i - 1]);
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
zfc_interfaces__msg__AnalysisState__Sequence__fini(zfc_interfaces__msg__AnalysisState__Sequence * array)
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
      zfc_interfaces__msg__AnalysisState__fini(&array->data[i]);
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

zfc_interfaces__msg__AnalysisState__Sequence *
zfc_interfaces__msg__AnalysisState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__AnalysisState__Sequence * array = (zfc_interfaces__msg__AnalysisState__Sequence *)allocator.allocate(sizeof(zfc_interfaces__msg__AnalysisState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__msg__AnalysisState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__msg__AnalysisState__Sequence__destroy(zfc_interfaces__msg__AnalysisState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__msg__AnalysisState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__msg__AnalysisState__Sequence__are_equal(const zfc_interfaces__msg__AnalysisState__Sequence * lhs, const zfc_interfaces__msg__AnalysisState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__msg__AnalysisState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__msg__AnalysisState__Sequence__copy(
  const zfc_interfaces__msg__AnalysisState__Sequence * input,
  zfc_interfaces__msg__AnalysisState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__msg__AnalysisState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__msg__AnalysisState * data =
      (zfc_interfaces__msg__AnalysisState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__msg__AnalysisState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__msg__AnalysisState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__msg__AnalysisState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
