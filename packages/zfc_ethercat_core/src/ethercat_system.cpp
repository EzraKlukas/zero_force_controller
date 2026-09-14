#include "ethercat_system.hpp"
#include "cycle_timing.hpp"
#include <cerrno>
#include <cmath>
#include <sstream>
#include <stdexcept>
namespace zfc {
namespace {
constexpr std::uint64_t kNsecPerSec = 1000000000ULL;
constexpr std::uint16_t kEk1100Alias = 0, kEk1100Position = 0;
constexpr std::uint32_t kBeckhoffVendorId = 2, kEk1100ProductCode = 0x044c2c52;
int SleepUntil(const timespec &deadline) noexcept {
  int result;
  do {
    result =
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, nullptr);
  } while (result == EINTR);
  return result;
}
} // namespace
std::uint64_t TimespecToNs(const timespec &time) noexcept {
  return static_cast<std::uint64_t>(time.tv_sec) * kNsecPerSec +
         static_cast<std::uint64_t>(time.tv_nsec);
}

void AddNs(timespec *time, std::uint64_t ns) noexcept {
  time->tv_sec += static_cast<time_t>(ns / kNsecPerSec);
  time->tv_nsec += static_cast<long>(ns % kNsecPerSec);
  while (time->tv_nsec >= static_cast<long>(kNsecPerSec)) {
    time->tv_nsec -= static_cast<long>(kNsecPerSec);
    ++time->tv_sec;
  }
}

std::uint64_t MonotonicNs() noexcept {
  timespec time{};
  clock_gettime(CLOCK_MONOTONIC, &time);
  return TimespecToNs(time);
}
bool ElmChannelValid(const Elm3604::Channel &channel) noexcept {
  return channel.number_of_samples > 0U && !channel.txpdo_state &&
         !channel.error;
}

// Recording starts only after communication, drive state, and ELM sample
// validity are all true. If any of these become false after recording starts,
// the run is treated as communication loss.
bool ReadyToRecord(const EthercatState &state,
                   const Elm3604::Feedback &elm) noexcept {
  return state.have_master && state.have_domain && state.have_elm3604 &&
         state.have_clearpath && state.master.link_up &&
         state.master.slaves_responding == kExpectedSlaveCount &&
         state.domain.wc_state == EC_WC_COMPLETE && state.ek1100.online &&
         state.ek1100.operational && state.elm3604.online &&
         state.elm3604.operational && state.clearpath.online &&
         state.clearpath.operational && state.drive_operation_enabled_csp &&
         ElmChannelValid(elm.x) && ElmChannelValid(elm.y) &&
         ElmChannelValid(elm.z);
}

void StopSequence::start(const Clearpath::PDO::TxPDOs &motor) noexcept {
  command_ = {};
  command_.mode_op = CiA402::kModeCsp;
  command_.target_position = motor.actual_position;
  // Never enable a drive that was not already enabled merely to stop it.
  cycle_ = CiA402::IsOperationEnabledCSP(motor) ? 0 : 20;
}
Clearpath::Command StopSequence::next() noexcept {
  command_.controlword = cycle_ < 20   ? CiA402::kControlwordEnableOperation
                         : cycle_ < 70 ? CiA402::kControlwordShutdown
                                       : CiA402::kControlwordDisableVoltage;
  if (!done())
    ++cycle_;
  return command_;
}

