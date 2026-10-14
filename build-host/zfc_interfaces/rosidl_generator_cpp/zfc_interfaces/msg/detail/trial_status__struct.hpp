// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from zfc_interfaces:msg/TrialStatus.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__TRIAL_STATUS__STRUCT_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__TRIAL_STATUS__STRUCT_HPP_

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

#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__msg__TrialStatus __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__msg__TrialStatus __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TrialStatus_
{
  using Type = TrialStatus_<ContainerAllocator>;

  explicit TrialStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->trial_id = 0ull;
      this->final_sequence = 0ull;
      this->dropped_samples = 0ull;
      this->failed_publication_samples = 0ull;
      this->phase = 0;
      this->fault_code = 0;
      this->completed = false;
      this->successful = false;
      this->capture_complete = false;
    }
  }

  explicit TrialStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->trial_id = 0ull;
      this->final_sequence = 0ull;
      this->dropped_samples = 0ull;
      this->failed_publication_samples = 0ull;
      this->phase = 0;
      this->fault_code = 0;
      this->completed = false;
      this->successful = false;
      this->capture_complete = false;
    }
  }

  // field types and members
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _trial_id_type =
    uint64_t;
  _trial_id_type trial_id;
  using _final_sequence_type =
    uint64_t;
  _final_sequence_type final_sequence;
  using _dropped_samples_type =
    uint64_t;
  _dropped_samples_type dropped_samples;
  using _failed_publication_samples_type =
    uint64_t;
  _failed_publication_samples_type failed_publication_samples;
  using _phase_type =
    uint8_t;
  _phase_type phase;
  using _fault_code_type =
    uint8_t;
  _fault_code_type fault_code;
  using _completed_type =
    bool;
  _completed_type completed;
  using _successful_type =
    bool;
  _successful_type successful;
  using _capture_complete_type =
    bool;
  _capture_complete_type capture_complete;

  // setters for named parameter idiom
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__trial_id(
    const uint64_t & _arg)
  {
    this->trial_id = _arg;
    return *this;
  }
  Type & set__final_sequence(
    const uint64_t & _arg)
  {
    this->final_sequence = _arg;
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
  Type & set__phase(
    const uint8_t & _arg)
  {
    this->phase = _arg;
    return *this;
  }
  Type & set__fault_code(
    const uint8_t & _arg)
  {
    this->fault_code = _arg;
    return *this;
  }
  Type & set__completed(
    const bool & _arg)
  {
    this->completed = _arg;
    return *this;
  }
  Type & set__successful(
    const bool & _arg)
  {
    this->successful = _arg;
    return *this;
  }
  Type & set__capture_complete(
    const bool & _arg)
  {
    this->capture_complete = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::msg::TrialStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::msg::TrialStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::msg::TrialStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::msg::TrialStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::msg::TrialStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::msg::TrialStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::msg::TrialStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::msg::TrialStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::msg::TrialStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::msg::TrialStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__msg__TrialStatus
    std::shared_ptr<zfc_interfaces::msg::TrialStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__msg__TrialStatus
    std::shared_ptr<zfc_interfaces::msg::TrialStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TrialStatus_ & other) const
  {
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->trial_id != other.trial_id) {
      return false;
    }
    if (this->final_sequence != other.final_sequence) {
      return false;
    }
    if (this->dropped_samples != other.dropped_samples) {
      return false;
    }
    if (this->failed_publication_samples != other.failed_publication_samples) {
      return false;
    }
    if (this->phase != other.phase) {
      return false;
    }
    if (this->fault_code != other.fault_code) {
      return false;
    }
    if (this->completed != other.completed) {
      return false;
    }
    if (this->successful != other.successful) {
      return false;
    }
    if (this->capture_complete != other.capture_complete) {
      return false;
    }
    return true;
  }
  bool operator!=(const TrialStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TrialStatus_

// alias to use template instance with default allocator
using TrialStatus =
  zfc_interfaces::msg::TrialStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__MSG__DETAIL__TRIAL_STATUS__STRUCT_HPP_
