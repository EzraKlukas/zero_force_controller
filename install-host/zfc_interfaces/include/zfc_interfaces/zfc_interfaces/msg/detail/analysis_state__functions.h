// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from zfc_interfaces:msg/AnalysisState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__FUNCTIONS_H_
#define ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "zfc_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "zfc_interfaces/msg/detail/analysis_state__struct.h"

/// Initialize msg/AnalysisState message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * zfc_interfaces__msg__AnalysisState
 * )) before or use
 * zfc_interfaces__msg__AnalysisState__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__msg__AnalysisState__init(zfc_interfaces__msg__AnalysisState * msg);

/// Finalize msg/AnalysisState message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__msg__AnalysisState__fini(zfc_interfaces__msg__AnalysisState * msg);

/// Create msg/AnalysisState message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * zfc_interfaces__msg__AnalysisState__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__msg__AnalysisState *
zfc_interfaces__msg__AnalysisState__create();

/// Destroy msg/AnalysisState message.
/**
 * It calls
 * zfc_interfaces__msg__AnalysisState__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__msg__AnalysisState__destroy(zfc_interfaces__msg__AnalysisState * msg);

/// Check for msg/AnalysisState message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__msg__AnalysisState__are_equal(const zfc_interfaces__msg__AnalysisState * lhs, const zfc_interfaces__msg__AnalysisState * rhs);

/// Copy a msg/AnalysisState message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__msg__AnalysisState__copy(
  const zfc_interfaces__msg__AnalysisState * input,
  zfc_interfaces__msg__AnalysisState * output);

/// Initialize array of msg/AnalysisState messages.
/**
 * It allocates the memory for the number of elements and calls
 * zfc_interfaces__msg__AnalysisState__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__msg__AnalysisState__Sequence__init(zfc_interfaces__msg__AnalysisState__Sequence * array, size_t size);

/// Finalize array of msg/AnalysisState messages.
/**
 * It calls
 * zfc_interfaces__msg__AnalysisState__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__msg__AnalysisState__Sequence__fini(zfc_interfaces__msg__AnalysisState__Sequence * array);

/// Create array of msg/AnalysisState messages.
/**
 * It allocates the memory for the array and calls
 * zfc_interfaces__msg__AnalysisState__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__msg__AnalysisState__Sequence *
zfc_interfaces__msg__AnalysisState__Sequence__create(size_t size);

/// Destroy array of msg/AnalysisState messages.
/**
 * It calls
 * zfc_interfaces__msg__AnalysisState__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__msg__AnalysisState__Sequence__destroy(zfc_interfaces__msg__AnalysisState__Sequence * array);

/// Check for msg/AnalysisState message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__msg__AnalysisState__Sequence__are_equal(const zfc_interfaces__msg__AnalysisState__Sequence * lhs, const zfc_interfaces__msg__AnalysisState__Sequence * rhs);

/// Copy an array of msg/AnalysisState messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__msg__AnalysisState__Sequence__copy(
  const zfc_interfaces__msg__AnalysisState__Sequence * input,
  zfc_interfaces__msg__AnalysisState__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__FUNCTIONS_H_
