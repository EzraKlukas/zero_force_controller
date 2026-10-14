// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from zfc_interfaces:srv/OperatorCommand.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__STRUCT_HPP_
#define ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__srv__OperatorCommand_Request __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__srv__OperatorCommand_Request __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct OperatorCommand_Request_
{
  using Type = OperatorCommand_Request_<ContainerAllocator>;

  explicit OperatorCommand_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command = "";
      this->external_contact_clear = false;
    }
  }

  explicit OperatorCommand_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : command(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command = "";
      this->external_contact_clear = false;
    }
  }

  // field types and members
  using _command_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _command_type command;
  using _external_contact_clear_type =
    bool;
  _external_contact_clear_type external_contact_clear;

  // setters for named parameter idiom
  Type & set__command(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->command = _arg;
    return *this;
  }
  Type & set__external_contact_clear(
    const bool & _arg)
  {
    this->external_contact_clear = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::srv::OperatorCommand_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::srv::OperatorCommand_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::srv::OperatorCommand_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::srv::OperatorCommand_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::srv::OperatorCommand_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::srv::OperatorCommand_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::srv::OperatorCommand_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::srv::OperatorCommand_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::srv::OperatorCommand_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::srv::OperatorCommand_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__srv__OperatorCommand_Request
    std::shared_ptr<zfc_interfaces::srv::OperatorCommand_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__srv__OperatorCommand_Request
    std::shared_ptr<zfc_interfaces::srv::OperatorCommand_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const OperatorCommand_Request_ & other) const
  {
    if (this->command != other.command) {
      return false;
    }
    if (this->external_contact_clear != other.external_contact_clear) {
      return false;
    }
    return true;
  }
  bool operator!=(const OperatorCommand_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct OperatorCommand_Request_

// alias to use template instance with default allocator
using OperatorCommand_Request =
  zfc_interfaces::srv::OperatorCommand_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace zfc_interfaces


#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__srv__OperatorCommand_Response __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__srv__OperatorCommand_Response __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct OperatorCommand_Response_
{
  using Type = OperatorCommand_Response_<ContainerAllocator>;

  explicit OperatorCommand_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->stop_acknowledged = false;
      this->message = "";
    }
  }

  explicit OperatorCommand_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->stop_acknowledged = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _stop_acknowledged_type =
    bool;
  _stop_acknowledged_type stop_acknowledged;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__stop_acknowledged(
    const bool & _arg)
  {
    this->stop_acknowledged = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::srv::OperatorCommand_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::srv::OperatorCommand_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::srv::OperatorCommand_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::srv::OperatorCommand_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::srv::OperatorCommand_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::srv::OperatorCommand_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::srv::OperatorCommand_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::srv::OperatorCommand_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::srv::OperatorCommand_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::srv::OperatorCommand_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__srv__OperatorCommand_Response
    std::shared_ptr<zfc_interfaces::srv::OperatorCommand_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__srv__OperatorCommand_Response
    std::shared_ptr<zfc_interfaces::srv::OperatorCommand_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const OperatorCommand_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->stop_acknowledged != other.stop_acknowledged) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const OperatorCommand_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct OperatorCommand_Response_

// alias to use template instance with default allocator
using OperatorCommand_Response =
  zfc_interfaces::srv::OperatorCommand_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace zfc_interfaces

namespace zfc_interfaces
{

namespace srv
{

struct OperatorCommand
{
  using Request = zfc_interfaces::srv::OperatorCommand_Request;
  using Response = zfc_interfaces::srv::OperatorCommand_Response;
};

}  // namespace srv

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__STRUCT_HPP_
