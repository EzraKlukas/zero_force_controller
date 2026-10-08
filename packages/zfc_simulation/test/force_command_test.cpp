#include <algorithm>
#include "zfc_simulation/force_command.hpp"
#include <gtest/gtest.h>
TEST(ForceCommand, ReplacesBoundsReleasesAndExpiresIncludingPause) {
  zfc_simulation::ForceCommand c;
  EXPECT_EQ(c.value(1),0);
  c.receive(4,10); EXPECT_EQ(c.value(20),4);
  c.receive(-3,20); EXPECT_EQ(c.value(30),-3);
  c.receive(100,30); EXPECT_EQ(c.value(40),10);
  c.receive(0,40); EXPECT_EQ(c.value(50),0);
  c.receive(4,50); EXPECT_EQ(c.value(500000051),0);
  c.receive(NAN,60); EXPECT_EQ(c.value(70),0);
  c.receive(4,80,false); EXPECT_EQ(c.value(90),0);
}
