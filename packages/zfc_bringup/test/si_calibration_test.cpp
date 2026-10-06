#include "zfc_ethercat_hardware/si_calibration.hpp"
#include <gtest/gtest.h>
#include <map>
using zfc_ethercat_hardware::SiCalibration;
std::map<std::string, std::string> installation() {
  return {{"metres_per_count","0.001"}, {"encoder_zero_counts","100"},
    {"velocity_mps_per_raw_unit","0.02"},
    {"force_x_newtons_per_count","2"}, {"force_y_newtons_per_count","-3"},
    {"force_z_newtons_per_count","4"}, {"force_x_zero_counts","10"},
    {"force_y_zero_counts","20"}, {"force_z_zero_counts","30"},
    {"conventions_confirmed","true"}, {"force_frame","load_cell_link"},
    {"force_channel_mapping","x,y,z"}};
}
TEST(SiCalibration, AffineChannelsAndIndependentVelocity) {
  const auto c = SiCalibration::load(installation(), 0, 0.5);
  EXPECT_DOUBLE_EQ(c.position(110), 0.01);
  EXPECT_DOUBLE_EQ(c.velocity(10), 0.2); // deliberately NOT s*raw velocity
  EXPECT_DOUBLE_EQ(c.force(0,12), 4);
  EXPECT_DOUBLE_EQ(c.force(1,22), -6);
  EXPECT_DOUBLE_EQ(c.force(2,32), 8);
}
TEST(SiCalibration, RoundingNegativeScaleAndTravel) {
  for (const char *scale : {"0.001","-0.001"}) {
    auto params = installation();
    params["metres_per_count"] = scale;
    auto c = SiCalibration::load(params, 0, 0.5);
    std::int32_t raw = 0;
    ASSERT_TRUE(c.to_counts(0.0106, raw));
    EXPECT_EQ(raw, scale[0] == '-' ? 89 : 111);
    EXPECT_NEAR(c.position(raw), 0.011, 1e-15);
    EXPECT_FALSE(c.to_counts(-0.0001, raw));
    EXPECT_FALSE(c.to_counts(0.5001, raw));
    EXPECT_FALSE(c.to_counts(NAN, raw));
    EXPECT_FALSE(c.to_counts(INFINITY, raw));
  }
  auto c = SiCalibration::load(installation(), 0, 0.5);
  c.upper = 0.0108; // rounding to .011 exceeds travel even though request is in range
  std::int32_t raw;
  EXPECT_FALSE(c.to_counts(0.0107, raw));
  c = SiCalibration::load(installation(), 0, 0.5);
  c.encoder_zero_counts = 0;
  EXPECT_TRUE(c.to_counts(.0005, raw));
  EXPECT_EQ(raw, 1);
  c.metres_per_count = -.001;
  EXPECT_TRUE(c.to_counts(.0005, raw));
  EXPECT_EQ(raw, -1); // std::round ties away from zero, including negative raw
}
TEST(SiCalibration, Int32RangeBeforeConversion) {
  auto c = SiCalibration::load(installation(), 0, 0.5);
  c.encoder_zero_counts = std::numeric_limits<std::int32_t>::max();
  std::int32_t raw = 7;
  EXPECT_TRUE(c.to_counts(0, raw));
  EXPECT_EQ(raw, std::numeric_limits<std::int32_t>::max());
  EXPECT_FALSE(c.to_counts(0.0001, raw));
  c.encoder_zero_counts = std::numeric_limits<std::int32_t>::min();
  c.metres_per_count = -0.001;
  EXPECT_TRUE(c.to_counts(0, raw));
  EXPECT_FALSE(c.to_counts(0.0001, raw));
  c.metres_per_count = std::numeric_limits<double>::denorm_min();
  EXPECT_FALSE(c.to_counts(0.5, raw));
}
TEST(SiCalibration, PreciseInvalidInstallationAndConventions) {
  auto params = installation();
  for (const auto &key : {"metres_per_count","encoder_zero_counts",
      "velocity_mps_per_raw_unit","force_x_newtons_per_count",
      "force_y_newtons_per_count","force_z_newtons_per_count",
      "force_x_zero_counts","force_y_zero_counts","force_z_zero_counts"}) {
    for (const auto &bad : {"nan","inf","nope"}) {
      auto invalid = params;
      invalid[key] = bad;
      try { SiCalibration::load(invalid, 0, 0.5); FAIL() << key; }
      catch (const std::runtime_error &e) {
        EXPECT_NE(std::string(e.what()).find(key), std::string::npos);
      }
    }
    auto missing = params;
    missing.erase(key);
    EXPECT_THROW(SiCalibration::load(missing, 0, 0.5), std::runtime_error);
  }
  params["conventions_confirmed"] = "false";
  EXPECT_THROW(SiCalibration::load(params, 0, 0.5), std::runtime_error);
  params = installation();
  params["metres_per_count"] = "0";
  EXPECT_THROW(SiCalibration::load(params, 0, 0.5), std::runtime_error);
  params = installation();
  params["force_channel_mapping"] = "y,x,z";
  EXPECT_THROW(SiCalibration::load(params, 0, 0.5), std::runtime_error);
}
