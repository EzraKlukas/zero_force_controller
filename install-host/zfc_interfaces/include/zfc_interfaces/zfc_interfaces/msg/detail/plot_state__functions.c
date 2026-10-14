// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from zfc_interfaces:msg/PlotState.idl
// generated code does not contain a copyright notice
#include "zfc_interfaces/msg/detail/plot_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `state`
#include "zfc_interfaces/msg/detail/controller_state__functions.h"

bool
zfc_interfaces__msg__PlotState__init(zfc_interfaces__msg__PlotState * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    zfc_interfaces__msg__PlotState__fini(msg);
    return false;
  }
  // state
  if (!zfc_interfaces__msg__ControllerState__init(&msg->state)) {
    zfc_interfaces__msg__PlotState__fini(msg);
    return false;
  }
  // inertial_compensation_n
  return true;
}

void
zfc_interfaces__msg__PlotState__fini(zfc_interfaces__msg__PlotState * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // state
  zfc_interfaces__msg__ControllerState__fini(&msg->state);
  // inertial_compensation_n
}

bool
zfc_interfaces__msg__PlotState__are_equal(const zfc_interfaces__msg__PlotState * lhs, const zfc_interfaces__msg__PlotState * rhs)
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
  // state
  if (!zfc_interfaces__msg__ControllerState__are_equal(
      &(lhs->state), &(rhs->state)))
  {
    return false;
  }
  // inertial_compensation_n
  if (lhs->inertial_compensation_n != rhs->inertial_compensation_n) {
    return false;
  }
  return true;
}

bool
zfc_interfaces__msg__PlotState__copy(
  const zfc_interfaces__msg__PlotState * input,
  zfc_interfaces__msg__PlotState * output)
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
  // state
  if (!zfc_interfaces__msg__ControllerState__copy(
      &(input->state), &(output->state)))
  {
    return false;
  }
  // inertial_compensation_n
  output->inertial_compensation_n = input->inertial_compensation_n;
  return true;
}

zfc_interfaces__msg__PlotState *
zfc_interfaces__msg__PlotState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__PlotState * msg = (zfc_interfaces__msg__PlotState *)allocator.allocate(sizeof(zfc_interfaces__msg__PlotState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(zfc_interfaces__msg__PlotState));
  bool success = zfc_interfaces__msg__PlotState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
zfc_interfaces__msg__PlotState__destroy(zfc_interfaces__msg__PlotState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    zfc_interfaces__msg__PlotState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
zfc_interfaces__msg__PlotState__Sequence__init(zfc_interfaces__msg__PlotState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__PlotState * data = NULL;

  if (size) {
    data = (zfc_interfaces__msg__PlotState *)allocator.zero_allocate(size, sizeof(zfc_interfaces__msg__PlotState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = zfc_interfaces__msg__PlotState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        zfc_interfaces__msg__PlotState__fini(&data[i - 1]);
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
zfc_interfaces__msg__PlotState__Sequence__fini(zfc_interfaces__msg__PlotState__Sequence * array)
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
      zfc_interfaces__msg__PlotState__fini(&array->data[i]);
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

zfc_interfaces__msg__PlotState__Sequence *
zfc_interfaces__msg__PlotState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  zfc_interfaces__msg__PlotState__Sequence * array = (zfc_interfaces__msg__PlotState__Sequence *)allocator.allocate(sizeof(zfc_interfaces__msg__PlotState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = zfc_interfaces__msg__PlotState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
zfc_interfaces__msg__PlotState__Sequence__destroy(zfc_interfaces__msg__PlotState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    zfc_interfaces__msg__PlotState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
zfc_interfaces__msg__PlotState__Sequence__are_equal(const zfc_interfaces__msg__PlotState__Sequence * lhs, const zfc_interfaces__msg__PlotState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!zfc_interfaces__msg__PlotState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
zfc_interfaces__msg__PlotState__Sequence__copy(
  const zfc_interfaces__msg__PlotState__Sequence * input,
  zfc_interfaces__msg__PlotState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(zfc_interfaces__msg__PlotState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    zfc_interfaces__msg__PlotState * data =
      (zfc_interfaces__msg__PlotState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!zfc_interfaces__msg__PlotState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          zfc_interfaces__msg__PlotState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!zfc_interfaces__msg__PlotState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
