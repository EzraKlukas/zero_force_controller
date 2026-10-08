#pragma once
#include <cmath>
namespace zfc {
// ROS plumbing uses this after pure logic. Physical default keeps NaN stop.
struct CommandOutput {
  bool finite_fault_hold=false;
  double last_finite=NAN;
  bool fault_latched=false;
  bool resolve(double requested,double measured,double &out) noexcept {
    if (!finite_fault_hold) {
      out=requested;
      if (std::isfinite(out)) last_finite=out;
      return true;
    }
    if (std::isfinite(requested)) {
      last_finite=requested;
      fault_latched=false;
    } else {
      if (!fault_latched && std::isfinite(measured)) last_finite=measured;
      fault_latched=true; // Freeze once; do not follow drift while faulted.
    }
    // If no finite position has ever existed, leave the backend command alone.
    if (!std::isfinite(last_finite)) return false;
    out=last_finite;
    return true;
  }
};
} // namespace zfc
