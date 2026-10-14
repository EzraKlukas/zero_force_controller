// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from zfc_interfaces:msg/CalibrationResult.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__CALIBRATION_RESULT__STRUCT_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__CALIBRATION_RESULT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__msg__CalibrationResult __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__msg__CalibrationResult __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CalibrationResult_
{
  using Type = CalibrationResult_<ContainerAllocator>;

  explicit CalibrationResult_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->valid = false;
      this->reason = "";
      this->inertial_force_coefficient_kg = 0.0;
      this->intercept_n = 0.0;
      this->r_squared = 0.0;
      this->residual_rms_n = 0.0;
      this->uncertainty_kg = 0.0;
      this->sample_count = 0ull;
      this->plateau_count = 0ull;
      this->positive_slope_kg = 0.0;
      this->negative_slope_kg = 0.0;
      this->tracking_rms_m = 0.0;
      this->acceleration_source = "";
    }
  }

  explicit CalibrationResult_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : reason(_alloc),
    acceleration_source(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->valid = false;
      this->reason = "";
      this->inertial_force_coefficient_kg = 0.0;
      this->intercept_n = 0.0;
      this->r_squared = 0.0;
      this->residual_rms_n = 0.0;
      this->uncertainty_kg = 0.0;
      this->sample_count = 0ull;
      this->plateau_count = 0ull;
      this->positive_slope_kg = 0.0;
      this->negative_slope_kg = 0.0;
      this->tracking_rms_m = 0.0;
      this->acceleration_source = "";
    }
  }

  // field types and members
  using _valid_type =
    bool;
  _valid_type valid;
  using _reason_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _reason_type reason;
  using _inertial_force_coefficient_kg_type =
    double;
  _inertial_force_coefficient_kg_type inertial_force_coefficient_kg;
  using _intercept_n_type =
    double;
  _intercept_n_type intercept_n;
  using _r_squared_type =
    double;
  _r_squared_type r_squared;
  using _residual_rms_n_type =
    double;
  _residual_rms_n_type residual_rms_n;
  using _uncertainty_kg_type =
    double;
  _uncertainty_kg_type uncertainty_kg;
  using _sample_count_type =
    uint64_t;
  _sample_count_type sample_count;
  using _plateau_count_type =
    uint64_t;
  _plateau_count_type plateau_count;
  using _positive_slope_kg_type =
    double;
  _positive_slope_kg_type positive_slope_kg;
  using _negative_slope_kg_type =
    double;
  _negative_slope_kg_type negative_slope_kg;
  using _tracking_rms_m_type =
    double;
  _tracking_rms_m_type tracking_rms_m;
  using _acceleration_source_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _acceleration_source_type acceleration_source;

  // setters for named parameter idiom
  Type & set__valid(
    const bool & _arg)
  {
    this->valid = _arg;
    return *this;
  }
  Type & set__reason(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->reason = _arg;
    return *this;
  }
  Type & set__inertial_force_coefficient_kg(
    const double & _arg)
  {
    this->inertial_force_coefficient_kg = _arg;
    return *this;
  }
  Type & set__intercept_n(
    const double & _arg)
  {
    this->intercept_n = _arg;
    return *this;
  }
  Type & set__r_squared(
    const double & _arg)
  {
    this->r_squared = _arg;
    return *this;
  }
  Type & set__residual_rms_n(
    const double & _arg)
  {
    this->residual_rms_n = _arg;
    return *this;
  }
  Type & set__uncertainty_kg(
    const double & _arg)
  {
    this->uncertainty_kg = _arg;
    return *this;
  }
  Type & set__sample_count(
    const uint64_t & _arg)
  {
    this->sample_count = _arg;
    return *this;
  }
  Type & set__plateau_count(
    const uint64_t & _arg)
  {
    this->plateau_count = _arg;
    return *this;
  }
  Type & set__positive_slope_kg(
    const double & _arg)
  {
    this->positive_slope_kg = _arg;
    return *this;
  }
  Type & set__negative_slope_kg(
    const double & _arg)
  {
    this->negative_slope_kg = _arg;
    return *this;
  }
  Type & set__tracking_rms_m(
    const double & _arg)
  {
    this->tracking_rms_m = _arg;
    return *this;
  }
  Type & set__acceleration_source(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->acceleration_source = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::msg::CalibrationResult_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::msg::CalibrationResult_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::msg::CalibrationResult_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::msg::CalibrationResult_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::msg::CalibrationResult_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::msg::CalibrationResult_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::msg::CalibrationResult_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::msg::CalibrationResult_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::msg::CalibrationResult_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::msg::CalibrationResult_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__msg__CalibrationResult
    std::shared_ptr<zfc_interfaces::msg::CalibrationResult_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__msg__CalibrationResult
    std::shared_ptr<zfc_interfaces::msg::CalibrationResult_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CalibrationResult_ & other) const
  {
    if (this->valid != other.valid) {
      return false;
    }
    if (this->reason != other.reason) {
      return false;
    }
    if (this->inertial_force_coefficient_kg != other.inertial_force_coefficient_kg) {
      return false;
    }
    if (this->intercept_n != other.intercept_n) {
      return false;
    }
    if (this->r_squared != other.r_squared) {
      return false;
    }
    if (this->residual_rms_n != other.residual_rms_n) {
      return false;
    }
    if (this->uncertainty_kg != other.uncertainty_kg) {
      return false;
    }
    if (this->sample_count != other.sample_count) {
      return false;
    }
    if (this->plateau_count != other.plateau_count) {
      return false;
    }
    if (this->positive_slope_kg != other.positive_slope_kg) {
      return false;
    }
    if (this->negative_slope_kg != other.negative_slope_kg) {
      return false;
    }
    if (this->tracking_rms_m != other.tracking_rms_m) {
      return false;
    }
    if (this->acceleration_source != other.acceleration_source) {
      return false;
    }
    return true;
  }
  bool operator!=(const CalibrationResult_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CalibrationResult_

// alias to use template instance with default allocator
using CalibrationResult =
  zfc_interfaces::msg::CalibrationResult_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__MSG__DETAIL__CALIBRATION_RESULT__STRUCT_HPP_
