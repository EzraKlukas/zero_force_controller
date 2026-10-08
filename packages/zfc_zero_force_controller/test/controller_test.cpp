#include "zfc_zero_force_controller/zero_force_controller.hpp"
#include <gtest/gtest.h>
#include <thread>
using namespace zfc_zero_force_controller;
using Callback = controller_interface::CallbackReturn;
using UpdateResult = controller_interface::return_type;
class ControllerTest : public ::testing::Test {
protected:
  ZeroForceController controller;
  double actual = 0.123, target = -999, force = 1, velocity = 0;
  hardware_interface::CommandInterface cmd{"carriage", "position", &target};
  hardware_interface::StateInterface pos{"carriage", "position", &actual};
  hardware_interface::StateInterface vel{"carriage", "velocity", &velocity};
  hardware_interface::StateInterface sensor{"load_cell", "force.x", &force};
  static void SetUpTestSuite() { rclcpp::init(0, nullptr); }
  static void TearDownTestSuite() { rclcpp::shutdown(); }
  void SetUp() override {
    ASSERT_EQ(controller.init("offline_si", "",
      rclcpp::NodeOptions().parameter_overrides({rclcpp::Parameter("update_rate", 1000), rclcpp::Parameter("use_sim_time", true), rclcpp::Parameter("hold_only", true)})), UpdateResult::OK);
    ASSERT_EQ(controller.on_configure(rclcpp_lifecycle::State{}), Callback::SUCCESS);
    std::vector<hardware_interface::LoanedCommandInterface> commands;
    commands.emplace_back(cmd);
    std::vector<hardware_interface::LoanedStateInterface> states;
    states.emplace_back(pos);
    states.emplace_back(vel);
    states.emplace_back(sensor);
    controller.assign_interfaces(std::move(commands), std::move(states));
  }
  void drain() {
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(controller.get_node()->get_node_base_interface());
    executor.spin_some(std::chrono::milliseconds(50));
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    executor.spin_some();
  }
  UpdateResult update(std::int64_t ns = 1000000) {
    return controller.update(rclcpp::Time(0), rclcpp::Duration::from_nanoseconds(ns));
  }
};
TEST_F(ControllerTest, TransportIndependentNamesHoldRestartAndDeactivation) {
  EXPECT_EQ(controller.command_interface_configuration().names,
            std::vector<std::string>({"carriage/position"}));
  EXPECT_EQ(controller.state_interface_configuration().names,
            std::vector<std::string>({"carriage/position", "carriage/velocity", "load_cell/force.x"}));
  for (double start : {0.123, 0.234}) {
    actual = start;
    ASSERT_EQ(controller.on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
    EXPECT_DOUBLE_EQ(target, actual);
    for (int i = 0; i < 100; ++i) {
      ASSERT_EQ(update(), UpdateResult::OK);
      EXPECT_DOUBLE_EQ(target, actual);
    }
    actual += .001;
    EXPECT_EQ(controller.on_deactivate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
    EXPECT_DOUBLE_EQ(target, actual);
    drain();
  }
}
TEST_F(ControllerTest, InvalidSensorExportsPersistentStopSentinel) {
  force = NAN;
  EXPECT_EQ(controller.on_activate(rclcpp_lifecycle::State{}), Callback::ERROR);
  EXPECT_TRUE(std::isnan(target));
  force = 1;
  ASSERT_EQ(controller.on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  force = NAN;
  EXPECT_EQ(update(), UpdateResult::ERROR);
  EXPECT_TRUE(std::isnan(target));
  force = 1;
  EXPECT_EQ(update(), UpdateResult::ERROR);
  EXPECT_TRUE(std::isnan(target));
  EXPECT_EQ(controller.on_deactivate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_TRUE(std::isnan(target));
}
TEST_F(ControllerTest, PositionAndPeriodFaultsStop) {
  ASSERT_EQ(controller.on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_EQ(update(10000001), UpdateResult::ERROR);
  EXPECT_TRUE(std::isnan(target));
  ASSERT_EQ(controller.on_deactivate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  drain();
  ASSERT_EQ(controller.on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  actual = NAN;
  EXPECT_EQ(update(), UpdateResult::ERROR);
  EXPECT_TRUE(std::isnan(target));
}
TEST_F(ControllerTest, InactiveSettingsApplyAtActivationAndActiveChangesRejected) {
  EXPECT_TRUE(controller.get_node()->set_parameter(rclcpp::Parameter("hold_only", false)).successful);
  EXPECT_TRUE(controller.get_node()->set_parameter(rclcpp::Parameter("baseline_duration_s", .001)).successful);
  EXPECT_TRUE(controller.get_node()->set_parameter(rclcpp::Parameter("noise_duration_s", .001)).successful);
  EXPECT_TRUE(controller.get_node()->set_parameter(rclcpp::Parameter("damping_per_s", 0.0)).successful);
  ASSERT_EQ(controller.on_activate(rclcpp_lifecycle::State{}), Callback::SUCCESS);
  EXPECT_FALSE(controller.get_node()->set_parameter(rclcpp::Parameter("acceleration_per_force", .2)).successful);
  EXPECT_EQ(update(),UpdateResult::OK);
  EXPECT_EQ(update(),UpdateResult::OK);
  force=-1;
  EXPECT_EQ(update(),UpdateResult::OK);
  EXPECT_GT(target,actual);
  ASSERT_EQ(controller.on_deactivate(rclcpp_lifecycle::State{}),Callback::SUCCESS);
  EXPECT_TRUE(controller.get_node()->set_parameter(rclcpp::Parameter("acceleration_per_force", .2)).successful);
  EXPECT_FALSE(controller.get_node()->set_parameter(rclcpp::Parameter("joint_name", "changed")).successful);
  EXPECT_FALSE(controller.get_node()->set_parameter(rclcpp::Parameter("acceleration_per_force", INFINITY)).successful);
}
