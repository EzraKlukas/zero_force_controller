#pragma once
#include "ethercat_system.hpp"
#include <cmath>
#include <cstdint>
#include <limits>
namespace zfc {
enum class CommandResult { valid, invalid, excessive_increment, limit };
inline bool ToCounts(double value, std::int32_t &out) noexcept {
  if (!std::isfinite(value) || std::trunc(value) != value ||
      value < std::numeric_limits<std::int32_t>::min() ||
      value > std::numeric_limits<std::int32_t>::max())
    return false;
  out = static_cast<std::int32_t>(value);
  return true;
}
inline CommandResult ValidateCommand(double value, std::int32_t previous,
                                     const Clearpath::PDO::TxPDOs &motor,
                                     std::int32_t maximum,
                                     std::int32_t &out) noexcept {
  if (!ToCounts(value, out))
    return CommandResult::invalid;
  const auto delta = std::int64_t(out) - previous;
  if (maximum <= 0 || maximum > kMaximumIncrementCounts || delta > maximum ||
      delta < -maximum)
    return CommandResult::excessive_increment;
  // Check both intent and residual following error into a limit.
  if ((motor.negative_limit_reached() &&
       (delta < 0 || out < motor.actual_position)) ||
      (motor.positive_limit_reached() &&
       (delta > 0 || out > motor.actual_position)))
    return CommandResult::limit;
  return CommandResult::valid;
}
} // namespace zfc
