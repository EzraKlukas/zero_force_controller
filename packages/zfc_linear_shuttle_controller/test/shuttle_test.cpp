#include "zfc_linear_shuttle_controller/shuttle.hpp"
#include <gtest/gtest.h>
using namespace zfc_linear_shuttle_controller;
TEST(Shuttle, ExactSequenceAndRestart) {
  Shuttle s;
  ASSERT_TRUE(s.configure({}));
  for (int start : {123, -456}) {
    ASSERT_TRUE(s.activate(start));
    EXPECT_EQ(s.target(), start);
    for (int i = 1; i <= 1000; ++i) {
      ASSERT_TRUE(s.update(1000000));
      EXPECT_EQ(s.target(), start + 10 * i);
    }
    for (int i = 1; i <= 1000; ++i) {
      ASSERT_TRUE(s.update(1000000));
      EXPECT_EQ(s.target(), start + 10000 - 10 * i);
    }
    for (int i = 0; i < 100; ++i) {
      ASSERT_TRUE(s.update(1000000));
      EXPECT_EQ(s.target(), start);
    }
    s.reset();
    EXPECT_FALSE(s.update(1000000));
  }
}
TEST(Shuttle, NegativeDirectionRepeatAndPeriod) {
  Shuttle s;
  Parameters p;
  p.initial_direction = -1;
  p.updates_per_leg = 2;
  p.repeat = true;
  ASSERT_TRUE(s.configure(p));
  ASSERT_TRUE(s.activate(5));
  for (int target : {-5, -15, -5, 5, -5, -15, -5, 5}) {
    ASSERT_TRUE(s.update(2000000));
    EXPECT_EQ(s.target(), target);
  }
  EXPECT_EQ(s.excessive_periods(), 8U);
  EXPECT_FALSE(s.update(0));
  EXPECT_FALSE(s.update(-1));
  EXPECT_FALSE(s.update(10000001));
  EXPECT_EQ(s.target(), 5);
}
TEST(Shuttle, Validation) {
  Parameters p;
  for (auto direction : {0, 2, -2}) {
    p.initial_direction = direction;
    EXPECT_FALSE(Shuttle::valid(p));
  }
  p = {};
  p.increment_counts_per_update = 0;
  EXPECT_FALSE(Shuttle::valid(p));
  p.increment_counts_per_update = -1;
  EXPECT_FALSE(Shuttle::valid(p));
  p.increment_counts_per_update = 11;
  EXPECT_FALSE(Shuttle::valid(p));
  p = {};
  p.updates_per_leg = 0;
  EXPECT_FALSE(Shuttle::valid(p));
  p.updates_per_leg = -1;
  EXPECT_FALSE(Shuttle::valid(p));
  p.updates_per_leg = INT64_MAX;
  EXPECT_FALSE(Shuttle::valid(p));
  p = {};
  p.expected_update_rate_hz = 999;
  EXPECT_FALSE(Shuttle::valid(p));
}
TEST(Shuttle, OverflowAndInvalidActivation) {
  Shuttle s;
  ASSERT_TRUE(s.configure({}));
  EXPECT_FALSE(s.activate(INT32_MAX));
  EXPECT_TRUE(s.activate(INT32_MAX - 10000));
  for (int i = 0; i < 2000; ++i)
    ASSERT_TRUE(s.update(1000000));
  EXPECT_EQ(s.target(), INT32_MAX - 10000);
  EXPECT_FALSE(s.activate(NAN));
  EXPECT_FALSE(s.activate(INFINITY));
  EXPECT_FALSE(s.activate(0.25));
  EXPECT_FALSE(s.activate(2147483648.0));
  Parameters p;
  p.initial_direction = -1;
  ASSERT_TRUE(s.configure(p));
  EXPECT_FALSE(s.activate(INT32_MIN));
  EXPECT_TRUE(s.activate(INT32_MIN + 10000));
  for (int i = 0; i < 2000; ++i)
    ASSERT_TRUE(s.update(1000000));
  EXPECT_EQ(s.target(), INT32_MIN + 10000);
}
