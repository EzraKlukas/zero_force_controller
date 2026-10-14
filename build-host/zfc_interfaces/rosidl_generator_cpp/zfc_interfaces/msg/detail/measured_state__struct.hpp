// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from zfc_interfaces:msg/MeasuredState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__MEASURED_STATE__STRUCT_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__MEASURED_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'force_stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__msg__MeasuredState __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__msg__MeasuredState __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MeasuredState_
{
  using Type = MeasuredState_<ContainerAllocator>;

  explicit MeasuredState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    force_stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->position_m = 0.0;
      this->velocity_mps = 0.0;
      this->force_n = 0.0;
      this->joint_fresh = false;
      this->force_fresh = false;
      this->valid = false;
      this->detail = "";
    }
  }

  explicit MeasuredState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    force_stamp(_alloc, _init),
    detail(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->position_m = 0.0;
      this->velocity_mps = 0.0;
      this->force_n = 0.0;
      this->joint_fresh = false;
      this->force_fresh = false;
      this->valid = false;
      this->detail = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _force_stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _force_stamp_type force_stamp;
  using _position_m_type =
    double;
  _position_m_type position_m;
  using _velocity_mps_type =
    double;
  _velocity_mps_type velocity_mps;
  using _force_n_type =
    double;
  _force_n_type force_n;
  using _joint_fresh_type =
    bool;
  _joint_fresh_type joint_fresh;
  using _force_fresh_type =
    bool;
  _force_fresh_type force_fresh;
  using _valid_type =
    bool;
  _valid_type valid;
  using _detail_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _detail_type detail;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__force_stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->force_stamp = _arg;
    return *this;
  }
  Type & set__position_m(
    const double & _arg)
  {
    this->position_m = _arg;
    return *this;
  }
  Type & set__velocity_mps(
    const double & _arg)
  {
    this->velocity_mps = _arg;
    return *this;
  }
  Type & set__force_n(
    const double & _arg)
  {
    this->force_n = _arg;
    return *this;
  }
  Type & set__joint_fresh(
    const bool & _arg)
  {
    this->joint_fresh = _arg;
    return *this;
  }
  Type & set__force_fresh(
    const bool & _arg)
  {
    this->force_fresh = _arg;
    return *this;
  }
  Type & set__valid(
    const bool & _arg)
  {
    this->valid = _arg;
    return *this;
  }
  Type & set__detail(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->detail = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::msg::MeasuredState_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::msg::MeasuredState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::msg::MeasuredState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::msg::MeasuredState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::msg::MeasuredState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::msg::MeasuredState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::msg::MeasuredState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::msg::MeasuredState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::msg::MeasuredState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::msg::MeasuredState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__msg__MeasuredState
    std::shared_ptr<zfc_interfaces::msg::MeasuredState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__msg__MeasuredState
    std::shared_ptr<zfc_interfaces::msg::MeasuredState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MeasuredState_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->force_stamp != other.force_stamp) {
      return false;
    }
    if (this->position_m != other.position_m) {
      return false;
    }
    if (this->velocity_mps != other.velocity_mps) {
      return false;
    }
    if (this->force_n != other.force_n) {
      return false;
    }
    if (this->joint_fresh != other.joint_fresh) {
      return false;
    }
    if (this->force_fresh != other.force_fresh) {
      return false;
    }
    if (this->valid != other.valid) {
      return false;
    }
    if (this->detail != other.detail) {
      return false;
    }
    return true;
  }
  bool operator!=(const MeasuredState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MeasuredState_

// alias to use template instance with default allocator
using MeasuredState =
  zfc_interfaces::msg::MeasuredState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__MSG__DETAIL__MEASURED_STATE__STRUCT_HPP_
