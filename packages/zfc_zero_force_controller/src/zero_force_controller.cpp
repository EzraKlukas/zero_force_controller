#include "zfc_zero_force_controller/zero_force_controller.hpp"
#include "cycle_timing.hpp"
#include "pluginlib/class_list_macros.hpp"
namespace zfc_zero_force_controller {
using Callback = controller_interface::CallbackReturn;
using Result = controller_interface::return_type;
controller_interface::InterfaceConfiguration
ZeroForceController::command_interface_configuration() const {
  return {controller_interface::interface_configuration_type::INDIVIDUAL,
          {"clearpath_axis/target_position_counts"}};
}
controller_interface::InterfaceConfiguration
ZeroForceController::state_interface_configuration() const {
  return {controller_interface::interface_configuration_type::INDIVIDUAL,
          {"clearpath_axis/actual_position_counts", "ethercat/ready",
           "clearpath_axis/negative_limit", "clearpath_axis/positive_limit"}};
}
Callback ZeroForceController::on_init() {
  try {
    auto_declare<bool>("do_calibrate_", false);
    auto_declare<std::int32_t>("center_zone_half_width_", 1000);
    auto_declare<std::int32_t>("base_velocity_", 500);
    auto_declare<std::int32_t>("jerk_step_", 5);
    auto_declare<std::int32_t>("max_acceleration_limit_", 20);
    auto_declare<std::int32_t>("cycles_per_acceleration_increase_", 10);
  } catch (const std::exception &e) {
    RCLCPP_ERROR(get_node()->get_logger(), "%s", e.what());
    return Callback::ERROR;
  }
  return Callback::SUCCESS;
}
Callback ZeroForceController::on_configure(const rclcpp_lifecycle::State &) {
  try {
    CalibrationParameters p;
    p.do_calibrate_ = get_node()->get_parameter("do_calibrate_").as_bool();
    p.center_zone_half_width_ =
        get_node()->get_parameter("center_zone_half_width_").as_int();
    p.base_velocity_ = get_node()->get_parameter("base_velocity_").as_int();
    p.jerk_step_ = get_node()->get_parameter("jerk_step_").as_int();
    p.max_acceleration_limit_ =
        get_node()->get_parameter("max_acceleration_limit_").as_int();
    p.cycles_per_acceleration_increase_ =
        get_node()
            ->get_parameter("cycles_per_acceleration_increase_")
            .as_int();
    if (sequencer_.configure(p))
      return Callback::SUCCESS;
    RCLCPP_ERROR(get_node()->get_logger(),
                 "Requires +ve bounded params.");
  } catch (const std::exception &e) {
    RCLCPP_ERROR(get_node()->get_logger(), "%s", e.what());
  }
  return Callback::ERROR;
}
Callback ZeroForceController::on_activate(const rclcpp_lifecycle::State &) {
  if (command_interfaces_.size() != 1 || state_interfaces_.size() != 4 ||
      state_interfaces_[1].get_value() != 1.0 ||
      (state_interfaces_[2].get_value() || state_interfaces_[3].get_value()) ||
      !sequencer_.activate(state_interfaces_[0].get_value()))
    return Callback::ERROR;
  failed_ = false;
  command_interfaces_[0].set_value(sequencer_.target());
  return Callback::SUCCESS;
}
Callback ZeroForceController::on_deactivate(const rclcpp_lifecycle::State &) {
  if (!failed_ && !command_interfaces_.empty() && !state_interfaces_.empty())
    command_interfaces_[0].set_value(state_interfaces_[0].get_value());
  sequencer_.reset();
  return Callback::SUCCESS;
}
Result ZeroForceController::update(const rclcpp::Time &,
                                   const rclcpp::Duration &period) {
  zfc::timing::Boundary probe(zfc::timing::controller_entry,
                              zfc::timing::controller_exit);
  ZFC_VALUE(zfc::timing::controller_active, 1);

  // declaring references to point to command and state interfaces
  // corresponding with named variables for clearer code.
  auto &target_position_counts = command_interfaces_[0];
  // const auto &actual_position_counts = state_interfaces_[0];
  const bool &ready = state_interfaces_[1].get_value() == 1.0;
  const auto &negative_limit = state_interfaces_[2];
  const auto &positive_limit = state_interfaces_[3];

  // I could do checking of actual - target. Probably done in hardware.

  bool ok = false;
  if (ready) {
    zfc::timing::Boundary calculation(zfc::timing::calculation_entry,
                                      zfc::timing::calculation_exit);
    if (negative_limit.get_value() || positive_limit.get_value()) {
      sequencer_.limit_hit();
    }
    ok = sequencer_.update(period.nanoseconds());
  }
  if (!ready || !ok) {
    failed_ = true;
    // Hardware treats this sentinel as a fault and executes its bounded
    // stop.
    target_position_counts.set_value(std::numeric_limits<double>::quiet_NaN());
    return Result::ERROR;
  }
  target_position_counts.set_value(sequencer_.target());
  return Result::OK;
}
} // namespace zfc_zero_force_controller
PLUGINLIB_EXPORT_CLASS(zfc_zero_force_controller::ZeroForceController,
                       controller_interface::ControllerInterface)
