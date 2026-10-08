#include "zfc_zero_force_controller/zero_force_logic.hpp"
#include <gtest/gtest.h>
using namespace zfc_zero_force_controller;
zfc::Inputs sample(double force=10) { return {.25,0,force,0,1000000}; }
void windows(ZeroForceLogic &logic, zfc::Inputs &in) {
  for (int i=0;i<2000;++i) { in.time_ns+=1000000; ASSERT_TRUE(logic.update(in).valid); }
}
TEST(ZeroForceLogic, FrozenBaselineAndRmsOfSquaredDeviations) {
  ZeroForceSettings p;
  p.baseline_duration_s=.003; p.noise_duration_s=.004;
  ZeroForceLogic logic;
  auto in=sample();
  ASSERT_TRUE(logic.activate(p,in));
  for (int i=0;i<3;++i) { in.time_ns+=1000000; EXPECT_TRUE(logic.update(in).valid); }
  EXPECT_EQ(logic.snapshot().phase,zfc::Phase::noise);
  EXPECT_DOUBLE_EQ(logic.snapshot().baseline_force_n,10);
  for (double force:{11,9,13,7}) {
    in.force_n=force; in.time_ns+=1000000; EXPECT_TRUE(logic.update(in).valid);
    EXPECT_DOUBLE_EQ(logic.snapshot().reference_position_m,.25);
  }
  EXPECT_NEAR(logic.snapshot().noise_rms_n,std::sqrt(5.0),1e-14);
  EXPECT_EQ(logic.snapshot().phase,zfc::Phase::compliant);
  EXPECT_DOUBLE_EQ(logic.snapshot().baseline_force_n,10);
}
TEST(ZeroForceLogic, SupportForcePolarityDeadbandAndDamping) {
  for (int sign:{-1,1}) {
    ZeroForceLogic logic; ZeroForceSettings p; p.force_response_sign=sign;
    p.minimum_deadband_n=.1; p.damping_per_s=0;
    auto in=sample();
    ASSERT_TRUE(logic.activate(p,in)); windows(logic,in);
    in.force_n=9; in.time_ns+=1000000;
    const auto s=logic.update(in);
    EXPECT_NEAR(s.reference_acceleration_mps2,sign*-.09,1e-14);
    EXPECT_EQ(s.reference_position_m>.25,sign==-1);
    EXPECT_DOUBLE_EQ(s.baseline_force_n,10);
  }
  ZeroForceLogic logic; ZeroForceSettings p;
  auto in=sample();
  ASSERT_TRUE(logic.activate(p,in)); windows(logic,in);
  in.force_n=10.02; in.time_ns+=1000000;
  EXPECT_DOUBLE_EQ(logic.update(in).reference_velocity_mps,0);
}
TEST(ZeroForceLogic, PreviousEffectiveAccelerationInertiaCompensation) {
  ZeroForceLogic logic; ZeroForceSettings p;
  p.acceleration_per_force=1; p.damping_per_s=0; p.minimum_deadband_n=0;
  p.inertial_force_coefficient_kg=2; p.max_acceleration_mps2=5;
  auto in=sample(0);
  ASSERT_TRUE(logic.activate(p,in)); windows(logic,in);
  in.force_n=-1; in.time_ns+=1000000;
  auto s=logic.update(in);
  EXPECT_DOUBLE_EQ(s.reference_acceleration_mps2,1);
  in.force_n=2; in.time_ns+=1000000;
  s=logic.update(in);
  EXPECT_DOUBLE_EQ(s.residual_force_n,0);
  EXPECT_DOUBLE_EQ(s.reference_acceleration_mps2,0);
  EXPECT_DOUBLE_EQ(s.reference_velocity_mps,.001);
}
TEST(ZeroForceLogic, BoundsFaultsResetRestartAndFiniteSettings) {
  ZeroForceLogic logic; ZeroForceSettings p;
  auto in=sample();
  ASSERT_TRUE(logic.activate(p,in)); windows(logic,in);
  in.position_m=.4; in.time_ns+=1000000;
  EXPECT_FALSE(logic.update(in).valid);
  EXPECT_TRUE(std::isnan(logic.snapshot().reference_position_m));
  EXPECT_FALSE(logic.update(sample()).valid);
  ASSERT_TRUE(logic.activate(p,sample(20)));
  EXPECT_EQ(logic.snapshot().phase,zfc::Phase::baseline);
  EXPECT_DOUBLE_EQ(logic.snapshot().noise_rms_n,0);
  EXPECT_DOUBLE_EQ(logic.snapshot().baseline_force_n,0);
  in=sample(20); in.period_ns=10000001;
  EXPECT_FALSE(logic.update(in).valid);
  p.acceleration_per_force=NAN;
  EXPECT_FALSE(logic.activate(p,sample()));
  p={}; p.damping_per_s=INFINITY;
  EXPECT_FALSE(logic.activate(p,sample()));
  p={}; in=sample(); in.velocity_mps=.01;
  EXPECT_FALSE(logic.activate(p,in));
}
TEST(ZeroForceLogic, VelocityAccelerationLimitsAndEffectiveDamping) {
  ZeroForceLogic logic; ZeroForceSettings p;
  p.minimum_deadband_n=0; p.damping_per_s=0;
  auto in=sample();
  ASSERT_TRUE(logic.activate(p,in)); windows(logic,in);
  double previous=0;
  for (int i=0;i<100;++i) {
    in.force_n=-100; in.time_ns+=1000000;
    const auto s=logic.update(in);
    ASSERT_TRUE(s.valid);
    EXPECT_LE(std::abs(s.reference_velocity_mps),p.max_velocity_mps);
    EXPECT_LE(std::abs(s.reference_acceleration_mps2),p.max_acceleration_mps2+1e-12);
    EXPECT_NEAR(s.reference_acceleration_mps2,(s.reference_velocity_mps-previous)/zfc::dt,1e-12);
    previous=s.reference_velocity_mps;
  }
  // Removing residual force must damp the existing velocity, not reverse it.
  p.damping_per_s=5;
  ASSERT_TRUE(logic.activate(p,sample()));
  in=sample(); windows(logic,in);
  in.force_n=-1; in.time_ns+=1000000;
  const double moving=logic.update(in).reference_velocity_mps;
  in.force_n=10; in.time_ns+=1000000;
  const auto damped=logic.update(in);
  EXPECT_GT(damped.reference_velocity_mps,0);
  EXPECT_LT(damped.reference_velocity_mps,moving);
  EXPECT_LT(damped.reference_acceleration_mps2,0);
}
