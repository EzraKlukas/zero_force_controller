#pragma once
#include "controller_interface/controller_interface.hpp"
#include "zfc_linear_shuttle_controller/ramp_command_generator.hpp"
namespace zfc_linear_shuttle_controller {
class LinearShuttleController
    : public controller_interface::ControllerInterface {
public:
  controller_interface::InterfaceConfiguration
  command_interface_configuration() const override;
  controller_interface::InterfaceConfiguration
  state_interface_configuration() const override;
  controller_interface::CallbackReturn on_init() override;
  controller_interface::CallbackReturn
  on_configure(const rclcpp_lifecycle::State &) override;
  controller_interface::CallbackReturn
  on_activate(const rclcpp_lifecycle::State &) override;
  controller_interface::CallbackReturn
  on_deactivate(const rclcpp_lifecycle::State &) override;
  controller_interface::return_type update(const rclcpp::Time &,
                                           const rclcpp::Duration &) override;

private:
  RampCommandGenerator ramp_;
  bool failed_ = false;
};
} // namespace zfc_linear_shuttle_controller
