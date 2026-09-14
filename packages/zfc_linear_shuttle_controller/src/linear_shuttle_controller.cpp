#include "zfc_linear_shuttle_controller/linear_shuttle_controller.hpp"
#include "cycle_timing.hpp"
#include "pluginlib/class_list_macros.hpp"
namespace zfc_linear_shuttle_controller {
using Callback = controller_interface::CallbackReturn;
using Result = controller_interface::return_type;
controller_interface::InterfaceConfiguration
LinearShuttleController::command_interface_configuration() const {
  return {controller_interface::interface_configuration_type::INDIVIDUAL,
          {"clearpath_axis/target_position_counts"}};
}
controller_interface::InterfaceConfiguration
LinearShuttleController::state_interface_configuration() const {
  return {controller_interface::interface_configuration_type::INDIVIDUAL,
          {"clearpath_axis/actual_position_counts", "ethercat/ready"}};
}
Callback LinearShuttleController::on_init() {
  try {
    auto_declare<std::int64_t>("increment_counts_per_update", 10);
    auto_declare<std::int64_t>("updates_per_leg", 1000);
    auto_declare<std::int64_t>("initial_direction", 1);
    auto_declare<bool>("repeat", false);
    auto_declare<bool>("hold_only", false);
    auto_declare<std::int64_t>("expected_update_rate_hz", 1000);
  } catch (const std::exception &e) {
    RCLCPP_ERROR(get_node()->get_logger(), "%s", e.what());
    return Callback::ERROR;
  }
  return Callback::SUCCESS;
}
Callback
LinearShuttleController::on_configure(const rclcpp_lifecycle::State &) {
  try {
    Parameters p;
    p.increment_counts_per_update =
        get_node()->get_parameter("increment_counts_per_update").as_int();
    p.updates_per_leg = get_node()->get_parameter("updates_per_leg").as_int();
    p.initial_direction =
        get_node()->get_parameter("initial_direction").as_int();
    p.repeat = get_node()->get_parameter("repeat").as_bool();
    p.hold_only = get_node()->get_parameter("hold_only").as_bool();
    p.expected_update_rate_hz =
        get_node()->get_parameter("expected_update_rate_hz").as_int();
    if (shuttle_.configure(p) && get_update_rate() == 1000)
      return Callback::SUCCESS;
    RCLCPP_ERROR(get_node()->get_logger(),
                 "Require 1 kHz controller rate, increment 1..10, direction "
                 "+/-1, and a positive bounded leg length");
  } catch (const std::exception &e) {
    RCLCPP_ERROR(get_node()->get_logger(), "%s", e.what());
  }
  return Callback::ERROR;
}
Callback LinearShuttleController::on_activate(const rclcpp_lifecycle::State &) {
  if (command_interfaces_.size() != 1 || state_interfaces_.size() != 2 ||
      state_interfaces_[1].get_value() != 1.0 ||
      !shuttle_.activate(state_interfaces_[0].get_value()))
    return Callback::ERROR;
  failed_ = false;
  command_interfaces_[0].set_value(shuttle_.target());
  return Callback::SUCCESS;
}
Callback
LinearShuttleController::on_deactivate(const rclcpp_lifecycle::State &) {
  if (!failed_ && !command_interfaces_.empty() && !state_interfaces_.empty())
    command_interfaces_[0].set_value(state_interfaces_[0].get_value());
  shuttle_.reset();
  return Callback::SUCCESS;
}
Result LinearShuttleController::update(const rclcpp::Time &,
                                       const rclcpp::Duration &period) {
  zfc::timing::Boundary probe(zfc::timing::controller_entry,
                              zfc::timing::controller_exit);
  ZFC_VALUE(zfc::timing::controller_active, 1);
  const bool ready = state_interfaces_[1].get_value() == 1.0;
  bool ok = false;
  if (ready) {
    zfc::timing::Boundary calculation(zfc::timing::calculation_entry,
                                      zfc::timing::calculation_exit);
    ok = shuttle_.update(period.nanoseconds());
  }
  if (!ready || !ok) {
    failed_ = true;
    // Hardware treats this sentinel as a fault and executes its bounded stop.
    command_interfaces_[0].set_value(std::numeric_limits<double>::quiet_NaN());
    return Result::ERROR;
  }
  command_interfaces_[0].set_value(shuttle_.target());
  return Result::OK;
}
} // namespace zfc_linear_shuttle_controller
PLUGINLIB_EXPORT_CLASS(zfc_linear_shuttle_controller::LinearShuttleController,
                       controller_interface::ControllerInterface)
