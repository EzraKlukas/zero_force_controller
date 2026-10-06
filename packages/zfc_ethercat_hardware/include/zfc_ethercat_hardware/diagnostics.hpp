#pragma once
#include "cycle_timing.hpp"
#include "ethercat_system.hpp"
#include <array>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <thread>
namespace zfc_ethercat_hardware {
enum class FaultReason {
  none,
  startup_timeout,
  master_link,
  slave_count_identity,
  incomplete_wc,
  slave_not_operational,
  drive_csp_loss,
  elm_invalid,
  cm_period,
  monotonic_gap,
  sequencing,
  invalid_command,
  excessive_increment,
  logical_limit,
  shutdown_failure
};
inline const char *FaultName(FaultReason r) noexcept {
  constexpr const char *names[] = {"none",
                                   "startup_timeout",
                                   "master_link",
                                   "slave_count_identity",
                                   "incomplete_wc",
                                   "slave_not_operational",
                                   "drive_csp_loss",
                                   "elm_invalid",
                                   "cm_period",
                                   "monotonic_gap",
                                   "sequencing",
                                   "invalid_command",
                                   "excessive_increment",
                                   "logical_limit",
                                   "shutdown_failure"};
  return names[static_cast<unsigned>(r)];
}
struct DiagnosticRecord {
  const char *event = "none", *phase = "unconfigured";
  FaultReason reason = FaultReason::none;
  std::uint64_t mono_ns = 0, reads = 0, writes = 0, interval_ns = 0,
                handoff_ns = 0;
  std::int64_t period_ns = 0;
  std::uint64_t command_changes = 0, excessive_periods = 0,
                maximum_interval_ns = 0, maximum_tracking_counts = 0;
  zfc::Snapshot snapshot{};
  double target = 0;
  bool claimed = false, read_pending = false;
  unsigned stop_cycle = 120;
  std::array<double, 25> raw_state{};
};
// Single serialized producer (Resource Manager), independent non-RT consumer.
// No EtherCAT access from this thread. Losses are counted, never block RT.
class DiagnosticSink {
public:
  void start() {
    if (thread_.joinable())
      return;
    thread_ = std::jthread([this](std::stop_token stop) {
      while (!stop.stop_requested()) {
        drain();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
      }
      drain();
    });
  }
  ~DiagnosticSink() {
    if (thread_.joinable()) {
      thread_.request_stop();
      thread_.join();
    }
  }
  std::uint64_t drops() const noexcept {
    return dropped_.load(std::memory_order_relaxed);
  }
  void push(const DiagnosticRecord &r) noexcept {
    zfc::timing::FineSpan probe(zfc::timing::diagnostic_push_ns);
    const auto w = write_.load(std::memory_order_relaxed);
    if (w - read_.load(std::memory_order_acquire) == records_.size()) {
      ++dropped_;
      return;
    }
    records_[w % records_.size()] = r;
    write_.store(w + 1, std::memory_order_release);
  }

private:
  void drain() {
    auto r = read_.load(std::memory_order_relaxed);
    while (r != write_.load(std::memory_order_acquire)) {
      print(records_[r % records_.size()]);
      read_.store(++r, std::memory_order_release);
    }
  }
  void print(const DiagnosticRecord &r) {
    const auto &s = r.snapshot;
    const auto &b = s.bus;
    const auto &m = s.motor;
    std::fprintf(
        stderr,
        "ZFC event=%s mono_ns=%llu phase=%s reason=%s reads=%llu writes=%llu "
        "period_ns=%lld interval_ns=%llu handoff_ns=%llu link=%u slaves=%u "
        "master_al=%u wc=%u wc_state=%u ek=%u/%u/%u elm=%u/%u/%u "
        "drive=%u/%u/%u sw=%u cia=%u mode=%d actual=%d target=%.0f "
        "limits=%u/%u ready=%u claimed=%u pending=%u stop_cycle=%u "
        "dropped=%llu",
        r.event, (unsigned long long)r.mono_ns, r.phase, FaultName(r.reason),
        (unsigned long long)r.reads, (unsigned long long)r.writes,
        (long long)r.period_ns, (unsigned long long)r.interval_ns,
        (unsigned long long)r.handoff_ns, b.master.link_up,
        b.master.slaves_responding, b.master.al_states,
        b.domain.working_counter, unsigned(b.domain.wc_state), b.ek1100.online,
        b.ek1100.operational, b.ek1100.al_state, b.elm3604.online,
        b.elm3604.operational, b.elm3604.al_state, b.clearpath.online,
        b.clearpath.operational, b.clearpath.al_state, m.statusword,
        unsigned(CiA402::DecodeStatusword(m.statusword)), int(m.mode_display),
        m.actual_position, r.target, m.negative_limit_reached(),
        m.positive_limit_reached(), s.ready, r.claimed, r.read_pending,
        r.stop_cycle, (unsigned long long)dropped_.load());
    const Elm3604::Channel channels[] = {s.elm.x, s.elm.y, s.elm.z};
    const char *names[] = {"x", "y", "z"};
    for (unsigned i = 0; i < 3; ++i) {
      const auto &c = channels[i];
      std::fprintf(stderr, " %s=%d/%u/%u/%u/%u/%u/%u/%u", names[i],
                   c.raw_sample, c.number_of_samples, c.input_cycle_counter,
                   c.error, c.txpdo_state, c.underrange, c.overrange, c.diag);
    }
    std::fprintf(stderr,
                 " changes=%llu excessive_periods=%llu max_interval_ns=%llu "
        "max_tracking_counts=%llu raw_velocity=%d raw_torque=%d "
        "backend_ready=%.0f communication_faults=%.0f invalid_commands=%.0f "
        "limit_rejections=%.0f\n",
                 (unsigned long long)r.command_changes,
                 (unsigned long long)r.excessive_periods,
                 (unsigned long long)r.maximum_interval_ns,
                 (unsigned long long)r.maximum_tracking_counts,
                 m.actual_velocity, m.actual_torque, r.raw_state[13],
                 r.raw_state[21], r.raw_state[22], r.raw_state[24]);
  }
  static_assert(std::atomic<std::uint64_t>::is_always_lock_free);
  std::array<DiagnosticRecord, 4096> records_{};
  std::atomic<std::uint64_t> read_{0}, write_{0}, dropped_{0};
  std::jthread thread_;
};
} // namespace zfc_ethercat_hardware
