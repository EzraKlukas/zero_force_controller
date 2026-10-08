#include "zfc_zero_force_controller/zero_force_logic.hpp"
#include "zfc_calibration_controller/calibration_sequencer_logic.hpp"
#include "zfc_interfaces/capture.hpp"
#include <gtest/gtest.h>
#include <cstdlib>
#include <new>
namespace {
thread_local bool armed=false;
thread_local std::size_t allocations=0;
}
void *operator new(std::size_t n) {
  if (armed) ++allocations;
  if (auto *p=std::malloc(n ? n : 1)) return p;
  throw std::bad_alloc();
}
void *operator new[](std::size_t n) { return ::operator new(n); }
void operator delete(void *p) noexcept { std::free(p); }
void operator delete[](void *p) noexcept { std::free(p); }
void operator delete(void *p,std::size_t) noexcept { std::free(p); }
void operator delete[](void *p,std::size_t) noexcept { std::free(p); }
TEST(LogicAllocation, ActivationUpdatesCaptureAndCompletionAllocateNothing) {
  zfc_zero_force_controller::ZeroForceLogic zero;
  zfc_zero_force_controller::ZeroForceSettings zp;
  zp.baseline_duration_s=zp.noise_duration_s=.003;
  zfc_calibration_controller::CalibrationSequencerLogic cal;
  zfc_calibration_controller::CalibrationSettings cp;
  cp.trajectory.base_velocity_mps=.01;
  cp.trajectory.max_acceleration_mps2=.2;
  cp.trajectory.cycles_per_acceleration_increase=1;
  zfc::Capture<16> capture;
  zfc::Inputs in{.25,0,12,0,1000000};
  bool valid=true;
  allocations=0; armed=true;
  valid=zero.activate(zp,in) && cal.activate(cp,in) && capture.begin(1);
  for (int i=0;i<4000;++i) {
    in.time_ns+=1000000;
    const auto z=zero.update({.25,0,12,in.time_ns,1000000});
    const auto c=cal.update(in);
    valid=valid && z.valid && c.valid;
    in.position_m=c.reference_position_m;
    in.velocity_mps=c.reference_velocity_mps;
    capture.append(c);
  }
  capture.finish(true);
  zfc::CaptureRecord r;
  while (capture.pop(r)) {}
  zfc::Completion terminal;
  valid=valid && capture.completion(terminal);
  armed=false;
  EXPECT_TRUE(valid);
  EXPECT_EQ(allocations,0U);
  EXPECT_EQ(cal.snapshot().phase,zfc::Phase::complete);
  EXPECT_GT(terminal.dropped,0U);
}
