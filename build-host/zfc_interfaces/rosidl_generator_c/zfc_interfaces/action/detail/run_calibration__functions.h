// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from zfc_interfaces:action/RunCalibration.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__FUNCTIONS_H_
#define ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "zfc_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "zfc_interfaces/action/detail/run_calibration__struct.h"

/// Initialize action/RunCalibration message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * zfc_interfaces__action__RunCalibration_Goal
 * )) before or use
 * zfc_interfaces__action__RunCalibration_Goal__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_Goal__init(zfc_interfaces__action__RunCalibration_Goal * msg);

/// Finalize action/RunCalibration message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_Goal__fini(zfc_interfaces__action__RunCalibration_Goal * msg);

/// Create action/RunCalibration message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * zfc_interfaces__action__RunCalibration_Goal__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_Goal *
zfc_interfaces__action__RunCalibration_Goal__create();

/// Destroy action/RunCalibration message.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_Goal__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_Goal__destroy(zfc_interfaces__action__RunCalibration_Goal * msg);

/// Check for action/RunCalibration message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_Goal__are_equal(const zfc_interfaces__action__RunCalibration_Goal * lhs, const zfc_interfaces__action__RunCalibration_Goal * rhs);

/// Copy a action/RunCalibration message.
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
zfc_interfaces__action__RunCalibration_Goal__copy(
  const zfc_interfaces__action__RunCalibration_Goal * input,
  zfc_interfaces__action__RunCalibration_Goal * output);

