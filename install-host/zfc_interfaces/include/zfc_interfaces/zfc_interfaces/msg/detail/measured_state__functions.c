// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from zfc_interfaces:msg/MeasuredState.idl
// generated code does not contain a copyright notice
#include "zfc_interfaces/msg/detail/measured_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `force_stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `detail`
#include "rosidl_runtime_c/string_functions.h"

bool
zfc_interfaces__msg__MeasuredState__init(zfc_interfaces__msg__MeasuredState * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    zfc_interfaces__msg__MeasuredState__fini(msg);
    return false;
  }
  // force_stamp
  if (!builtin_interfaces__msg__Time__init(&msg->force_stamp)) {
    zfc_interfaces__msg__MeasuredState__fini(msg);
    return false;
  }
  // position_m
  // velocity_mps
  // force_n
  // joint_fresh
  // force_fresh
  // valid
  // detail
  if (!rosidl_runtime_c__String__init(&msg->detail)) {
    zfc_interfaces__msg__MeasuredState__fini(msg);
    return false;
  }
  return true;
}

void
zfc_interfaces__msg__MeasuredState__fini(zfc_interfaces__msg__MeasuredState * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // force_stamp
  builtin_interfaces__msg__Time__fini(&msg->force_stamp);
  // position_m
  // velocity_mps
  // force_n
  // joint_fresh
  // force_fresh
  // valid
  // detail
  rosidl_runtime_c__String__fini(&msg->detail);
}

bool
zfc_interfaces__msg__MeasuredState__are_equal(const zfc_interfaces__msg__MeasuredState * lhs, const zfc_interfaces__msg__MeasuredState * rhs)
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
  // force_stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->force_stamp), &(rhs->force_stamp)))
  {
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
  // joint_fresh
  if (lhs->joint_fresh != rhs->joint_fresh) {
    return false;
  }
  // force_fresh
  if (lhs->force_fresh != rhs->force_fresh) {
    return false;
  }
  // valid
  if (lhs->valid != rhs->valid) {
    return false;
  }
  // detail
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->detail), &(rhs->detail)))
  {
    return false;
  }
  return true;
}

bool
zfc_interfaces__msg__MeasuredState__copy(
  const zfc_interfaces__msg__MeasuredState * input,
  zfc_interfaces__msg__MeasuredState * output)
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
  // force_stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->force_stamp), &(output->force_stamp)))
  {
    return false;
  }
  // position_m
  output->position_m = input->position_m;
  // velocity_mps
  output->velocity_mps = input->velocity_mps;
  // force_n
  output->force_n = input->force_n;
  // joint_fresh
  output->joint_fresh = input->joint_fresh;
  // force_fresh
  output->force_fresh = input->force_fresh;
  // valid
  output->valid = input->valid;
  // detail
  if (!rosidl_runtime_c__String__copy(
      &(input->detail), &(output->detail)))
  {
    return false;
  }
  return true;
}

zfc_interfaces__msg__MeasuredState *
zfc_interfaces__msg__MeasuredState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__MeasuredState * msg = (zfc_interfaces__msg__MeasuredState *)allocator.allocate(sizeof(zfc_interfaces__msg__MeasuredState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__msg__MeasuredState));
  bool success = zfc_interfaces__msg__MeasuredState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__msg__MeasuredState__destroy(zfc_interfaces__msg__MeasuredState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__msg__MeasuredState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__msg__MeasuredState__Sequence__init(zfc_interfaces__msg__MeasuredState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__MeasuredState * data = NULL;

  if (size) {
    data = (zfc_interfaces__msg__MeasuredState *)allocator.zero_allocate(size, sizeof(zfc_interfaces__msg__MeasuredState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__msg__MeasuredState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__msg__MeasuredState__fini(&data[i - 1]);
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
zfc_interfaces__msg__MeasuredState__Sequence__fini(zfc_interfaces__msg__MeasuredState__Sequence * array)
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
      zfc_interfaces__msg__MeasuredState__fini(&array->data[i]);
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

zfc_interfaces__msg__MeasuredState__Sequence *
zfc_interfaces__msg__MeasuredState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__MeasuredState__Sequence * array = (zfc_interfaces__msg__MeasuredState__Sequence *)allocator.allocate(sizeof(zfc_interfaces__msg__MeasuredState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__msg__MeasuredState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__msg__MeasuredState__Sequence__destroy(zfc_interfaces__msg__MeasuredState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__msg__MeasuredState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__msg__MeasuredState__Sequence__are_equal(const zfc_interfaces__msg__MeasuredState__Sequence * lhs, const zfc_interfaces__msg__MeasuredState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__msg__MeasuredState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__msg__MeasuredState__Sequence__copy(
  const zfc_interfaces__msg__MeasuredState__Sequence * input,
  zfc_interfaces__msg__MeasuredState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__msg__MeasuredState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__msg__MeasuredState * data =
      (zfc_interfaces__msg__MeasuredState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__msg__MeasuredState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__msg__MeasuredState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__msg__MeasuredState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
