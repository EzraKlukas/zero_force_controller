// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from zfc_interfaces:srv/ApplyCalibration.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__SRV__DETAIL__APPLY_CALIBRATION__BUILDER_HPP_
#define ZFC_INTERFACES__SRV__DETAIL__APPLY_CALIBRATION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "zfc_interfaces/srv/detail/apply_calibration__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace zfc_interfaces
{

namespace srv
{

namespace builder
{

class Init_ApplyCalibration_Request_result_file
{
public:
  Init_ApplyCalibration_Request_result_file()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::zfc_interfaces::srv::ApplyCalibration_Request result_file(::zfc_interfaces::srv::ApplyCalibration_Request::_result_file_type arg)
  {
    msg_.result_file = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::srv::ApplyCalibration_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::srv::ApplyCalibration_Request>()
{
  return zfc_interfaces::srv::builder::Init_ApplyCalibration_Request_result_file();
}

}  // namespace zfc_interfaces


namespace zfc_interfaces
{

namespace srv
{

namespace builder
{

class Init_ApplyCalibration_Response_fit
{
public:
  explicit Init_ApplyCalibration_Response_fit(::zfc_interfaces::srv::ApplyCalibration_Response & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::srv::ApplyCalibration_Response fit(::zfc_interfaces::srv::ApplyCalibration_Response::_fit_type arg)
  {
    msg_.fit = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::srv::ApplyCalibration_Response msg_;
};

class Init_ApplyCalibration_Response_message
{
public:
  explicit Init_ApplyCalibration_Response_message(::zfc_interfaces::srv::ApplyCalibration_Response & msg)
  : msg_(msg)
  {}
  Init_ApplyCalibration_Response_fit message(::zfc_interfaces::srv::ApplyCalibration_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_ApplyCalibration_Response_fit(msg_);
  }

private:
  ::zfc_interfaces::srv::ApplyCalibration_Response msg_;
};

class Init_ApplyCalibration_Response_success
{
public:
  Init_ApplyCalibration_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ApplyCalibration_Response_message success(::zfc_interfaces::srv::ApplyCalibration_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ApplyCalibration_Response_message(msg_);
  }

private:
  ::zfc_interfaces::srv::ApplyCalibration_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::srv::ApplyCalibration_Response>()
{
  return zfc_interfaces::srv::builder::Init_ApplyCalibration_Response_success();
}

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__SRV__DETAIL__APPLY_CALIBRATION__BUILDER_HPP_
