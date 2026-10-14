// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from zfc_interfaces:srv/OperatorCommand.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__FUNCTIONS_H_
#define ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "zfc_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "zfc_interfaces/srv/detail/operator_command__struct.h"

/// Initialize srv/OperatorCommand message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * zfc_interfaces__srv__OperatorCommand_Request
 * )) before or use
 * zfc_interfaces__srv__OperatorCommand_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__srv__OperatorCommand_Request__init(zfc_interfaces__srv__OperatorCommand_Request * msg);

/// Finalize srv/OperatorCommand message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__srv__OperatorCommand_Request__fini(zfc_interfaces__srv__OperatorCommand_Request * msg);

/// Create srv/OperatorCommand message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * zfc_interfaces__srv__OperatorCommand_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__srv__OperatorCommand_Request *
zfc_interfaces__srv__OperatorCommand_Request__create();

/// Destroy srv/OperatorCommand message.
/**
 * It calls
 * zfc_interfaces__srv__OperatorCommand_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__srv__OperatorCommand_Request__destroy(zfc_interfaces__srv__OperatorCommand_Request * msg);

/// Check for srv/OperatorCommand message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__srv__OperatorCommand_Request__are_equal(const zfc_interfaces__srv__OperatorCommand_Request * lhs, const zfc_interfaces__srv__OperatorCommand_Request * rhs);

/// Copy a srv/OperatorCommand message.
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
zfc_interfaces__srv__OperatorCommand_Request__copy(
  const zfc_interfaces__srv__OperatorCommand_Request * input,
  zfc_interfaces__srv__OperatorCommand_Request * output);

/// Initialize array of srv/OperatorCommand messages.
/**
 * It allocates the memory for the number of elements and calls
 * zfc_interfaces__srv__OperatorCommand_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__srv__OperatorCommand_Request__Sequence__init(zfc_interfaces__srv__OperatorCommand_Request__Sequence * array, size_t size);

/// Finalize array of srv/OperatorCommand messages.
/**
 * It calls
 * zfc_interfaces__srv__OperatorCommand_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__srv__OperatorCommand_Request__Sequence__fini(zfc_interfaces__srv__OperatorCommand_Request__Sequence * array);

/// Create array of srv/OperatorCommand messages.
/**
 * It allocates the memory for the array and calls
 * zfc_interfaces__srv__OperatorCommand_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__srv__OperatorCommand_Request__Sequence *
zfc_interfaces__srv__OperatorCommand_Request__Sequence__create(size_t size);

/// Destroy array of srv/OperatorCommand messages.
/**
 * It calls
 * zfc_interfaces__srv__OperatorCommand_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__srv__OperatorCommand_Request__Sequence__destroy(zfc_interfaces__srv__OperatorCommand_Request__Sequence * array);

/// Check for srv/OperatorCommand message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__srv__OperatorCommand_Request__Sequence__are_equal(const zfc_interfaces__srv__OperatorCommand_Request__Sequence * lhs, const zfc_interfaces__srv__OperatorCommand_Request__Sequence * rhs);

/// Copy an array of srv/OperatorCommand messages.
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
zfc_interfaces__srv__OperatorCommand_Request__Sequence__copy(
  const zfc_interfaces__srv__OperatorCommand_Request__Sequence * input,
  zfc_interfaces__srv__OperatorCommand_Request__Sequence * output);

/// Initialize srv/OperatorCommand message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * zfc_interfaces__srv__OperatorCommand_Response
 * )) before or use
 * zfc_interfaces__srv__OperatorCommand_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__srv__OperatorCommand_Response__init(zfc_interfaces__srv__OperatorCommand_Response * msg);

/// Finalize srv/OperatorCommand message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__srv__OperatorCommand_Response__fini(zfc_interfaces__srv__OperatorCommand_Response * msg);

/// Create srv/OperatorCommand message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * zfc_interfaces__srv__OperatorCommand_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__srv__OperatorCommand_Response *
zfc_interfaces__srv__OperatorCommand_Response__create();

/// Destroy srv/OperatorCommand message.
/**
 * It calls
 * zfc_interfaces__srv__OperatorCommand_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__srv__OperatorCommand_Response__destroy(zfc_interfaces__srv__OperatorCommand_Response * msg);

/// Check for srv/OperatorCommand message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__srv__OperatorCommand_Response__are_equal(const zfc_interfaces__srv__OperatorCommand_Response * lhs, const zfc_interfaces__srv__OperatorCommand_Response * rhs);

/// Copy a srv/OperatorCommand message.
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
zfc_interfaces__srv__OperatorCommand_Response__copy(
  const zfc_interfaces__srv__OperatorCommand_Response * input,
  zfc_interfaces__srv__OperatorCommand_Response * output);

/// Initialize array of srv/OperatorCommand messages.
/**
 * It allocates the memory for the number of elements and calls
 * zfc_interfaces__srv__OperatorCommand_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__srv__OperatorCommand_Response__Sequence__init(zfc_interfaces__srv__OperatorCommand_Response__Sequence * array, size_t size);

/// Finalize array of srv/OperatorCommand messages.
/**
 * It calls
 * zfc_interfaces__srv__OperatorCommand_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__srv__OperatorCommand_Response__Sequence__fini(zfc_interfaces__srv__OperatorCommand_Response__Sequence * array);

/// Create array of srv/OperatorCommand messages.
/**
 * It allocates the memory for the array and calls
 * zfc_interfaces__srv__OperatorCommand_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
zfc_interfaces__srv__OperatorCommand_Response__Sequence *
zfc_interfaces__srv__OperatorCommand_Response__Sequence__create(size_t size);

/// Destroy array of srv/OperatorCommand messages.
/**
 * It calls
 * zfc_interfaces__srv__OperatorCommand_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
void
zfc_interfaces__srv__OperatorCommand_Response__Sequence__destroy(zfc_interfaces__srv__OperatorCommand_Response__Sequence * array);

/// Check for srv/OperatorCommand message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_zfc_interfaces
bool
zfc_interfaces__srv__OperatorCommand_Response__Sequence__are_equal(const zfc_interfaces__srv__OperatorCommand_Response__Sequence * lhs, const zfc_interfaces__srv__OperatorCommand_Response__Sequence * rhs);

/// Copy an array of srv/OperatorCommand messages.
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
zfc_interfaces__srv__OperatorCommand_Response__Sequence__copy(
  const zfc_interfaces__srv__OperatorCommand_Response__Sequence * input,
  zfc_interfaces__srv__OperatorCommand_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__FUNCTIONS_H_
