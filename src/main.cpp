// zero_force_controller main application.
//
// Owns EtherCAT master/domain setup, realtime-ish cyclic scheduling, readiness
// checks, CSV capture, and bounded shutdown. The physical zero-force behavior
// lives in DriveLogic; this file keeps that logic isolated from IgH process
// data pointers and raw PDO offsets.

#include <algorithm>
#include <cerrno>
#include <cinttypes>
#include <cmath>
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <exception>
#include <limits>
#include <new>
#include <string>

#include <sched.h>
#include <sys/mman.h>
#include <unistd.h>

#include <ecrt.h>

#include "cia402.hpp"
#include "clearpath_pdo.hpp"
#include "drive_logic.hpp"
#include "elm3604_pdo.hpp"

namespace {

constexpr std::uint64_t kNsecPerSec = 1000000000ULL;
constexpr unsigned int kFrequencyHz = 1000;
constexpr double kDefaultDurationSeconds = 60.0;
constexpr double kDefaultStartupTimeoutSeconds = 20.0;
constexpr std::int32_t kDefaultPositionStepPerCycle = 0;
constexpr double kDefaultProportionality = 0;
constexpr double kDefaultDrag = 0;
constexpr unsigned int kExpectedSlaveCount = 3;
constexpr int kRealtimePriority = 50;
constexpr std::size_t kMaxSafeStack = 8U * 1024U;
constexpr std::uint64_t kMaxSamples = 10000000ULL;
constexpr std::uint16_t kEk1100Alias = 0;
constexpr std::uint16_t kEk1100Position = 0;
constexpr std::uint32_t kBeckhoffVendorId = 0x00000002;
constexpr std::uint32_t kEk1100ProductCode = 0x044c2c52;
constexpr unsigned int kShutdownHoldCycles = 20;
constexpr unsigned int kShutdownCycles = 50;
constexpr unsigned int kDisableVoltageCycles = 50;

// Written only by signal handlers and polled by the cyclic loop.
volatile std::sig_atomic_t g_stop_requested = 0;

// Latched after DriveLogic reports the first active limit response. From that
// point the loop commands ReturnHome() instead of normal balancing.
bool limitSwitchHit = false;

struct Options {
  double duration_seconds = kDefaultDurationSeconds;
  double startup_timeout_seconds = kDefaultStartupTimeoutSeconds;
  std::string output_path = "combined_capture.csv";
  std::int32_t position_step_per_cycle = kDefaultPositionStepPerCycle;
  double kp = kDefaultProportionality;
  double drag = kDefaultDrag;
  bool help = false;
};

// One row of post-run CSV data. The cyclic loop copies raw feedback and the
// command it just wrote into this preallocated buffer; file IO happens later.
struct SampleRecord {
  std::uint64_t sample_index;
  std::uint64_t scheduled_time_ns;
  std::uint64_t actual_time_ns;
  std::int64_t wakeup_latency_ns;

  Elm3604::Feedback elm;

  std::uint16_t motor_statusword;
  std::int8_t motor_mode_display;
  std::int32_t motor_actual_position;
  std::int32_t motor_actual_velocity;
  std::int16_t motor_actual_torque;
  std::uint32_t motor_digital_inputs;
  bool motor_negative_limit_reached;
  bool motor_positive_limit_reached;
  bool motor_raw_input_a_line_on;
  bool motor_raw_input_b_line_on;

