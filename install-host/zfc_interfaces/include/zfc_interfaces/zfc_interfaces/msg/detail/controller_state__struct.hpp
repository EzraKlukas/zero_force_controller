// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from zfc_interfaces:msg/ControllerState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__CONTROLLER_STATE__STRUCT_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__CONTROLLER_STATE__STRUCT_HPP_

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
# define DEPRECATED__zfc_interfaces__msg__ControllerState __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__msg__ControllerState __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ControllerState_
{
  using Type = ControllerState_<ContainerAllocator>;

  explicit ControllerState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->trial_id = 0ull;
      this->sequence = 0ull;
      this->phase = 0;
      this->fault_code = 0;
      this->valid = false;
      this->position_m = 0.0;
      this->velocity_mps = 0.0;
      this->force_n = 0.0;
      this->reference_position_m = 0.0;
      this->reference_velocity_mps = 0.0;
      this->reference_acceleration_mps2 = 0.0;
      this->baseline_force_n = 0.0;
      this->noise_rms_n = 0.0;
      this->residual_force_n = 0.0;
      this->progress = 0.0;
      this->excessive_periods = 0ull;
    }
  }

  explicit ControllerState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->trial_id = 0ull;
      this->sequence = 0ull;
      this->phase = 0;
      this->fault_code = 0;
      this->valid = false;
      this->position_m = 0.0;
      this->velocity_mps = 0.0;
      this->force_n = 0.0;
      this->reference_position_m = 0.0;
      this->reference_velocity_mps = 0.0;
      this->reference_acceleration_mps2 = 0.0;
      this->baseline_force_n = 0.0;
      this->noise_rms_n = 0.0;
      this->residual_force_n = 0.0;
      this->progress = 0.0;
      this->excessive_periods = 0ull;
    }
  }

  // field types and members
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _trial_id_type =
    uint64_t;
  _trial_id_type trial_id;
  using _sequence_type =
    uint64_t;
  _sequence_type sequence;
  using _phase_type =
    uint8_t;
  _phase_type phase;
  using _fault_code_type =
    uint8_t;
  _fault_code_type fault_code;
  using _valid_type =
    bool;
  _valid_type valid;
  using _position_m_type =
    double;
  _position_m_type position_m;
  using _velocity_mps_type =
    double;
  _velocity_mps_type velocity_mps;
  using _force_n_type =
    double;
  _force_n_type force_n;
  using _reference_position_m_type =
    double;
  _reference_position_m_type reference_position_m;
  using _reference_velocity_mps_type =
    double;
  _reference_velocity_mps_type reference_velocity_mps;
  using _reference_acceleration_mps2_type =
    double;
  _reference_acceleration_mps2_type reference_acceleration_mps2;
  using _baseline_force_n_type =
    double;
  _baseline_force_n_type baseline_force_n;
  using _noise_rms_n_type =
    double;
  _noise_rms_n_type noise_rms_n;
  using _residual_force_n_type =
    double;
  _residual_force_n_type residual_force_n;
  using _progress_type =
    double;
  _progress_type progress;
  using _excessive_periods_type =
    uint64_t;
  _excessive_periods_type excessive_periods;

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
  Type & set__sequence(
    const uint64_t & _arg)
  {
    this->sequence = _arg;
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
  Type & set__valid(
    const bool & _arg)
  {
    this->valid = _arg;
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
  Type & set__reference_position_m(
    const double & _arg)
  {
    this->reference_position_m = _arg;
    return *this;
  }
  Type & set__reference_velocity_mps(
    const double & _arg)
  {
    this->reference_velocity_mps = _arg;
    return *this;
  }
  Type & set__reference_acceleration_mps2(
    const double & _arg)
  {
    this->reference_acceleration_mps2 = _arg;
    return *this;
  }
  Type & set__baseline_force_n(
    const double & _arg)
  {
    this->baseline_force_n = _arg;
    return *this;
  }
  Type & set__noise_rms_n(
    const double & _arg)
  {
    this->noise_rms_n = _arg;
    return *this;
  }
  Type & set__residual_force_n(
    const double & _arg)
  {
    this->residual_force_n = _arg;
    return *this;
  }
  Type & set__progress(
    const double & _arg)
  {
    this->progress = _arg;
    return *this;
  }
  Type & set__excessive_periods(
    const uint64_t & _arg)
  {
    this->excessive_periods = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::msg::ControllerState_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::msg::ControllerState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::msg::ControllerState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::msg::ControllerState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::msg::ControllerState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::msg::ControllerState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::msg::ControllerState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::msg::ControllerState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::msg::ControllerState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::msg::ControllerState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__msg__ControllerState
    std::shared_ptr<zfc_interfaces::msg::ControllerState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__msg__ControllerState
    std::shared_ptr<zfc_interfaces::msg::ControllerState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ControllerState_ & other) const
  {
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->trial_id != other.trial_id) {
      return false;
    }
    if (this->sequence != other.sequence) {
      return false;
    }
    if (this->phase != other.phase) {
      return false;
    }
    if (this->fault_code != other.fault_code) {
      return false;
    }
    if (this->valid != other.valid) {
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
    if (this->reference_position_m != other.reference_position_m) {
      return false;
    }
    if (this->reference_velocity_mps != other.reference_velocity_mps) {
      return false;
    }
    if (this->reference_acceleration_mps2 != other.reference_acceleration_mps2) {
      return false;
    }
    if (this->baseline_force_n != other.baseline_force_n) {
      return false;
    }
    if (this->noise_rms_n != other.noise_rms_n) {
      return false;
    }
    if (this->residual_force_n != other.residual_force_n) {
      return false;
    }
    if (this->progress != other.progress) {
      return false;
    }
    if (this->excessive_periods != other.excessive_periods) {
      return false;
    }
    return true;
  }
  bool operator!=(const ControllerState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ControllerState_

// alias to use template instance with default allocator
using ControllerState =
  zfc_interfaces::msg::ControllerState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__MSG__DETAIL__CONTROLLER_STATE__STRUCT_HPP_
