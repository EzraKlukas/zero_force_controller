// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from zfc_interfaces:msg/TrialStatus.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__TRIAL_STATUS__BUILDER_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__TRIAL_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "zfc_interfaces/msg/detail/trial_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace zfc_interfaces
{

namespace msg
{

namespace builder
{

class Init_TrialStatus_capture_complete
{
public:
  explicit Init_TrialStatus_capture_complete(::zfc_interfaces::msg::TrialStatus & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::msg::TrialStatus capture_complete(::zfc_interfaces::msg::TrialStatus::_capture_complete_type arg)
  {
    msg_.capture_complete = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::msg::TrialStatus msg_;
};

class Init_TrialStatus_successful
{
public:
  explicit Init_TrialStatus_successful(::zfc_interfaces::msg::TrialStatus & msg)
  : msg_(msg)
  {}
  Init_TrialStatus_capture_complete successful(::zfc_interfaces::msg::TrialStatus::_successful_type arg)
  {
    msg_.successful = std::move(arg);
    return Init_TrialStatus_capture_complete(msg_);
  }

private:
  ::zfc_interfaces::msg::TrialStatus msg_;
};

class Init_TrialStatus_completed
{
public:
  explicit Init_TrialStatus_completed(::zfc_interfaces::msg::TrialStatus & msg)
  : msg_(msg)
  {}
  Init_TrialStatus_successful completed(::zfc_interfaces::msg::TrialStatus::_completed_type arg)
  {
    msg_.completed = std::move(arg);
    return Init_TrialStatus_successful(msg_);
  }

private:
  ::zfc_interfaces::msg::TrialStatus msg_;
};

class Init_TrialStatus_fault_code
{
public:
  explicit Init_TrialStatus_fault_code(::zfc_interfaces::msg::TrialStatus & msg)
  : msg_(msg)
  {}
  Init_TrialStatus_completed fault_code(::zfc_interfaces::msg::TrialStatus::_fault_code_type arg)
  {
    msg_.fault_code = std::move(arg);
    return Init_TrialStatus_completed(msg_);
  }

private:
  ::zfc_interfaces::msg::TrialStatus msg_;
};

class Init_TrialStatus_phase
{
public:
  explicit Init_TrialStatus_phase(::zfc_interfaces::msg::TrialStatus & msg)
  : msg_(msg)
  {}
  Init_TrialStatus_fault_code phase(::zfc_interfaces::msg::TrialStatus::_phase_type arg)
  {
    msg_.phase = std::move(arg);
    return Init_TrialStatus_fault_code(msg_);
  }

private:
  ::zfc_interfaces::msg::TrialStatus msg_;
};

class Init_TrialStatus_failed_publication_samples
{
public:
  explicit Init_TrialStatus_failed_publication_samples(::zfc_interfaces::msg::TrialStatus & msg)
  : msg_(msg)
  {}
  Init_TrialStatus_phase failed_publication_samples(::zfc_interfaces::msg::TrialStatus::_failed_publication_samples_type arg)
  {
    msg_.failed_publication_samples = std::move(arg);
    return Init_TrialStatus_phase(msg_);
  }

private:
  ::zfc_interfaces::msg::TrialStatus msg_;
};

class Init_TrialStatus_dropped_samples
{
public:
  explicit Init_TrialStatus_dropped_samples(::zfc_interfaces::msg::TrialStatus & msg)
  : msg_(msg)
  {}
  Init_TrialStatus_failed_publication_samples dropped_samples(::zfc_interfaces::msg::TrialStatus::_dropped_samples_type arg)
  {
    msg_.dropped_samples = std::move(arg);
    return Init_TrialStatus_failed_publication_samples(msg_);
  }

private:
  ::zfc_interfaces::msg::TrialStatus msg_;
};

class Init_TrialStatus_final_sequence
{
public:
  explicit Init_TrialStatus_final_sequence(::zfc_interfaces::msg::TrialStatus & msg)
  : msg_(msg)
  {}
  Init_TrialStatus_dropped_samples final_sequence(::zfc_interfaces::msg::TrialStatus::_final_sequence_type arg)
  {
    msg_.final_sequence = std::move(arg);
    return Init_TrialStatus_dropped_samples(msg_);
  }

private:
  ::zfc_interfaces::msg::TrialStatus msg_;
};

class Init_TrialStatus_trial_id
{
public:
  explicit Init_TrialStatus_trial_id(::zfc_interfaces::msg::TrialStatus & msg)
  : msg_(msg)
  {}
  Init_TrialStatus_final_sequence trial_id(::zfc_interfaces::msg::TrialStatus::_trial_id_type arg)
  {
    msg_.trial_id = std::move(arg);
    return Init_TrialStatus_final_sequence(msg_);
  }

private:
  ::zfc_interfaces::msg::TrialStatus msg_;
};

class Init_TrialStatus_stamp
{
public:
  Init_TrialStatus_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TrialStatus_trial_id stamp(::zfc_interfaces::msg::TrialStatus::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_TrialStatus_trial_id(msg_);
  }

private:
  ::zfc_interfaces::msg::TrialStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::msg::TrialStatus>()
{
  return zfc_interfaces::msg::builder::Init_TrialStatus_stamp();
}

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__MSG__DETAIL__TRIAL_STATUS__BUILDER_HPP_