  std::uint16_t motor_controlword;
  std::int8_t motor_mode_command;
  std::int32_t motor_target_position;
  std::int32_t motor_target_velocity;
  std::int16_t motor_target_torque;
};

// Last observed EtherCAT and drive state, used both as a readiness gate and as
// diagnostic output if startup or acquisition fails.
struct EthercatState {
  ec_master_state_t master{};
  ec_domain_state_t domain{};
  ec_slave_config_state_t elm3604{};
  ec_slave_config_state_t clearpath{};
  bool have_master = false;
  bool have_domain = false;
  bool have_elm3604 = false;
  bool have_clearpath = false;
  bool drive_operation_enabled_csp = false;
  Clearpath::PDO::TxPDOs last_motor_feedback{};
};

// End-of-run information that determines whether the program reports a normal
// completion, a startup failure, communication loss, or a signal interruption.
struct RunSummary {
  std::uint64_t samples = 0;
  std::uint64_t timing_overruns = 0;
  EthercatState final_state{};
  bool startup_timeout = false;
  bool communication_lost = false;
  bool interrupted = false;
  bool duration_complete = false;
};

// Small summary calculated while writing CSV, after realtime work is finished.
struct CsvSummary {
  bool have_samples = false;
  std::int32_t min_x_raw = 0;
  std::int32_t max_x_raw = 0;
  std::int32_t min_y_raw = 0;
  std::int32_t max_y_raw = 0;
  std::int32_t min_z_raw = 0;
  std::int32_t max_z_raw = 0;
};

// Pointers and PDO offsets needed by one process-data cycle.
struct RuntimeContext {
  ec_master_t *master = nullptr;
  ec_domain_t *domain = nullptr;
  ec_slave_config_t *elm3604_config = nullptr;
  ec_slave_config_t *clearpath_config = nullptr;
  std::uint8_t *domain_data = nullptr;
  Elm3604::PdoOffsets elm_offsets{};
  Clearpath::PdoOffsets clearpath_offsets{};
};

void SignalHandler(int) { g_stop_requested = 1; }

void PrintUsage(const char *program) {
  std::printf(
      "Usage: %s [options]\n"
      "\n"
      "Options:\n"
      "  --help                              Show this help and exit.\n"
      "  --duration <seconds>                Capture duration after readiness "
      "(default: %.1f).\n"
      "  --output <path>                     CSV output path (default: "
      "combined_capture.csv).\n"
      "  --startup-timeout <seconds>         Time allowed to reach ready state "
      "(default: %.1f).\n"
      "  --position-step-per-cycle <counts>  Optional CSP target-position step "
      "after enablement (default: %d).\n"
      "  --kp                                P tuning constant (default: "
      "%.2f).\n"
      "The loop frequency is fixed at %u Hz.\n",
      program, kDefaultDurationSeconds, kDefaultStartupTimeoutSeconds,
      kDefaultPositionStepPerCycle, kDefaultProportionality, kFrequencyHz);
}

bool ParseDouble(const char *text, const char *name, double min_value,
                 double max_value, double *out) {
  errno = 0;
  char *end = nullptr;
  const double value = std::strtod(text, &end);
  if (errno != 0 || end == text || *end != '\0' || !std::isfinite(value) ||
      value < min_value || value > max_value) {
    std::fprintf(stderr, "Invalid %s '%s'; expected [%.3f, %.3f].\n", name,
                 text, min_value, max_value);
    return false;
  }
  *out = value;
  return true;
}

bool ParseInt32(const char *text, const char *name, std::int32_t *out) {
  errno = 0;
  char *end = nullptr;
  const long value = std::strtol(text, &end, 10);
  if (errno != 0 || end == text || *end != '\0' ||
      value < std::numeric_limits<std::int32_t>::min() ||
      value > std::numeric_limits<std::int32_t>::max()) {
    std::fprintf(stderr, "Invalid %s '%s'; expected a signed 32-bit integer.\n",
                 name, text);
    return false;
  }
  *out = static_cast<std::int32_t>(value);
  return true;
}

bool ParseOptions(int argc, char **argv, Options *options) {
  for (int i = 1; i < argc; ++i) {
    const std::string arg(argv[i]);
    if (arg == "--help") {
      options->help = true;
      return true;
    }
    if (arg == "--duration") {
      if (++i >= argc) {
        std::fprintf(stderr, "--duration requires a value.\n");
        return false;
      }
      if (!ParseDouble(argv[i], "duration", 0.001, 3600.0,
                       &options->duration_seconds)) {
        return false;
      }
    } else if (arg == "--output") {
      if (++i >= argc) {
        std::fprintf(stderr, "--output requires a path.\n");
        return false;
      }
      options->output_path = argv[i];
      if (options->output_path.empty()) {
        std::fprintf(stderr, "--output path must not be empty.\n");
        return false;
      }
    } else if (arg == "--startup-timeout") {
      if (++i >= argc) {
        std::fprintf(stderr, "--startup-timeout requires a value.\n");
        return false;
      }
      if (!ParseDouble(argv[i], "startup timeout", 0.001, 300.0,
                       &options->startup_timeout_seconds)) {
        return false;
      }
    } else if (arg == "--position-step-per-cycle") {
      if (++i >= argc) {
        std::fprintf(stderr, "--position-step-per-cycle requires a value.\n");
        return false;
      }
      if (!ParseInt32(argv[i], "position step per cycle",
                      &options->position_step_per_cycle)) {
        return false;
      }
    } else if (arg == "--kp") {
      if (++i >= argc) {
        std::fprintf(stderr, "--kp requires a value.\n");
        return false;
      }
      if (!ParseDouble(argv[i],
                       "position steps per cycle per x_axis 1000 force steps",
                       0.01, 2.0, &options->kp)) {
        return false;
      }
    } else if (arg == "--drag") {
      if (++i >= argc) {
        std::fprintf(stderr, "--kp requires a value.\n");
        return false;
      }
      if (!ParseDouble(
              argv[i],
              "proportionality between velocity and negative acceleration.",
              0.0000001, 0.5, &options->drag)) {
        return false;
      }
    } else {
      std::fprintf(stderr, "Unknown option '%s'. Use --help.\n", arg.c_str());
      return false;
    }
  }
  return true;
}

std::uint64_t TimespecToNs(const timespec &time) {
  return static_cast<std::uint64_t>(time.tv_sec) * kNsecPerSec +
         static_cast<std::uint64_t>(time.tv_nsec);
}

void AddNs(timespec *time, std::uint64_t ns) {
  time->tv_sec += static_cast<time_t>(ns / kNsecPerSec);
  time->tv_nsec += static_cast<long>(ns % kNsecPerSec);
  while (time->tv_nsec >= static_cast<long>(kNsecPerSec)) {
    time->tv_nsec -= static_cast<long>(kNsecPerSec);
    ++time->tv_sec;
  }
}

int SleepUntil(const timespec &deadline) {
  for (;;) {
    const int ret =
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, nullptr);
    if (ret == 0) {
      return 0;
    }
    if (ret == EINTR && !g_stop_requested) {
      continue;
    }
    return ret;
  }
}

