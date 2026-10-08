#include "zfc_ethercat_hardware/si_calibration.hpp"
#include <gtest/gtest.h>
#include <map>
using zfc_ethercat_hardware::SiCalibration;
using zfc_ethercat_hardware::EncoderSession;
std::map<std::string,std::string> installation() {
  return {{"m_per_count","0.001"},{"velocity_from_encoder","false"},
    {"velocity_mps_per_raw_unit","0.02"},
    {"force_x_newtons_per_count","2"},{"force_y_newtons_per_count","-3"},
    {"force_z_newtons_per_count","4"},{"force_x_zero_counts","10"},
    {"force_y_zero_counts","20"},{"force_z_zero_counts","30"},
    {"conventions_confirmed","true"},{"force_frame","load_cell_link"},
    {"force_channel_mapping","x,y,z"}};
}
TEST(SiCalibration, AffineChannelsIndependentVelocityAndOptionalOffsets) {
  auto c=SiCalibration::load(installation());
  EXPECT_FALSE(c.to_counts(0,c.reference_counts));
  EXPECT_TRUE(std::isnan(c.position(110)));
  ASSERT_TRUE(c.set_reference(100));
  EXPECT_FALSE(c.set_reference(101));
  EXPECT_DOUBLE_EQ(c.position(110),.01);
  EXPECT_DOUBLE_EQ(c.velocity(10),.2);
  EXPECT_DOUBLE_EQ(c.force(0,12),4);
  EXPECT_DOUBLE_EQ(c.force(1,22),-6);
  EXPECT_DOUBLE_EQ(c.force(2,32),8);
  auto params=installation();
  params.erase("force_x_zero_counts");
  EXPECT_DOUBLE_EQ(SiCalibration::load(params).force(0,12),24);
}
TEST(SiCalibration, RoundingBothSignsGeneralBoundsAndOverflow) {
  for (const auto *scale:{"0.001","-0.001"}) {
    auto params=installation(); params["m_per_count"]=scale;
    params["soft_bounds_enabled"]="true";
    params["soft_lower_m"]="-0.5"; params["soft_upper_m"]="0.5";
    auto c=SiCalibration::load(params); ASSERT_TRUE(c.set_reference(0));
    std::int32_t raw=0;
    ASSERT_TRUE(c.to_counts(.0005,raw));
    EXPECT_EQ(raw,scale[0]=='-' ? -1 : 1);
    ASSERT_TRUE(c.to_counts(-.0106,raw));
    EXPECT_EQ(raw,scale[0]=='-' ? 11 : -11);
    EXPECT_FALSE(c.to_counts(.5001,raw));
    EXPECT_FALSE(c.to_counts(-.5001,raw));
    EXPECT_FALSE(c.to_counts(NAN,raw));
    c.upper=.0108;
    EXPECT_FALSE(c.to_counts(.0107,raw));
  }
  auto c=SiCalibration::load(installation()); std::int32_t raw=7;
  ASSERT_TRUE(c.set_reference(std::numeric_limits<std::int32_t>::max()));
  EXPECT_TRUE(c.to_counts(0,raw));
  EXPECT_FALSE(c.to_counts(.0001,raw));
  c.clear_reference();
  ASSERT_TRUE(c.set_reference(std::numeric_limits<std::int32_t>::min()));
  c.m_per_count=-.001;
  EXPECT_FALSE(c.to_counts(.0001,raw));
  c.m_per_count=std::numeric_limits<double>::denorm_min();
  EXPECT_FALSE(c.to_counts(.5,raw));
}
TEST(SiCalibration, InvalidRequiredCalibrationAndUnconfirmedSigns) {
  const auto good=installation();
  for (const auto *key:{"m_per_count","velocity_mps_per_raw_unit",
      "force_x_newtons_per_count","force_y_newtons_per_count","force_z_newtons_per_count"}) {
    for (const auto *bad:{"nan","inf","0","nope"}) {
      auto p=good; p[key]=bad;
      EXPECT_THROW(SiCalibration::load(p),std::runtime_error);
    }
    auto p=good; p.erase(key);
    EXPECT_THROW(SiCalibration::load(p),std::runtime_error);
  }
  auto p=good; p["conventions_confirmed"]="false";
  EXPECT_THROW(SiCalibration::load(p),std::runtime_error);
  p=good; p["velocity_from_encoder"]="true"; p.erase("velocity_mps_per_raw_unit");
  EXPECT_NO_THROW(SiCalibration::load(p));
  p["soft_bounds_enabled"]="true"; p["soft_lower_m"]="1"; p["soft_upper_m"]="-1";
  EXPECT_THROW(SiCalibration::load(p),std::runtime_error);
}
TEST(EncoderSession, StationaryCaptureMeasuredElapsedFreezeAndResetDetection) {
  EncoderSession s;
  EXPECT_TRUE(s.observe(100,1000000,true,2e-7,1000));
  EXPECT_FALSE(s.valid());
  EXPECT_TRUE(s.observe(100,2000000,true,2e-7,1000));
  ASSERT_TRUE(s.valid()); EXPECT_EQ(s.reference(),100);
  // 10 counts / 2 ms = .001 m/s. No PDO-unit or nominal-rate assumption.
  EXPECT_TRUE(s.observe(110,4000000,false,2e-7,1000));
  EXPECT_NEAR(s.velocity(),.001,1e-15);
  EXPECT_EQ(s.reference(),100);
  s.suspend();
  EXPECT_TRUE(s.observe(110,10000000,true,2e-7,1000));
  EXPECT_EQ(s.reference(),100);
  EXPECT_FALSE(s.observe(-5000,11000000,true,2e-7,1000));
  EXPECT_EQ(s.reference(),100);
  s.end(); EXPECT_FALSE(s.valid());
  ASSERT_TRUE(s.observe(-5000,12000000,true,-2e-7,1000));
  ASSERT_TRUE(s.observe(-5000,13000000,true,-2e-7,1000));
  EXPECT_EQ(s.reference(),-5000);
  ASSERT_TRUE(s.observe(-5010,15000000,false,-2e-7,1000));
  EXPECT_NEAR(s.velocity(),.001,1e-15);
}
