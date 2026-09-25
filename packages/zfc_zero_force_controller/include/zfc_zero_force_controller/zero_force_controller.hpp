#pragma once
#include "controller_interface/controller_interface.hpp"
#include "zfc_zero_force_controller/calibration_sequencer.hpp"
namespace zfc_zero_force_controller {
class ZeroForceController : public controller_interface::ControllerInterface {
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
  CalibrationSequencer sequencer_;
  bool failed_ = false;
};
} // namespace zfc_zero_force_controller
