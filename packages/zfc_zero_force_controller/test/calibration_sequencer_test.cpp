#include "zfc_zero_force_controller/zero_force_controller.hpp"
#include <gtest/gtest.h>
using namespace zfc_zero_force_controller;
TEST(CalibrationSequencer, BoundedSequenceAndRestart) {
  CalibrationSequencer s;
  CalibrationParameters p;
  p.center_zone_half_width_ = 1000;
  p.base_velocity_ = 500;
  p.jerk_step_ = 5;
  p.max_acceleration_limit_ = 20;
  p.cycles_per_acceleration_increase_ = 10;

  ASSERT_TRUE(s.configure({}));
  for (int start : {123, -456}) {
    ASSERT_TRUE(s.activate(start));
    EXPECT_EQ(s.target(), start);
    while (!s.finished_calibration()) {
      ASSERT_TRUE(s.update(1000000));
      EXPECT_LE(std::abs(s.target() - start),
                (p.base_velocity_ * (p.base_velocity_ + 1)) +
                    p.center_zone_half_width_);
    }
    s.reset();
    EXPECT_FALSE(s.update(1000000));
  }
}
TEST(CalibrationSequencer, HoldAndPeriodValidation) {
  CalibrationSequencer sequencer;
  CalibrationParameters p;
  p.do_calibrate_ = false;
  ASSERT_TRUE(sequencer.configure(p));
  for (int start : {123, -456}) {
    ASSERT_TRUE(sequencer.activate(start));
    for (int i = 0; i < 1000; ++i) {
      ASSERT_TRUE(sequencer.update(1000000));
      EXPECT_EQ(sequencer.target(), start);
    }
    EXPECT_FALSE(sequencer.update(0));
    EXPECT_FALSE(sequencer.update(10000001));
    EXPECT_FALSE(sequencer.activate(NAN));
  }
}
