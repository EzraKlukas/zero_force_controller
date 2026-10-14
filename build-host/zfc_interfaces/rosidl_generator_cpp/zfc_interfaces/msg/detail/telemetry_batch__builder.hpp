// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from zfc_interfaces:msg/TelemetryBatch.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__TELEMETRY_BATCH__BUILDER_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__TELEMETRY_BATCH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "zfc_interfaces/msg/detail/telemetry_batch__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace zfc_interfaces
{

namespace msg
{

namespace builder
{

class Init_TelemetryBatch_failed_publication_samples
{
public:
  explicit Init_TelemetryBatch_failed_publication_samples(::zfc_interfaces::msg::TelemetryBatch & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::msg::TelemetryBatch failed_publication_samples(::zfc_interfaces::msg::TelemetryBatch::_failed_publication_samples_type arg)
  {
    msg_.failed_publication_samples = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::msg::TelemetryBatch msg_;
};

class Init_TelemetryBatch_dropped_samples
{
public:
  explicit Init_TelemetryBatch_dropped_samples(::zfc_interfaces::msg::TelemetryBatch & msg)
  : msg_(msg)
  {}
  Init_TelemetryBatch_failed_publication_samples dropped_samples(::zfc_interfaces::msg::TelemetryBatch::_dropped_samples_type arg)
  {
    msg_.dropped_samples = std::move(arg);
    return Init_TelemetryBatch_failed_publication_samples(msg_);
  }

private:
  ::zfc_interfaces::msg::TelemetryBatch msg_;
};

class Init_TelemetryBatch_samples
{
public:
  explicit Init_TelemetryBatch_samples(::zfc_interfaces::msg::TelemetryBatch & msg)
  : msg_(msg)
  {}
  Init_TelemetryBatch_dropped_samples samples(::zfc_interfaces::msg::TelemetryBatch::_samples_type arg)
  {
    msg_.samples = std::move(arg);
    return Init_TelemetryBatch_dropped_samples(msg_);
  }

private:
  ::zfc_interfaces::msg::TelemetryBatch msg_;
};

class Init_TelemetryBatch_stamp
{
public:
  Init_TelemetryBatch_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TelemetryBatch_samples stamp(::zfc_interfaces::msg::TelemetryBatch::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_TelemetryBatch_samples(msg_);
  }

private:
  ::zfc_interfaces::msg::TelemetryBatch msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::msg::TelemetryBatch>()
{
  return zfc_interfaces::msg::builder::Init_TelemetryBatch_stamp();
}

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__MSG__DETAIL__TELEMETRY_BATCH__BUILDER_HPP_
