// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from zfc_interfaces:msg/AnalysisState.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__BUILDER_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "zfc_interfaces/msg/detail/analysis_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace zfc_interfaces
{

namespace msg
{

namespace builder
{

class Init_AnalysisState_trial_directory
{
public:
  explicit Init_AnalysisState_trial_directory(::zfc_interfaces::msg::AnalysisState & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::msg::AnalysisState trial_directory(::zfc_interfaces::msg::AnalysisState::_trial_directory_type arg)
  {
    msg_.trial_directory = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::msg::AnalysisState msg_;
};

class Init_AnalysisState_operation_pending
{
public:
  explicit Init_AnalysisState_operation_pending(::zfc_interfaces::msg::AnalysisState & msg)
  : msg_(msg)
  {}
  Init_AnalysisState_trial_directory operation_pending(::zfc_interfaces::msg::AnalysisState::_operation_pending_type arg)
  {
    msg_.operation_pending = std::move(arg);
    return Init_AnalysisState_trial_directory(msg_);
  }

private:
  ::zfc_interfaces::msg::AnalysisState msg_;
};

class Init_AnalysisState_backend
{
public:
  explicit Init_AnalysisState_backend(::zfc_interfaces::msg::AnalysisState & msg)
  : msg_(msg)
  {}
  Init_AnalysisState_operation_pending backend(::zfc_interfaces::msg::AnalysisState::_backend_type arg)
  {
    msg_.backend = std::move(arg);
    return Init_AnalysisState_operation_pending(msg_);
  }

private:
  ::zfc_interfaces::msg::AnalysisState msg_;
};

class Init_AnalysisState_fit
{
public:
  explicit Init_AnalysisState_fit(::zfc_interfaces::msg::AnalysisState & msg)
  : msg_(msg)
  {}
  Init_AnalysisState_backend fit(::zfc_interfaces::msg::AnalysisState::_fit_type arg)
  {
    msg_.fit = std::move(arg);
    return Init_AnalysisState_backend(msg_);
  }

private:
  ::zfc_interfaces::msg::AnalysisState msg_;
};

class Init_AnalysisState_detail
{
public:
  explicit Init_AnalysisState_detail(::zfc_interfaces::msg::AnalysisState & msg)
  : msg_(msg)
  {}
  Init_AnalysisState_fit detail(::zfc_interfaces::msg::AnalysisState::_detail_type arg)
  {
    msg_.detail = std::move(arg);
    return Init_AnalysisState_fit(msg_);
  }

private:
  ::zfc_interfaces::msg::AnalysisState msg_;
};

class Init_AnalysisState_stop_acknowledged
{
public:
  explicit Init_AnalysisState_stop_acknowledged(::zfc_interfaces::msg::AnalysisState & msg)
  : msg_(msg)
  {}
  Init_AnalysisState_detail stop_acknowledged(::zfc_interfaces::msg::AnalysisState::_stop_acknowledged_type arg)
  {
    msg_.stop_acknowledged = std::move(arg);
    return Init_AnalysisState_detail(msg_);
  }

private:
  ::zfc_interfaces::msg::AnalysisState msg_;
};

class Init_AnalysisState_final_sequence
{
public:
  explicit Init_AnalysisState_final_sequence(::zfc_interfaces::msg::AnalysisState & msg)
  : msg_(msg)
  {}
  Init_AnalysisState_stop_acknowledged final_sequence(::zfc_interfaces::msg::AnalysisState::_final_sequence_type arg)
  {
    msg_.final_sequence = std::move(arg);
    return Init_AnalysisState_stop_acknowledged(msg_);
  }

private:
  ::zfc_interfaces::msg::AnalysisState msg_;
};

class Init_AnalysisState_dropped_samples
{
public:
  explicit Init_AnalysisState_dropped_samples(::zfc_interfaces::msg::AnalysisState & msg)
  : msg_(msg)
  {}
  Init_AnalysisState_final_sequence dropped_samples(::zfc_interfaces::msg::AnalysisState::_dropped_samples_type arg)
  {
    msg_.dropped_samples = std::move(arg);
    return Init_AnalysisState_final_sequence(msg_);
  }

private:
  ::zfc_interfaces::msg::AnalysisState msg_;
};

class Init_AnalysisState_recorded_samples
{
public:
  explicit Init_AnalysisState_recorded_samples(::zfc_interfaces::msg::AnalysisState & msg)
  : msg_(msg)
  {}
  Init_AnalysisState_dropped_samples recorded_samples(::zfc_interfaces::msg::AnalysisState::_recorded_samples_type arg)
  {
    msg_.recorded_samples = std::move(arg);
    return Init_AnalysisState_dropped_samples(msg_);
  }

private:
  ::zfc_interfaces::msg::AnalysisState msg_;
};

class Init_AnalysisState_progress
{
public:
  explicit Init_AnalysisState_progress(::zfc_interfaces::msg::AnalysisState & msg)
  : msg_(msg)
  {}
  Init_AnalysisState_recorded_samples progress(::zfc_interfaces::msg::AnalysisState::_progress_type arg)
  {
    msg_.progress = std::move(arg);
    return Init_AnalysisState_recorded_samples(msg_);
  }

private:
  ::zfc_interfaces::msg::AnalysisState msg_;
};

class Init_AnalysisState_stage_code
{
public:
  explicit Init_AnalysisState_stage_code(::zfc_interfaces::msg::AnalysisState & msg)
  : msg_(msg)
  {}
  Init_AnalysisState_progress stage_code(::zfc_interfaces::msg::AnalysisState::_stage_code_type arg)
  {
    msg_.stage_code = std::move(arg);
    return Init_AnalysisState_progress(msg_);
  }

private:
  ::zfc_interfaces::msg::AnalysisState msg_;
};

class Init_AnalysisState_stage
{
public:
  explicit Init_AnalysisState_stage(::zfc_interfaces::msg::AnalysisState & msg)
  : msg_(msg)
  {}
  Init_AnalysisState_stage_code stage(::zfc_interfaces::msg::AnalysisState::_stage_type arg)
  {
    msg_.stage = std::move(arg);
    return Init_AnalysisState_stage_code(msg_);
  }

private:
  ::zfc_interfaces::msg::AnalysisState msg_;
};

class Init_AnalysisState_trial_id
{
public:
  explicit Init_AnalysisState_trial_id(::zfc_interfaces::msg::AnalysisState & msg)
  : msg_(msg)
  {}
  Init_AnalysisState_stage trial_id(::zfc_interfaces::msg::AnalysisState::_trial_id_type arg)
  {
    msg_.trial_id = std::move(arg);
    return Init_AnalysisState_stage(msg_);
  }

private:
  ::zfc_interfaces::msg::AnalysisState msg_;
};

class Init_AnalysisState_header
{
public:
  Init_AnalysisState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AnalysisState_trial_id header(::zfc_interfaces::msg::AnalysisState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_AnalysisState_trial_id(msg_);
  }

private:
  ::zfc_interfaces::msg::AnalysisState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::msg::AnalysisState>()
{
  return zfc_interfaces::msg::builder::Init_AnalysisState_header();
}

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__MSG__DETAIL__ANALYSIS_STATE__BUILDER_HPP_
