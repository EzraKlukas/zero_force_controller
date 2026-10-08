#include "zfc_calibration_controller/calibration_sequencer_controller.hpp"
#include "cycle_timing.hpp"
#include "pluginlib/class_list_macros.hpp"
namespace zfc_calibration_controller {
using Callback=controller_interface::CallbackReturn;
using Result=controller_interface::return_type;
namespace {
CalibrationSettings settings(const Params &q) {
  CalibrationSettings p;
  p.bounds={q.excursion_limit_m,q.use_position_bounds,q.lower_position_m,q.upper_position_m};
  p.stationary_velocity_mps=q.stationary_velocity_mps;

  p.trajectory={q.center_zone_half_width_m,q.base_velocity_mps,q.jerk_mps3,
    q.initial_acceleration_mps2,q.acceleration_increment_mps2,
    q.max_acceleration_mps2,q.cycles_per_acceleration_increase};
  p.settling_acceleration_mps2=q.settling_acceleration_mps2;
  p.settling_timeout_s=q.settling_timeout_s; p.tracking_tolerance_m=q.tracking_tolerance_m;
  p.stationary_duration_s=q.stationary_duration_s;
  return p;
}
}
controller_interface::InterfaceConfiguration CalibrationSequencerController::command_interface_configuration() const {
  return {controller_interface::interface_configuration_type::INDIVIDUAL,{joint_name_+"/position"}};
}
controller_interface::InterfaceConfiguration CalibrationSequencerController::state_interface_configuration() const {
  return {controller_interface::interface_configuration_type::INDIVIDUAL,
          {joint_name_+"/position",joint_name_+"/velocity",force_interface_}};
}
Callback CalibrationSequencerController::on_init() {
  try {
    listener_=std::make_shared<ParamListener>(get_node());
    const auto p=listener_->get_params();
    joint_name_=p.joint_name; force_interface_=p.force_interface;
    output_.finite_fault_hold=p.finite_fault_hold;
    if (p.finite_fault_hold && !get_node()->get_parameter("use_sim_time").as_bool())
      throw std::runtime_error("finite_fault_hold is simulation-only and requires use_sim_time");
    if (joint_name_.empty() || joint_name_.find('/')!=std::string::npos ||
        force_interface_.find('/')==std::string::npos || force_interface_.front()=='/' ||
        force_interface_.back()=='/')
      throw std::runtime_error("Require joint_name and force resource/interface names");
    // Registered after listener: rclcpp invokes newest validation callback first.
    guard_=get_node()->add_on_set_parameters_callback([this](const auto &) {
      rcl_interfaces::msg::SetParametersResult result;
      result.successful=!active_.load(std::memory_order_acquire);
      result.reason=result.successful ? "" : "Controller is active; deactivate before editing settings or trial ID";
      return result;
    });
    telemetry_=std::make_unique<zfc::TelemetryPublisher>(get_node());
    return Callback::SUCCESS;
  } catch (const std::exception &e) {
    RCLCPP_ERROR(get_node()->get_logger(),"%s",e.what());
    return Callback::ERROR;
  }
}
Callback CalibrationSequencerController::on_configure(const rclcpp_lifecycle::State &) {
  try {
    if (!settings(listener_->get_params()).valid())
      throw std::runtime_error("Invalid finite SI settings, bounds or cross-parameter constraints");
    return Callback::SUCCESS;
  } catch (const std::exception &e) {
    RCLCPP_ERROR(get_node()->get_logger(),"%s",e.what());
    return Callback::ERROR;
  }
}
Callback CalibrationSequencerController::on_activate(const rclcpp_lifecycle::State &) {
  active_.store(true,std::memory_order_release);
  try {
    if (command_interfaces_.size()!=1 || state_interfaces_.size()!=3)
      throw std::runtime_error("Require position command and position/velocity/force feedback");
    const auto p=listener_->get_params(); // No listener access in update().
    const zfc::Inputs in{state_interfaces_[0].get_value(),state_interfaces_[1].get_value(),
                        state_interfaces_[2].get_value(),get_node()->now().nanoseconds(),1000000};
    if (!logic_.activate(settings(p),in))
      throw std::runtime_error("Activation requires finite stationary feedback and a valid excursion envelope");
    const auto trial=p.trial_id==0 ? last_trial_+1 : static_cast<std::uint64_t>(p.trial_id);
    if (trial<=last_trial_ || !telemetry_->begin(trial))
      throw std::runtime_error("Trial ID must increase; await previous trial_status drain before reactivation");
    last_trial_=trial;
    write_command(in.position_m,in.position_m);
    telemetry_->sample(logic_.snapshot());
    return Callback::SUCCESS;
  } catch (const std::exception &e) {
    active_.store(false,std::memory_order_release);
    if (command_interfaces_.size()==1 && state_interfaces_.size()==3) {
      const bool finite=std::isfinite(state_interfaces_[0].get_value()) &&
        std::isfinite(state_interfaces_[1].get_value()) &&
        std::isfinite(state_interfaces_[2].get_value());
      write_command(finite ? state_interfaces_[0].get_value() : NAN,state_interfaces_[0].get_value());
    }
    RCLCPP_ERROR(get_node()->get_logger(),"%s",e.what());
    return Callback::ERROR;
  }
}
Callback CalibrationSequencerController::on_deactivate(const rclcpp_lifecycle::State &) {
  if (!command_interfaces_.empty() && !state_interfaces_.empty()) {
    const double actual=state_interfaces_[0].get_value();
    const bool finite=state_interfaces_.size()==3 && std::isfinite(actual) &&
      std::isfinite(state_interfaces_[1].get_value()) && std::isfinite(state_interfaces_[2].get_value());
    write_command(logic_.snapshot().valid && finite ? actual : NAN,actual);
  }
  telemetry_->finish(false); // A completed trial's latched terminal state is retained.
  logic_.reset();
  active_.store(false,std::memory_order_release);
  return Callback::SUCCESS;
}
void CalibrationSequencerController::write_command(double requested,double measured) noexcept {
  double command;
  if (output_.resolve(requested,measured,command)) command_interfaces_[0].set_value(command);
}
Result CalibrationSequencerController::update(const rclcpp::Time &time,const rclcpp::Duration &period) {
  zfc::timing::Boundary probe(zfc::timing::controller_entry,zfc::timing::controller_exit);
  ZFC_VALUE(zfc::timing::controller_active,1);
  const zfc::Inputs in{state_interfaces_[0].get_value(),state_interfaces_[1].get_value(),
                      state_interfaces_[2].get_value(),time.nanoseconds(),period.nanoseconds()};
  zfc::Snapshot state;
  {
    zfc::timing::Boundary calculate(zfc::timing::calculation_entry,zfc::timing::calculation_exit);
    state=logic_.update(in);
  }
  write_command(state.reference_position_m,in.position_m);
  telemetry_->sample(state); // Bounded preallocated queue; no ROS work here.
  if (!state.valid || state.phase==zfc::Phase::complete)
    telemetry_->finish(state.phase==zfc::Phase::complete && state.valid);
  return state.valid ? Result::OK : Result::ERROR;
}
} // namespace zfc_calibration_controller
PLUGINLIB_EXPORT_CLASS(zfc_calibration_controller::CalibrationSequencerController,controller_interface::ControllerInterface)
