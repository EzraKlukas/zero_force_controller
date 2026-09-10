#include "zfc_ethercat_hardware/ethercat_hardware.hpp"
#include "pluginlib/class_list_macros.hpp"
#include "rclcpp/rclcpp.hpp"
#include <algorithm>
#include <charconv>
#include <string_view>
namespace zfc_ethercat_hardware {
namespace {
constexpr std::string_view command_name =
    "clearpath_axis/target_position_counts";
struct Interface {
  const char *resource;
  const char *name;
};
constexpr std::array<Interface, 25> interfaces{
    {{"clearpath_axis", "actual_position_counts"},
     {"clearpath_axis", "actual_velocity_raw"},
     {"clearpath_axis", "actual_torque_raw"},
     {"clearpath_axis", "statusword"},
     {"clearpath_axis", "mode_display"},
     {"clearpath_axis", "negative_limit"},
     {"clearpath_axis", "positive_limit"},
     {"elm3604", "x_raw_counts"},
     {"elm3604", "y_raw_counts"},
     {"elm3604", "z_raw_counts"},
     {"elm3604", "x_valid"},
     {"elm3604", "y_valid"},
     {"elm3604", "z_valid"},
     {"ethercat", "ready"},
     {"ethercat", "link_up"},
     {"ethercat", "slaves_responding"},
     {"ethercat", "working_counter"},
     {"ethercat", "working_counter_complete"},
     {"ethercat", "communication_fault"},
     {"ethercat", "read_calls"},
     {"ethercat", "write_calls"},
     {"ethercat", "communication_faults"},
     {"ethercat", "invalid_commands"},
     {"ethercat", "excessive_period_observations"},
     {"ethercat", "limit_rejections"}}};
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
  command_ = 0;
  previous_ = 0;
  active_ = claimed_ = fault_ = read_pending_ = prefaulted_ = false;
  stop_complete_ = true;
  last_read_ns_ = 0;
  stop_sequence_ = {};
}
EthercatHardware::Callback
EthercatHardware::on_init(const hardware_interface::HardwareInfo &info) {
  if (SystemInterface::on_init(info) != Callback::SUCCESS)
    return Callback::ERROR;
  reset();
  diagnostics_.start();
  try {
    for (const auto &[key, value] : info.hardware_parameters) {
      if (key != "startup_timeout_seconds" && key != "max_increment_counts" &&
          key != "update_rate_hz")
        throw std::runtime_error("Unknown hardware parameter: " + key);
      if (key == "startup_timeout_seconds") {
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
            number !=
                (key == "update_rate_hz" ? 1000 : zfc::kMaximumIncrementCounts))
          throw std::runtime_error(
              "Require update_rate_hz=1000 and max_increment_counts=10");
      }
    }
    std::array<bool, 25> found{};
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
                "Only clearpath_axis/target_position_counts may be commanded");
        }
      }
    };
    check(info.joints);
    check(info.sensors);
    check(info.gpios);
    if (commands != 1 || !std::all_of(found.begin(), found.end(),
                                      [](bool value) { return value; }))
      throw std::runtime_error("URDF must declare all 25 raw state interfaces "
                               "and one count command");
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
    result.emplace_back(interfaces[i].resource, interfaces[i].name, &state_[i]);
  return result;
}
std::vector<hardware_interface::CommandInterface>
EthercatHardware::export_command_interfaces() {
  std::vector<hardware_interface::CommandInterface> result;
  result.emplace_back("clearpath_axis", "target_position_counts", &command_);
  return result;
}
EthercatHardware::Callback
EthercatHardware::on_configure(const rclcpp_lifecycle::State &) {
  phase_ = "configure";
  first_fault_ = {};
  fault_reported_ = false;
  std::string error;
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
  stop_complete_ = false;
  if (!core_.startup(startup_timeout_, error)) {
    RCLCPP_ERROR(rclcpp::get_logger("zfc_ethercat_hardware"), "%s",
                 error.c_str());
    fault(FaultReason::startup_timeout);
    stop();
    report_fault();
    return Callback::ERROR;
  }
  fault_ = false;
  active_ = true;
  claimed_ = false;
  read_pending_ = false;
  last_read_ns_ = 0;
  previous_ = core_.snapshot().motor.actual_position;
  command_ = previous_;
  copy_state();
  activation_end_ns_ = zfc::MonotonicNs();
  first_write_ = true;
  phase_ = "active";
  diagnostics_.push(record("activation-ready"));
  return Callback::SUCCESS;
}
bool EthercatHardware::stop() noexcept {
  active_ = claimed_ = false;
  read_pending_ = false;
  if (stop_complete_ || !core_.configured())
    return true;
  command_ = core_.snapshot().motor.actual_position;
  phase_ = "shutdown";
  const bool success = core_.shutdown();
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
  state_[13] = active_ && !fault_ && s.ready;
  state_[14] = s.bus.master.link_up;
  state_[15] = s.bus.master.slaves_responding;
  state_[16] = s.bus.domain.working_counter;
  state_[17] = s.bus.domain.wc_state == EC_WC_COMPLETE;
}
DiagnosticRecord EthercatHardware::record(const char *event) const noexcept {
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
  r.snapshot = core_.snapshot();
  r.target = command_;
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
  command_ = core_.snapshot().motor.actual_position;
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
    command_ = previous_ = core_.snapshot().motor.actual_position;
  }
  if (HasCommand(start)) {
    if (!active_ || fault_ || !core_.snapshot().ready)
      return Result::ERROR;
    command_ = previous_ = core_.snapshot().motor.actual_position;
    claimed_ = true;
  }
  return Result::OK;
}
EthercatHardware::Result
EthercatHardware::read(const rclcpp::Time &, const rclcpp::Duration &period) {
  ++state_[19];
  if (!core_.configured())
    return Result::OK;
  if (!prefaulted_) {
    PrefaultStack();
    prefaulted_ = true;
  }
  const auto now = zfc::MonotonicNs();
  read_entry_ns_ = now;
  interval_ns_ = last_read_ns_ ? now - last_read_ns_ : 0;
  supplied_period_ns_ = period.nanoseconds();
  core_.read(now); // Humble supplies system-time stamps; IgH requires our
                   // monotonic basis.
  if (active_) {
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
    if (last_read_ns_ && interval_ns_ > 10000000)
      fault(FaultReason::monotonic_gap);
    if (last_read_ns_ &&
        (period.nanoseconds() <= 0 || period.nanoseconds() > 10000000))
      fault(FaultReason::cm_period);
  }
  last_read_ns_ = now;
  read_pending_ = true;
  copy_state();
  return Result::OK;
}
EthercatHardware::Result EthercatHardware::write(const rclcpp::Time &,
                                                 const rclcpp::Duration &) {
  ++state_[20];
  if (!core_.configured())
    return Result::OK;
  if (active_ && !read_pending_)
    fault(FaultReason::sequencing);
  read_pending_ = false;
  Clearpath::Command output{};
  output.mode_op = CiA402::kModeCsp;
  output.target_position = previous_;
  if (active_ && !fault_) {
    {
      std::int32_t counts;
      const auto validation = zfc::ValidateCommand(
          claimed_ ? command_ : double(previous_), previous_,
          core_.snapshot().motor, zfc::kMaximumIncrementCounts, counts);
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
  report_fault();
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
