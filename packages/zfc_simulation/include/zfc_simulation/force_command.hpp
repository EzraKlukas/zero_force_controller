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
  void receive(double value,std::int64_t now,bool correct_target=true) noexcept {
    force=correct_target && std::isfinite(value) ? std::clamp(value,-bound_n,bound_n) : 0;
    received_ns=now;
  }
  double value(std::int64_t now) const noexcept {
    return received_ns>0 && now>=received_ns && now-received_ns<=timeout_ns ? force : 0;
  }
};
} // namespace zfc_simulation
