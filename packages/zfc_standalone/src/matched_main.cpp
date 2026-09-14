// Profiling-only matched HOLD runner. There is deliberately no motion option.
#include "cycle_timing.hpp"
#include "diagnostic_sink.hpp"
#include "matched_shuttle.hpp"
#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sched.h>
#include <sys/mman.h>
namespace {
volatile std::sig_atomic_t stopped = 0;
void stop_signal(int) { stopped = 1; }
int sleep_until(const timespec &deadline) {
  int rc;
  do {
    rc = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, nullptr);
  } while (rc == EINTR && !stopped);
  return rc;
}
} // namespace
int main(int argc, char **argv) {
  if (argc == 2 && std::strcmp(argv[1], "--help") == 0) {
    std::puts("matched_hold_runner [capture_seconds=60] [warmup_seconds=30]; "
              "HOLD ONLY; no motion option");
    return 0;
  }
  const auto parse = [](const char *v, long fallback) {
    if (!v)
      return fallback;
    char *end = nullptr;
    const long n = std::strtol(v, &end, 10);
    return end && *end == 0 && n >= 1 && n <= 1200 ? n : -1L;
  };
  const long seconds = parse(argc > 1 ? argv[1] : nullptr, 60);
  const long warmup = parse(argc > 2 ? argv[2] : nullptr, 30);
  if (seconds < 1 || warmup < 30 || argc > 3)
    return 2;
  zfc::timing::initialize();
  zfc::DiagnosticSink diagnostics;
  diagnostics.start(); // TS consumer created before requesting FIFO.
  zfc::Shuttle controller;
  zfc::Parameters params;
  params.hold_only = true;
  if (!controller.configure(params))
    return 2;
  std::signal(SIGINT, stop_signal);
  std::signal(SIGTERM, stop_signal);
  volatile unsigned char stack[8192];
  for (auto &v : stack)
    v = 0;
  sched_param scheduling{};
  scheduling.sched_priority = 50;
  if (mlockall(MCL_CURRENT | MCL_FUTURE) ||
      sched_setscheduler(0, SCHED_FIFO, &scheduling)) {
    std::perror("matched runner realtime setup");
    return 1;
  }
  zfc::EthercatSystem core;
  std::string error;
  if (!core.configure(error)) {
    std::fprintf(stderr, "%s\n", error.c_str());
    return 1;
  }
  timespec deadline{};
  clock_gettime(CLOCK_MONOTONIC, &deadline);
  const auto start = zfc::TimespecToNs(deadline);
  std::uint64_t last = 0, last_exchange = 0, ready_at = 0, cycles = 0;
  std::int32_t previous = 0;
  bool starting = true;
  zfc::FaultReason first_fault = zfc::FaultReason::none;
  const auto latch = [&](zfc::FaultReason f) {
    if (first_fault == zfc::FaultReason::none)
      first_fault = f;
  };
#if ZFC_PROFILE_LEVEL
  zfc::timing::managed_loop = true;
#endif
  while (!stopped) {
    zfc::AddNs(&deadline, zfc::kPeriodNs);
    if (sleep_until(deadline))
      break;
    zfc::timing::begin();
    const auto now = zfc::MonotonicNs();
    const auto interval = last ? now - last : zfc::kPeriodNs;
    last = now;
    ZFC_VALUE(zfc::timing::deadline_mono_ns, zfc::TimespecToNs(deadline));
    ZFC_VALUE(zfc::timing::phase, starting ? 1
                                  : now < ready_at + warmup * 1000000000ULL
                                      ? 2
                                      : 3);
    bool skip = last_exchange && now - last_exchange < 500000;
    {
      zfc::timing::HardwareRead read_probe;
      if (skip) {
        if (!starting)
          latch(zfc::FaultReason::cm_period);
      } else {
        last_exchange = now;
        // Preserve the standalone scheduled CLOCK_MONOTONIC application time.
        core.read(zfc::TimespecToNs(deadline));
        if (interval > 10000000)
          latch(zfc::FaultReason::monotonic_gap);
        if (starting && now - start > 20000000000ULL)
          latch(zfc::FaultReason::startup_timeout);
        const auto &s = core.snapshot();
        const auto &b = s.bus;
        if (!starting) {
          if (!b.master.link_up)
            latch(zfc::FaultReason::master_link);
          else if (b.master.slaves_responding != 3)
            latch(zfc::FaultReason::slave_count_identity);
          else if (b.domain.wc_state != EC_WC_COMPLETE)
            latch(zfc::FaultReason::incomplete_wc);
          else if (!b.ek1100.online || !b.ek1100.operational ||
                   !b.elm3604.online || !b.elm3604.operational ||
                   !b.clearpath.online || !b.clearpath.operational)
            latch(zfc::FaultReason::slave_not_operational);
          else if (!CiA402::IsOperationEnabledCSP(s.motor))
            latch(zfc::FaultReason::drive_csp_loss);
          else if (!zfc::ElmChannelValid(s.elm.x) ||
                   !zfc::ElmChannelValid(s.elm.y) ||
                   !zfc::ElmChannelValid(s.elm.z))
            latch(zfc::FaultReason::elm_invalid);
        }
      }
    }
    Clearpath::Command command{};
    command.mode_op = CiA402::kModeCsp;
    command.target_position = previous;
    if (!starting && first_fault == zfc::FaultReason::none) {
      zfc::timing::Boundary wrapper(zfc::timing::controller_entry,
                                    zfc::timing::controller_exit);
      ZFC_VALUE(zfc::timing::controller_active, 1);
      bool ok;
      {
        zfc::timing::Boundary calc(zfc::timing::calculation_entry,
                                   zfc::timing::calculation_exit);
        ok = controller.update(interval);
      }
      if (!ok)
        latch(zfc::FaultReason::cm_period);
      command.target_position = controller.target();
    }
    {
      zfc::timing::HardwareWrite write_probe;
      if (!skip) {
        if (starting && first_fault == zfc::FaultReason::none) {
          CiA402::UpdateCSPEnableState(core.snapshot().motor, &command);
          command.target_position = previous =
              core.snapshot().motor.actual_position;
          if (core.snapshot().ready) {
            starting = false;
            ready_at = now;
            if (!controller.activate(previous))
              latch(zfc::FaultReason::invalid_command);
          }
        } else {
          std::int32_t counts;
          const auto v = zfc::ValidateCommand(
              command.target_position, previous, core.snapshot().motor,
              zfc::kMaximumIncrementCounts, counts);
          if (v != zfc::CommandResult::valid)
            latch(v == zfc::CommandResult::limit
                      ? zfc::FaultReason::logical_limit
                  : v == zfc::CommandResult::excessive_increment
                      ? zfc::FaultReason::excessive_increment
                      : zfc::FaultReason::invalid_command);
          command.controlword = CiA402::kControlwordEnableOperation;
        }
        // On first fault stop sending trajectory commands; bounded shutdown
        // below.
        if (first_fault == zfc::FaultReason::none)
          core.write(command);
      }
      ZFC_VALUE(zfc::timing::fault, static_cast<int>(first_fault));
      ZFC_VALUE(zfc::timing::diagnostic_drops, diagnostics.drops());
      if (++cycles % 1000 == 0 || first_fault != zfc::FaultReason::none) {
        zfc::DiagnosticRecord r;
        {
          zfc::timing::FineSpan construction(
              zfc::timing::diagnostic_construct_ns);
          r.event =
              first_fault == zfc::FaultReason::none ? "status" : "first-fault";
          r.phase = starting ? "startup" : "matched-hold";
          r.reason = first_fault;
          r.mono_ns = now;
          r.reads = r.writes = cycles;
          r.interval_ns = interval;
          r.snapshot = core.snapshot();
          r.target = command.target_position;
        }
        diagnostics.push(r);
      }
    }
    zfc::timing::finish();
    if (first_fault != zfc::FaultReason::none ||
        (ready_at && now - ready_at >= (seconds + warmup) * 1000000000ULL))
      break;
  }
  const bool shutdown_ok = core.shutdown();
  core.release();
  sched_param normal{};
  sched_setscheduler(0, SCHED_OTHER, &normal);
  zfc::timing::flush();
  std::fprintf(stderr,
               "matched-hold finished cycles=%llu ready=%d fault=%s "
               "shutdown_confirmed=%d diagnostic_drops=%llu\n",
               (unsigned long long)cycles, !starting,
               zfc::FaultName(first_fault), shutdown_ok,
               (unsigned long long)diagnostics.drops());
  return shutdown_ok && first_fault == zfc::FaultReason::none && !starting ? 0
                                                                           : 1;
}
