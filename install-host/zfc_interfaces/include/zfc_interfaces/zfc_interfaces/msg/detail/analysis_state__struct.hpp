// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from zfc_interfaces:msg/AnalysisState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__STRUCT_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__STRUCT_HPP_

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
// Member 'fit'
#include "zfc_interfaces/msg/detail/calibration_result__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__msg__AnalysisState __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__msg__AnalysisState __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AnalysisState_
{
  using Type = AnalysisState_<ContainerAllocator>;

  explicit AnalysisState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    fit(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->trial_id = 0ull;
      this->stage = "";
      this->stage_code = 0;
      this->progress = 0.0;
      this->recorded_samples = 0ull;
      this->dropped_samples = 0ull;
      this->final_sequence = 0ull;
      this->stop_acknowledged = false;
      this->detail = "";
      this->backend = "";
      this->operation_pending = false;
      this->trial_directory = "";
    }
  }

  explicit AnalysisState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    stage(_alloc),
    detail(_alloc),
    fit(_alloc, _init),
    backend(_alloc),
    trial_directory(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->trial_id = 0ull;
      this->stage = "";
      this->stage_code = 0;
      this->progress = 0.0;
      this->recorded_samples = 0ull;
      this->dropped_samples = 0ull;
      this->final_sequence = 0ull;
      this->stop_acknowledged = false;
      this->detail = "";
      this->backend = "";
      this->operation_pending = false;
      this->trial_directory = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _trial_id_type =
    uint64_t;
  _trial_id_type trial_id;
  using _stage_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _stage_type stage;
  using _stage_code_type =
    uint8_t;
  _stage_code_type stage_code;
  using _progress_type =
    double;
  _progress_type progress;
  using _recorded_samples_type =
    uint64_t;
  _recorded_samples_type recorded_samples;
  using _dropped_samples_type =
    uint64_t;
  _dropped_samples_type dropped_samples;
  using _final_sequence_type =
    uint64_t;
  _final_sequence_type final_sequence;
  using _stop_acknowledged_type =
    bool;
  _stop_acknowledged_type stop_acknowledged;
  using _detail_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _detail_type detail;
  using _fit_type =
    zfc_interfaces::msg::CalibrationResult_<ContainerAllocator>;
  _fit_type fit;
  using _backend_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _backend_type backend;
  using _operation_pending_type =
    bool;
  _operation_pending_type operation_pending;
  using _trial_directory_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _trial_directory_type trial_directory;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__trial_id(
    const uint64_t & _arg)
  {
    this->trial_id = _arg;
    return *this;
  }
  Type & set__stage(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->stage = _arg;
    return *this;
  }
  Type & set__stage_code(
    const uint8_t & _arg)
  {
    this->stage_code = _arg;
    return *this;
  }
  Type & set__progress(
    const double & _arg)
  {
    this->progress = _arg;
    return *this;
  }
  Type & set__recorded_samples(
    const uint64_t & _arg)
  {
    this->recorded_samples = _arg;
    return *this;
  }
  Type & set__dropped_samples(
    const uint64_t & _arg)
  {
    this->dropped_samples = _arg;
    return *this;
  }
  Type & set__final_sequence(
    const uint64_t & _arg)
  {
    this->final_sequence = _arg;
    return *this;
  }
  Type & set__stop_acknowledged(
    const bool & _arg)
  {
    this->stop_acknowledged = _arg;
    return *this;
  }
  Type & set__detail(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->detail = _arg;
    return *this;
  }
  Type & set__fit(
    const zfc_interfaces::msg::CalibrationResult_<ContainerAllocator> & _arg)
  {
    this->fit = _arg;
    return *this;
  }
  Type & set__backend(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->backend = _arg;
    return *this;
  }
  Type & set__operation_pending(
    const bool & _arg)
  {
    this->operation_pending = _arg;
    return *this;
  }
  Type & set__trial_directory(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->trial_directory = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::msg::AnalysisState_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::msg::AnalysisState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::msg::AnalysisState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::msg::AnalysisState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::msg::AnalysisState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::msg::AnalysisState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::msg::AnalysisState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::msg::AnalysisState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::msg::AnalysisState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::msg::AnalysisState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__msg__AnalysisState
    std::shared_ptr<zfc_interfaces::msg::AnalysisState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__msg__AnalysisState
    std::shared_ptr<zfc_interfaces::msg::AnalysisState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AnalysisState_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->trial_id != other.trial_id) {
      return false;
    }
    if (this->stage != other.stage) {
      return false;
    }
    if (this->stage_code != other.stage_code) {
      return false;
    }
    if (this->progress != other.progress) {
      return false;
    }
    if (this->recorded_samples != other.recorded_samples) {
      return false;
    }
    if (this->dropped_samples != other.dropped_samples) {
      return false;
    }
    if (this->final_sequence != other.final_sequence) {
      return false;
    }
    if (this->stop_acknowledged != other.stop_acknowledged) {
      return false;
    }
    if (this->detail != other.detail) {
      return false;
    }
    if (this->fit != other.fit) {
      return false;
    }
    if (this->backend != other.backend) {
      return false;
    }
    if (this->operation_pending != other.operation_pending) {
      return false;
    }
    if (this->trial_directory != other.trial_directory) {
      return false;
    }
    return true;
  }
  bool operator!=(const AnalysisState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AnalysisState_

// alias to use template instance with default allocator
using AnalysisState =
  zfc_interfaces::msg::AnalysisState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__STRUCT_HPP_
