#pragma once
#include <rclcpp/parameter.hpp>
#include <tl/expected.hpp>
#include <cmath>
inline tl::expected<void,std::string> finite_si(const rclcpp::Parameter &p) {
  if (!std::isfinite(p.as_double()))
    return tl::make_unexpected(p.get_name()+" must be finite");
  return {};
}