const char *WcStateName(ec_wc_state_t state) {
  switch (state) {
  case EC_WC_ZERO:
    return "zero";
  case EC_WC_INCOMPLETE:
    return "incomplete";
  case EC_WC_COMPLETE:
    return "complete";
  }
  return "unknown";
}

void PrefaultStack() {
  volatile unsigned char dummy[kMaxSafeStack];
  for (std::size_t i = 0; i < kMaxSafeStack; ++i) {
    dummy[i] = 0;
  }
  const volatile unsigned char keep = dummy[kMaxSafeStack - 1U];
  (void)keep;
}

void InstallSignalHandlers() {
  struct sigaction action{};
  action.sa_handler = SignalHandler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  sigaction(SIGINT, &action, nullptr);
  sigaction(SIGTERM, &action, nullptr);
}

void ConfigureRealtimeBestEffort() {
  if (mlockall(MCL_CURRENT | MCL_FUTURE) == -1) {
    std::fprintf(stderr,
                 "Warning: mlockall(MCL_CURRENT | MCL_FUTURE) failed: %s\n",
                 std::strerror(errno));
  }

  PrefaultStack();

  const int min_priority = sched_get_priority_min(SCHED_FIFO);
  const int max_priority = sched_get_priority_max(SCHED_FIFO);
  if (min_priority == -1 || max_priority == -1) {
    std::fprintf(stderr,
                 "Warning: could not query SCHED_FIFO priority range: %s\n",
                 std::strerror(errno));
    return;
  }

  struct sched_param param{};
  param.sched_priority =
      std::clamp(kRealtimePriority, min_priority, max_priority);
  std::printf("Requesting SCHED_FIFO priority %d.\n", param.sched_priority);
  if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
    std::fprintf(stderr, "Warning: sched_setscheduler(SCHED_FIFO) failed: %s\n",
                 std::strerror(errno));
  }
}

// Refreshes master/domain/slave states from IgH and caches the latest motor
// feedback for both readiness checks and failure reporting.
void PollStates(const RuntimeContext &ctx, const Clearpath::PDO::TxPDOs &motor,
                EthercatState *state) {
  ecrt_master_state(ctx.master, &state->master);
  ecrt_domain_state(ctx.domain, &state->domain);
  ecrt_slave_config_state(ctx.elm3604_config, &state->elm3604);
  ecrt_slave_config_state(ctx.clearpath_config, &state->clearpath);
  state->have_master = true;
  state->have_domain = true;
  state->have_elm3604 = true;
  state->have_clearpath = true;
  state->drive_operation_enabled_csp = CiA402::IsOperationEnabledCSP(motor);
  state->last_motor_feedback = motor;
}

bool ElmChannelValid(const Elm3604::Channel &channel) {
  return channel.number_of_samples > 0U && !channel.txpdo_state &&
         !channel.error;
}

// Recording starts only after communication, drive state, and ELM sample
// validity are all true. If any of these become false after recording starts,
// the run is treated as communication loss.
bool ReadyToRecord(const EthercatState &state, const Elm3604::Feedback &elm) {
  return state.have_master && state.have_domain && state.have_elm3604 &&
         state.have_clearpath && state.master.link_up &&
         state.master.slaves_responding == kExpectedSlaveCount &&
         state.domain.wc_state == EC_WC_COMPLETE && state.elm3604.online &&
         state.elm3604.operational && state.clearpath.online &&
         state.clearpath.operational && state.drive_operation_enabled_csp &&
         ElmChannelValid(elm.x) && ElmChannelValid(elm.y) &&
         ElmChannelValid(elm.z);
}