/// Initialize array of action/RunCalibration messages.
/**
 * It allocates the memory for the number of elements and calls
 * zfc_interfaces__action__RunCalibration_Goal__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_Goal__Sequence__init(zfc_interfaces__action__RunCalibration_Goal__Sequence * array, size_t size);

/// Finalize array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_Goal__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_Goal__Sequence__fini(zfc_interfaces__action__RunCalibration_Goal__Sequence * array);

/// Create array of action/RunCalibration messages.
/**
 * It allocates the memory for the array and calls
 * zfc_interfaces__action__RunCalibration_Goal__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_Goal__Sequence *
zfc_interfaces__action__RunCalibration_Goal__Sequence__create(size_t size);

/// Destroy array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_Goal__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_Goal__Sequence__destroy(zfc_interfaces__action__RunCalibration_Goal__Sequence * array);

/// Check for action/RunCalibration message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_Goal__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_Goal__Sequence * lhs, const zfc_interfaces__action__RunCalibration_Goal__Sequence * rhs);

/// Copy an array of action/RunCalibration messages.
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
zfc_interfaces__action__RunCalibration_Goal__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_Goal__Sequence * input,
  zfc_interfaces__action__RunCalibration_Goal__Sequence * output);

/// Initialize action/RunCalibration message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * zfc_interfaces__action__RunCalibration_Result
 * )) before or use
 * zfc_interfaces__action__RunCalibration_Result__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_Result__init(zfc_interfaces__action__RunCalibration_Result * msg);

/// Finalize action/RunCalibration message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_Result__fini(zfc_interfaces__action__RunCalibration_Result * msg);

/// Create action/RunCalibration message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * zfc_interfaces__action__RunCalibration_Result__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_Result *
zfc_interfaces__action__RunCalibration_Result__create();

/// Destroy action/RunCalibration message.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_Result__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_Result__destroy(zfc_interfaces__action__RunCalibration_Result * msg);

/// Check for action/RunCalibration message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_Result__are_equal(const zfc_interfaces__action__RunCalibration_Result * lhs, const zfc_interfaces__action__RunCalibration_Result * rhs);

/// Copy a action/RunCalibration message.
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
zfc_interfaces__action__RunCalibration_Result__copy(
  const zfc_interfaces__action__RunCalibration_Result * input,
  zfc_interfaces__action__RunCalibration_Result * output);

/// Initialize array of action/RunCalibration messages.
/**
 * It allocates the memory for the number of elements and calls
 * zfc_interfaces__action__RunCalibration_Result__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_Result__Sequence__init(zfc_interfaces__action__RunCalibration_Result__Sequence * array, size_t size);

/// Finalize array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_Result__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_Result__Sequence__fini(zfc_interfaces__action__RunCalibration_Result__Sequence * array);

/// Create array of action/RunCalibration messages.
/**
 * It allocates the memory for the array and calls
 * zfc_interfaces__action__RunCalibration_Result__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_Result__Sequence *
zfc_interfaces__action__RunCalibration_Result__Sequence__create(size_t size);

/// Destroy array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_Result__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_Result__Sequence__destroy(zfc_interfaces__action__RunCalibration_Result__Sequence * array);

/// Check for action/RunCalibration message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_Result__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_Result__Sequence * lhs, const zfc_interfaces__action__RunCalibration_Result__Sequence * rhs);

/// Copy an array of action/RunCalibration messages.
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
zfc_interfaces__action__RunCalibration_Result__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_Result__Sequence * input,
  zfc_interfaces__action__RunCalibration_Result__Sequence * output);

/// Initialize action/RunCalibration message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * zfc_interfaces__action__RunCalibration_Feedback
 * )) before or use
 * zfc_interfaces__action__RunCalibration_Feedback__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_Feedback__init(zfc_interfaces__action__RunCalibration_Feedback * msg);

/// Finalize action/RunCalibration message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_Feedback__fini(zfc_interfaces__action__RunCalibration_Feedback * msg);

/// Create action/RunCalibration message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * zfc_interfaces__action__RunCalibration_Feedback__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_Feedback *
zfc_interfaces__action__RunCalibration_Feedback__create();

/// Destroy action/RunCalibration message.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_Feedback__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_Feedback__destroy(zfc_interfaces__action__RunCalibration_Feedback * msg);

/// Check for action/RunCalibration message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_Feedback__are_equal(const zfc_interfaces__action__RunCalibration_Feedback * lhs, const zfc_interfaces__action__RunCalibration_Feedback * rhs);

/// Copy a action/RunCalibration message.
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
zfc_interfaces__action__RunCalibration_Feedback__copy(
  const zfc_interfaces__action__RunCalibration_Feedback * input,
  zfc_interfaces__action__RunCalibration_Feedback * output);

/// Initialize array of action/RunCalibration messages.
/**
 * It allocates the memory for the number of elements and calls
 * zfc_interfaces__action__RunCalibration_Feedback__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_Feedback__Sequence__init(zfc_interfaces__action__RunCalibration_Feedback__Sequence * array, size_t size);

/// Finalize array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_Feedback__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_Feedback__Sequence__fini(zfc_interfaces__action__RunCalibration_Feedback__Sequence * array);

/// Create array of action/RunCalibration messages.
/**
 * It allocates the memory for the array and calls
 * zfc_interfaces__action__RunCalibration_Feedback__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_Feedback__Sequence *
zfc_interfaces__action__RunCalibration_Feedback__Sequence__create(size_t size);

/// Destroy array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_Feedback__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_Feedback__Sequence__destroy(zfc_interfaces__action__RunCalibration_Feedback__Sequence * array);

/// Check for action/RunCalibration message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_Feedback__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_Feedback__Sequence * lhs, const zfc_interfaces__action__RunCalibration_Feedback__Sequence * rhs);

/// Copy an array of action/RunCalibration messages.
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
zfc_interfaces__action__RunCalibration_Feedback__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_Feedback__Sequence * input,
  zfc_interfaces__action__RunCalibration_Feedback__Sequence * output);

/// Initialize action/RunCalibration message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * zfc_interfaces__action__RunCalibration_SendGoal_Request
 * )) before or use
 * zfc_interfaces__action__RunCalibration_SendGoal_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_SendGoal_Request__init(zfc_interfaces__action__RunCalibration_SendGoal_Request * msg);

/// Finalize action/RunCalibration message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_SendGoal_Request__fini(zfc_interfaces__action__RunCalibration_SendGoal_Request * msg);

/// Create action/RunCalibration message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * zfc_interfaces__action__RunCalibration_SendGoal_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_SendGoal_Request *
zfc_interfaces__action__RunCalibration_SendGoal_Request__create();

/// Destroy action/RunCalibration message.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_SendGoal_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_SendGoal_Request__destroy(zfc_interfaces__action__RunCalibration_SendGoal_Request * msg);

/// Check for action/RunCalibration message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_SendGoal_Request__are_equal(const zfc_interfaces__action__RunCalibration_SendGoal_Request * lhs, const zfc_interfaces__action__RunCalibration_SendGoal_Request * rhs);

/// Copy a action/RunCalibration message.
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
zfc_interfaces__action__RunCalibration_SendGoal_Request__copy(
  const zfc_interfaces__action__RunCalibration_SendGoal_Request * input,
  zfc_interfaces__action__RunCalibration_SendGoal_Request * output);

/// Initialize array of action/RunCalibration messages.
/**
 * It allocates the memory for the number of elements and calls
 * zfc_interfaces__action__RunCalibration_SendGoal_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__init(zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * array, size_t size);

/// Finalize array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_SendGoal_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__fini(zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * array);

/// Create array of action/RunCalibration messages.
/**
 * It allocates the memory for the array and calls
 * zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence *
zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__create(size_t size);

/// Destroy array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__destroy(zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * array);

/// Check for action/RunCalibration message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * lhs, const zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * rhs);

/// Copy an array of action/RunCalibration messages.
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
zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * input,
  zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence * output);

/// Initialize action/RunCalibration message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * zfc_interfaces__action__RunCalibration_SendGoal_Response
 * )) before or use
 * zfc_interfaces__action__RunCalibration_SendGoal_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_SendGoal_Response__init(zfc_interfaces__action__RunCalibration_SendGoal_Response * msg);

/// Finalize action/RunCalibration message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_SendGoal_Response__fini(zfc_interfaces__action__RunCalibration_SendGoal_Response * msg);

/// Create action/RunCalibration message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * zfc_interfaces__action__RunCalibration_SendGoal_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_SendGoal_Response *
zfc_interfaces__action__RunCalibration_SendGoal_Response__create();

/// Destroy action/RunCalibration message.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_SendGoal_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_SendGoal_Response__destroy(zfc_interfaces__action__RunCalibration_SendGoal_Response * msg);

/// Check for action/RunCalibration message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_SendGoal_Response__are_equal(const zfc_interfaces__action__RunCalibration_SendGoal_Response * lhs, const zfc_interfaces__action__RunCalibration_SendGoal_Response * rhs);

/// Copy a action/RunCalibration message.
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
zfc_interfaces__action__RunCalibration_SendGoal_Response__copy(
  const zfc_interfaces__action__RunCalibration_SendGoal_Response * input,
  zfc_interfaces__action__RunCalibration_SendGoal_Response * output);

/// Initialize array of action/RunCalibration messages.
/**
 * It allocates the memory for the number of elements and calls
 * zfc_interfaces__action__RunCalibration_SendGoal_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__init(zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * array, size_t size);

/// Finalize array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_SendGoal_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__fini(zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * array);

/// Create array of action/RunCalibration messages.
/**
 * It allocates the memory for the array and calls
 * zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence *
zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__create(size_t size);

/// Destroy array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__destroy(zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * array);

/// Check for action/RunCalibration message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * lhs, const zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * rhs);

/// Copy an array of action/RunCalibration messages.
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
zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * input,
  zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence * output);

/// Initialize action/RunCalibration message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * zfc_interfaces__action__RunCalibration_GetResult_Request
 * )) before or use
 * zfc_interfaces__action__RunCalibration_GetResult_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_GetResult_Request__init(zfc_interfaces__action__RunCalibration_GetResult_Request * msg);

/// Finalize action/RunCalibration message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_GetResult_Request__fini(zfc_interfaces__action__RunCalibration_GetResult_Request * msg);

/// Create action/RunCalibration message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * zfc_interfaces__action__RunCalibration_GetResult_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_GetResult_Request *
zfc_interfaces__action__RunCalibration_GetResult_Request__create();

/// Destroy action/RunCalibration message.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_GetResult_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_GetResult_Request__destroy(zfc_interfaces__action__RunCalibration_GetResult_Request * msg);

/// Check for action/RunCalibration message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_GetResult_Request__are_equal(const zfc_interfaces__action__RunCalibration_GetResult_Request * lhs, const zfc_interfaces__action__RunCalibration_GetResult_Request * rhs);

/// Copy a action/RunCalibration message.
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
zfc_interfaces__action__RunCalibration_GetResult_Request__copy(
  const zfc_interfaces__action__RunCalibration_GetResult_Request * input,
  zfc_interfaces__action__RunCalibration_GetResult_Request * output);

/// Initialize array of action/RunCalibration messages.
/**
 * It allocates the memory for the number of elements and calls
 * zfc_interfaces__action__RunCalibration_GetResult_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__init(zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * array, size_t size);

/// Finalize array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_GetResult_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__fini(zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * array);

/// Create array of action/RunCalibration messages.
/**
 * It allocates the memory for the array and calls
 * zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence *
zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__create(size_t size);

/// Destroy array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__destroy(zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * array);

/// Check for action/RunCalibration message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * lhs, const zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * rhs);

/// Copy an array of action/RunCalibration messages.
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
zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * input,
  zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence * output);

/// Initialize action/RunCalibration message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * zfc_interfaces__action__RunCalibration_GetResult_Response
 * )) before or use
 * zfc_interfaces__action__RunCalibration_GetResult_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_GetResult_Response__init(zfc_interfaces__action__RunCalibration_GetResult_Response * msg);

/// Finalize action/RunCalibration message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_GetResult_Response__fini(zfc_interfaces__action__RunCalibration_GetResult_Response * msg);

/// Create action/RunCalibration message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * zfc_interfaces__action__RunCalibration_GetResult_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_GetResult_Response *
zfc_interfaces__action__RunCalibration_GetResult_Response__create();

/// Destroy action/RunCalibration message.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_GetResult_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_GetResult_Response__destroy(zfc_interfaces__action__RunCalibration_GetResult_Response * msg);

/// Check for action/RunCalibration message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_GetResult_Response__are_equal(const zfc_interfaces__action__RunCalibration_GetResult_Response * lhs, const zfc_interfaces__action__RunCalibration_GetResult_Response * rhs);

/// Copy a action/RunCalibration message.
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
zfc_interfaces__action__RunCalibration_GetResult_Response__copy(
  const zfc_interfaces__action__RunCalibration_GetResult_Response * input,
  zfc_interfaces__action__RunCalibration_GetResult_Response * output);

/// Initialize array of action/RunCalibration messages.
/**
 * It allocates the memory for the number of elements and calls
 * zfc_interfaces__action__RunCalibration_GetResult_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__init(zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * array, size_t size);

/// Finalize array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_GetResult_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__fini(zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * array);

/// Create array of action/RunCalibration messages.
/**
 * It allocates the memory for the array and calls
 * zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence *
zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__create(size_t size);

/// Destroy array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__destroy(zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * array);

/// Check for action/RunCalibration message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * lhs, const zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * rhs);

/// Copy an array of action/RunCalibration messages.
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
zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * input,
  zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence * output);

/// Initialize action/RunCalibration message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * zfc_interfaces__action__RunCalibration_FeedbackMessage
 * )) before or use
 * zfc_interfaces__action__RunCalibration_FeedbackMessage__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_FeedbackMessage__init(zfc_interfaces__action__RunCalibration_FeedbackMessage * msg);

/// Finalize action/RunCalibration message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_FeedbackMessage__fini(zfc_interfaces__action__RunCalibration_FeedbackMessage * msg);

/// Create action/RunCalibration message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * zfc_interfaces__action__RunCalibration_FeedbackMessage__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_FeedbackMessage *
zfc_interfaces__action__RunCalibration_FeedbackMessage__create();

/// Destroy action/RunCalibration message.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_FeedbackMessage__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_FeedbackMessage__destroy(zfc_interfaces__action__RunCalibration_FeedbackMessage * msg);

/// Check for action/RunCalibration message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_FeedbackMessage__are_equal(const zfc_interfaces__action__RunCalibration_FeedbackMessage * lhs, const zfc_interfaces__action__RunCalibration_FeedbackMessage * rhs);

/// Copy a action/RunCalibration message.
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
zfc_interfaces__action__RunCalibration_FeedbackMessage__copy(
  const zfc_interfaces__action__RunCalibration_FeedbackMessage * input,
  zfc_interfaces__action__RunCalibration_FeedbackMessage * output);

/// Initialize array of action/RunCalibration messages.
/**
 * It allocates the memory for the number of elements and calls
 * zfc_interfaces__action__RunCalibration_FeedbackMessage__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__init(zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * array, size_t size);

/// Finalize array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_FeedbackMessage__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__fini(zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * array);

/// Create array of action/RunCalibration messages.
/**
 * It allocates the memory for the array and calls
 * zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence *
zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__create(size_t size);

/// Destroy array of action/RunCalibration messages.
/**
 * It calls
 * zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__destroy(zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * array);

/// Check for action/RunCalibration message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__are_equal(const zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * lhs, const zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * rhs);

/// Copy an array of action/RunCalibration messages.
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
zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__copy(
  const zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * input,
  zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__FUNCTIONS_H_
