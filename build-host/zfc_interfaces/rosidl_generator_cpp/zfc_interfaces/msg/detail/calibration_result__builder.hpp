// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from zfc_interfaces:msg/CalibrationResult.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__CALIBRATION_RESULT__BUILDER_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__CALIBRATION_RESULT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "zfc_interfaces/msg/detail/calibration_result__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace zfc_interfaces
{

namespace msg
{

namespace builder
{

class Init_CalibrationResult_acceleration_source
{
public:
  explicit Init_CalibrationResult_acceleration_source(::zfc_interfaces::msg::CalibrationResult & msg)
  : msg_(msg)
  {}
  ::zfc_interfaces::msg::CalibrationResult acceleration_source(::zfc_interfaces::msg::CalibrationResult::_acceleration_source_type arg)
  {
    msg_.acceleration_source = std::move(arg);
    return std::move(msg_);
  }

private:
  ::zfc_interfaces::msg::CalibrationResult msg_;
};

class Init_CalibrationResult_tracking_rms_m
{
public:
  explicit Init_CalibrationResult_tracking_rms_m(::zfc_interfaces::msg::CalibrationResult & msg)
  : msg_(msg)
  {}
  Init_CalibrationResult_acceleration_source tracking_rms_m(::zfc_interfaces::msg::CalibrationResult::_tracking_rms_m_type arg)
  {
    msg_.tracking_rms_m = std::move(arg);
    return Init_CalibrationResult_acceleration_source(msg_);
  }

private:
  ::zfc_interfaces::msg::CalibrationResult msg_;
};

class Init_CalibrationResult_negative_slope_kg
{
public:
  explicit Init_CalibrationResult_negative_slope_kg(::zfc_interfaces::msg::CalibrationResult & msg)
  : msg_(msg)
  {}
  Init_CalibrationResult_tracking_rms_m negative_slope_kg(::zfc_interfaces::msg::CalibrationResult::_negative_slope_kg_type arg)
  {
    msg_.negative_slope_kg = std::move(arg);
    return Init_CalibrationResult_tracking_rms_m(msg_);
  }

private:
  ::zfc_interfaces::msg::CalibrationResult msg_;
};

class Init_CalibrationResult_positive_slope_kg
{
public:
  explicit Init_CalibrationResult_positive_slope_kg(::zfc_interfaces::msg::CalibrationResult & msg)
  : msg_(msg)
  {}
  Init_CalibrationResult_negative_slope_kg positive_slope_kg(::zfc_interfaces::msg::CalibrationResult::_positive_slope_kg_type arg)
  {
    msg_.positive_slope_kg = std::move(arg);
    return Init_CalibrationResult_negative_slope_kg(msg_);
  }

private:
  ::zfc_interfaces::msg::CalibrationResult msg_;
};

class Init_CalibrationResult_plateau_count
{
public:
  explicit Init_CalibrationResult_plateau_count(::zfc_interfaces::msg::CalibrationResult & msg)
  : msg_(msg)
  {}
  Init_CalibrationResult_positive_slope_kg plateau_count(::zfc_interfaces::msg::CalibrationResult::_plateau_count_type arg)
  {
    msg_.plateau_count = std::move(arg);
    return Init_CalibrationResult_positive_slope_kg(msg_);
  }

private:
  ::zfc_interfaces::msg::CalibrationResult msg_;
};

class Init_CalibrationResult_sample_count
{
public:
  explicit Init_CalibrationResult_sample_count(::zfc_interfaces::msg::CalibrationResult & msg)
  : msg_(msg)
  {}
  Init_CalibrationResult_plateau_count sample_count(::zfc_interfaces::msg::CalibrationResult::_sample_count_type arg)
  {
    msg_.sample_count = std::move(arg);
    return Init_CalibrationResult_plateau_count(msg_);
  }

private:
  ::zfc_interfaces::msg::CalibrationResult msg_;
};

class Init_CalibrationResult_uncertainty_kg
{
public:
  explicit Init_CalibrationResult_uncertainty_kg(::zfc_interfaces::msg::CalibrationResult & msg)
  : msg_(msg)
  {}
  Init_CalibrationResult_sample_count uncertainty_kg(::zfc_interfaces::msg::CalibrationResult::_uncertainty_kg_type arg)
  {
    msg_.uncertainty_kg = std::move(arg);
    return Init_CalibrationResult_sample_count(msg_);
  }

private:
  ::zfc_interfaces::msg::CalibrationResult msg_;
};

class Init_CalibrationResult_residual_rms_n
{
public:
  explicit Init_CalibrationResult_residual_rms_n(::zfc_interfaces::msg::CalibrationResult & msg)
  : msg_(msg)
  {}
  Init_CalibrationResult_uncertainty_kg residual_rms_n(::zfc_interfaces::msg::CalibrationResult::_residual_rms_n_type arg)
  {
    msg_.residual_rms_n = std::move(arg);
    return Init_CalibrationResult_uncertainty_kg(msg_);
  }

private:
  ::zfc_interfaces::msg::CalibrationResult msg_;
};

class Init_CalibrationResult_r_squared
{
public:
  explicit Init_CalibrationResult_r_squared(::zfc_interfaces::msg::CalibrationResult & msg)
  : msg_(msg)
  {}
  Init_CalibrationResult_residual_rms_n r_squared(::zfc_interfaces::msg::CalibrationResult::_r_squared_type arg)
  {
    msg_.r_squared = std::move(arg);
    return Init_CalibrationResult_residual_rms_n(msg_);
  }

private:
  ::zfc_interfaces::msg::CalibrationResult msg_;
};

class Init_CalibrationResult_intercept_n
{
public:
  explicit Init_CalibrationResult_intercept_n(::zfc_interfaces::msg::CalibrationResult & msg)
  : msg_(msg)
  {}
  Init_CalibrationResult_r_squared intercept_n(::zfc_interfaces::msg::CalibrationResult::_intercept_n_type arg)
  {
    msg_.intercept_n = std::move(arg);
    return Init_CalibrationResult_r_squared(msg_);
  }

private:
  ::zfc_interfaces::msg::CalibrationResult msg_;
};

class Init_CalibrationResult_inertial_force_coefficient_kg
{
public:
  explicit Init_CalibrationResult_inertial_force_coefficient_kg(::zfc_interfaces::msg::CalibrationResult & msg)
  : msg_(msg)
  {}
  Init_CalibrationResult_intercept_n inertial_force_coefficient_kg(::zfc_interfaces::msg::CalibrationResult::_inertial_force_coefficient_kg_type arg)
  {
    msg_.inertial_force_coefficient_kg = std::move(arg);
    return Init_CalibrationResult_intercept_n(msg_);
  }

private:
  ::zfc_interfaces::msg::CalibrationResult msg_;
};

class Init_CalibrationResult_reason
{
public:
  explicit Init_CalibrationResult_reason(::zfc_interfaces::msg::CalibrationResult & msg)
  : msg_(msg)
  {}
  Init_CalibrationResult_inertial_force_coefficient_kg reason(::zfc_interfaces::msg::CalibrationResult::_reason_type arg)
  {
    msg_.reason = std::move(arg);
    return Init_CalibrationResult_inertial_force_coefficient_kg(msg_);
  }

private:
  ::zfc_interfaces::msg::CalibrationResult msg_;
};

class Init_CalibrationResult_valid
{
public:
  Init_CalibrationResult_valid()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CalibrationResult_reason valid(::zfc_interfaces::msg::CalibrationResult::_valid_type arg)
  {
    msg_.valid = std::move(arg);
    return Init_CalibrationResult_reason(msg_);
  }

private:
  ::zfc_interfaces::msg::CalibrationResult msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::zfc_interfaces::msg::CalibrationResult>()
{
  return zfc_interfaces::msg::builder::Init_CalibrationResult_valid();
}

}  // namespace zfc_interfaces

#endif  // ZFC_INTERFACES__MSG__DETAIL__CALIBRATION_RESULT__BUILDER_HPP_
