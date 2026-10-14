// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from zfc_interfaces:msg/ControllerState.idl
// generated code does not contain a copyright notice
#include "zfc_interfaces/msg/detail/controller_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
zfc_interfaces__msg__ControllerState__init(zfc_interfaces__msg__ControllerState * msg)
{
  if (!msg) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    zfc_interfaces__msg__ControllerState__fini(msg);
    return false;
  }
  // trial_id
  // sequence
  // phase
  // fault_code
  // valid
  // position_m
  // velocity_mps
  // force_n
  // reference_position_m
  // reference_velocity_mps
  // reference_acceleration_mps2
  // baseline_force_n
  // noise_rms_n
  // residual_force_n
  // progress
  // excessive_periods
  return true;
}

void
zfc_interfaces__msg__ControllerState__fini(zfc_interfaces__msg__ControllerState * msg)
{
  if (!msg) {
    return;
  }
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // trial_id
  // sequence
  // phase
  // fault_code
  // valid
  // position_m
  // velocity_mps
  // force_n
  // reference_position_m
  // reference_velocity_mps
  // reference_acceleration_mps2
  // baseline_force_n
  // noise_rms_n
  // residual_force_n
  // progress
  // excessive_periods
}

bool
zfc_interfaces__msg__ControllerState__are_equal(const zfc_interfaces__msg__ControllerState * lhs, const zfc_interfaces__msg__ControllerState * rhs)
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
  // sequence
  if (lhs->sequence != rhs->sequence) {
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
  // valid
  if (lhs->valid != rhs->valid) {
    return false;
  }
  // position_m
  if (lhs->position_m != rhs->position_m) {
    return false;
  }
  // velocity_mps
  if (lhs->velocity_mps != rhs->velocity_mps) {
    return false;
  }
  // force_n
  if (lhs->force_n != rhs->force_n) {
    return false;
  }
  // reference_position_m
  if (lhs->reference_position_m != rhs->reference_position_m) {
    return false;
  }
  // reference_velocity_mps
  if (lhs->reference_velocity_mps != rhs->reference_velocity_mps) {
    return false;
  }
  // reference_acceleration_mps2
  if (lhs->reference_acceleration_mps2 != rhs->reference_acceleration_mps2) {
    return false;
  }
  // baseline_force_n
  if (lhs->baseline_force_n != rhs->baseline_force_n) {
    return false;
  }
  // noise_rms_n
  if (lhs->noise_rms_n != rhs->noise_rms_n) {
    return false;
  }
  // residual_force_n
  if (lhs->residual_force_n != rhs->residual_force_n) {
    return false;
  }
  // progress
  if (lhs->progress != rhs->progress) {
    return false;
  }
  // excessive_periods
  if (lhs->excessive_periods != rhs->excessive_periods) {
    return false;
  }
  return true;
}

bool
zfc_interfaces__msg__ControllerState__copy(
  const zfc_interfaces__msg__ControllerState * input,
  zfc_interfaces__msg__ControllerState * output)
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
  // sequence
  output->sequence = input->sequence;
  // phase
  output->phase = input->phase;
  // fault_code
  output->fault_code = input->fault_code;
  // valid
  output->valid = input->valid;
  // position_m
  output->position_m = input->position_m;
  // velocity_mps
  output->velocity_mps = input->velocity_mps;
  // force_n
  output->force_n = input->force_n;
  // reference_position_m
  output->reference_position_m = input->reference_position_m;
  // reference_velocity_mps
  output->reference_velocity_mps = input->reference_velocity_mps;
  // reference_acceleration_mps2
  output->reference_acceleration_mps2 = input->reference_acceleration_mps2;
  // baseline_force_n
  output->baseline_force_n = input->baseline_force_n;
  // noise_rms_n
  output->noise_rms_n = input->noise_rms_n;
  // residual_force_n
  output->residual_force_n = input->residual_force_n;
  // progress
  output->progress = input->progress;
  // excessive_periods
  output->excessive_periods = input->excessive_periods;
  return true;
}

zfc_interfaces__msg__ControllerState *
zfc_interfaces__msg__ControllerState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__ControllerState * msg = (zfc_interfaces__msg__ControllerState *)allocator.allocate(sizeof(zfc_interfaces__msg__ControllerState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__msg__ControllerState));
  bool success = zfc_interfaces__msg__ControllerState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__msg__ControllerState__destroy(zfc_interfaces__msg__ControllerState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__msg__ControllerState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__msg__ControllerState__Sequence__init(zfc_interfaces__msg__ControllerState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__ControllerState * data = NULL;

  if (size) {
    data = (zfc_interfaces__msg__ControllerState *)allocator.zero_allocate(size, sizeof(zfc_interfaces__msg__ControllerState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__msg__ControllerState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__msg__ControllerState__fini(&data[i - 1]);
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
zfc_interfaces__msg__ControllerState__Sequence__fini(zfc_interfaces__msg__ControllerState__Sequence * array)
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
      zfc_interfaces__msg__ControllerState__fini(&array->data[i]);
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

zfc_interfaces__msg__ControllerState__Sequence *
zfc_interfaces__msg__ControllerState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__ControllerState__Sequence * array = (zfc_interfaces__msg__ControllerState__Sequence *)allocator.allocate(sizeof(zfc_interfaces__msg__ControllerState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__msg__ControllerState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__msg__ControllerState__Sequence__destroy(zfc_interfaces__msg__ControllerState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__msg__ControllerState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__msg__ControllerState__Sequence__are_equal(const zfc_interfaces__msg__ControllerState__Sequence * lhs, const zfc_interfaces__msg__ControllerState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__msg__ControllerState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__msg__ControllerState__Sequence__copy(
  const zfc_interfaces__msg__ControllerState__Sequence * input,
  zfc_interfaces__msg__ControllerState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__msg__ControllerState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__msg__ControllerState * data =
      (zfc_interfaces__msg__ControllerState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__msg__ControllerState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__msg__ControllerState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__msg__ControllerState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
