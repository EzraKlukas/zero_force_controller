#include "controller_interface/controller_interface.hpp"
#include "hardware_interface/resource_manager.hpp"
#include "pluginlib/class_loader.hpp"
#include "zfc_interfaces/msg/trial_status.hpp"
#include <gtest/gtest.h>
#include <thread>
namespace {
using Controller=controller_interface::ControllerInterface;
using Callback=controller_interface::CallbackReturn;
using UpdateResult=controller_interface::return_type;
class HandoffTest : public testing::Test {
protected:
  static void SetUpTestSuite() { rclcpp::init(0,nullptr); }
  static void TearDownTestSuite() { rclcpp::shutdown(); }
  pluginlib::ClassLoader<Controller> loader{"controller_interface","controller_interface::ControllerInterface"};
  std::shared_ptr<Controller> make(const char *plugin,const char *name,
                                 std::vector<rclcpp::Parameter> parameters={}) {
    auto c=loader.createSharedInstance(plugin);
    parameters.emplace_back("update_rate",1000);
    parameters.emplace_back("use_sim_time",true);
    EXPECT_EQ(c->init(name,"",rclcpp::NodeOptions().parameter_overrides(parameters)),UpdateResult::OK);
    EXPECT_EQ(c->on_configure(rclcpp_lifecycle::State{}),Callback::SUCCESS);
    return c;
  }
};
// Stock ROS mock only in this test; never installed as a production backend.
constexpr auto robot=R"(<robot name="fixture">
<link name="base"/><link name="tool"/><joint name="carriage" type="prismatic">
<parent link="base"/><child link="tool"/><axis xyz="0 0 1"/>
<limit lower="-1" upper="1" effort="1" velocity="1"/></joint>
<ros2_control name="Fixture" type="system"><hardware>
<plugin>mock_components/GenericSystem</plugin></hardware>
<joint name="carriage"><command_interface name="position"/>
<state_interface name="position"><param name="initial_value">0.25</param></state_interface>
<state_interface name="velocity"><param name="initial_value">0</param></state_interface></joint>
<sensor name="load_cell"><state_interface name="force.x">
<param name="initial_value">0</param></state_interface></sensor>
</ros2_control></robot>)";
TEST_F(HandoffTest, ResourceManagerRejectsConcurrentClaimAndAllowsMeasuredHandoff) {
  hardware_interface::ResourceManager rm(robot,true,true);
  auto zero=make("zfc_zero_force_controller/ZeroForceController","exclusive_zero",
                 {rclcpp::Parameter("hold_only",true)});
  auto cal=make("zfc_calibration_controller/CalibrationSequencerController","exclusive_cal");
  EXPECT_EQ(zero->command_interface_configuration().names,cal->command_interface_configuration().names);
  auto assign=[&](const auto &c) {
    std::vector<hardware_interface::LoanedCommandInterface> commands;
    commands.emplace_back(rm.claim_command_interface("carriage/position"));
    std::vector<hardware_interface::LoanedStateInterface> states;
    for (const auto &name:c->state_interface_configuration().names)
      states.emplace_back(rm.claim_state_interface(name));
    c->assign_interfaces(std::move(commands),std::move(states));
  };
  assign(zero);
  ASSERT_EQ(zero->on_activate(rclcpp_lifecycle::State{}),Callback::SUCCESS);
  EXPECT_TRUE(rm.command_interface_is_claimed("carriage/position"));
  EXPECT_THROW(rm.claim_command_interface("carriage/position"),std::runtime_error);
  ASSERT_EQ(zero->on_deactivate(rclcpp_lifecycle::State{}),Callback::SUCCESS);
  zero->release_interfaces();
  EXPECT_FALSE(rm.command_interface_is_claimed("carriage/position"));
  assign(cal);
  ASSERT_EQ(cal->on_activate(rclcpp_lifecycle::State{}),Callback::SUCCESS);
  EXPECT_FALSE(cal->get_node()->set_parameter(rclcpp::Parameter("base_velocity_mps",.02)).successful);
  ASSERT_EQ(cal->on_deactivate(rclcpp_lifecycle::State{}),Callback::SUCCESS);
  cal->release_interfaces();
  EXPECT_TRUE(cal->get_node()->set_parameter(rclcpp::Parameter("base_velocity_mps",.02)).successful);
  EXPECT_FALSE(cal->get_node()->set_parameter(rclcpp::Parameter("joint_name","other")).successful);
}
TEST_F(HandoffTest, CalibrationCompletionIsStationaryTimestampedAndLatched) {
  auto cal=make("zfc_calibration_controller/CalibrationSequencerController","offline_trial",
    {rclcpp::Parameter("trial_id",42),rclcpp::Parameter("base_velocity_mps",.01),
     rclcpp::Parameter("max_acceleration_mps2",.2),
     rclcpp::Parameter("cycles_per_acceleration_increase",1)});
  double actual=.25,velocity=0,force=12,target=NAN;
  hardware_interface::CommandInterface command("carriage","position",&target);
  hardware_interface::StateInterface q("carriage","position",&actual),
    v("carriage","velocity",&velocity),f("load_cell","force.x",&force);
  std::vector<hardware_interface::LoanedCommandInterface> commands;
  commands.emplace_back(command);
  std::vector<hardware_interface::LoanedStateInterface> states;
  states.emplace_back(q); states.emplace_back(v); states.emplace_back(f);
  cal->assign_interfaces(std::move(commands),std::move(states));
  ASSERT_EQ(cal->on_activate(rclcpp_lifecycle::State{}),Callback::SUCCESS);
  EXPECT_DOUBLE_EQ(target,actual);
  // Ideal tracking fixture, not servo dynamics or simulator validation.
  for (int i=1;i<=4000;++i) {
    const auto before=target;
    ASSERT_EQ(cal->update(rclcpp::Time(i*1000000LL),
      rclcpp::Duration::from_nanoseconds(1000000)),UpdateResult::OK);
    velocity=(target-before)/.001;
    actual=target;
  }
  EXPECT_DOUBLE_EQ(velocity,0);
  auto observer=std::make_shared<rclcpp::Node>("trial_observer");
  zfc_interfaces::msg::TrialStatus status;
  bool received=false;
  auto subscription=observer->create_subscription<zfc_interfaces::msg::TrialStatus>(
    "/offline_trial/trial_status",rclcpp::QoS(1).reliable().transient_local(),
    [&](const zfc_interfaces::msg::TrialStatus &m) { status=m; received=true; });
  rclcpp::executors::SingleThreadedExecutor executor;
  executor.add_node(cal->get_node()->get_node_base_interface());
  executor.add_node(observer);
  for (int i=0;i<100 && !received;++i) {
    executor.spin_some(); std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  ASSERT_TRUE(received);
  EXPECT_EQ(status.trial_id,42U);
  EXPECT_GT(status.final_sequence,100U);
  EXPECT_TRUE(status.completed); EXPECT_TRUE(status.successful);
  EXPECT_TRUE(status.capture_complete); EXPECT_EQ(status.dropped_samples,0U);
  EXPECT_GT(status.stamp.nanosec+status.stamp.sec*1000000000LL,0);
  // Late reader must receive the terminal state without another update.
  bool late_received=false;
  auto late=observer->create_subscription<zfc_interfaces::msg::TrialStatus>(
    "/offline_trial/trial_status",rclcpp::QoS(1).reliable().transient_local(),
    [&](const zfc_interfaces::msg::TrialStatus &m) { late_received=m.trial_id==42 && m.completed; });
  for (int i=0;i<100 && !late_received;++i) {
    executor.spin_some(); std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  EXPECT_TRUE(late_received);
  EXPECT_EQ(cal->on_deactivate(rclcpp_lifecycle::State{}),Callback::SUCCESS);
  EXPECT_DOUBLE_EQ(target,actual);
}
TEST_F(HandoffTest, InvalidSensorKeepsPhysicalNaNButLatchesFiniteSimulationHold) {
  for (const bool simulation : {false,true}) {
    for (const char *plugin : {"zfc_zero_force_controller/ZeroForceController",
                              "zfc_calibration_controller/CalibrationSequencerController"}) {
      auto c=make(plugin,"fault_policy",{rclcpp::Parameter("finite_fault_hold",simulation)});
      double actual=.25,velocity=0,force=2.4525,target=NAN;
      hardware_interface::CommandInterface command("carriage","position",&target);
      hardware_interface::StateInterface q("carriage","position",&actual),
        v("carriage","velocity",&velocity),f("load_cell","force.x",&force);
      std::vector<hardware_interface::LoanedCommandInterface> commands;
      commands.emplace_back(command);
      std::vector<hardware_interface::LoanedStateInterface> states;
      states.emplace_back(q); states.emplace_back(v); states.emplace_back(f);
      c->assign_interfaces(std::move(commands),std::move(states));
      ASSERT_EQ(c->on_activate(rclcpp_lifecycle::State{}),Callback::SUCCESS);
      force=NAN;
      EXPECT_EQ(c->update(rclcpp::Time(1000000LL),rclcpp::Duration::from_nanoseconds(1000000)),UpdateResult::ERROR);
      if (simulation) EXPECT_DOUBLE_EQ(target,.25);
      else EXPECT_TRUE(std::isnan(target));
      actual=.26; // A fault must not follow later feedback drift.
      EXPECT_EQ(c->update(rclcpp::Time(2000000LL),rclcpp::Duration::from_nanoseconds(1000000)),UpdateResult::ERROR);
      EXPECT_EQ(c->on_deactivate(rclcpp_lifecycle::State{}),Callback::SUCCESS);
      if (simulation) EXPECT_DOUBLE_EQ(target,.25);
      else EXPECT_TRUE(std::isnan(target));
    }
  }
}
} // namespace
