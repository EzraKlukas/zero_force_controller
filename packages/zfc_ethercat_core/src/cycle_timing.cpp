#include "cycle_timing.hpp"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <sched.h>
#include <stdexcept>
#include <string>
namespace zfc::timing {
namespace {
std::int64_t now(clockid_t id) noexcept {
  timespec t{};
  clock_gettime(id, &t);
  return std::int64_t(t.tv_sec) * 1000000000 + t.tv_nsec;
}
} // namespace
std::int64_t raw_ns() noexcept { return now(CLOCK_MONOTONIC_RAW); }
std::int64_t mono_ns() noexcept { return now(CLOCK_MONOTONIC); }
std::int64_t system_ns() noexcept { return now(CLOCK_REALTIME); }
#if ZFC_PROFILE_LEVEL
thread_local Record current{};
thread_local bool in_cycle = false, managed_loop = false;
namespace {
struct Storage {
  std::string path;
  std::unique_ptr<Record[]> data;
  std::unique_ptr<Buffer> buffer;
  std::int64_t id = 0;
  ~Storage() { flush(); }
} storage;
thread_local Record *last_committed = nullptr;
thread_local std::int64_t sequence = 0, previous_read = 0;
std::int64_t env_integer(const char *name, std::int64_t fallback) {
  const char *v = std::getenv(name);
  if (!v)
    return fallback;
  std::size_t used;
  auto result = std::stoll(v, &used);
  if (v[used] != 0 || result < 0)
    throw std::runtime_error(name);
  return result;
}
} // namespace
void initialize() {
  if (storage.buffer)
    return;
  const char *path = std::getenv("ZFC_TRACE_PATH");
  if (!path || !*path)
    return;
  const auto capacity = env_integer("ZFC_TRACE_CAPACITY", 180000);
  if (capacity < 1 || capacity > 2000000)
    throw std::runtime_error("trace capacity 1..2000000");
  storage.path = path;
  storage.id = env_integer("ZFC_RUN_ID", 0);
  storage.data = std::make_unique<Record[]>(capacity);
  // Explicit volatile page touch; zero initialization alone can use lazy pages.
  auto *bytes = reinterpret_cast<volatile unsigned char *>(storage.data.get());
  for (std::size_t i = 0; i < capacity * sizeof(Record); i += 4096)
    bytes[i] = 0;
  storage.buffer = std::make_unique<Buffer>(storage.data.get(), capacity);
}
void begin() noexcept {
  in_cycle = bool(storage.buffer);
  if (!in_cycle)
    return;
  current = {};
  current[schema] = 2;
  current[run_id] = storage.id;
  current[level] = ZFC_PROFILE_LEVEL;
  current[cycle] = sequence++;
  current[cycle_entry] = raw_ns();
  current[cycle_mono_ns] = mono_ns();
  current[cpu] = sched_getcpu();
}
void finish() noexcept {
  if (!in_cycle)
    return;
  const auto read = current[hardware_read_entry];
  if (read) {
    current[actual_period_ns] = previous_read ? read - previous_read : 0;
    previous_read = read;
  }
  current[trace_drops] = storage.buffer->drops();
  current[commit_entry] = raw_ns();
  auto *out = storage.buffer->append(current);
  last_committed = out;
  const auto end = raw_ns();
  if (out)
    (*out)[commit_exit] = end;
  in_cycle = false;
}
void after_sleep() noexcept {
  if (last_committed)
    (*last_committed)[sleep_exit] = raw_ns();
}
void map_system_deadline(std::int64_t deadline) noexcept {
  if (!in_cycle)
    return;
  const auto before = mono_ns();
  const auto system = system_ns();
  const auto after = mono_ns();
  current[deadline_system_ns] = deadline;
  current[cycle_system_ns] = system;
  current[deadline_mono_ns] = before + (after - before) / 2 + deadline - system;
  current[clock_mapping_window_ns] = after - before;
}
void flush() {
  if (!storage.buffer || storage.path.empty())
    return;
  // This is deliberately a post-run operation. No RT-thread file access.
  FILE *f = std::fopen(storage.path.c_str(), "wbx");
  if (!f) {
    std::perror("trace open");
    return;
  }
  const std::int64_t header[] = {0x5a464354494d4531LL,
                                 2,
                                 sizeof(Record),
                                 std::int64_t(storage.buffer->size()),
                                 std::int64_t(storage.buffer->drops()),
                                 ZFC_PROFILE_LEVEL,
                                 field_count,
                                 0};
  const bool ok =
      std::fwrite(header, sizeof(header), 1, f) == 1 &&
      std::fwrite(storage.data.get(), sizeof(Record), storage.buffer->size(),
                  f) == storage.buffer->size();
  const auto closed = std::fclose(f);
  if (!ok || closed)
    std::perror("trace write");
  else
    storage.path.clear();
}
#endif
} // namespace zfc::timing
