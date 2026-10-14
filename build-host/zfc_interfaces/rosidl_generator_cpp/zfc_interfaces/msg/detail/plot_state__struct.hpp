// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from zfc_interfaces:msg/PlotState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__PLOT_STATE__STRUCT_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__PLOT_STATE__STRUCT_HPP_

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
// Member 'state'
#include "zfc_interfaces/msg/detail/controller_state__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__msg__PlotState __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__msg__PlotState __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PlotState_
{
  using Type = PlotState_<ContainerAllocator>;

  explicit PlotState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    state(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->inertial_compensation_n = 0.0;
    }
  }

  explicit PlotState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    state(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->inertial_compensation_n = 0.0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _state_type =
    zfc_interfaces::msg::ControllerState_<ContainerAllocator>;
  _state_type state;
  using _inertial_compensation_n_type =
    double;
  _inertial_compensation_n_type inertial_compensation_n;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__state(
    const zfc_interfaces::msg::ControllerState_<ContainerAllocator> & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__inertial_compensation_n(
    const double & _arg)
  {
    this->inertial_compensation_n = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::msg::PlotState_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::msg::PlotState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::msg::PlotState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::msg::PlotState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::msg::PlotState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::msg::PlotState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::msg::PlotState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::msg::PlotState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::msg::PlotState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::msg::PlotState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__msg__PlotState
    std::shared_ptr<zfc_interfaces::msg::PlotState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__msg__PlotState
    std::shared_ptr<zfc_interfaces::msg::PlotState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlotState_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->inertial_compensation_n != other.inertial_compensation_n) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlotState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlotState_

// alias to use template instance with default allocator
using PlotState =
  zfc_interfaces::msg::PlotState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__MSG__DETAIL__PLOT_STATE__STRUCT_HPP_
