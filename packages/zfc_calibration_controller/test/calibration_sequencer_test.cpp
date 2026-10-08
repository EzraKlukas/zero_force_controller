#include "zfc_calibration_controller/calibration_sequencer_logic.hpp"
#include <gtest/gtest.h>
using namespace zfc_calibration_controller;

CalibrationParameters motion(double s = 1e-6) {
  const double a = std::abs(s), dt = CalibrationSequencer::dt;
  return { 1000*a, 500*s/dt, 5*a/(dt*dt*dt),
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

TEST(CalibrationSequencer, PeriodValidation) {
  CalibrationSequencer s;
  ASSERT_TRUE(s.configure({}));
  ASSERT_TRUE(s.activate(.25));
  EXPECT_FALSE(s.update(0));
  EXPECT_FALSE(s.update(10000001));
  EXPECT_FALSE(s.activate(NAN));
  CalibrationParameters p;
  p.jerk_mps3=NAN;
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
TEST(CalibrationLogic, SettlesStationaryAndReportsActualReferenceChanges) {
  CalibrationSettings p;
  CalibrationSequencerLogic logic;
  zfc::Inputs in{.25,0,12,0,1000000};
  ASSERT_TRUE(logic.activate(p,in));
  bool saw_settling=false, saw_clip=false;
  auto previous=logic.snapshot();
  for (int i=0;i<1000000 && logic.snapshot().phase!=zfc::Phase::complete;++i) {
    // An ideal tracking fixture is test-only, not a simulation adapter.
    in.position_m=previous.reference_position_m;
    in.velocity_mps=previous.reference_velocity_mps;
    in.time_ns+=1000000;
    const auto s=logic.update(in);
    ASSERT_TRUE(s.valid) << i;
    EXPECT_NEAR(s.reference_acceleration_mps2,
      (s.reference_velocity_mps-previous.reference_velocity_mps)/zfc::dt,1e-10);
    if (s.phase==zfc::Phase::settling) saw_settling=true;
    if (i>0 && s.phase==zfc::Phase::trajectory && std::abs(s.reference_acceleration_mps2)>2.1)
      saw_clip=true;
    previous=s;
  }
  EXPECT_TRUE(saw_settling);
  EXPECT_TRUE(saw_clip);
  EXPECT_EQ(logic.snapshot().phase,zfc::Phase::complete);
  EXPECT_DOUBLE_EQ(logic.snapshot().reference_velocity_mps,0);
  EXPECT_DOUBLE_EQ(logic.snapshot().reference_acceleration_mps2,0);
  EXPECT_DOUBLE_EQ(logic.snapshot().progress,1);
}
TEST(CalibrationLogic, PreflightExcursionSignedBoundsAndFaults) {
  CalibrationSettings p; CalibrationSequencerLogic logic;
  zfc::Inputs in{0,0,0,0,1000000};
  p.bounds.excursion_limit_m=.001;
  EXPECT_FALSE(logic.activate(p,in));
  p={}; p.bounds.use_position_bounds=true;
  p.bounds.lower_position_m=-.1; p.bounds.upper_position_m=.1;
  ASSERT_TRUE(logic.activate(p,in));
  in.position_m=.2; in.time_ns+=1000000;
  EXPECT_FALSE(logic.update(in).valid);
  EXPECT_TRUE(std::isnan(logic.snapshot().reference_position_m));
  in={0,0,NAN,0,1000000};
  EXPECT_FALSE(logic.activate(p,in));
  in.force_n=0; ASSERT_TRUE(logic.activate(p,in));
  in.period_ns=0; EXPECT_FALSE(logic.update(in).valid);
}
