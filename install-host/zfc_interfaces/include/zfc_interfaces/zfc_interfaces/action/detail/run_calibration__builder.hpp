// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from zfc_interfaces:action/RunCalibration.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__BUILDER_HPP_
#define ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "zfc_interfaces/action/detail/run_calibration__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace zfc_interfaces
{

namespace action
{

namespace builder
{

class Init_RunCalibration_Goal_external_contact_clear
{
public:
  explicit Init_RunCalibration_Goal_external_contact_clear(::zfc_interfaces::action::RunCalibration_Goal & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::action::RunCalibration_Goal external_contact_clear(::zfc_interfaces::action::RunCalibration_Goal::_external_contact_clear_type arg)
  {
    msg_.external_contact_clear = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_Goal msg_;
};

class Init_RunCalibration_Goal_activate_zero_force_after
{
public:
  Init_RunCalibration_Goal_activate_zero_force_after()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunCalibration_Goal_external_contact_clear activate_zero_force_after(::zfc_interfaces::action::RunCalibration_Goal::_activate_zero_force_after_type arg)
  {
    msg_.activate_zero_force_after = std::move(arg);
    return Init_RunCalibration_Goal_external_contact_clear(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::action::RunCalibration_Goal>()
{
  return zfc_interfaces::action::builder::Init_RunCalibration_Goal_activate_zero_force_after();
}

}  // namespace zfc_interfaces


namespace zfc_interfaces
{

namespace action
{

namespace builder
{

class Init_RunCalibration_Result_fit
{
public:
  explicit Init_RunCalibration_Result_fit(::zfc_interfaces::action::RunCalibration_Result & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::action::RunCalibration_Result fit(::zfc_interfaces::action::RunCalibration_Result::_fit_type arg)
  {
    msg_.fit = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_Result msg_;
};

class Init_RunCalibration_Result_stop_acknowledged
{
public:
  explicit Init_RunCalibration_Result_stop_acknowledged(::zfc_interfaces::action::RunCalibration_Result & msg)
  : msg_(msg)
  {}
  Init_RunCalibration_Result_fit stop_acknowledged(::zfc_interfaces::action::RunCalibration_Result::_stop_acknowledged_type arg)
  {
    msg_.stop_acknowledged = std::move(arg);
    return Init_RunCalibration_Result_fit(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_Result msg_;
};

class Init_RunCalibration_Result_zero_force_active
{
public:
  explicit Init_RunCalibration_Result_zero_force_active(::zfc_interfaces::action::RunCalibration_Result & msg)
  : msg_(msg)
  {}
  Init_RunCalibration_Result_stop_acknowledged zero_force_active(::zfc_interfaces::action::RunCalibration_Result::_zero_force_active_type arg)
  {
    msg_.zero_force_active = std::move(arg);
    return Init_RunCalibration_Result_stop_acknowledged(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_Result msg_;
};

class Init_RunCalibration_Result_applied
{
public:
  explicit Init_RunCalibration_Result_applied(::zfc_interfaces::action::RunCalibration_Result & msg)
  : msg_(msg)
  {}
  Init_RunCalibration_Result_zero_force_active applied(::zfc_interfaces::action::RunCalibration_Result::_applied_type arg)
  {
    msg_.applied = std::move(arg);
    return Init_RunCalibration_Result_zero_force_active(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_Result msg_;
};

class Init_RunCalibration_Result_message
{
public:
  explicit Init_RunCalibration_Result_message(::zfc_interfaces::action::RunCalibration_Result & msg)
  : msg_(msg)
  {}
  Init_RunCalibration_Result_applied message(::zfc_interfaces::action::RunCalibration_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_RunCalibration_Result_applied(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_Result msg_;
};

class Init_RunCalibration_Result_trial_directory
{
public:
  explicit Init_RunCalibration_Result_trial_directory(::zfc_interfaces::action::RunCalibration_Result & msg)
  : msg_(msg)
  {}
  Init_RunCalibration_Result_message trial_directory(::zfc_interfaces::action::RunCalibration_Result::_trial_directory_type arg)
  {
    msg_.trial_directory = std::move(arg);
    return Init_RunCalibration_Result_message(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_Result msg_;
};

class Init_RunCalibration_Result_trial_id
{
public:
  explicit Init_RunCalibration_Result_trial_id(::zfc_interfaces::action::RunCalibration_Result & msg)
  : msg_(msg)
  {}
  Init_RunCalibration_Result_trial_directory trial_id(::zfc_interfaces::action::RunCalibration_Result::_trial_id_type arg)
  {
    msg_.trial_id = std::move(arg);
    return Init_RunCalibration_Result_trial_directory(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_Result msg_;
};

class Init_RunCalibration_Result_success
{
public:
  Init_RunCalibration_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunCalibration_Result_trial_id success(::zfc_interfaces::action::RunCalibration_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_RunCalibration_Result_trial_id(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::action::RunCalibration_Result>()
{
  return zfc_interfaces::action::builder::Init_RunCalibration_Result_success();
}

}  // namespace zfc_interfaces


namespace zfc_interfaces
{

namespace action
{

namespace builder
{

class Init_RunCalibration_Feedback_state
{
public:
  Init_RunCalibration_Feedback_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::zfc_interfaces::action::RunCalibration_Feedback state(::zfc_interfaces::action::RunCalibration_Feedback::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::action::RunCalibration_Feedback>()
{
  return zfc_interfaces::action::builder::Init_RunCalibration_Feedback_state();
}

}  // namespace zfc_interfaces


namespace zfc_interfaces
{

namespace action
{

namespace builder
{

class Init_RunCalibration_SendGoal_Request_goal
{
public:
  explicit Init_RunCalibration_SendGoal_Request_goal(::zfc_interfaces::action::RunCalibration_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::action::RunCalibration_SendGoal_Request goal(::zfc_interfaces::action::RunCalibration_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_SendGoal_Request msg_;
};

class Init_RunCalibration_SendGoal_Request_goal_id
{
public:
  Init_RunCalibration_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunCalibration_SendGoal_Request_goal goal_id(::zfc_interfaces::action::RunCalibration_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_RunCalibration_SendGoal_Request_goal(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::action::RunCalibration_SendGoal_Request>()
{
  return zfc_interfaces::action::builder::Init_RunCalibration_SendGoal_Request_goal_id();
}

}  // namespace zfc_interfaces


namespace zfc_interfaces
{

namespace action
{

namespace builder
{

class Init_RunCalibration_SendGoal_Response_stamp
{
public:
  explicit Init_RunCalibration_SendGoal_Response_stamp(::zfc_interfaces::action::RunCalibration_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::action::RunCalibration_SendGoal_Response stamp(::zfc_interfaces::action::RunCalibration_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_SendGoal_Response msg_;
};

class Init_RunCalibration_SendGoal_Response_accepted
{
public:
  Init_RunCalibration_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunCalibration_SendGoal_Response_stamp accepted(::zfc_interfaces::action::RunCalibration_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_RunCalibration_SendGoal_Response_stamp(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::action::RunCalibration_SendGoal_Response>()
{
  return zfc_interfaces::action::builder::Init_RunCalibration_SendGoal_Response_accepted();
}

}  // namespace zfc_interfaces


namespace zfc_interfaces
{

namespace action
{

namespace builder
{

class Init_RunCalibration_GetResult_Request_goal_id
{
public:
  Init_RunCalibration_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::zfc_interfaces::action::RunCalibration_GetResult_Request goal_id(::zfc_interfaces::action::RunCalibration_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::action::RunCalibration_GetResult_Request>()
{
  return zfc_interfaces::action::builder::Init_RunCalibration_GetResult_Request_goal_id();
}

}  // namespace zfc_interfaces


namespace zfc_interfaces
{

namespace action
{

namespace builder
{

class Init_RunCalibration_GetResult_Response_result
{
public:
  explicit Init_RunCalibration_GetResult_Response_result(::zfc_interfaces::action::RunCalibration_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::action::RunCalibration_GetResult_Response result(::zfc_interfaces::action::RunCalibration_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_GetResult_Response msg_;
};

class Init_RunCalibration_GetResult_Response_status
{
public:
  Init_RunCalibration_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunCalibration_GetResult_Response_result status(::zfc_interfaces::action::RunCalibration_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_RunCalibration_GetResult_Response_result(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::action::RunCalibration_GetResult_Response>()
{
  return zfc_interfaces::action::builder::Init_RunCalibration_GetResult_Response_status();
}

}  // namespace zfc_interfaces


namespace zfc_interfaces
{

namespace action
{

namespace builder
{

class Init_RunCalibration_FeedbackMessage_feedback
{
public:
  explicit Init_RunCalibration_FeedbackMessage_feedback(::zfc_interfaces::action::RunCalibration_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::action::RunCalibration_FeedbackMessage feedback(::zfc_interfaces::action::RunCalibration_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_FeedbackMessage msg_;
};

class Init_RunCalibration_FeedbackMessage_goal_id
{
public:
  Init_RunCalibration_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunCalibration_FeedbackMessage_feedback goal_id(::zfc_interfaces::action::RunCalibration_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_RunCalibration_FeedbackMessage_feedback(msg_);
  }

private:
  ::zfc_interfaces::action::RunCalibration_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::action::RunCalibration_FeedbackMessage>()
{
  return zfc_interfaces::action::builder::Init_RunCalibration_FeedbackMessage_goal_id();
}

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__ACTION__DETAIL__RUN_CALIBRATION__BUILDER_HPP_
