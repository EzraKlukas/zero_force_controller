#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
namespace zfc_simulation {
// Simulation-only replace semantics; caller serializes receive/value.
struct ForceCommand {
  static constexpr double bound_n=10;
  static constexpr std::int64_t timeout_ns=500000000;
  double force=0;
  std::int64_t received_ns=0;
  bool enabled=true;
  void enable(bool value) noexcept {
    enabled=value;
    force=0;
    received_ns=0; // A release/re-enable must never resurrect an old push.
  }
  void receive(double value,std::int64_t now,bool correct_target=true) noexcept {
    force=enabled && correct_target && std::isfinite(value) ? std::clamp(value,-bound_n,bound_n) : 0;
    received_ns=now;
  }
  double value(std::int64_t now) const noexcept {
    return received_ns>0 && now>=received_ns && now-received_ns<=timeout_ns ? force : 0;
  }
};
} // namespace zfc_simulation
