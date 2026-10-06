#include "zfc_zero_force_controller/zero_force_controller.hpp"
#include <gtest/gtest.h>
using namespace zfc_zero_force_controller;
using Callback = controller_interface::CallbackReturn;
using Result = controller_interface::return_type;
class ControllerTest : public ::testing::Test {
protected:
  ZeroForceController controller;
  double actual = 0.123, target = -999, force = 1;
  hardware_interface::CommandInterface cmd{"carriage", "position", &target};
  hardware_interface::StateInterface pos{"carriage", "position", &actual};
  hardware_interface::StateInterface sensor{"load_cell", "force.x", &force};
  static void SetUpTestSuite() { rclcpp::init(0, nullptr); }
  static void TearDownTestSuite() { rclcpp::shutdown(); }
  void SetUp() override {
    ASSERT_EQ(controller.init("offline_si", "",
      rclcpp::NodeOptions().parameter_overrides({rclcpp::Parameter("update_rate", 1000)})), Result::OK);
    ASSERT_EQ(controller.on_configure(rclcpp_lifecycle::State{}), Callback::SUCCESS);
    std::vector<hardware_interface::LoanedCommandInterface> commands;
    commands.emplace_back(cmd);
    std::vector<hardware_interface::LoanedStateInterface> states;
    states.emplace_back(pos);
    states.emplace_back(sensor);
    controller.assign_interfaces(std::move(commands), std::move(states));
  }
  Result update(std::int64_t ns = 1000000) {
    return controller.update(rclcpp::Time(0), rclcpp::Duration::from_nanoseconds(ns));
  }
};
TEST_F(ControllerTest, TransportIndependentNamesHoldRestartAndDeactivation) {
  EXPECT_EQ(controller.command_interface_configuration().names,
            std::vector<std::string>({"carriage/position"}));
  EXPECT_EQ(controller.state_interface_configuration().names,
            std::vector<std::string>({"carriage/position", "load_cell/force.x"}));
  for (double start : {0.123, 0.234}) {
    actual = start;
    ASSERT_EQ(controller.on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
    EXPECT_DOUBLE_EQ(target, actual);
    for (int i = 0; i < 100; ++i) {
      ASSERT_EQ(update(), Result::OK);
      EXPECT_DOUBLE_EQ(target, actual);
    }
    actual += .001;
    EXPECT_EQ(controller.on_deactivate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
    EXPECT_DOUBLE_EQ(target, actual);
  }
}
TEST_F(ControllerTest, InvalidSensorExportsPersistentStopSentinel) {
  force = NAN;
  EXPECT_EQ(controller.on_activate(rclcpp_lifecycle::State{}), Callback::ERROR);
  force = 1;
  ASSERT_EQ(controller.on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  force = NAN;
  EXPECT_EQ(update(), Result::ERROR);
  EXPECT_TRUE(std::isnan(target));
  force = 1;
  EXPECT_EQ(update(), Result::ERROR);
  EXPECT_TRUE(std::isnan(target));
  EXPECT_EQ(controller.on_deactivate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_TRUE(std::isnan(target));
}
TEST_F(ControllerTest, PositionAndPeriodFaultsStop) {
  ASSERT_EQ(controller.on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_EQ(update(10000001), Result::ERROR);
  EXPECT_TRUE(std::isnan(target));
  ASSERT_EQ(controller.on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  actual = NAN;
  EXPECT_EQ(update(), Result::ERROR);
  EXPECT_TRUE(std::isnan(target));
}
TEST_F(ControllerTest, UnsetTrajectoryRefusedAndNamesParameterized) {
  controller.get_node()->set_parameter(rclcpp::Parameter("do_calibrate", true));
  EXPECT_EQ(controller.on_configure(rclcpp_lifecycle::State{}), Callback::ERROR);
  controller.get_node()->set_parameter(rclcpp::Parameter("do_calibrate", false));
  controller.get_node()->set_parameter(rclcpp::Parameter("joint_name", "stage_joint"));
  controller.get_node()->set_parameter(rclcpp::Parameter("force_interface", "sensor/force.y"));
  ASSERT_EQ(controller.on_configure(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_EQ(controller.command_interface_configuration().names,
            std::vector<std::string>({"stage_joint/position"}));
  EXPECT_EQ(controller.state_interface_configuration().names,
            std::vector<std::string>({"stage_joint/position", "sensor/force.y"}));
}
