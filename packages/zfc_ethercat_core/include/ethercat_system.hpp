#pragma once
#include "cia402.hpp"
#include "elm3604_pdo.hpp"
#include <cstdint>
#include <ctime>
#include <string>

namespace zfc {
inline constexpr std::uint64_t kPeriodNs = 1000000;
inline constexpr unsigned kExpectedSlaveCount = 3;
// A single conservative contract shared with the raw-count controller.
inline constexpr std::int32_t kMaximumIncrementCounts = 10;
std::uint64_t TimespecToNs(const timespec &time) noexcept;
std::uint64_t MonotonicNs() noexcept;
void AddNs(timespec *time, std::uint64_t ns) noexcept;
bool ElmChannelValid(const Elm3604::Channel &channel) noexcept;
struct EthercatState {
  ec_master_state_t master{};
  ec_domain_state_t domain{};
  ec_slave_config_state_t ek1100{};
  ec_slave_config_state_t elm3604{};
  ec_slave_config_state_t clearpath{};
  bool have_master = false;
  bool have_domain = false;
  bool have_elm3604 = false;
  bool have_clearpath = false;
  bool drive_operation_enabled_csp = false;
  Clearpath::PDO::TxPDOs last_motor_feedback{};
};

bool ReadyToRecord(const EthercatState &state,
                   const Elm3604::Feedback &elm) noexcept;
struct Snapshot {
  Elm3604::Feedback elm{};
  Clearpath::PDO::TxPDOs motor{};
  EthercatState bus{};
  bool ready = false;
};
// Cycle-driven stop sequencer: also used from active ROS write(), without
// sleeping.
class StopSequence {
public:
  void start(const Clearpath::PDO::TxPDOs &motor) noexcept;
  Clearpath::Command next() noexcept;
  bool done() const noexcept { return cycle_ >= 120; }
  unsigned cycle() const noexcept { return cycle_; }

private:
  unsigned cycle_ = 120;
  Clearpath::Command command_{};
};
class EthercatSystem {
public:
  EthercatSystem() = default;
  ~EthercatSystem() { release(); }
  EthercatSystem(const EthercatSystem &) = delete;
  EthercatSystem &operator=(const EthercatSystem &) = delete;
  bool configure(std::string &error, bool activate_now = true);
  bool activate(std::string &error);
  void release() noexcept;
  bool configured() const noexcept { return ctx_.domain_data != nullptr; }
  // application_ns is CLOCK_MONOTONIC, never ROS/system epoch time.
  std::uint64_t read(std::uint64_t application_ns) noexcept;
  void write(const Clearpath::Command &command) noexcept;
  const Snapshot &snapshot() const noexcept { return snapshot_; }
  // Lifecycle/reference runner only: these functions exchange and sleep at 1
  // kHz.
  bool startup(double timeout_seconds, std::string &error);
  bool shutdown() noexcept;

private:
  struct RuntimeContext {
    ec_master_t *master = nullptr;
    ec_domain_t *domain = nullptr;
    ec_slave_config_t *ek1100_config = nullptr;
    ec_slave_config_t *elm3604_config = nullptr;
    ec_slave_config_t *clearpath_config = nullptr;
    std::uint8_t *domain_data = nullptr;
    Elm3604::PdoOffsets elm_offsets{};
    Clearpath::PdoOffsets clearpath_offsets{};
  };

  RuntimeContext ctx_{};
  Snapshot snapshot_{};
  unsigned sync_ref_counter_ = 0;
};
} // namespace zfc