void PrintReadinessSummary(const EthercatState &state) {
  std::fprintf(stderr, "Startup readiness was not reached.\n");
  std::fprintf(stderr,
               "Expected exactly %u slaves: 0:0 EK1100, 0:1 ELM3604-0002, "
               "0:2 ClearPath EC.\n",
               kExpectedSlaveCount);
  if (state.have_master) {
    std::fprintf(stderr, "Master: link=%s, slaves=%u, AL states=0x%02X.\n",
                 state.master.link_up ? "up" : "down",
                 state.master.slaves_responding, state.master.al_states);
  } else {
    std::fprintf(stderr, "Master: no state received.\n");
  }
  if (state.have_domain) {
    std::fprintf(stderr, "Domain: WC=%u, state=%s.\n",
                 state.domain.working_counter,
                 WcStateName(state.domain.wc_state));
  } else {
    std::fprintf(stderr, "Domain: no state received.\n");
  }
  if (state.have_elm3604) {
    std::fprintf(stderr,
                 "ELM3604: online=%u, operational=%u, AL state=0x%02X.\n",
                 state.elm3604.online, state.elm3604.operational,
                 state.elm3604.al_state);
  } else {
    std::fprintf(stderr, "ELM3604: no state received.\n");
  }
  if (state.have_clearpath) {
    std::fprintf(
        stderr,
        "ClearPath: online=%u, operational=%u, AL state=0x%02X, "
        "statusword=0x%04X, mode_display=%d.\n",
        state.clearpath.online, state.clearpath.operational,
        state.clearpath.al_state,
        static_cast<unsigned int>(state.last_motor_feedback.statusword),
        static_cast<int>(state.last_motor_feedback.mode_display));
  } else {
    std::fprintf(stderr, "ClearPath: no state received.\n");
  }
}

void SyncDistributedClocks(ec_master_t *master,
                           unsigned int *sync_ref_counter) {
  if (*sync_ref_counter != 0U) {
    --(*sync_ref_counter);
  } else {
    *sync_ref_counter = 1U;
    timespec time{};
    clock_gettime(CLOCK_MONOTONIC, &time);
    ecrt_master_sync_reference_clock_to(master, TimespecToNs(time));
  }
  ecrt_master_sync_slave_clocks(master);
}

// Performs the receive/read half of a 1 kHz cycle and measures wakeup latency
// against the absolute CLOCK_MONOTONIC deadline used by clock_nanosleep().
void BeginCycle(const RuntimeContext &ctx, const timespec &deadline,
                Elm3604::Feedback *elm_feedback,
                Clearpath::PDO::TxPDOs *motor_feedback,
                std::uint64_t *actual_ns, std::int64_t *latency_ns) {
  const std::uint64_t scheduled_ns = TimespecToNs(deadline);
  ecrt_master_application_time(ctx.master, scheduled_ns);

  timespec actual_time{};
  clock_gettime(CLOCK_MONOTONIC, &actual_time);
  *actual_ns = TimespecToNs(actual_time);
  *latency_ns = static_cast<std::int64_t>(*actual_ns - scheduled_ns);

  ecrt_master_receive(ctx.master);
  ecrt_domain_process(ctx.domain);

  *elm_feedback = Elm3604::ReadFeedback(ctx.domain_data, ctx.elm_offsets);
  *motor_feedback =
      Clearpath::ReadTxPDOs(ctx.domain_data, ctx.clearpath_offsets);
}

// Performs the write/send half of a cycle after DriveLogic or the CiA-402
// enable state machine has selected the next command.
void EndCycle(const RuntimeContext &ctx, const Clearpath::Command &command,
              unsigned int *sync_ref_counter) {
  Clearpath::WriteCommand(ctx.domain_data, ctx.clearpath_offsets, command);
  SyncDistributedClocks(ctx.master, sync_ref_counter);
  ecrt_domain_queue(ctx.domain);
  ecrt_master_send(ctx.master);
}

// Bounded, best-effort stop sequence used on normal exit or interruption. This
// is not an emergency stop; it keeps exchanging process data briefly, holds the
// current target, requests shutdown, then disables voltage.
void SendBoundedShutdown(const RuntimeContext &ctx, Clearpath::Command command,
                         std::uint64_t period_ns,
                         unsigned int *sync_ref_counter) {
  command.target_velocity = 0;
  command.target_torque = 0;
  command.mode_op = CiA402::kModeCsp;

  timespec deadline{};
  clock_gettime(CLOCK_MONOTONIC, &deadline);
  AddNs(&deadline, period_ns);

  const unsigned int total_cycles =
      kShutdownHoldCycles + kShutdownCycles + kDisableVoltageCycles;
  for (unsigned int i = 0; i < total_cycles; ++i) {
    if (i < kShutdownHoldCycles) {
      command.controlword = CiA402::kControlwordEnableOperation;
    } else if (i < kShutdownHoldCycles + kShutdownCycles) {
      command.controlword = CiA402::kControlwordShutdown;
    } else {
      command.controlword = CiA402::kControlwordDisableVoltage;
    }

    const int sleep_ret = SleepUntil(deadline);
    if (sleep_ret != 0 && sleep_ret != EINTR) {
      break;
    }

    Elm3604::Feedback elm{};
    Clearpath::PDO::TxPDOs motor{};
    std::uint64_t actual_ns = 0;
    std::int64_t latency_ns = 0;
    BeginCycle(ctx, deadline, &elm, &motor, &actual_ns, &latency_ns);
    EndCycle(ctx, command, sync_ref_counter);
    AddNs(&deadline, period_ns);
  }
}

