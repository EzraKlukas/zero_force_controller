#pragma once
#include "controller_interface/controller_interface.hpp"
#include "zfc_calibration_controller/calibration_sequencer_logic.hpp"
#include "zfc_calibration_controller/calibration_parameters.hpp"
#include "zfc_interfaces/telemetry_publisher.hpp"
#include "zfc_interfaces/command_output.hpp"
#include <atomic>
namespace zfc_calibration_controller {
class CalibrationSequencerController : public controller_interface::ControllerInterface {
public:
  controller_interface::InterfaceConfiguration command_interface_configuration() const override;
  controller_interface::InterfaceConfiguration state_interface_configuration() const override;
  controller_interface::CallbackReturn on_init() override;
  controller_interface::CallbackReturn on_configure(const rclcpp_lifecycle::State &) override;
  controller_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State &) override;
  controller_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State &) override;
  controller_interface::return_type update(const rclcpp::Time &, const rclcpp::Duration &) override;
private:
  void write_command(double requested,double measured) noexcept;
  zfc::CommandOutput output_;
  CalibrationSequencerLogic logic_;
  std::shared_ptr<ParamListener> listener_;
  std::unique_ptr<zfc::TelemetryPublisher> telemetry_;
  rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr guard_;
  std::atomic<bool> active_{false};
  std::string joint_name_="carriage", force_interface_="load_cell/force.x";
  std::uint64_t last_trial_=0;
};
} // namespace zfc_calibration_controller