bool EthercatSystem::configure(std::string &error, bool activate_now) {
  if (ctx_.master) {
    error = "EtherCAT master already owned";
    return false;
  }
  try {
    auto *master = ecrt_request_master(0);
    if (!master)
      throw std::runtime_error("Cannot request IgH master 0; check permissions "
                               "and exclusive ownership");
    ctx_.master = master;
    // Verify actual identities before configuring any startup SDOs.
    const std::uint32_t vendors[] = {kBeckhoffVendorId, Elm3604::kVendorId,
                                     Clearpath::kVendorId};
    const std::uint32_t products[] = {kEk1100ProductCode, Elm3604::kProductCode,
                                      Clearpath::kProductCode};
    for (std::uint16_t pos = 0; pos < 3; ++pos) {
      ec_slave_info_t slave{};
      if (ecrt_master_get_slave(master, pos, &slave) != 0 ||
          slave.vendor_id != vendors[pos] ||
          slave.product_code != products[pos]) {
        throw std::runtime_error("Missing or mismatched slave at 0:" +
                                 std::to_string(pos));
      }
    }
    ctx_.domain = ecrt_master_create_domain(master);
    if (!ctx_.domain) {
      throw std::runtime_error("Failed to create process-data domain.\n");
    }

    ctx_.ek1100_config =
        ecrt_master_slave_config(master, kEk1100Alias, kEk1100Position,
                                 kBeckhoffVendorId, kEk1100ProductCode);
    if (!ctx_.ek1100_config) {
      throw std::runtime_error(
          "Failed to configure EK1100 at alias 0, position 0");
    }

    ctx_.elm3604_config =
        ecrt_master_slave_config(master, Elm3604::kAlias, Elm3604::kPosition,
                                 Elm3604::kVendorId, Elm3604::kProductCode);
    if (!ctx_.elm3604_config) {
      throw std::runtime_error(
          "Failed to configure ELM3604-0002 at alias 0, position 1.\n");
    }

    ctx_.clearpath_config = ecrt_master_slave_config(
        master, Clearpath::kAlias, Clearpath::kPosition, Clearpath::kVendorId,
        Clearpath::kProductCode);
    if (!ctx_.clearpath_config) {
      throw std::runtime_error(
          "Failed to configure ClearPath EC at alias 0, position 2.\n");
    }
    if (!Elm3604::ConfigureStartupSdos(ctx_.elm3604_config)) {
      throw std::runtime_error("ELM3604 configuration failed");
    }
    if (!Elm3604::ConfigurePDOs(ctx_.elm3604_config)) {
      throw std::runtime_error("ELM3604 configuration failed");
    }
    if (!Elm3604::RegisterPDOEntries(ctx_.domain, &ctx_.elm_offsets)) {
      throw std::runtime_error("ELM3604 configuration failed");
    }

    constexpr std::uint32_t kElmSync0CycleNs = 1'000'000;
    constexpr std::uint16_t kElmDcAssignActivate = 0x0700;
    constexpr std::int32_t kElmSync0ShiftNs = 0;
    constexpr std::uint32_t kElmSync1DelayNs = 20'000;

    ecrt_slave_config_dc(ctx_.elm3604_config, kElmDcAssignActivate,
                         kElmSync0CycleNs, kElmSync0ShiftNs, kElmSync1DelayNs,
                         0);
    Clearpath::RemapPDOs(ctx_.clearpath_config);
    ctx_.clearpath_offsets =
        Clearpath::ConfigurePDOOffsets(ctx_.clearpath_config, ctx_.domain);

    ecrt_slave_config_dc(ctx_.clearpath_config, Clearpath::kDcAssignActivate,
                         kPeriodNs, Clearpath::kSync0ShiftNs, 0, 0);
    return !activate_now || activate(error);
  } catch (const std::exception &exception) {
    error = exception.what();
    release();
    return false;
  }
}
bool EthercatSystem::activate(std::string &error) {
  if (configured())
    return true;
  if (!ctx_.master || !ctx_.domain) {
    error = "Master/domain not configured";
    return false;
  }
  try {
    if (ecrt_master_activate(ctx_.master) != 0) {
      throw std::runtime_error("Failed to activate EtherCAT master.\n");
    }

    ctx_.domain_data = ecrt_domain_data(ctx_.domain);
    if (!ctx_.domain_data) {
      throw std::runtime_error("Failed to get process-data domain memory.\n");
    }

    Clearpath::Command disabled{};
    disabled.mode_op = CiA402::kModeCsp;
    Clearpath::WriteCommand(ctx_.domain_data, ctx_.clearpath_offsets, disabled);
    return true;
  } catch (const std::exception &exception) {
    error = exception.what();
    release();
    return false;
  }
}

