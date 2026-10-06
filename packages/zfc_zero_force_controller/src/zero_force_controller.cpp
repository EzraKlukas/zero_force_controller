#include "zfc_zero_force_controller/zero_force_controller.hpp"
#include "cycle_timing.hpp"
#include "pluginlib/class_list_macros.hpp"
namespace zfc_zero_force_controller {
using Callback = controller_interface::CallbackReturn;
using Result = controller_interface::return_type;
controller_interface::InterfaceConfiguration
ZeroForceController::command_interface_configuration() const {
  return {controller_interface::interface_configuration_type::INDIVIDUAL,
          {joint_name_ + "/position"}};
}
controller_interface::InterfaceConfiguration
ZeroForceController::state_interface_configuration() const {
  return {controller_interface::interface_configuration_type::INDIVIDUAL,
          {joint_name_ + "/position", force_interface_}};
}
Callback ZeroForceController::on_init() {
  try {
    auto_declare<std::string>("joint_name", "carriage");
    auto_declare<std::string>("force_interface", "load_cell/force.x");
    auto_declare<bool>("do_calibrate", false);
    for (const auto *name : {"center_zone_half_width_m", "base_velocity_mps",
         "jerk_mps3", "initial_acceleration_mps2",
         "acceleration_increment_mps2", "max_acceleration_mps2"})
      auto_declare<double>(name, std::numeric_limits<double>::quiet_NaN());
    auto_declare<std::int64_t>("cycles_per_acceleration_increase", 5);
  } catch (const std::exception &e) {
    RCLCPP_ERROR(get_node()->get_logger(), "%s", e.what());
    return Callback::ERROR;
  }
  return Callback::SUCCESS;
}
Callback ZeroForceController::on_configure(const rclcpp_lifecycle::State &) {
  try {
    CalibrationParameters p;
    joint_name_ = get_node()->get_parameter("joint_name").as_string();
    force_interface_ = get_node()->get_parameter("force_interface").as_string();
    if (joint_name_.empty() || joint_name_.find('/') != std::string::npos ||
        force_interface_.find('/') == std::string::npos)
      throw std::runtime_error("Require joint_name and resource/interface force_interface");
    p.do_calibrate = get_node()->get_parameter("do_calibrate").as_bool();
    p.center_zone_half_width_m = get_node()->get_parameter("center_zone_half_width_m").as_double();
    p.base_velocity_mps = get_node()->get_parameter("base_velocity_mps").as_double();
    p.jerk_mps3 = get_node()->get_parameter("jerk_mps3").as_double();
    p.initial_acceleration_mps2 = get_node()->get_parameter("initial_acceleration_mps2").as_double();
    p.acceleration_increment_mps2 = get_node()->get_parameter("acceleration_increment_mps2").as_double();
    p.max_acceleration_mps2 = get_node()->get_parameter("max_acceleration_mps2").as_double();
    p.cycles_per_acceleration_increase =
        get_node()->get_parameter("cycles_per_acceleration_increase").as_int();
    if (sequencer_.configure(p))
      return Callback::SUCCESS;
    RCLCPP_ERROR(get_node()->get_logger(),
                 "Calibration mode requires finite, set SI trajectory parameters and positive acceleration magnitudes");
  } catch (const std::exception &e) {
    RCLCPP_ERROR(get_node()->get_logger(), "%s", e.what());
  }
  return Callback::ERROR;
}
Callback ZeroForceController::on_activate(const rclcpp_lifecycle::State &) {
  if (command_interfaces_.size() != 1 || state_interfaces_.size() != 2 ||
      !std::isfinite(state_interfaces_[1].get_value()) ||
      !sequencer_.activate(state_interfaces_[0].get_value()))
    return Callback::ERROR;
  failed_ = false;
  command_interfaces_[0].set_value(sequencer_.target());
  controller_state_ = ControllerState::calibrate;
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

  auto &target_position = command_interfaces_[0];
  const bool valid = std::isfinite(state_interfaces_[0].get_value()) &&
                     std::isfinite(state_interfaces_[1].get_value());

  bool ok = false;
  if (valid) {
    zfc::timing::Boundary calculation(zfc::timing::calculation_entry,
                                      zfc::timing::calculation_exit);
    ok = sequencer_.update(period.nanoseconds());
  }
  if (failed_ || !valid || !ok) {
    failed_ = true;
    // Hardware treats this sentinel as a fault and executes its bounded
    // stop.
    target_position.set_value(std::numeric_limits<double>::quiet_NaN());
    return Result::ERROR;
  }
  target_position.set_value(sequencer_.target());
  return Result::OK;
}
} // namespace zfc_zero_force_controller
PLUGINLIB_EXPORT_CLASS(zfc_zero_force_controller::ZeroForceController,
                       controller_interface::ControllerInterface)
