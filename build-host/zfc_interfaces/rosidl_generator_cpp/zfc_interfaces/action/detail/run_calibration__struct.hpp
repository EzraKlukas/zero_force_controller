// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from zfc_interfaces:action/RunCalibration.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__STRUCT_HPP_
#define ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__action__RunCalibration_Goal __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__action__RunCalibration_Goal __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct RunCalibration_Goal_
{
  using Type = RunCalibration_Goal_<ContainerAllocator>;

  explicit RunCalibration_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->activate_zero_force_after = false;
      this->external_contact_clear = false;
    }
  }

  explicit RunCalibration_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->activate_zero_force_after = false;
      this->external_contact_clear = false;
    }
  }

  // field types and members
  using _activate_zero_force_after_type =
    bool;
  _activate_zero_force_after_type activate_zero_force_after;
  using _external_contact_clear_type =
    bool;
  _external_contact_clear_type external_contact_clear;

  // setters for named parameter idiom
  Type & set__activate_zero_force_after(
    const bool & _arg)
  {
    this->activate_zero_force_after = _arg;
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
    zfc_interfaces::action::RunCalibration_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::action::RunCalibration_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_Goal
    std::shared_ptr<zfc_interfaces::action::RunCalibration_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_Goal
    std::shared_ptr<zfc_interfaces::action::RunCalibration_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RunCalibration_Goal_ & other) const
  {
    if (this->activate_zero_force_after != other.activate_zero_force_after) {
      return false;
    }
    if (this->external_contact_clear != other.external_contact_clear) {
      return false;
    }
    return true;
  }
  bool operator!=(const RunCalibration_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RunCalibration_Goal_

// alias to use template instance with default allocator
using RunCalibration_Goal =
  zfc_interfaces::action::RunCalibration_Goal_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace zfc_interfaces


// Include directives for member types
// Member 'fit'
#include "zfc_interfaces/msg/detail/calibration_result__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__action__RunCalibration_Result __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__action__RunCalibration_Result __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct RunCalibration_Result_
{
  using Type = RunCalibration_Result_<ContainerAllocator>;

  explicit RunCalibration_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : fit(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->trial_id = 0ull;
      this->trial_directory = "";
      this->message = "";
      this->applied = false;
      this->zero_force_active = false;
      this->stop_acknowledged = false;
    }
  }

  explicit RunCalibration_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : trial_directory(_alloc),
    message(_alloc),
    fit(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->trial_id = 0ull;
      this->trial_directory = "";
      this->message = "";
      this->applied = false;
      this->zero_force_active = false;
      this->stop_acknowledged = false;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _trial_id_type =
    uint64_t;
  _trial_id_type trial_id;
  using _trial_directory_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _trial_directory_type trial_directory;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _applied_type =
    bool;
  _applied_type applied;
  using _zero_force_active_type =
    bool;
  _zero_force_active_type zero_force_active;
  using _stop_acknowledged_type =
    bool;
  _stop_acknowledged_type stop_acknowledged;
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
  Type & set__trial_id(
    const uint64_t & _arg)
  {
    this->trial_id = _arg;
    return *this;
  }
  Type & set__trial_directory(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->trial_directory = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }
  Type & set__applied(
    const bool & _arg)
  {
    this->applied = _arg;
    return *this;
  }
  Type & set__zero_force_active(
    const bool & _arg)
  {
    this->zero_force_active = _arg;
    return *this;
  }
  Type & set__stop_acknowledged(
    const bool & _arg)
  {
    this->stop_acknowledged = _arg;
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
    zfc_interfaces::action::RunCalibration_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::action::RunCalibration_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_Result
    std::shared_ptr<zfc_interfaces::action::RunCalibration_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_Result
    std::shared_ptr<zfc_interfaces::action::RunCalibration_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RunCalibration_Result_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->trial_id != other.trial_id) {
      return false;
    }
    if (this->trial_directory != other.trial_directory) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->applied != other.applied) {
      return false;
    }
    if (this->zero_force_active != other.zero_force_active) {
      return false;
    }
    if (this->stop_acknowledged != other.stop_acknowledged) {
      return false;
    }
    if (this->fit != other.fit) {
      return false;
    }
    return true;
  }
  bool operator!=(const RunCalibration_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RunCalibration_Result_

// alias to use template instance with default allocator
using RunCalibration_Result =
  zfc_interfaces::action::RunCalibration_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace zfc_interfaces


// Include directives for member types
// Member 'state'
#include "zfc_interfaces/msg/detail/analysis_state__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__action__RunCalibration_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__action__RunCalibration_Feedback __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct RunCalibration_Feedback_
{
  using Type = RunCalibration_Feedback_<ContainerAllocator>;

  explicit RunCalibration_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : state(_init)
  {
    (void)_init;
  }

  explicit RunCalibration_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : state(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _state_type =
    zfc_interfaces::msg::AnalysisState_<ContainerAllocator>;
  _state_type state;

  // setters for named parameter idiom
  Type & set__state(
    const zfc_interfaces::msg::AnalysisState_<ContainerAllocator> & _arg)
  {
    this->state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::action::RunCalibration_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::action::RunCalibration_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_Feedback
    std::shared_ptr<zfc_interfaces::action::RunCalibration_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_Feedback
    std::shared_ptr<zfc_interfaces::action::RunCalibration_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RunCalibration_Feedback_ & other) const
  {
    if (this->state != other.state) {
      return false;
    }
    return true;
  }
  bool operator!=(const RunCalibration_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RunCalibration_Feedback_

// alias to use template instance with default allocator
using RunCalibration_Feedback =
  zfc_interfaces::action::RunCalibration_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace zfc_interfaces


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "zfc_interfaces/action/detail/run_calibration__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__action__RunCalibration_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__action__RunCalibration_SendGoal_Request __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct RunCalibration_SendGoal_Request_
{
  using Type = RunCalibration_SendGoal_Request_<ContainerAllocator>;

  explicit RunCalibration_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit RunCalibration_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    goal(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _goal_type =
    zfc_interfaces::action::RunCalibration_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const zfc_interfaces::action::RunCalibration_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::action::RunCalibration_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::action::RunCalibration_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_SendGoal_Request
    std::shared_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_SendGoal_Request
    std::shared_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RunCalibration_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const RunCalibration_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RunCalibration_SendGoal_Request_

// alias to use template instance with default allocator
using RunCalibration_SendGoal_Request =
  zfc_interfaces::action::RunCalibration_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace zfc_interfaces


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__action__RunCalibration_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__action__RunCalibration_SendGoal_Response __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct RunCalibration_SendGoal_Response_
{
  using Type = RunCalibration_SendGoal_Response_<ContainerAllocator>;

  explicit RunCalibration_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit RunCalibration_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  // field types and members
  using _accepted_type =
    bool;
  _accepted_type accepted;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__accepted(
    const bool & _arg)
  {
    this->accepted = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::action::RunCalibration_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::action::RunCalibration_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_SendGoal_Response
    std::shared_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_SendGoal_Response
    std::shared_ptr<zfc_interfaces::action::RunCalibration_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RunCalibration_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const RunCalibration_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RunCalibration_SendGoal_Response_

// alias to use template instance with default allocator
using RunCalibration_SendGoal_Response =
  zfc_interfaces::action::RunCalibration_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace zfc_interfaces

namespace zfc_interfaces
{

namespace action
{

struct RunCalibration_SendGoal
{
  using Request = zfc_interfaces::action::RunCalibration_SendGoal_Request;
  using Response = zfc_interfaces::action::RunCalibration_SendGoal_Response;
};

}  // namespace action

}  // namespace zfc_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__action__RunCalibration_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__action__RunCalibration_GetResult_Request __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct RunCalibration_GetResult_Request_
{
  using Type = RunCalibration_GetResult_Request_<ContainerAllocator>;

  explicit RunCalibration_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit RunCalibration_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::action::RunCalibration_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::action::RunCalibration_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_GetResult_Request
    std::shared_ptr<zfc_interfaces::action::RunCalibration_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_GetResult_Request
    std::shared_ptr<zfc_interfaces::action::RunCalibration_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RunCalibration_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const RunCalibration_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RunCalibration_GetResult_Request_

// alias to use template instance with default allocator
using RunCalibration_GetResult_Request =
  zfc_interfaces::action::RunCalibration_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace zfc_interfaces


// Include directives for member types
// Member 'result'
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__action__RunCalibration_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__action__RunCalibration_GetResult_Response __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct RunCalibration_GetResult_Response_
{
  using Type = RunCalibration_GetResult_Response_<ContainerAllocator>;

  explicit RunCalibration_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit RunCalibration_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  // field types and members
  using _status_type =
    int8_t;
  _status_type status;
  using _result_type =
    zfc_interfaces::action::RunCalibration_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const zfc_interfaces::action::RunCalibration_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::action::RunCalibration_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::action::RunCalibration_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_GetResult_Response
    std::shared_ptr<zfc_interfaces::action::RunCalibration_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_GetResult_Response
    std::shared_ptr<zfc_interfaces::action::RunCalibration_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RunCalibration_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const RunCalibration_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RunCalibration_GetResult_Response_

// alias to use template instance with default allocator
using RunCalibration_GetResult_Response =
  zfc_interfaces::action::RunCalibration_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace zfc_interfaces

namespace zfc_interfaces
{

namespace action
{

struct RunCalibration_GetResult
{
  using Request = zfc_interfaces::action::RunCalibration_GetResult_Request;
  using Response = zfc_interfaces::action::RunCalibration_GetResult_Response;
};

}  // namespace action

}  // namespace zfc_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "zfc_interfaces/action/detail/run_calibration__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__zfc_interfaces__action__RunCalibration_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__zfc_interfaces__action__RunCalibration_FeedbackMessage __declspec(deprecated)
#endif

namespace zfc_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct RunCalibration_FeedbackMessage_
{
  using Type = RunCalibration_FeedbackMessage_<ContainerAllocator>;

  explicit RunCalibration_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit RunCalibration_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    feedback(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _feedback_type =
    zfc_interfaces::action::RunCalibration_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const zfc_interfaces::action::RunCalibration_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    zfc_interfaces::action::RunCalibration_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const zfc_interfaces::action::RunCalibration_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<zfc_interfaces::action::RunCalibration_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      zfc_interfaces::action::RunCalibration_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<zfc_interfaces::action::RunCalibration_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<zfc_interfaces::action::RunCalibration_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_FeedbackMessage
    std::shared_ptr<zfc_interfaces::action::RunCalibration_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__zfc_interfaces__action__RunCalibration_FeedbackMessage
    std::shared_ptr<zfc_interfaces::action::RunCalibration_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RunCalibration_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const RunCalibration_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RunCalibration_FeedbackMessage_

// alias to use template instance with default allocator
using RunCalibration_FeedbackMessage =
  zfc_interfaces::action::RunCalibration_FeedbackMessage_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace zfc_interfaces

#include "action_msgs/srv/cancel_goal.hpp"
#include "action_msgs/msg/goal_info.hpp"
#include "action_msgs/msg/goal_status_array.hpp"

namespace zfc_interfaces
{

namespace action
{

struct RunCalibration
{
  /// The goal message defined in the action definition.
  using Goal = zfc_interfaces::action::RunCalibration_Goal;
  /// The result message defined in the action definition.
  using Result = zfc_interfaces::action::RunCalibration_Result;
  /// The feedback message defined in the action definition.
  using Feedback = zfc_interfaces::action::RunCalibration_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = zfc_interfaces::action::RunCalibration_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = zfc_interfaces::action::RunCalibration_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = zfc_interfaces::action::RunCalibration_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct RunCalibration RunCalibration;

}  // namespace action

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__STRUCT_HPP_
