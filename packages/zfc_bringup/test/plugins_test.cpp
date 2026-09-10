#include "ament_index_cpp/get_package_share_directory.hpp"
#include "controller_interface/controller_interface.hpp"
#include "fake_igh.hpp"
#include "hardware_interface/component_parser.hpp"
#include "hardware_interface/resource_manager.hpp"
#include "hardware_interface/system_interface.hpp"
#include "pluginlib/class_loader.hpp"
#include <chrono>
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
  std::ifstream input(
      ament_index_cpp::get_package_share_directory("zfc_bringup") +
      "/urdf/ethercat.urdf");
  ASSERT_TRUE(input.good());
  std::ostringstream xml;
  xml << input.rdbuf();
  const auto infos =
      hardware_interface::parse_control_resources_from_urdf(xml.str());
  ASSERT_EQ(infos.size(), 1U);
  ASSERT_EQ(hw->on_init(infos[0]), Callback::SUCCESS);
  EXPECT_EQ(hw->export_state_interfaces().size(), 25U);
  EXPECT_EQ(hw->export_command_interfaces().size(), 1U);
  EXPECT_EQ(hw->on_cleanup(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_EQ(hw->on_cleanup(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  auto bad = infos[0];
  bad.hardware_parameters["update_rate_hz"] = "999";
  EXPECT_EQ(hw->on_init(bad), Callback::ERROR);
}
TEST(Plugins, ControllerRunsThroughLoanedInterfaces) {
  rclcpp::init(0, nullptr);
  {
    pluginlib::ClassLoader<controller_interface::ControllerInterface> loader(
        "controller_interface", "controller_interface::ControllerInterface");
    auto controller = loader.createSharedInstance(
        "zfc_linear_shuttle_controller/LinearShuttleController");
    ASSERT_EQ(controller->init("offline_shuttle", "",
                               rclcpp::NodeOptions().parameter_overrides(
                                   {rclcpp::Parameter("update_rate", 1000)})),
              controller_interface::return_type::OK);
    EXPECT_EQ(controller->configure().id(),
              lifecycle_msgs::msg::State::PRIMARY_STATE_INACTIVE);
    double actual = 123, target = -999, ready = 1;
    hardware_interface::CommandInterface cmd("clearpath_axis",
                                             "target_position_counts", &target);
    hardware_interface::StateInterface pos("clearpath_axis",
                                           "actual_position_counts", &actual);
    hardware_interface::StateInterface state("ethercat", "ready", &ready);
    std::vector<hardware_interface::LoanedCommandInterface> commands;
    commands.emplace_back(cmd);
    std::vector<hardware_interface::LoanedStateInterface> states;
    states.emplace_back(pos);
    states.emplace_back(state);
    controller->assign_interfaces(std::move(commands), std::move(states));
    ASSERT_EQ(controller->on_activate(rclcpp_lifecycle::State{}),
              Callback::SUCCESS);
    EXPECT_EQ(target, 123);
    for (int i = 1; i <= 2000; ++i) {
      EXPECT_EQ(controller->update(rclcpp::Time(0),
                                   rclcpp::Duration::from_nanoseconds(1000000)),
                controller_interface::return_type::OK);
      EXPECT_EQ(target, 123 + 10 * (i <= 1000 ? i : 2000 - i));
    }
    EXPECT_EQ(controller->on_deactivate(rclcpp_lifecycle::State{}),
              Callback::SUCCESS);
    actual = -234;
    ASSERT_EQ(controller->on_activate(rclcpp_lifecycle::State{}),
              Callback::SUCCESS);
    EXPECT_EQ(target, -234);
    controller->on_deactivate(rclcpp_lifecycle::State{});
    controller->release_interfaces();
  }
  rclcpp::shutdown();
}

namespace {
hardware_interface::HardwareInfo TestInfo() {
  std::ifstream input(
      ament_index_cpp::get_package_share_directory("zfc_bringup") +
      "/urdf/ethercat.urdf");
  std::ostringstream xml;
  xml << input.rdbuf();
  auto info =
      hardware_interface::parse_control_resources_from_urdf(xml.str()).at(0);
  info.hardware_parameters["startup_timeout_seconds"] = "0.02";
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
    for (unsigned i = 0; i < 10 && state("ethercat/ready") != 1; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      ASSERT_EQ(hw->read(time, period), Result::OK);
      ASSERT_EQ(hw->write(time, period), Result::OK);
    }
    ASSERT_EQ(state("ethercat/ready"), 1);
    ASSERT_EQ(commands[0].get_value(), 123);
    ASSERT_EQ(hw->perform_command_mode_switch(
                  {"clearpath_axis/target_position_counts"}, {}),
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
    commands[0].set_value(target);
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
  // Startup takes four exchanges, so reference sync falls on this first
  // read/write.
  EXPECT_EQ(fake_igh::order, "ARPFSQTARPSQT");
  EXPECT_EQ(fake_igh::sends, sends + 2);
  EXPECT_EQ(fake_igh::requests, 1U);
  EXPECT_EQ(state("ethercat/read_calls"), 6);
  EXPECT_EQ(state("ethercat/write_calls"), 6);
  EXPECT_EQ(hw->perform_command_mode_switch(
                {}, {"clearpath_axis/target_position_counts"}),
            Result::OK);
  const auto held = state("clearpath_axis/actual_position_counts");
  EXPECT_EQ(cycle(999999), Result::OK);
  EXPECT_EQ(fake_igh::target(), held);
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
  EXPECT_EQ(state("ethercat/invalid_commands"), 1);
  finish_fault();
}
TEST_F(HardwareTest, ExcessiveStepStops) {
  activate();
  EXPECT_EQ(cycle(134), Result::OK);
  EXPECT_EQ(fake_igh::target(), 123);
  EXPECT_EQ(state("ethercat/invalid_commands"), 1);
  finish_fault();
}
TEST_F(HardwareTest, CommunicationLossStops) {
  activate();
  fake_igh::link = false;
  EXPECT_EQ(cycle(133), Result::OK);
  EXPECT_EQ(fake_igh::target(), 123);
  EXPECT_EQ(state("ethercat/communication_faults"), 1);
  EXPECT_EQ(state("ethercat/ready"), 0);
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
  EXPECT_EQ(state("ethercat/ready"), 0);
  EXPECT_EQ(state("elm3604/x_valid"), 0);
  finish_fault();
}
TEST_F(HardwareTest, LimitRejects) {
  activate();
  EC_WRITE_U32(fake_igh::data.data() + fake_igh::offsets[0x60FD], 2);
  EXPECT_EQ(cycle(133), Result::OK);
  EXPECT_EQ(fake_igh::target(), 123);
  EXPECT_EQ(state("ethercat/limit_rejections"), 1);
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

TEST(Plugins, ResourceManagerReadUpdateWrite) {
  fake_igh::reset();
  rclcpp::init(0, nullptr);
  {
    std::ifstream input(
        ament_index_cpp::get_package_share_directory("zfc_bringup") +
        "/urdf/ethercat.urdf");
    std::ostringstream xml;
    xml << input.rdbuf();
    hardware_interface::ResourceManager manager(xml.str());
    EXPECT_EQ(fake_igh::requests, 0U);
    EXPECT_EQ(manager.state_interface_keys().size(), 25U);
    EXPECT_EQ(manager.command_interface_keys().size(), 1U);
    rclcpp_lifecycle::State active(
        lifecycle_msgs::msg::State::PRIMARY_STATE_ACTIVE, "active");

    pluginlib::ClassLoader<controller_interface::ControllerInterface> loader(
        "controller_interface", "controller_interface::ControllerInterface");
    auto controller = loader.createSharedInstance(
        "zfc_linear_shuttle_controller/LinearShuttleController");
    ASSERT_EQ(controller->init("resource_manager_shuttle", "",
                               rclcpp::NodeOptions().parameter_overrides(
                                   {rclcpp::Parameter("update_rate", 1000)})),
              controller_interface::return_type::OK);
    ASSERT_EQ(controller->configure().id(),
              lifecycle_msgs::msg::State::PRIMARY_STATE_INACTIVE);
    const std::vector<std::string> names{
        "clearpath_axis/target_position_counts"};
    ASSERT_EQ(manager.set_component_state("EthercatSystem", active),
              hardware_interface::return_type::OK);
    const auto startup_period = rclcpp::Duration::from_nanoseconds(1000000);
    for (int i = 0; i < 5; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      ASSERT_TRUE(manager.read(rclcpp::Time(0), startup_period).ok);
      ASSERT_TRUE(manager.write(rclcpp::Time(0), startup_period).ok);
    }
    ASSERT_TRUE(manager.perform_command_mode_switch(names, {}));
    std::vector<hardware_interface::LoanedCommandInterface> commands;
    commands.emplace_back(manager.claim_command_interface(names[0]));
    std::vector<hardware_interface::LoanedStateInterface> states;
    states.emplace_back(
        manager.claim_state_interface("clearpath_axis/actual_position_counts"));
    states.emplace_back(manager.claim_state_interface("ethercat/ready"));
    controller->assign_interfaces(std::move(commands), std::move(states));
    ASSERT_EQ(controller->on_activate(rclcpp_lifecycle::State{}),
              Callback::SUCCESS);
    const auto period = rclcpp::Duration::from_nanoseconds(1000000);
    for (int i = 1; i <= 2010; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      const rclcpp::Time time(std::int64_t(i) * 1000000);
      ASSERT_TRUE(manager.read(time, period).ok);
      ASSERT_EQ(controller->update(time, period),
                controller_interface::return_type::OK);
      ASSERT_TRUE(manager.write(time, period).ok);
      EXPECT_EQ(fake_igh::target(), 123 + (i <= 1000   ? 10 * i
                                           : i <= 2000 ? 10 * (2000 - i)
                                                       : 0));
    }
    ASSERT_TRUE(manager.perform_command_mode_switch({}, names));
    ASSERT_EQ(controller->on_deactivate(rclcpp_lifecycle::State{}),
              Callback::SUCCESS);
    controller->release_interfaces();
    ASSERT_TRUE(manager.shutdown_components());
    EXPECT_EQ(fake_igh::releases, 1U);
  }
  rclcpp::shutdown();
}

TEST_F(HardwareTest, ActivationIsPromptAndStartupIsIncremental) {
  ASSERT_EQ(hw->on_configure(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_EQ(fake_igh::sends, 0U);
  const auto before = std::chrono::steady_clock::now();
  ASSERT_EQ(hw->on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_LT(std::chrono::steady_clock::now() - before,
            std::chrono::milliseconds(10));
  EXPECT_EQ(fake_igh::sends, 0U);
  EXPECT_EQ(state("ethercat/ready"), 0);
  EXPECT_EQ(hw->perform_command_mode_switch(
                {"clearpath_axis/target_position_counts"}, {}),
            Result::ERROR);
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
  EXPECT_EQ(state("ethercat/ready"), 1);
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
  EXPECT_EQ(state("ethercat/ready"), 0);
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
