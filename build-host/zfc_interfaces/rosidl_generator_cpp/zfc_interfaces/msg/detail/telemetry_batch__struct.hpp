// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from zfc_interfaces:msg/TelemetryBatch.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__TELEMETRY_BATCH__STRUCT_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__TELEMETRY_BATCH__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"
// Member 'samples'
#include "zfc_interfaces/msg/detail/controller_state__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__msg__TelemetryBatch __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__msg__TelemetryBatch __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TelemetryBatch_
{
  using Type = TelemetryBatch_<ContainerAllocator>;

  explicit TelemetryBatch_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->dropped_samples = 0ull;
      this->failed_publication_samples = 0ull;
    }
  }

  explicit TelemetryBatch_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->dropped_samples = 0ull;
      this->failed_publication_samples = 0ull;
    }
  }

  // field types and members
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _samples_type =
    rosidl_runtime_cpp::BoundedVector<zfc_interfaces::msg::ControllerState_<ContainerAllocator>, 256, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<zfc_interfaces::msg::ControllerState_<ContainerAllocator>>>;
  _samples_type samples;
  using _dropped_samples_type =
    uint64_t;
  _dropped_samples_type dropped_samples;
  using _failed_publication_samples_type =
    uint64_t;
  _failed_publication_samples_type failed_publication_samples;

  // setters for named parameter idiom
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__samples(
    const rosidl_runtime_cpp::BoundedVector<zfc_interfaces::msg::ControllerState_<ContainerAllocator>, 256, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<zfc_interfaces::msg::ControllerState_<ContainerAllocator>>> & _arg)
  {
    this->samples = _arg;
    return *this;
  }
  Type & set__dropped_samples(
    const uint64_t & _arg)
  {
    this->dropped_samples = _arg;
    return *this;
  }
  Type & set__failed_publication_samples(
    const uint64_t & _arg)
  {
    this->failed_publication_samples = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::msg::TelemetryBatch_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::msg::TelemetryBatch_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::msg::TelemetryBatch_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::msg::TelemetryBatch_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::msg::TelemetryBatch_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::msg::TelemetryBatch_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::msg::TelemetryBatch_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::msg::TelemetryBatch_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::msg::TelemetryBatch_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::msg::TelemetryBatch_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__msg__TelemetryBatch
    std::shared_ptr<zfc_interfaces::msg::TelemetryBatch_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__msg__TelemetryBatch
    std::shared_ptr<zfc_interfaces::msg::TelemetryBatch_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TelemetryBatch_ & other) const
  {
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->samples != other.samples) {
      return false;
    }
    if (this->dropped_samples != other.dropped_samples) {
      return false;
    }
    if (this->failed_publication_samples != other.failed_publication_samples) {
      return false;
    }
    return true;
  }
  bool operator!=(const TelemetryBatch_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TelemetryBatch_

// alias to use template instance with default allocator
using TelemetryBatch =
  zfc_interfaces::msg::TelemetryBatch_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__MSG__DETAIL__TELEMETRY_BATCH__STRUCT_HPP_
