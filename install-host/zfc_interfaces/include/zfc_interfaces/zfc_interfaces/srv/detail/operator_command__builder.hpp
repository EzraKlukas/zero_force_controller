// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from zfc_interfaces:srv/OperatorCommand.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__BUILDER_HPP_
#define ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "zfc_interfaces/srv/detail/operator_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace zfc_interfaces
{

namespace srv
{

namespace builder
{

class Init_OperatorCommand_Request_external_contact_clear
{
public:
  explicit Init_OperatorCommand_Request_external_contact_clear(::zfc_interfaces::srv::OperatorCommand_Request & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::srv::OperatorCommand_Request external_contact_clear(::zfc_interfaces::srv::OperatorCommand_Request::_external_contact_clear_type arg)
  {
    msg_.external_contact_clear = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::srv::OperatorCommand_Request msg_;
};

class Init_OperatorCommand_Request_command
{
public:
  Init_OperatorCommand_Request_command()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OperatorCommand_Request_external_contact_clear command(::zfc_interfaces::srv::OperatorCommand_Request::_command_type arg)
  {
    msg_.command = std::move(arg);
    return Init_OperatorCommand_Request_external_contact_clear(msg_);
  }

private:
  ::zfc_interfaces::srv::OperatorCommand_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::srv::OperatorCommand_Request>()
{
  return zfc_interfaces::srv::builder::Init_OperatorCommand_Request_command();
}

}  // namespace zfc_interfaces


namespace zfc_interfaces
{

namespace srv
{

namespace builder
{

class Init_OperatorCommand_Response_message
{
public:
  explicit Init_OperatorCommand_Response_message(::zfc_interfaces::srv::OperatorCommand_Response & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::srv::OperatorCommand_Response message(::zfc_interfaces::srv::OperatorCommand_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::srv::OperatorCommand_Response msg_;
};

class Init_OperatorCommand_Response_stop_acknowledged
{
public:
  explicit Init_OperatorCommand_Response_stop_acknowledged(::zfc_interfaces::srv::OperatorCommand_Response & msg)
  : msg_(msg)
  {}
  Init_OperatorCommand_Response_message stop_acknowledged(::zfc_interfaces::srv::OperatorCommand_Response::_stop_acknowledged_type arg)
  {
    msg_.stop_acknowledged = std::move(arg);
    return Init_OperatorCommand_Response_message(msg_);
  }

private:
  ::zfc_interfaces::srv::OperatorCommand_Response msg_;
};

class Init_OperatorCommand_Response_success
{
public:
  Init_OperatorCommand_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OperatorCommand_Response_stop_acknowledged success(::zfc_interfaces::srv::OperatorCommand_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_OperatorCommand_Response_stop_acknowledged(msg_);
  }

private:
  ::zfc_interfaces::srv::OperatorCommand_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::srv::OperatorCommand_Response>()
{
  return zfc_interfaces::srv::builder::Init_OperatorCommand_Response_success();
}

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__SRV__DETAIL__OPERATOR_COMMAND__BUILDER_HPP_
