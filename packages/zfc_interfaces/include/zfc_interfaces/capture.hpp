#pragma once
#include "zfc_interfaces/control_types.hpp"
#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>
namespace zfc {
struct CaptureRecord {
  std::uint64_t trial_id=0, sequence=0;
  Snapshot state{};
};
struct Completion {
  CaptureRecord final{};
  std::uint64_t dropped=0;
  bool completed=false;
};
// One serialized control/lifecycle producer; one non-RT consumer. No reset of
// ring indices across trials, and no allocation or waiting on the producer.
template<std::size_t Capacity> class Capture {
public:
  bool begin(std::uint64_t trial) noexcept {
    if (running_ || terminal_pending_.load(std::memory_order_acquire) || trial==0)
      return false;
    trial_=trial;
    sequence_=drops_=0;
    published_drops_.store(0,std::memory_order_release);
    last_={trial_,0,{}};
    running_=true;
    return true;
  }
  void append(const Snapshot &state) noexcept {
    if (!running_) return;
    last_={trial_, ++sequence_, state};
    const auto w=write_.load(std::memory_order_relaxed);
    if (w-read_.load(std::memory_order_acquire)==Capacity) {
      ++drops_;
      published_drops_.store(drops_,std::memory_order_release);
      return;
    }
    records_[w%Capacity]=last_;
    write_.store(w+1, std::memory_order_release);
  }
  void finish(bool completed) noexcept {
    if (!running_) return;
    terminal_={last_, drops_, completed};
    running_=false;
    terminal_pending_.store(true, std::memory_order_release);
  }
  bool pop(CaptureRecord &out) noexcept {
    const auto r=read_.load(std::memory_order_relaxed);
    if (r==write_.load(std::memory_order_acquire)) return false;
    out=records_[r%Capacity];
    read_.store(r+1, std::memory_order_release);
    return true;
  }
  bool completion(Completion &out) noexcept {
    if (!terminal_pending_.load(std::memory_order_acquire) ||
        read_.load(std::memory_order_relaxed)!=write_.load(std::memory_order_acquire))
      return false;
    out=terminal_;
    terminal_pending_.store(false, std::memory_order_release);
    return true;
  }
  std::uint64_t drops() const noexcept { return published_drops_.load(std::memory_order_acquire); }
private:
  static_assert(Capacity>0);
  static_assert(std::atomic<std::uint64_t>::is_always_lock_free);
  static_assert(std::atomic<bool>::is_always_lock_free);
  std::array<CaptureRecord, Capacity> records_{};
  std::atomic<std::uint64_t> read_{0}, write_{0};
  std::atomic<std::uint64_t> published_drops_{0};
  std::atomic<bool> terminal_pending_{false};
  std::uint64_t trial_=0, sequence_=0, drops_=0;
  bool running_=false;
  CaptureRecord last_{};
  Completion terminal_{};
};
} // namespace zfc
