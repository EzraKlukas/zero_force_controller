#include "zfc_ethercat_hardware/ethercat_hardware.hpp"
#include "cycle_timing.hpp"
#include "pluginlib/class_list_macros.hpp"
#include "rclcpp/rclcpp.hpp"
#include <algorithm>
#include <charconv>
#include <ethercat_system.hpp>
#include <string_view>
namespace zfc_ethercat_hardware {
namespace {
constexpr std::string_view command_name =
    "carriage/position";
struct Interface {
  const char *resource;
  const char *name;
};
constexpr std::array<Interface, 5> interfaces{{
    {"carriage", "position"}, {"carriage", "velocity"},
    {"load_cell", "force.x"}, {"load_cell", "force.y"},
    {"load_cell", "force.z"}}};
// Touch the control-thread stack once. Active cycles have no allocations.
void PrefaultStack() noexcept {
  volatile unsigned char stack[8192];
  for (std::size_t i = 0; i < sizeof(stack); ++i)
    stack[i] = 0;
}
bool HasCommand(const std::vector<std::string> &names) noexcept {
  return std::any_of(names.begin(), names.end(),
                     [](const auto &name) { return name == command_name; });
}
} // namespace
EthercatHardware::~EthercatHardware() {
  stop();
  core_.release();
}
void EthercatHardware::reset() noexcept {
  state_.fill(0);
  session_.end();
  calibration_.clear_reference();
  si_state_.fill(NAN);
  // Keep the final measured SI hold across error/cleanup. Interfaces stay NaN
  // until fresh, valid feedback is available on the next activation.
  previous_ = 0;
  active_ = claimed_ = fault_ = read_pending_ = prefaulted_ = false;
  stop_complete_ = true;
  last_read_ns_ = 0;
  stop_sequence_ = {};
}
EthercatHardware::Callback
EthercatHardware::on_init(const hardware_interface::HardwareInfo &info) {
  if (core_.configured() || active_) {
    RCLCPP_ERROR(rclcpp::get_logger("zfc_ethercat_hardware"),
      "Cannot reinitialize an open hardware session; deactivate and clean up first");
    return Callback::ERROR;
  }
  if (SystemInterface::on_init(info) != Callback::SUCCESS)
    return Callback::ERROR;
  reset();
  quiet_diagnostics_ = false;
  zfc::timing::initialize();
  diagnostics_.start();
  try {
    for (const auto &[key, value] : info.hardware_parameters) {
      if (SiCalibration::parameter(key))
        continue; // Validate all installation data in configure, before I/O.
      if (key != "startup_timeout_seconds" &&
          key != "update_rate_hz" && key != "diagnostic_mode")
        throw std::runtime_error("Unknown hardware parameter: " + key);
      if (key == "diagnostic_mode") {
        if (value != "production" && value != "quiet")
          throw std::runtime_error(
              "diagnostic_mode must be production or quiet");
        quiet_diagnostics_ = value == "quiet";
      } else if (key == "startup_timeout_seconds") {
        std::size_t used = 0;
        startup_timeout_ = std::stod(value, &used);
        if (used != value.size() || !std::isfinite(startup_timeout_) ||
            startup_timeout_ <= 0 || startup_timeout_ > 300)
          throw std::runtime_error(
              "startup_timeout_seconds must be in (0,300]");
      } else {
        int number = 0;
        const auto result =
            std::from_chars(value.data(), value.data() + value.size(), number);
        if (result.ec != std::errc{} ||
            result.ptr != value.data() + value.size() ||
            number != 1000)
              {
                throw std::runtime_error(
                    "Require update_rate_hz=1000");
              }
      }
    }
    std::array<bool, 5> found{};
    unsigned commands = 0;
    auto check = [&](const auto &resources) {
      for (const auto &resource : resources) {
        for (const auto &it : resource.state_interfaces) {
          bool match = false;
          for (std::size_t i = 0; i < interfaces.size(); ++i) {
            if (resource.name == interfaces[i].resource &&
                it.name == interfaces[i].name && !found[i]) {
              found[i] = true;
              match = true;
              break;
            }
          }
          if (!match)
            throw std::runtime_error("Unexpected/duplicate state interface: " +
                                     resource.name + "/" + it.name);
        }
        for (const auto &it : resource.command_interfaces) {
          if (resource.name + "/" + it.name != command_name || ++commands != 1)
            throw std::runtime_error(
                "Only carriage/position may be commanded");
        }
      }
    };
    check(info.joints);
    check(info.sensors);
    check(info.gpios);
    if (commands != 1 || !std::all_of(found.begin(), found.end(),
                                      [](bool value) { return value; }))
      throw std::runtime_error("Require carriage position/velocity, load_cell force.x/y/z, and one position command");
  } catch (const std::exception &e) {
    RCLCPP_ERROR(rclcpp::get_logger("zfc_ethercat_hardware"), "%s", e.what());
    return Callback::ERROR;
  }
  return Callback::SUCCESS;
}
std::vector<hardware_interface::StateInterface>
EthercatHardware::export_state_interfaces() {
  std::vector<hardware_interface::StateInterface> result;
  result.reserve(interfaces.size());
  for (std::size_t i = 0; i < interfaces.size(); ++i)
    result.emplace_back(interfaces[i].resource, interfaces[i].name, &si_state_[i]);
  return result;
}
std::vector<hardware_interface::CommandInterface>
EthercatHardware::export_command_interfaces() {
  std::vector<hardware_interface::CommandInterface> result;
  result.emplace_back("carriage", "position", &command_);
  return result;
}
EthercatHardware::Callback
EthercatHardware::on_configure(const rclcpp_lifecycle::State &) {
  phase_ = "configure";
  first_fault_ = {};
  fault_reported_ = false;
  std::string error;
  try {
    calibration_ = SiCalibration::load(info_.hardware_parameters);
  } catch (const std::exception &e) {
    RCLCPP_ERROR(rclcpp::get_logger("zfc_ethercat_hardware"),
                 "Hardware configuration blocked before IgH access: %s", e.what());
    return Callback::FAILURE;
  }
  if (!core_.configure(error)) {
    RCLCPP_ERROR(rclcpp::get_logger("zfc_ethercat_hardware"), "%s",
                 error.c_str());
    return Callback::FAILURE;
  }
  return Callback::SUCCESS;
}
EthercatHardware::Callback
EthercatHardware::on_activate(const rclcpp_lifecycle::State &) {
  phase_ = "activate_startup";
  diagnostics_.push(record("activation-enter"));
  std::string error;
  PrefaultStack();
  if (!core_.activate(error)) {
    RCLCPP_ERROR(rclcpp::get_logger("zfc_ethercat_hardware"), "%s",
                 error.c_str());
    return Callback::ERROR;
  }
  stop_complete_ = false;
  fault_ = false;
  active_ = true;
  starting_ = true;
  claimed_ = false;
  read_pending_ = false;
  skipped_ = false;
  last_read_ns_ = last_exchange_ns_ = 0;
  maximum_interval_ns_ = maximum_tracking_counts_ = 0;
  startup_begin_ns_ = activation_end_ns_ = zfc::MonotonicNs();
  first_write_ = true;
  hold_measured();
  copy_state();
  diagnostics_.push(record("activation-armed"));
  return Callback::SUCCESS;
}

bool EthercatHardware::stop() noexcept {
  active_ = claimed_ = starting_ = false;
  read_pending_ = false;
  if (core_.configured())
    hold_measured();
  if (stop_complete_ || !core_.configured())
    return true;
  phase_ = "shutdown";
  const bool success = core_.shutdown();
  hold_measured(); // shutdown exchanges may have supplied newer feedback
  session_.suspend();
  if (!success)
    fault(FaultReason::shutdown_failure);
  diagnostics_.push(record(success ? "shutdown-confirmed" : "shutdown-failed"));
  report_fault();
  stop_complete_ = true;
  return success;
}
EthercatHardware::Callback
EthercatHardware::on_deactivate(const rclcpp_lifecycle::State &) {
  const bool success = stop();
  copy_state();
  if (!success)
    RCLCPP_ERROR(
        rclcpp::get_logger("zfc_ethercat_hardware"),
        "Shutdown could not confirm Switch On Disabled with complete WC");
  return success ? Callback::SUCCESS : Callback::ERROR;
}
EthercatHardware::Callback
EthercatHardware::on_cleanup(const rclcpp_lifecycle::State &) {
  const bool success = stop();
  core_.release();
  reset();
  return success ? Callback::SUCCESS : Callback::ERROR;
}
EthercatHardware::Callback
EthercatHardware::on_shutdown(const rclcpp_lifecycle::State &state) {
  return on_cleanup(state);
}
EthercatHardware::Callback
EthercatHardware::on_error(const rclcpp_lifecycle::State &) {
  // Active I/O returns ERROR only after the cycle-driven stop has completed.
  // Lifecycle failures may arrive here earlier; stop() is bounded in that case.
  diagnostics_.push(record("on-error"));
  stop();
  core_.release();
  reset();
  return Callback::SUCCESS;
}
void EthercatHardware::copy_state() noexcept {
  const auto &s = core_.snapshot();
  state_[0] = s.motor.actual_position;
  state_[1] = s.motor.actual_velocity;
  state_[2] = s.motor.actual_torque;
  state_[3] = s.motor.statusword;
  state_[4] = s.motor.mode_display;
  state_[5] = s.motor.negative_limit_reached();
  state_[6] = s.motor.positive_limit_reached();
  state_[7] = s.elm.x.raw_sample;
  state_[8] = s.elm.y.raw_sample;
  state_[9] = s.elm.z.raw_sample;
  state_[10] = zfc::ElmChannelValid(s.elm.x);
  state_[11] = zfc::ElmChannelValid(s.elm.y);
  state_[12] = zfc::ElmChannelValid(s.elm.z);
  state_[13] = active_ && !starting_ && !fault_ && s.ready;
  state_[14] = s.bus.master.link_up;
  state_[15] = s.bus.master.slaves_responding;
  state_[16] = s.bus.domain.working_counter;
  state_[17] = s.bus.domain.wc_state == EC_WC_COMPLETE;
  si_state_.fill(NAN);
  if (can_claim()) {
    si_state_[0] = calibration_.position(s.motor.actual_position);
    si_state_[1] = calibration_.velocity_from_encoder ? session_.velocity() :
                   calibration_.velocity(s.motor.actual_velocity);
    si_state_[2] = calibration_.force(0, s.elm.x.raw_sample);
    si_state_[3] = calibration_.force(1, s.elm.y.raw_sample);
    si_state_[4] = calibration_.force(2, s.elm.z.raw_sample);
  }
}
void EthercatHardware::hold_measured() noexcept {
  previous_ = core_.snapshot().motor.actual_position;
  command_ = calibration_.position(previous_);
}
bool EthercatHardware::can_claim() const noexcept {
  const auto &s = core_.snapshot();
  return active_ && !starting_ && !fault_ && s.ready && session_.valid() &&
         zfc::ElmChannelValid(s.elm.x) && zfc::ElmChannelValid(s.elm.y) &&
         zfc::ElmChannelValid(s.elm.z) &&
         std::isfinite(calibration_.position(s.motor.actual_position)) &&
         std::isfinite(calibration_.velocity_from_encoder ? session_.velocity() :
                       calibration_.velocity(s.motor.actual_velocity)) &&
         std::isfinite(calibration_.force(0, s.elm.x.raw_sample)) &&
         std::isfinite(calibration_.force(1, s.elm.y.raw_sample)) &&
         std::isfinite(calibration_.force(2, s.elm.z.raw_sample));
}
DiagnosticRecord EthercatHardware::record(const char *event) const noexcept {
  zfc::timing::FineSpan probe(zfc::timing::diagnostic_construct_ns);
  DiagnosticRecord r;
  r.event = event;
  r.phase = phase_;
  r.reason = first_fault_.reason;
  r.mono_ns = zfc::MonotonicNs();
  r.reads = state_[19];
  r.writes = state_[20];
  r.interval_ns = interval_ns_;
  r.period_ns = supplied_period_ns_;
  r.handoff_ns = activation_end_ns_ && read_entry_ns_ >= activation_end_ns_
                     ? read_entry_ns_ - activation_end_ns_
                     : 0;
  r.command_changes = command_changes_;
  r.excessive_periods = state_[23];
  r.maximum_interval_ns = maximum_interval_ns_;
  r.maximum_tracking_counts = maximum_tracking_counts_;
  r.snapshot = core_.snapshot();
  r.raw_state = state_;
  r.target = previous_; // Diagnostic target stays in native encoder counts.
  r.claimed = claimed_;
  r.read_pending = read_pending_;
  r.stop_cycle = stop_sequence_.cycle();
  return r;
}
void EthercatHardware::report_fault() noexcept {
  if (first_fault_.reason != FaultReason::none && !fault_reported_) {
    diagnostics_.push(first_fault_);
    fault_reported_ = true;
  }
}
void EthercatHardware::fault(FaultReason reason) noexcept {
  if (first_fault_.reason == FaultReason::none) {
    first_fault_ = record("first-fault");
    first_fault_.reason = reason;
    ZFC_VALUE(zfc::timing::fault, static_cast<int>(reason));
  }
  if (fault_)
    return;
  fault_ = true;
  claimed_ = false;
  state_[13] = 0;
  if (reason >= FaultReason::master_link &&
      reason <= FaultReason::elm_invalid) {
    state_[18] = 1;
    ++state_[21];
  }
  hold_measured();
  si_state_.fill(NAN);
  stop_sequence_.start(core_.snapshot().motor);
}
EthercatHardware::Result EthercatHardware::perform_command_mode_switch(
    const std::vector<std::string> &start,
    const std::vector<std::string> &stop_names) {
  if (HasCommand(stop_names)) {
    if (active_ && !std::isfinite(command_)) {
      ++state_[22];
      fault(FaultReason::invalid_command);
    }
    claimed_ = false;
    hold_measured();
  }
  if (HasCommand(start)) {
    if (!can_claim() || claimed_)
      return Result::ERROR;
    hold_measured();
    claimed_ = true;
    command_changes_ = 0;
    observed_target_ = previous_;
    diagnostics_.push(record("motion-start"));
  }
  return Result::OK;
}
EthercatHardware::Result EthercatHardware::prepare_command_mode_switch(
    const std::vector<std::string> &start,
    const std::vector<std::string> &stop_names) {
  if (HasCommand(start) &&
      (!can_claim() || (claimed_ && !HasCommand(stop_names))))
    return Result::ERROR;
  return Result::OK;
}
EthercatHardware::Result
EthercatHardware::read(const rclcpp::Time &, const rclcpp::Duration &period) {
  zfc::timing::HardwareRead probe;
  ZFC_VALUE(zfc::timing::ros_period_ns, period.nanoseconds());
  ++state_[19];
  if (!active_ || !core_.configured())
    return Result::OK;
  if (!prefaulted_) {
    PrefaultStack();
    prefaulted_ = true;
  }
  const auto now = zfc::MonotonicNs();
  read_entry_ns_ = now;
  interval_ns_ = last_read_ns_ ? now - last_read_ns_ : 0;
  supplied_period_ns_ = period.nanoseconds();
  maximum_interval_ns_ = std::max(maximum_interval_ns_, interval_ns_);
  last_read_ns_ = now;
  skipped_ = false;
  // CM may catch up after a lifecycle callback. Never flood the bus.
  if (last_exchange_ns_ && now - last_exchange_ns_ < 500000) {
    skipped_ = true;
    if (!starting_)
      fault(FaultReason::cm_period);
    return Result::OK;
  }
  last_exchange_ns_ = now;
  core_.read(now);
  if (core_.snapshot().ready && !fault_) {
    const auto &motor=core_.snapshot().motor;
    if (!session_.observe(motor.actual_position, now, motor.actual_velocity==0,
                          calibration_.m_per_count, zfc::kMaximumVelocity))
      fault(FaultReason::encoder_discontinuity);
    if (session_.valid() && !calibration_.reference_valid) {
      calibration_.set_reference(session_.reference());
      diagnostics_.push(record("session-reference"));
    }
  }
  if (starting_ && !fault_) {
    if (first_write_ && now - activation_end_ns_ > 10000000)
      fault(FaultReason::monotonic_gap);
    else if (now - startup_begin_ns_ >
             static_cast<std::uint64_t>(startup_timeout_ * 1e9))
      fault(FaultReason::startup_timeout);
    else if (interval_ns_ > 10000000)
      fault(FaultReason::monotonic_gap);
    // Expected startup PDO/drive/ELM states are gated by the startup deadline.
  }
  if (active_ && !starting_) {
    const auto &s = core_.snapshot();
    const auto &b = s.bus;
    if (!b.master.link_up)
      fault(FaultReason::master_link);
    else if (b.master.slaves_responding != 3)
      fault(FaultReason::slave_count_identity);
    else if (b.domain.wc_state != EC_WC_COMPLETE)
      fault(FaultReason::incomplete_wc);
    else if (!b.ek1100.online || !b.ek1100.operational || !b.elm3604.online ||
             !b.elm3604.operational || !b.clearpath.online ||
             !b.clearpath.operational)
      fault(FaultReason::slave_not_operational);
    else if (!CiA402::IsOperationEnabledCSP(s.motor))
      fault(FaultReason::drive_csp_loss);
    else if (!zfc::ElmChannelValid(s.elm.x) || !zfc::ElmChannelValid(s.elm.y) ||
             !zfc::ElmChannelValid(s.elm.z))
      fault(FaultReason::elm_invalid);
    if (read_pending_)
      fault(FaultReason::sequencing);
    if (period.nanoseconds() > 1500000)
      ++state_[23];
    // Independently bound a scheduling gap even if ROS time jumps.
    if (interval_ns_ && interval_ns_ > 10000000)
      fault(FaultReason::monotonic_gap);
    if (interval_ns_ &&
        (period.nanoseconds() <= 0 || period.nanoseconds() > 10000000))
      fault(FaultReason::cm_period);
  }
  read_pending_ = true;
  copy_state();
  return Result::OK;
}
EthercatHardware::Result EthercatHardware::write(const rclcpp::Time &,
                                                 const rclcpp::Duration &) {
  zfc::timing::HardwareWrite probe;
  ZFC_VALUE(zfc::timing::phase, starting_  ? 1
                                : fault_   ? 5
                                : claimed_ ? 3
                                : active_  ? 2
                                           : 0);
  ZFC_VALUE(zfc::timing::fault, static_cast<int>(first_fault_.reason));
  ZFC_VALUE(zfc::timing::diagnostic_mode, quiet_diagnostics_);
  ZFC_VALUE(zfc::timing::diagnostic_drops, diagnostics_.drops());
  ++state_[20];
  if (!active_ || !core_.configured())
    return Result::OK;
  if (skipped_)
    return Result::OK;
  if (active_ && !read_pending_)
    fault(FaultReason::sequencing);
  read_pending_ = false;
  Clearpath::Command output{};
  output.mode_op = CiA402::kModeCsp;
  output.target_position = previous_;
  if (starting_ && !fault_) {
    CiA402::UpdateCSPEnableState(core_.snapshot().motor, &output);
    output.target_position = core_.snapshot().motor.actual_position;
    hold_measured();
    if (core_.snapshot().ready && session_.valid() && calibration_.reference_valid) {
      starting_ = false;
      phase_ = "active";
      copy_state();
      diagnostics_.push(record("startup-ready"));
    }
  } else if (active_ && !fault_) {
    {
      std::int32_t counts;
      std::int32_t converted = previous_;
      const bool converted_ok = !claimed_ || calibration_.to_counts(command_, converted);
      const auto validation = converted_ok ? zfc::ValidateCommand(
          double(converted), previous_,
          core_.snapshot().motor, zfc::kMaximumVelocity, counts)
          : zfc::CommandResult::invalid;
      if (validation != zfc::CommandResult::valid) {
        if (validation == zfc::CommandResult::limit)
          ++state_[24];
        else
          ++state_[22];
        fault(validation == zfc::CommandResult::limit
                  ? FaultReason::logical_limit
              : validation == zfc::CommandResult::excessive_increment
                  ? FaultReason::excessive_increment
                  : FaultReason::invalid_command);
      } else
        output.target_position = previous_ = counts;
    }
    output.controlword = CiA402::kControlwordEnableOperation;
  }
  if (fault_) {
    hold_measured();
    // One stop step per CM cycle; no extra scheduling authority.
    // Wait for one more read after the final disable-voltage frame before
    // ERROR.
    if (stop_sequence_.done()) {
      core_.write(stop_sequence_.next());
      stop_complete_ = true;
      active_ = false;
      return Result::ERROR;
    }
    output = stop_sequence_.next();
    if (output.controlword == CiA402::kControlwordEnableOperation &&
        !CiA402::IsOperationEnabledCSP(core_.snapshot().motor))
      output.controlword = CiA402::kControlwordShutdown;
  }
  core_.write(output);
  if (claimed_ && !fault_) {
    const auto error = std::int64_t(output.target_position) -
                       core_.snapshot().motor.actual_position;
    maximum_tracking_counts_ = std::max(
        maximum_tracking_counts_, std::uint64_t(error < 0 ? -error : error));
  }
  report_fault();
  if (claimed_ && !fault_ && output.target_position != observed_target_) {
    observed_target_ = output.target_position;
    ++command_changes_;
    ZFC_VALUE(zfc::timing::command_change, 1);
    if (!quiet_diagnostics_)
      diagnostics_.push(record("motion-command"));
  }
  if (first_write_) {
    diagnostics_.push(record("first-cm-write"));
    first_write_ = false;
  }
  if (static_cast<std::uint64_t>(state_[20]) % 1000 == 0)
    diagnostics_.push(record("status"));
  return Result::OK;
}
} // namespace zfc_ethercat_hardware
PLUGINLIB_EXPORT_CLASS(zfc_ethercat_hardware::EthercatHardware,
                       hardware_interface::SystemInterface)
