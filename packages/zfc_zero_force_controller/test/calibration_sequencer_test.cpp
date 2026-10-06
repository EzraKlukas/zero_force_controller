#include "zfc_zero_force_controller/calibration_sequencer.hpp"
#include <gtest/gtest.h>
using namespace zfc_zero_force_controller;

CalibrationParameters motion(double s = 1e-6) {
  const double a = std::abs(s), dt = CalibrationSequencer::dt;
  return {true, 1000*a, 500*s/dt, 5*a/(dt*dt*dt),
          a/(dt*dt), a/(dt*dt), 10*a/(dt*dt), 5};
}

// Frozen recurrence from 88772b5, using its configured YAML values.
// The backend is intentionally absent from this reference.
struct Legacy {
  int position = 0, velocity = 0, acceleration = 0, limit = 1, cycles = 0;
  bool counted = true, finished = false;
  void update() {
    if (finished) return;
    const int direction = position >= 0 ? 1 : -1;
    if (std::abs(position) < 1000) {
      if (velocity == 0) velocity = 500;
      velocity = std::clamp(velocity, -500, 500);
      if (!counted && velocity > 0) {
        if (++cycles >= 5) {
          cycles = 0;
          if (++limit >= 10) finished = true;
        }
        counted = true;
      }
    } else {
      counted = false;
      acceleration -= direction * 5;
      acceleration = std::clamp(acceleration, -limit, limit);
      velocity += acceleration;
    }
    position += velocity;
  }
};

TEST(CalibrationSequencer, LegacyWithinOneEncoderCountAndRestartBothPolarities) {
  for (double s : {1e-6, -1e-6, 3.7e-7, -3.7e-7}) {
    CalibrationSequencer sequencer;
    ASSERT_TRUE(sequencer.configure(motion(s)));
    for (double start : {0.25, -0.1}) {
      ASSERT_TRUE(sequencer.activate(start));
      Legacy legacy;
      int updates = 0;
      while (!legacy.finished && updates < 2000000) {
        legacy.update();
        ASSERT_TRUE(sequencer.update(1000000));
        ASSERT_LE(std::abs((sequencer.target() - start)/s - legacy.position), 1.0)
            << "scale=" << s << " cycle=" << updates;
        ASSERT_EQ(sequencer.finished_calibration(), legacy.finished);
        ++updates;
      }
      ASSERT_TRUE(legacy.finished);
      const double held = sequencer.target();
      for (int i = 0; i < 100; ++i) {
        ASSERT_TRUE(sequencer.update(1000000));
        EXPECT_DOUBLE_EQ(sequencer.target(), held);
      }
      sequencer.reset();
      EXPECT_FALSE(sequencer.update(1000000));
    }
  }
}

TEST(CalibrationSequencer, HoldUnsetMotionAndPeriodPolicy) {
  CalibrationSequencer s;
  ASSERT_TRUE(s.configure({}));
  ASSERT_TRUE(s.activate(0.123));
  for (auto ns : {1000000, 1500001, 10000000}) {
    EXPECT_TRUE(s.update(ns));
    EXPECT_DOUBLE_EQ(s.target(), 0.123);
  }
  EXPECT_EQ(s.excessive_periods(), 2U);
  EXPECT_FALSE(s.update(10000001));
  EXPECT_FALSE(s.update(0));
  EXPECT_FALSE(s.update(-1));
  EXPECT_FALSE(s.activate(NAN));
  EXPECT_FALSE(s.activate(INFINITY));
}
TEST(CalibrationSequencer, RejectUnsetOrNonfiniteCalibrationTrajectory) {
  CalibrationSequencer s;
  CalibrationParameters p;
  p.do_calibrate = true;
  EXPECT_FALSE(s.configure(p));
  for (double bad : {double(NAN), double(INFINITY), 0.0, -1.0}) {
    p = motion();
    p.initial_acceleration_mps2 = bad;
    EXPECT_FALSE(s.configure(p));
  }
  p = motion();
  p.cycles_per_acceleration_increase = 0;
  EXPECT_FALSE(s.configure(p));
}
TEST(CalibrationSequencer, JitterDoesNotChangeRecurrence) {
  CalibrationSequencer a, b;
  ASSERT_TRUE(a.configure(motion()));
  ASSERT_TRUE(b.configure(motion()));
  ASSERT_TRUE(a.activate(0.25));
  ASSERT_TRUE(b.activate(0.25));
  for (int i = 0; i < 5000; ++i) {
    ASSERT_TRUE(a.update(1000000));
    ASSERT_TRUE(b.update(i % 2 ? 2000000 : 500000));
    EXPECT_DOUBLE_EQ(a.target(), b.target());
  }
}
