#include "hardware_interface/component_parser.hpp"
#include "controller_interface/controller_interface.hpp"
#include "pluginlib/class_loader.hpp"
#include "rclcpp/parameter_map.hpp"
#include <cmath>
#include <cstdio>
#include <gtest/gtest.h>
#include <string>
TEST(ControlResources, BothXacroBranchesParseWithSameContract) {
  for (const auto *backend : {"ethercat", "gazebo"}) {
    const std::string command = std::string("xacro '") + ZFC_BRINGUP_SOURCE +
        "/urdf/stage.urdf.xacro' backend:=" + backend;
    FILE *pipe = popen(command.c_str(), "r");
    ASSERT_NE(pipe, nullptr);
    std::string xml;
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), pipe))
      xml += buffer;
    ASSERT_EQ(pclose(pipe), 0);
    const auto infos = hardware_interface::parse_control_resources_from_urdf(xml);
    ASSERT_EQ(infos.size(), 1U);
    const auto &info = infos.front();
    EXPECT_EQ(info.name, "StageSystem");
    ASSERT_EQ(info.joints.size(), 1U);
    EXPECT_EQ(info.joints[0].name, "carriage");
    EXPECT_EQ(info.joints[0].command_interfaces.size(), 1U);
    EXPECT_EQ(info.joints[0].state_interfaces.size(), 2U);
    ASSERT_EQ(info.sensors.size(), 1U);
    EXPECT_EQ(info.sensors[0].name, "load_cell");
    EXPECT_EQ(info.sensors[0].state_interfaces.size(), 3U);
    EXPECT_TRUE(info.gpios.empty());
    if (std::string(backend) == "gazebo")
      EXPECT_TRUE(info.hardware_parameters.empty());
  }
}
TEST(ControlResources, NativeRosYamlAndForceOnlyBroadcaster) {
  const std::string directory = std::string(ZFC_BRINGUP_SOURCE) + "/config/";
  const auto parameters = rclcpp::parameter_map_from_yaml_file(directory + "controllers.yaml");
  for (const auto *file : {"hardware.yaml", "gazebo.yaml"})
    EXPECT_FALSE(rclcpp::parameter_map_from_yaml_file(directory + file).empty());
  bool found_speed = false;
  for (const auto &param : parameters.at("/calibration_sequencer_controller"))
    if (param.get_name() == "base_velocity_mps") {
      ASSERT_EQ(param.get_type(), rclcpp::ParameterType::PARAMETER_DOUBLE);
      EXPECT_DOUBLE_EQ(param.as_double(),.1);
      found_speed = true;
    }
  EXPECT_TRUE(found_speed);
  rclcpp::init(0, nullptr);
  {
    pluginlib::ClassLoader<controller_interface::ControllerInterface> loader(
      "controller_interface", "controller_interface::ControllerInterface");
    auto broadcaster = loader.createSharedInstance(
      "force_torque_sensor_broadcaster/ForceTorqueSensorBroadcaster");
    ASSERT_EQ(broadcaster->init("load_cell_broadcaster", "",
      rclcpp::NodeOptions().parameter_overrides(parameters.at("/load_cell_broadcaster"))),
      controller_interface::return_type::OK);
    ASSERT_EQ(broadcaster->on_configure(rclcpp_lifecycle::State{}),
              controller_interface::CallbackReturn::SUCCESS);
    EXPECT_EQ(broadcaster->state_interface_configuration().names,
      std::vector<std::string>({"load_cell/force.x", "load_cell/force.y", "load_cell/force.z"}));
  }
  rclcpp::shutdown();
}