// Main 1 kHz EtherCAT loop. All memory used for capture is supplied by the
// caller; there is no file IO in this loop.
RunSummary RunCyclic(const RuntimeContext &ctx, const Options &options,
                     SampleRecord *records, std::uint64_t max_samples) {
  RunSummary summary{};
  EthercatState state{};
  DriveLogic drive_logic(options.kp, options.drag);
  Clearpath::Command command{};
  unsigned int sync_ref_counter = 0;
  bool recording = false;
  bool hold_seeded = false;

  const std::uint64_t period_ns = kNsecPerSec / kFrequencyHz;
  const std::uint64_t startup_timeout_ns = static_cast<std::uint64_t>(
      options.startup_timeout_seconds * static_cast<double>(kNsecPerSec));

  timespec now{};
  clock_gettime(CLOCK_MONOTONIC, &now);
  const std::uint64_t startup_start_ns = TimespecToNs(now);
  timespec deadline = now;
  AddNs(&deadline, period_ns);

  while (!g_stop_requested) {
    const int sleep_ret = SleepUntil(deadline);
    if (sleep_ret == EINTR && g_stop_requested) {
      break;
    }
    if (sleep_ret != 0 && sleep_ret != EINTR) {
      summary.communication_lost = true;
      break;
    }

    Elm3604::Feedback elm{};
    Clearpath::PDO::TxPDOs motor{};
    std::uint64_t actual_ns = 0;
    std::int64_t latency_ns = 0;

    BeginCycle(ctx, deadline, &elm, &motor, &actual_ns, &latency_ns);

    if (latency_ns >= static_cast<std::int64_t>(period_ns)) {
      ++summary.timing_overruns;
    }

    PollStates(ctx, motor, &state);

    if (!CiA402::IsOperationEnabledCSP(motor)) {
      hold_seeded = false;
      CiA402::UpdateCSPEnableState(motor, &command);
    } else {
      if (!hold_seeded) {
        drive_logic.ResetHoldPosition(motor.actual_position);
        command.target_position = motor.actual_position;
        command.target_velocity = 0;
        command.target_torque = 0;
        hold_seeded = true;
      }

      // DriveLogic uses raw ELM counts and ClearPath motor counts. No SI-unit
      // calibration or force conversion is applied at this checkpoint.
      const CycleInputs inputs{elm, motor, summary.samples,
                               TimespecToNs(deadline), latency_ns};
      if (drive_logic.FindSetPoint(inputs)) {
        if (!limitSwitchHit) {
          limitSwitchHit = drive_logic.LimitSwitchCheck(inputs);
        }
        if (!limitSwitchHit) {
          drive_logic.CalculateNextCommand(inputs, &command);
        } else {
          if (drive_logic.ReturnHome(inputs, &command)) { 
              g_stop_requested = true; 
          }
        }
      }
    }

    EndCycle(ctx, command, &sync_ref_counter);

    const bool ready = ReadyToRecord(state, elm);
    if (!recording) {
      if (ready) {
        recording = true;
      } else if (actual_ns - startup_start_ns >= startup_timeout_ns) {
        summary.startup_timeout = true;
        break;
      }
    } else if (!ready) {
      summary.communication_lost = true;
      break;
    }

    if (recording && summary.samples < max_samples) {
      records[summary.samples] = SampleRecord{
          summary.samples,
          TimespecToNs(deadline),
          actual_ns,
          latency_ns,
          elm,
          motor.statusword,
          motor.mode_display,
          motor.actual_position,
          motor.actual_velocity,
          motor.actual_torque,
          motor.digital_input,
          motor.negative_limit_reached(),
          motor.positive_limit_reached(),
          motor.raw_input_a_line_on(),
          motor.raw_input_b_line_on(),
          command.controlword,
          command.mode_op,
          command.target_position,
          command.target_velocity,
          command.target_torque,
      };
      ++summary.samples;
      if (summary.samples >= max_samples) {
        summary.duration_complete = true;
        break;
      }
    }

    AddNs(&deadline, period_ns);
  }

  if (g_stop_requested) {
    summary.interrupted = true;
  }

  summary.final_state = state;
  SendBoundedShutdown(ctx, command, period_ns, &sync_ref_counter);
  return summary;
}