void EthercatSystem::release() noexcept {
  if (ctx_.master)
    ecrt_release_master(ctx_.master);
  ctx_ = {};
  snapshot_ = {};
  sync_ref_counter_ = 0;
}
std::uint64_t EthercatSystem::read(std::uint64_t application_ns) noexcept {
  timing::Boundary probe(timing::core_read_entry, timing::core_read_exit);
  if (!configured())
    return 0;
  ZFC_FINE(application_time_ns,
           ecrt_master_application_time(ctx_.master, application_ns);)
  const auto actual_ns = MonotonicNs();
  ZFC_FINE(receive_api_ns, ecrt_master_receive(ctx_.master);)
  ZFC_FINE(domain_process_ns, ecrt_domain_process(ctx_.domain);)
  ZFC_FINE(elm_decode_ns, snapshot_.elm = Elm3604::ReadFeedback(
                              ctx_.domain_data, ctx_.elm_offsets);)
  ZFC_FINE(motor_decode_ns, snapshot_.motor = Clearpath::ReadTxPDOs(
                                ctx_.domain_data, ctx_.clearpath_offsets);)
  auto &state = snapshot_.bus;
  ZFC_FINE(state_poll_ns, ecrt_master_state(ctx_.master, &state.master);
           ecrt_domain_state(ctx_.domain, &state.domain);
           ecrt_slave_config_state(ctx_.ek1100_config, &state.ek1100);
           ecrt_slave_config_state(ctx_.elm3604_config, &state.elm3604);
           ecrt_slave_config_state(ctx_.clearpath_config, &state.clearpath);)
  state.have_master = state.have_domain = state.have_elm3604 =
      state.have_clearpath = true;
  state.last_motor_feedback = snapshot_.motor;
  state.drive_operation_enabled_csp =
      CiA402::IsOperationEnabledCSP(snapshot_.motor);
  ZFC_FINE(readiness_ns, snapshot_.ready = ReadyToRecord(state, snapshot_.elm);)
  ZFC_VALUE(timing::ready, snapshot_.ready);
  ZFC_VALUE(timing::wc, state.domain.working_counter);
  ZFC_VALUE(timing::wc_state, state.domain.wc_state);
  ZFC_VALUE(timing::statusword, snapshot_.motor.statusword);
  ZFC_VALUE(timing::mode, snapshot_.motor.mode_display);
  ZFC_VALUE(timing::actual_counts, snapshot_.motor.actual_position);
  return actual_ns;
}
void EthercatSystem::write(const Clearpath::Command &command) noexcept {
  timing::Boundary probe(timing::core_write_entry, timing::core_write_exit);
  ZFC_VALUE(timing::target_counts, command.target_position);
  if (!configured())
    return;
  ZFC_FINE(encode_ns, Clearpath::WriteCommand(ctx_.domain_data,
                                              ctx_.clearpath_offsets, command);)
  if (sync_ref_counter_ != 0)
    --sync_ref_counter_;
  else {
    sync_ref_counter_ = 1;
    ZFC_VALUE(timing::reference_sync, 1);
    ZFC_FINE(reference_sync_ns,
             ecrt_master_sync_reference_clock_to(ctx_.master, MonotonicNs());)
  }
  ZFC_FINE(slave_sync_ns, ecrt_master_sync_slave_clocks(ctx_.master);)
  ZFC_FINE(domain_queue_ns, ecrt_domain_queue(ctx_.domain);)
  ZFC_FINE(send_api_ns, ecrt_master_send(ctx_.master);)
}
bool EthercatSystem::startup(double timeout_seconds, std::string &error) {
  if (!configured()) {
    error = "Master is not configured";
    return false;
  }
  if (!std::isfinite(timeout_seconds) || timeout_seconds <= 0 ||
      timeout_seconds > 300) {
    error = "Startup timeout must be in (0,300] seconds";
    return false;
  }
  const auto start = MonotonicNs();
  const auto timeout = static_cast<std::uint64_t>(timeout_seconds * 1e9);
  timespec deadline{};
  clock_gettime(CLOCK_MONOTONIC, &deadline);
  Clearpath::Command command{};
  while (MonotonicNs() - start < timeout) {
    AddNs(&deadline, kPeriodNs);
    if (SleepUntil(deadline) != 0)
      break;
    read(TimespecToNs(deadline));
    CiA402::UpdateCSPEnableState(snapshot_.motor, &command);
    // Seed on EVERY startup cycle, including the first Operation Enabled cycle.
    command.target_position = snapshot_.motor.actual_position;
    write(command);
    if (snapshot_.ready)
      return true;
  }
  const auto &b = snapshot_.bus;
  std::ostringstream out;
  out << "Startup timeout: link=" << b.master.link_up
      << " slaves=" << b.master.slaves_responding
      << " WC=" << b.domain.working_counter << " WC_state=" << b.domain.wc_state
      << " OP(EK/ELM/drive)=" << b.ek1100.operational << '/'
      << b.elm3604.operational << '/' << b.clearpath.operational
      << " statusword=" << snapshot_.motor.statusword
      << " mode=" << int(snapshot_.motor.mode_display)
      << " ELM_valid=" << ElmChannelValid(snapshot_.elm.x)
      << ElmChannelValid(snapshot_.elm.y) << ElmChannelValid(snapshot_.elm.z);
  error = out.str();
  return false;
}
bool EthercatSystem::shutdown() noexcept {
  if (!configured())
    return true;
  StopSequence stop;
  stop.start(snapshot_.motor);
  timespec deadline{};
  clock_gettime(CLOCK_MONOTONIC, &deadline);
  while (!stop.done()) {
    AddNs(&deadline, kPeriodNs);
    if (SleepUntil(deadline) != 0)
      return false;
    read(TimespecToNs(deadline));
    auto command = stop.next();
    if (command.controlword == CiA402::kControlwordEnableOperation &&
        !CiA402::IsOperationEnabledCSP(snapshot_.motor))
      command.controlword = CiA402::kControlwordShutdown;
    write(command);
  }
  AddNs(&deadline, kPeriodNs);
  if (SleepUntil(deadline) != 0)
    return false;
  read(TimespecToNs(deadline));
  write(stop.next());
  return snapshot_.bus.master.link_up &&
         snapshot_.bus.domain.wc_state == EC_WC_COMPLETE &&
         CiA402::DecodeStatusword(snapshot_.motor.statusword) ==
             CiA402::State::SwitchOnDisabled;
}
} // namespace zfc
