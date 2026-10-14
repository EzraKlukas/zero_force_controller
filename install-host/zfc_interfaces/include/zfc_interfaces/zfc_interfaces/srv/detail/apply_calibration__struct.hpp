// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from zfc_interfaces:srv/ApplyCalibration.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__SRV__DETAIL__APPLY_CALIBRATION__STRUCT_HPP_
#define ZFC_INTERFACES__SRV__DETAIL__APPLY_CALIBRATION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__srv__ApplyCalibration_Request __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__srv__ApplyCalibration_Request __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ApplyCalibration_Request_
{
  using Type = ApplyCalibration_Request_<ContainerAllocator>;

  explicit ApplyCalibration_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result_file = "";
    }
  }

  explicit ApplyCalibration_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result_file(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result_file = "";
    }
  }

  // field types and members
  using _result_file_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _result_file_type result_file;

  // setters for named parameter idiom
  Type & set__result_file(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->result_file = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::srv::ApplyCalibration_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::srv::ApplyCalibration_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::srv::ApplyCalibration_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::srv::ApplyCalibration_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::srv::ApplyCalibration_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::srv::ApplyCalibration_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::srv::ApplyCalibration_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::srv::ApplyCalibration_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::srv::ApplyCalibration_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::srv::ApplyCalibration_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__srv__ApplyCalibration_Request
    std::shared_ptr<zfc_interfaces::srv::ApplyCalibration_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__srv__ApplyCalibration_Request
    std::shared_ptr<zfc_interfaces::srv::ApplyCalibration_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ApplyCalibration_Request_ & other) const
  {
    if (this->result_file != other.result_file) {
      return false;
    }
    return true;
  }
  bool operator!=(const ApplyCalibration_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ApplyCalibration_Request_

// alias to use template instance with default allocator
using ApplyCalibration_Request =
  zfc_interfaces::srv::ApplyCalibration_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace zfc_interfaces


// Include directives for member types
// Member 'fit'
#include "zfc_interfaces/msg/detail/calibration_result__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__srv__ApplyCalibration_Response __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__srv__ApplyCalibration_Response __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ApplyCalibration_Response_
{
  using Type = ApplyCalibration_Response_<ContainerAllocator>;

  explicit ApplyCalibration_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : fit(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit ApplyCalibration_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc),
    fit(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _fit_type =
    zfc_interfaces::msg::CalibrationResult_<ContainerAllocator>;
  _fit_type fit;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }
  Type & set__fit(
    const zfc_interfaces::msg::CalibrationResult_<ContainerAllocator> & _arg)
  {
    this->fit = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::srv::ApplyCalibration_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::srv::ApplyCalibration_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::srv::ApplyCalibration_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::srv::ApplyCalibration_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::srv::ApplyCalibration_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::srv::ApplyCalibration_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::srv::ApplyCalibration_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::srv::ApplyCalibration_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::srv::ApplyCalibration_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::srv::ApplyCalibration_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__srv__ApplyCalibration_Response
    std::shared_ptr<zfc_interfaces::srv::ApplyCalibration_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__srv__ApplyCalibration_Response
    std::shared_ptr<zfc_interfaces::srv::ApplyCalibration_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ApplyCalibration_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->fit != other.fit) {
      return false;
    }
    return true;
  }
  bool operator!=(const ApplyCalibration_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ApplyCalibration_Response_

// alias to use template instance with default allocator
using ApplyCalibration_Response =
  zfc_interfaces::srv::ApplyCalibration_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace zfc_interfaces

namespace zfc_interfaces
{

namespace srv
{

struct ApplyCalibration
{
  using Request = zfc_interfaces::srv::ApplyCalibration_Request;
  using Response = zfc_interfaces::srv::ApplyCalibration_Response;
};

}  // namespace srv

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__SRV__DETAIL__APPLY_CALIBRATION__STRUCT_HPP_