void IncludeElmSample(const Elm3604::Feedback &elm, CsvSummary *summary) {
  if (!summary->have_samples) {
    summary->min_x_raw = elm.x.raw_sample;
    summary->max_x_raw = elm.x.raw_sample;
    summary->min_y_raw = elm.y.raw_sample;
    summary->max_y_raw = elm.y.raw_sample;
    summary->min_z_raw = elm.z.raw_sample;
    summary->max_z_raw = elm.z.raw_sample;
    summary->have_samples = true;
    return;
  }

  summary->min_x_raw = std::min(summary->min_x_raw, elm.x.raw_sample);
  summary->max_x_raw = std::max(summary->max_x_raw, elm.x.raw_sample);
  summary->min_y_raw = std::min(summary->min_y_raw, elm.y.raw_sample);
  summary->max_y_raw = std::max(summary->max_y_raw, elm.y.raw_sample);
  summary->min_z_raw = std::min(summary->min_z_raw, elm.z.raw_sample);
  summary->max_z_raw = std::max(summary->max_z_raw, elm.z.raw_sample);
}

int PrintElmChannelCsv(FILE *file, const Elm3604::Channel &channel) {
  return std::fprintf(file, "%" PRId32 ",%u,%u,%u,%u,%u,%u,%u",
                      channel.raw_sample,
                      static_cast<unsigned int>(channel.number_of_samples),
                      static_cast<unsigned int>(channel.input_cycle_counter),
                      channel.error ? 1U : 0U, channel.underrange ? 1U : 0U,
                      channel.overrange ? 1U : 0U, channel.diag ? 1U : 0U,
                      channel.txpdo_state ? 1U : 0U);
}

bool WriteCsv(const std::string &path, const SampleRecord *records,
              std::uint64_t sample_count, const Options &options,
              const RunSummary &run_summary, CsvSummary *csv_summary) {
  FILE *file = std::fopen(path.c_str(), "w");
  if (!file) {
    std::fprintf(stderr, "Failed to open '%s': %s\n", path.c_str(),
                 std::strerror(errno));
    return false;
  }

  bool ok = true;
  ok = ok && std::fprintf(file, "# zero_force_controller\n") >= 0;
  ok = ok && std::fprintf(file, "# topology: 0:0 EK1100, 0:1 ELM3604-0002, 0:2 "
                                "ClearPath EC\n") >= 0;
  ok = ok && std::fprintf(file, "# frequency_hz: %u\n", kFrequencyHz) >= 0;
  ok = ok && std::fprintf(file, "# requested_duration_s: %.9g\n",
                          options.duration_seconds) >= 0;
  ok = ok && std::fprintf(file, "# position_step_per_cycle: %" PRId32 "\n",
                          options.position_step_per_cycle) >= 0;
  ok = ok &&
       std::fprintf(file, "# elm_sample_entries: x=0x6001:01, y=0x6011:01, "
                          "z=0x6021:01\n") >= 0;
  ok = ok &&
       std::fprintf(file, "# elm_sample_type: signed 32-bit raw PDO\n") >= 0;
  ok = ok && std::fprintf(file, "# clearpath_mode: CSP\n") >= 0;
  ok = ok && std::fprintf(file, "# samples: %" PRIu64 "\n", sample_count) >= 0;
  ok = ok && std::fprintf(file, "# timing_overruns: %" PRIu64 "\n",
                          run_summary.timing_overruns) >= 0;
  ok = ok &&
       std::fprintf(file, "sample_index,scheduled_time_ns,actual_time_ns,"
                          "wakeup_latency_ns,"
                          "elm_x_raw_sample,elm_x_number_of_samples,"
                          "elm_x_input_cycle_counter,elm_x_error,"
                          "elm_x_underrange,elm_x_overrange,elm_x_diag,"
                          "elm_x_txpdo_state,"
                          "elm_y_raw_sample,elm_y_number_of_samples,"
                          "elm_y_input_cycle_counter,elm_y_error,"
                          "elm_y_underrange,elm_y_overrange,elm_y_diag,"
                          "elm_y_txpdo_state,"
                          "elm_z_raw_sample,elm_z_number_of_samples,"
                          "elm_z_input_cycle_counter,elm_z_error,"
                          "elm_z_underrange,elm_z_overrange,elm_z_diag,"
                          "elm_z_txpdo_state,"
                          "motor_statusword,motor_mode_display,"
                          "motor_actual_position,motor_actual_velocity,"
                          "motor_actual_torque,motor_digital_inputs,"
                          "motor_negative_limit_reached,"
                          "motor_positive_limit_reached,"
                          "motor_raw_input_a_line_on,motor_raw_input_b_line_on,"
                          "motor_controlword,"
                          "motor_mode_command,motor_target_position,"
                          "motor_target_velocity,motor_target_torque\n") >= 0;

  for (std::uint64_t i = 0; ok && i < sample_count; ++i) {
    const SampleRecord &r = records[i];
    IncludeElmSample(r.elm, csv_summary);

    ok = ok &&
         std::fprintf(file, "%" PRIu64 ",%" PRIu64 ",%" PRIu64 ",%" PRId64 ",",
                      r.sample_index, r.scheduled_time_ns, r.actual_time_ns,
                      r.wakeup_latency_ns) >= 0;
    ok = ok && PrintElmChannelCsv(file, r.elm.x) >= 0;
    ok = ok && std::fprintf(file, ",") >= 0;
    ok = ok && PrintElmChannelCsv(file, r.elm.y) >= 0;
    ok = ok && std::fprintf(file, ",") >= 0;
    ok = ok && PrintElmChannelCsv(file, r.elm.z) >= 0;
    ok = ok &&
         std::fprintf(
             file,
             ",%u,%d,%" PRId32 ",%" PRId32 ",%" PRId16 ",%" PRIu32
             ",%u,%u,%u,%u,%u,%d,%" PRId32 ",%" PRId32 ",%" PRId16 "\n",
             static_cast<unsigned int>(r.motor_statusword),
             static_cast<int>(r.motor_mode_display), r.motor_actual_position,
             r.motor_actual_velocity, r.motor_actual_torque,
             r.motor_digital_inputs, r.motor_negative_limit_reached ? 1U : 0U,
             r.motor_positive_limit_reached ? 1U : 0U,
             r.motor_raw_input_a_line_on ? 1U : 0U,
             r.motor_raw_input_b_line_on ? 1U : 0U,
             static_cast<unsigned int>(r.motor_controlword),
             static_cast<int>(r.motor_mode_command), r.motor_target_position,
             r.motor_target_velocity, r.motor_target_torque) >= 0;
  }

  if (std::ferror(file)) {
    ok = false;
  }
  if (std::fclose(file) != 0) {
    std::fprintf(stderr, "Failed to close '%s': %s\n", path.c_str(),
                 std::strerror(errno));
    ok = false;
  }
  if (!ok) {
    std::fprintf(stderr, "Failed while writing '%s'.\n", path.c_str());
  }
  return ok;
}

} // namespace

