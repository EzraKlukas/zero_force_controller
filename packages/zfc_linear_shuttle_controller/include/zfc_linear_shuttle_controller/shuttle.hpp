#pragma once
#include "count_command.hpp"
namespace zfc_linear_shuttle_controller {
struct Parameters {
  std::int64_t increment_counts_per_update = 10;
  std::int64_t updates_per_leg = 1000;
  std::int64_t initial_direction = 1;
  bool repeat = false;
  std::int64_t expected_update_rate_hz = 1000;
};
// No ROS, heap storage or time integration. Each accepted update is one exact
// step.
class Shuttle {
public:
  static bool valid(const Parameters &p) noexcept {
    return p.increment_counts_per_update > 0 &&
           p.increment_counts_per_update <= zfc::kMaximumIncrementCounts &&
           p.updates_per_leg > 0 &&
           (p.initial_direction == 1 || p.initial_direction == -1) &&
           p.expected_update_rate_hz == 1000 &&
           p.updates_per_leg <=
               (std::int64_t(UINT32_MAX) / p.increment_counts_per_update);
  }
  bool configure(const Parameters &p) noexcept {
    reset();
    configured_ = valid(p);
    if (configured_)
      p_ = p;
    return configured_;
  }
  bool activate(double actual) noexcept {
    reset();
    std::int32_t start;
    if (!configured_ || !zfc::ToCounts(actual, start))
      return false;
    const auto endpoint =
        std::int64_t(start) + p_.initial_direction *
                                  p_.increment_counts_per_update *
                                  p_.updates_per_leg;
    if (endpoint < INT32_MIN || endpoint > INT32_MAX)
      return false;
    start_ = target_ = start;
    active_ = true;
    return true;
  }
  void reset() noexcept {
    active_ = false;
    returning_ = false;
    finished_ = false;
    updates_ = 0;
    start_ = target_ = 0;
    excessive_periods_ = 0;
  }
  bool update(std::int64_t period_ns) noexcept {
    if (!active_ || period_ns <= 0)
      return false;
    // Observe jitter without changing the requested cycle-count sequence.
    // A gap beyond 10 ms faults; it is never compensated by a larger step.
    if (period_ns > 1500000)
      ++excessive_periods_;
    if (period_ns > 10000000)
      return false;
    if (finished_)
      return true;
    const auto delta = p_.initial_direction * p_.increment_counts_per_update *
                       (returning_ ? -1 : 1);
    const auto next = std::int64_t(target_) + delta;
    if (next < INT32_MIN || next > INT32_MAX)
      return false;
    target_ = static_cast<std::int32_t>(next);
    if (++updates_ == p_.updates_per_leg) {
      updates_ = 0;
      if (returning_) {
        if (target_ != start_)
          return false;
        finished_ = !p_.repeat;
        returning_ = false;
      } else
        returning_ = true;
    }
    return true;
  }
  std::int32_t target() const noexcept { return target_; }
  std::uint64_t excessive_periods() const noexcept {
    return excessive_periods_;
  }

private:
  Parameters p_{};
  bool configured_ = false, active_ = false, returning_ = false,
       finished_ = false;
  std::int64_t updates_ = 0;
  std::int32_t start_ = 0, target_ = 0;
  std::uint64_t excessive_periods_ = 0;
};
} // namespace zfc_linear_shuttle_controller
