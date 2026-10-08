#include "ament_index_cpp/get_package_share_directory.hpp"
#include "controller_interface/controller_interface.hpp"
#include "fake_igh.hpp"
#include "hardware_interface/component_parser.hpp"
#include "hardware_interface/resource_manager.hpp"
#include "hardware_interface/system_interface.hpp"
#include "pluginlib/class_loader.hpp"
#include <chrono>
#include <algorithm>
#include <fstream>
#include <gtest/gtest.h>
#include <sstream>
#include <thread>
using Callback = hardware_interface::CallbackReturn;
TEST(Plugins, HardwareLoadsAndInitDoesNotRequestMaster) {
  pluginlib::ClassLoader<hardware_interface::SystemInterface> loader(
      "hardware_interface", "hardware_interface::SystemInterface");
  auto hw =
      loader.createSharedInstance("zfc_ethercat_hardware/EthercatHardware");
  const std::string command = std::string("xacro '") + ZFC_BRINGUP_SOURCE +
      "/urdf/stage.urdf.xacro'";
  FILE *pipe = popen(command.c_str(), "r");
  if (!pipe) throw std::runtime_error("Cannot expand test Xacro");
  std::ostringstream xml;
  char buffer[4096];
  while (fgets(buffer, sizeof(buffer), pipe)) xml << buffer;
  if (pclose(pipe) != 0) throw std::runtime_error("Test Xacro failed");

  const auto infos =
      hardware_interface::parse_control_resources_from_urdf(xml.str());
  ASSERT_EQ(infos.size(), 1U);
  ASSERT_EQ(hw->on_init(infos[0]), Callback::SUCCESS);
  EXPECT_EQ(hw->export_state_interfaces().size(), 5U);
  EXPECT_EQ(hw->export_command_interfaces().size(), 1U);
  EXPECT_EQ(hw->on_cleanup(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_EQ(hw->on_cleanup(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  auto bad = infos[0];
  bad.hardware_parameters["update_rate_hz"] = "999";
  EXPECT_EQ(hw->on_init(bad), Callback::ERROR);
}
namespace {
hardware_interface::HardwareInfo TestInfo() {
  const std::string command = std::string("xacro '") + ZFC_BRINGUP_SOURCE +
      "/urdf/stage.urdf.xacro'";
  FILE *pipe = popen(command.c_str(), "r");
  if (!pipe) throw std::runtime_error("Cannot expand test Xacro");
  std::ostringstream xml;
  char buffer[4096];
  while (fgets(buffer, sizeof(buffer), pipe)) xml << buffer;
  if (pclose(pipe) != 0) throw std::runtime_error("Test Xacro failed");

  auto info =
      hardware_interface::parse_control_resources_from_urdf(xml.str()).at(0);
  info.hardware_parameters["startup_timeout_seconds"] = "0.02";
  const std::pair<const char *, const char *> calibration[] = {
    {"m_per_count","0.000001"}, {"velocity_from_encoder","true"},
    {"velocity_mps_per_raw_unit","0.002"},
    {"force_x_newtons_per_count","1"}, {"force_y_newtons_per_count","1"},
    {"force_z_newtons_per_count","1"}, {"force_x_zero_counts","0"},
    {"force_y_zero_counts","0"}, {"force_z_zero_counts","0"},
    {"conventions_confirmed","true"}, {"force_frame","load_cell_link"},
    {"force_channel_mapping","x,y,z"}};
  for (const auto &[key, value] : calibration) info.hardware_parameters[key] = value;
  return info;
}
class HardwareTest : public ::testing::Test {
protected:
  pluginlib::ClassLoader<hardware_interface::SystemInterface> loader{
      "hardware_interface", "hardware_interface::SystemInterface"};
  std::shared_ptr<hardware_interface::SystemInterface> hw;
  std::vector<hardware_interface::CommandInterface> commands;
  std::vector<hardware_interface::StateInterface> states;
  rclcpp::Time time{0};
  rclcpp::Duration period = rclcpp::Duration::from_nanoseconds(1000000);
  using Result = hardware_interface::return_type;
  void SetUp() override {
    fake_igh::reset();
    hw = loader.createSharedInstance("zfc_ethercat_hardware/EthercatHardware");
    ASSERT_EQ(hw->on_init(TestInfo()), Callback::SUCCESS);
    ASSERT_EQ(fake_igh::requests, 0U);
    commands = hw->export_command_interfaces();
    states = hw->export_state_interfaces();
  }
  void activate() {
    ASSERT_EQ(hw->on_configure(rclcpp_lifecycle::State{}), Callback::SUCCESS);
    ASSERT_EQ(hw->on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
    for (unsigned i = 0; i < 10 && !std::isfinite(state("carriage/position")); ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      ASSERT_EQ(hw->read(time, period), Result::OK);
      ASSERT_EQ(hw->write(time, period), Result::OK);
    }
    ASSERT_TRUE(std::isfinite(state("carriage/position")));
    ASSERT_DOUBLE_EQ(commands[0].get_value(), 0.0);
    ASSERT_EQ(hw->perform_command_mode_switch(
                  {"carriage/position"}, {}),
              Result::OK);
  }
  double state(const std::string &name) {
    for (const auto &s : states)
      if (s.get_name() == name)
        return s.get_value();
    throw std::runtime_error("Missing interface: " + name);
  }
  Result cycle(double target) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    EXPECT_EQ(hw->read(time, period), Result::OK);
    commands[0].set_value((target - 123) * 1e-6);
    return hw->write(time, period);
  }
  void finish_fault() {
    auto result = Result::OK;
    for (unsigned i = 0; i < 121 && result == Result::OK; ++i)
      result = cycle(999999);
    EXPECT_EQ(result, Result::ERROR);
    EXPECT_EQ(fake_igh::controlword(), 0);
    EXPECT_EQ(hw->on_error(rclcpp_lifecycle::State{}), Callback::SUCCESS);
    EXPECT_EQ(fake_igh::releases, 1U);
    EXPECT_EQ(hw->on_cleanup(rclcpp_lifecycle::State{}), Callback::SUCCESS);
    EXPECT_EQ(fake_igh::releases, 1U);
  }
};
} // namespace
TEST_F(HardwareTest, CycleOrderAndSingleOwnership) {
  activate();
  fake_igh::order.clear();
  const auto sends = fake_igh::sends;
  EXPECT_EQ(cycle(133), Result::OK);
  EXPECT_EQ(fake_igh::target(), 133);
  EXPECT_EQ(cycle(143), Result::OK);
  EXPECT_EQ(fake_igh::target(), 143);
  // Reference sync is periodic; session startup adds a stationary sample.
  auto order = fake_igh::order;
  order.erase(std::remove(order.begin(), order.end(), 'F'), order.end());
  EXPECT_EQ(order, "ARPSQTARPSQT");
  EXPECT_EQ(fake_igh::sends, sends + 2);
  EXPECT_EQ(fake_igh::requests, 1U);
  EXPECT_EQ(hw->perform_command_mode_switch(
                {}, {"carriage/position"}),
            Result::OK);
  const auto held = state("carriage/position");
  EXPECT_EQ(cycle(999999), Result::OK);
  EXPECT_EQ(fake_igh::target(), 123 + std::lround(held / 1e-6));
  EXPECT_EQ(hw->on_deactivate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_EQ(fake_igh::controlword(), 0);
  EXPECT_EQ(hw->on_cleanup(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_EQ(hw->on_cleanup(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_EQ(fake_igh::releases, 1U);
}
TEST_F(HardwareTest, InvalidCommandStopsWithoutForwarding) {
  activate();
  EXPECT_EQ(cycle(std::numeric_limits<double>::quiet_NaN()), Result::OK);
  EXPECT_EQ(fake_igh::target(), 123);
  finish_fault();
}
TEST_F(HardwareTest, ExcessiveStepStops) {
  activate();
  EXPECT_EQ(cycle(1124), Result::OK);
  EXPECT_EQ(fake_igh::target(), 123);
  finish_fault();
}
TEST_F(HardwareTest, ActualThousandCountBoundAppliesAfterSiRounding) {
  activate();
  EXPECT_EQ(hw->prepare_command_mode_switch({"carriage/position"}, {}), Result::ERROR);
  EXPECT_EQ(hw->perform_command_mode_switch({"carriage/position"}, {}), Result::ERROR);
  EXPECT_EQ(cycle(1123.49), Result::OK); // rounds to 1123, delta exactly 1000
  EXPECT_EQ(fake_igh::target(), 1123);
  EXPECT_EQ(cycle(2123.51), Result::OK); // rounds to 2124, delta 1001
  EXPECT_EQ(fake_igh::target(), 1123);
  finish_fault();
}
TEST_F(HardwareTest, CommunicationLossStops) {
  activate();
  fake_igh::link = false;
  EXPECT_EQ(cycle(133), Result::OK);
  EXPECT_EQ(fake_igh::target(), 123);
  EXPECT_TRUE(std::isnan(state("carriage/position")));
  finish_fault();
}
TEST_F(HardwareTest, DriveLossStopsWithoutReenable) {
  activate();
  fake_igh::drive_fault = true;
  EXPECT_EQ(cycle(133), Result::OK);
  EXPECT_EQ(fake_igh::controlword(), 6);
  EXPECT_EQ(fake_igh::target(), 123);
  finish_fault();
}
TEST_F(HardwareTest, InvalidElmStops) {
  activate();
  fake_igh::elm_valid = false;
  EXPECT_EQ(cycle(133), Result::OK);
  EXPECT_TRUE(std::isnan(state("carriage/position")));
  EXPECT_TRUE(std::isnan(state("load_cell/force.x")));
  finish_fault();
}
TEST_F(HardwareTest, LimitRejects) {
  activate();
  EC_WRITE_U32(fake_igh::data.data() + fake_igh::offsets[0x60FD], 2);
  EXPECT_EQ(cycle(133), Result::OK);
  EXPECT_EQ(fake_igh::target(), 123);
  finish_fault();
}
TEST_F(HardwareTest, StartupTimeoutAndCleanup) {
  fake_igh::complete = false;
  ASSERT_EQ(hw->on_configure(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_EQ(hw->on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  auto result = Result::OK;
  for (unsigned i = 0; i < 160 && result == Result::OK; ++i)
    result = cycle(123);
  EXPECT_EQ(result, Result::ERROR);
  EXPECT_EQ(fake_igh::controlword(), 0);
  EXPECT_EQ(hw->on_error(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_EQ(fake_igh::releases, 1U);
}
TEST_F(HardwareTest, ConfigurationFailuresReleaseOnce) {
  for (bool *failure : {&fake_igh::wrong_identity, &fake_igh::fail_domain,
                        &fake_igh::fail_sdo}) {
    fake_igh::reset();
    *failure = true;
    EXPECT_EQ(hw->on_configure(rclcpp_lifecycle::State{}), Callback::FAILURE);
    EXPECT_EQ(fake_igh::requests, 1U);
    EXPECT_EQ(fake_igh::releases, 1U);
    EXPECT_EQ(hw->on_cleanup(rclcpp_lifecycle::State{}), Callback::SUCCESS);
    EXPECT_EQ(fake_igh::releases, 1U);
  }
}

TEST_F(HardwareTest, ActivationIsPromptAndStartupIsIncremental) {
  ASSERT_EQ(hw->on_configure(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_EQ(fake_igh::sends, 0U);
  const auto before = std::chrono::steady_clock::now();
  ASSERT_EQ(hw->on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_LT(std::chrono::steady_clock::now() - before,
            std::chrono::milliseconds(10));
  EXPECT_EQ(fake_igh::sends, 0U);
  EXPECT_TRUE(std::isnan(state("carriage/position")));
  EXPECT_EQ(hw->prepare_command_mode_switch({"carriage/position"}, {}), Result::ERROR);
  EXPECT_EQ(hw->perform_command_mode_switch({"carriage/position"}, {}), Result::ERROR);
  // A supplied period including prior lifecycle work is not an actual cyclic
  // gap.
  for (unsigned i = 0; i < 3; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    ASSERT_EQ(hw->read(time, rclcpp::Duration::from_seconds(15)), Result::OK);
    ASSERT_EQ(hw->write(time, period), Result::OK);
    EXPECT_EQ(fake_igh::target(), 123);
    EXPECT_EQ(fake_igh::sends, i + 1);
  }
  EXPECT_EQ(cycle(99999), Result::OK);
  EXPECT_TRUE(std::isnan(state("carriage/position"))); // First ready sample only.
  EXPECT_EQ(hw->prepare_command_mode_switch({"carriage/position"}, {}), Result::ERROR);
  EXPECT_EQ(cycle(99999), Result::OK);
  ASSERT_TRUE(std::isfinite(state("carriage/position")));
  EXPECT_EQ(fake_igh::target(), 123);
}
TEST_F(HardwareTest, StartupCatchupDoesNotFloodBus) {
  ASSERT_EQ(hw->on_configure(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  ASSERT_EQ(hw->on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  ASSERT_EQ(hw->read(time, period), Result::OK);
  ASSERT_EQ(hw->write(time, period), Result::OK);
  const auto sends = fake_igh::sends;
  ASSERT_EQ(hw->read(time, period), Result::OK);
  ASSERT_EQ(hw->write(time, period), Result::OK);
  EXPECT_EQ(fake_igh::sends, sends);
}
TEST_F(HardwareTest, ActualGapStillStops) {
  activate();
  std::this_thread::sleep_for(std::chrono::milliseconds(12));
  EXPECT_EQ(cycle(133), Result::OK);
  EXPECT_TRUE(std::isnan(state("carriage/position")));
  EXPECT_EQ(fake_igh::target(), 123);
  finish_fault();
}
TEST_F(HardwareTest, MasterActivationFailureReleasesOnce) {
  ASSERT_EQ(hw->on_configure(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  fake_igh::fail_activate = true;
  EXPECT_EQ(hw->on_activate(rclcpp_lifecycle::State{}), Callback::ERROR);
  EXPECT_EQ(fake_igh::releases, 1U);
  hw->on_cleanup(rclcpp_lifecycle::State{});
  EXPECT_EQ(fake_igh::releases, 1U);
}

TEST_F(HardwareTest, FirstFaultSurvivesConsequencesAndErrorCleanup) {
  testing::internal::CaptureStderr();
  activate();
  fake_igh::complete = false;
  EXPECT_EQ(cycle(133), Result::OK);
  fake_igh::link = false;
  fake_igh::drive_fault = true;
  finish_fault();
  hw.reset(); // Join the consumer before examining its complete output.
  const auto diagnostic = testing::internal::GetCapturedStderr();
  const auto first = diagnostic.find("event=first-fault");
  ASSERT_NE(first, std::string::npos);
  EXPECT_EQ(diagnostic.find("event=first-fault", first + 1), std::string::npos);
  EXPECT_NE(diagnostic.find("reason=incomplete_wc", first), std::string::npos);
  EXPECT_EQ(diagnostic.find("reason=master_link"), std::string::npos);
  EXPECT_EQ(diagnostic.find("reason=drive_csp_loss"), std::string::npos);
  EXPECT_NE(diagnostic.find("event=on-error"), std::string::npos);
}

TEST_F(HardwareTest, QuietDiagnosticsRetainsFaultAndStatusContract) {
  auto info = TestInfo();
  info.hardware_parameters["diagnostic_mode"] = "quiet";
  ASSERT_EQ(hw->on_init(info), Callback::SUCCESS);
  activate();
  EXPECT_EQ(cycle(133), Result::OK);
  EXPECT_EQ(fake_igh::target(), 133);
  EXPECT_EQ(cycle(std::numeric_limits<double>::quiet_NaN()), Result::OK);
  EXPECT_TRUE(std::isnan(state("carriage/position")));
  finish_fault();
  info.hardware_parameters["diagnostic_mode"] = "silent-faults";
  EXPECT_EQ(hw->on_init(info), Callback::ERROR);
}

TEST_F(HardwareTest, MissingCalibrationBlocksBeforeMasterRequest) {
  auto info = TestInfo();
  info.hardware_parameters.erase("m_per_count");
  ASSERT_EQ(hw->on_init(info), Callback::SUCCESS);
  EXPECT_EQ(hw->on_configure(rclcpp_lifecycle::State{}), Callback::FAILURE);
  EXPECT_EQ(fake_igh::requests, 0U);
}
TEST_F(HardwareTest, NonfiniteCalibrationBlocksBeforeMasterRequest) {
  auto info = TestInfo();
  info.hardware_parameters["force_y_zero_counts"] = "nan";
  ASSERT_EQ(hw->on_init(info), Callback::SUCCESS);
  EXPECT_EQ(hw->on_configure(rclcpp_lifecycle::State{}), Callback::FAILURE);
  EXPECT_EQ(fake_igh::requests, 0U);
}
TEST_F(HardwareTest, FaultRejectsNewClaimsAndAllThreeForcesBecomeNaN) {
  activate();
  fake_igh::elm_valid = false;
  EXPECT_EQ(cycle(133), Result::OK);
  EXPECT_TRUE(std::isnan(state("load_cell/force.x")));
  EXPECT_TRUE(std::isnan(state("load_cell/force.y")));
  EXPECT_TRUE(std::isnan(state("load_cell/force.z")));
  EXPECT_EQ(hw->prepare_command_mode_switch({"carriage/position"}, {}), Result::ERROR);
  EXPECT_EQ(hw->perform_command_mode_switch({"carriage/position"}, {}), Result::ERROR);
  EXPECT_EQ(fake_igh::target(), 123);
  finish_fault();
}
TEST_F(HardwareTest, NegativeScaleKeepsRawSwitchDirectionAndFollowingError) {
  auto info = TestInfo();
  info.hardware_parameters["m_per_count"] = "-0.000001";
  ASSERT_EQ(hw->on_init(info), Callback::SUCCESS);
  ASSERT_EQ(hw->on_configure(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  ASSERT_EQ(hw->on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  for (int i = 0; i < 6; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    ASSERT_EQ(hw->read(time, period), Result::OK);
    ASSERT_EQ(hw->write(time, period), Result::OK);
  }
  ASSERT_EQ(hw->perform_command_mode_switch({"carriage/position"}, {}), Result::OK);
  EXPECT_NEAR(commands[0].get_value(), 0.0, 1e-12);
  // Positive raw switch forbids increasing counts: that is DOWN in SI.
  EC_WRITE_U32(fake_igh::data.data() + fake_igh::offsets[0x60FD], 2);
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  ASSERT_EQ(hw->read(time, period), Result::OK);
  commands[0].set_value(-10e-6); // raw 133
  EXPECT_EQ(hw->write(time, period), Result::OK);
  EXPECT_EQ(fake_igh::target(), 123);
  EXPECT_EQ(hw->perform_command_mode_switch({"carriage/position"}, {}), Result::ERROR);
  finish_fault();
}

TEST_F(HardwareTest, SessionReferenceSurvivesUnclaimAndHardwareReactivation) {
  activate();
  EXPECT_EQ(hw->on_init(TestInfo()),Callback::ERROR); // Never re-zero an open session.
  ASSERT_EQ(cycle(133),Result::OK);
  ASSERT_EQ(cycle(133),Result::OK);
  EXPECT_NEAR(state("carriage/position"),10e-6,1e-12);
  ASSERT_EQ(hw->perform_command_mode_switch({},{"carriage/position"}),Result::OK);
  ASSERT_EQ(hw->on_deactivate(rclcpp_lifecycle::State{}),Callback::SUCCESS);
  ASSERT_EQ(hw->on_activate(rclcpp_lifecycle::State{}),Callback::SUCCESS);
  for (int i=0;i<10 && !std::isfinite(state("carriage/position"));++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    ASSERT_EQ(hw->read(time,period),Result::OK);
    ASSERT_EQ(hw->write(time,period),Result::OK);
  }
  EXPECT_NEAR(state("carriage/position"),10e-6,1e-12);
  EXPECT_NEAR(commands[0].get_value(),10e-6,1e-12);
  ASSERT_EQ(hw->on_cleanup(rclcpp_lifecycle::State{}),Callback::SUCCESS);
}