int main(int argc, char **argv) {
  Options options;
  if (!ParseOptions(argc, argv, &options)) {
    return 2;
  }

  if (options.help) {
    PrintUsage(argv[0]);
    return 0;
  }

  const double requested_samples =
      std::ceil(options.duration_seconds * static_cast<double>(kFrequencyHz));
  if (requested_samples <= 0.0 ||
      requested_samples > static_cast<double>(kMaxSamples)) {
    std::fprintf(stderr,
                 "Requested duration requires %.0f samples; limit is %" PRIu64
                 ".\n",
                 requested_samples, kMaxSamples);
    return 2;
  }
  const std::uint64_t max_samples =
      static_cast<std::uint64_t>(requested_samples);

  SampleRecord *records = new (std::nothrow) SampleRecord[max_samples];
  if (!records) {
    std::fprintf(stderr, "Failed to allocate buffer for %" PRIu64 " records.\n",
                 max_samples);
    return 1;
  }

  InstallSignalHandlers();
  ConfigureRealtimeBestEffort();

  std::printf("Requesting EtherCAT master 0.\n");
  ec_master_t *master = ecrt_request_master(0);
  if (!master) {
    std::fprintf(stderr, "Failed to request EtherCAT master 0.\n");
    delete[] records;
    return 1;
  }

  int exit_code = 0;
  RuntimeContext ctx{};
  ctx.master = master;
  RunSummary run_summary{};

  do {
    ctx.domain = ecrt_master_create_domain(master);
    if (!ctx.domain) {
      std::fprintf(stderr, "Failed to create process-data domain.\n");
      exit_code = 1;
      break;
    }

    ec_slave_config_t *ek1100_config =
        ecrt_master_slave_config(master, kEk1100Alias, kEk1100Position,
                                 kBeckhoffVendorId, kEk1100ProductCode);
    if (!ek1100_config) {
      std::fprintf(stderr,
                   "Failed to configure EK1100 at alias 0, position 0.\n");
      exit_code = 1;
      break;
    }

    ctx.elm3604_config =
        ecrt_master_slave_config(master, Elm3604::kAlias, Elm3604::kPosition,
                                 Elm3604::kVendorId, Elm3604::kProductCode);
    if (!ctx.elm3604_config) {
      std::fprintf(
          stderr, "Failed to configure ELM3604-0002 at alias 0, position 1.\n");
      exit_code = 1;
      break;
    }

    ctx.clearpath_config = ecrt_master_slave_config(
        master, Clearpath::kAlias, Clearpath::kPosition, Clearpath::kVendorId,
        Clearpath::kProductCode);
    if (!ctx.clearpath_config) {
      std::fprintf(
          stderr, "Failed to configure ClearPath EC at alias 0, position 2.\n");
      exit_code = 1;
      break;
    }

    std::printf("Configuring ELM3604 X1-X3 TxPDOs 0x%04X-0x%04X.\n",
                Elm3604::kChannel1StatusTxPdo, Elm3604::kChannel3SampleTxPdo);
    if (!Elm3604::ConfigureStartupSdos(ctx.elm3604_config)) {
      exit_code = 1;
      break;
    }
    if (!Elm3604::ConfigurePDOs(ctx.elm3604_config)) {
      exit_code = 1;
      break;
    }
    if (!Elm3604::RegisterPDOEntries(ctx.domain, &ctx.elm_offsets)) {
      exit_code = 1;
      break;
    }

    constexpr std::uint32_t kElmSync0CycleNs = 1'000'000;
    constexpr std::uint16_t kElmDcAssignActivate = 0x0700;
    constexpr std::int32_t kElmSync0ShiftNs = 0;
    constexpr std::uint32_t kElmSync1DelayNs = 20'000;

    ecrt_slave_config_dc(ctx.elm3604_config, kElmDcAssignActivate,
                         kElmSync0CycleNs, kElmSync0ShiftNs, kElmSync1DelayNs,
                         0);

    std::printf("Configuring ClearPath CSP PDOs and distributed clocks.\n");
    try {
      Clearpath::RemapPDOs(ctx.clearpath_config);
      ctx.clearpath_offsets =
          Clearpath::ConfigurePDOOffsets(ctx.clearpath_config, ctx.domain);
    } catch (const std::exception &error) {
      std::fprintf(stderr, "%s\n", error.what());
      exit_code = 1;
      break;
    }

    ecrt_slave_config_dc(ctx.clearpath_config, Clearpath::kDcAssignActivate,
                         kNsecPerSec / kFrequencyHz, Clearpath::kSync0ShiftNs,
                         0, 0);

    std::printf("Activating master.\n");
    if (ecrt_master_activate(master) != 0) {
      std::fprintf(stderr, "Failed to activate EtherCAT master.\n");
      exit_code = 1;
      break;
    }

    ctx.domain_data = ecrt_domain_data(ctx.domain);
    if (!ctx.domain_data) {
      std::fprintf(stderr, "Failed to get process-data domain memory.\n");
      exit_code = 1;
      break;
    }

    std::printf("Starting %u Hz loop; waiting for three-slave readiness.\n",
                kFrequencyHz);
    run_summary = RunCyclic(ctx, options, records, max_samples);

    if (run_summary.startup_timeout) {
      PrintReadinessSummary(run_summary.final_state);
      exit_code = 1;
    } else if (run_summary.communication_lost) {
      std::fprintf(stderr,
                   "Communication readiness was lost during acquisition.\n");
      PrintReadinessSummary(run_summary.final_state);
      exit_code = 1;
    }
  } while (false);

  ecrt_release_master(master);
  master = nullptr;

  const bool should_write_csv =
      !run_summary.startup_timeout &&
      (exit_code == 0 || run_summary.samples > 0 || run_summary.interrupted);
  if (should_write_csv) {
    CsvSummary csv_summary{};
    if (!WriteCsv(options.output_path, records, run_summary.samples, options,
                  run_summary, &csv_summary)) {
      exit_code = 1;
    } else {
      std::printf("Output: %s\n", options.output_path.c_str());
      std::printf("Samples: %" PRIu64 "\n", run_summary.samples);
      if (csv_summary.have_samples) {
        std::printf("ELM X raw sample min/max: %" PRId32 " / %" PRId32 "\n",
                    csv_summary.min_x_raw, csv_summary.max_x_raw);
        std::printf("ELM Y raw sample min/max: %" PRId32 " / %" PRId32 "\n",
                    csv_summary.min_y_raw, csv_summary.max_y_raw);
        std::printf("ELM Z raw sample min/max: %" PRId32 " / %" PRId32 "\n",
                    csv_summary.min_z_raw, csv_summary.max_z_raw);
      } else {
        std::printf("ELM raw sample min/max: no samples captured\n");
      }
      std::printf("Timing overruns: %" PRIu64 "\n",
                  run_summary.timing_overruns);
      if (run_summary.interrupted) {
        std::printf("Acquisition stopped by signal.\n");
      } else if (run_summary.duration_complete) {
        std::printf("Requested duration completed.\n");
      }
    }
  }

  delete[] records;
  return exit_code;
}
