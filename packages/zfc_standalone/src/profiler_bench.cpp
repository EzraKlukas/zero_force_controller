#include "cycle_timing.hpp"
#include "matched_shuttle.hpp"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <sched.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <vector>
__attribute__((noinline)) bool calculate(zfc::Shuttle &s) {
  return s.update(1000000);
}
int main() {
  using namespace zfc::timing;
  constexpr std::size_t n = 100000;
  std::vector<std::int64_t> clocks(n), commit(n), full(n), calc(n);
  std::vector<Record> records(n);
  Buffer buffer(records.data(), records.size());
  Record r;
  zfc::Shuttle controller;
  zfc::Parameters p;
  p.hold_only = true;
  if (!controller.configure(p) || !controller.activate(123))
    return 1;
  initialize();
  // Pre-resolve clocks/TLS and touch all data outside the measured window.
  for (std::size_t i = 0; i < n; ++i) {
    clocks[i] = commit[i] = full[i] = calc[i] = 0;
    records[i][cycle] = i;
  }
#if ZFC_PROFILE_LEVEL
  managed_loop = true;
#endif
  raw_ns();
  mono_ns();
  sched_getcpu();
  const int locked = mlockall(MCL_CURRENT | MCL_FUTURE);
  rusage before{}, after{};
  getrusage(RUSAGE_THREAD, &before);
  std::int64_t checksum = 0;
  for (std::size_t i = 0; i < n; ++i) {
    auto a = raw_ns();
    auto b = raw_ns();
    clocks[i] = b - a;
    a = raw_ns();
    auto *stored = buffer.append(r);
    b = raw_ns();
    commit[i] = b - a;
    checksum += stored != nullptr;
    a = raw_ns();
    checksum += calculate(controller);
    b = raw_ns();
    calc[i] = b - a;
    a = raw_ns();
    begin();
    mark(hardware_read_entry);
    mark(core_read_entry);
    mark(core_read_exit);
    mark(hardware_read_exit);
    mark(controller_entry);
    mark(calculation_entry);
    mark(calculation_exit);
    mark(controller_exit);
    mark(hardware_write_entry);
    mark(core_write_entry);
    mark(core_write_exit);
    mark(hardware_write_exit);
    finish();
    b = raw_ns();
    full[i] = b - a;
  }
  getrusage(RUSAGE_THREAD, &after);
  flush();
  std::printf(
      "{\"samples\":%zu,\"record_bytes\":%zu,\"buffer_bytes\":%zu,\"level\":%d,"
      "\"cpu\":%d,\"mlock_ok\":%s,\"minor_faults\":%ld,\"major_faults\":%ld,"
      "\"voluntary_switches\":%ld,\"involuntary_switches\":%ld,\"checksum\":%"
      "lld",
      n, sizeof(Record), n * sizeof(Record), ZFC_PROFILE_LEVEL, sched_getcpu(),
      locked == 0 ? "true" : "false", after.ru_minflt - before.ru_minflt,
      after.ru_majflt - before.ru_majflt, after.ru_nvcsw - before.ru_nvcsw,
      after.ru_nivcsw - before.ru_nivcsw, (long long)checksum);
  const auto report = [](const char *name, std::vector<std::int64_t> &v) {
    std::sort(v.begin(), v.end());
    double mean = 0;
    for (auto x : v)
      mean += double(x) / v.size();
    std::printf(",\"%s\":{\"mean_ns\":%.3f,\"median_ns\":%lld,\"p99_ns\":%lld,"
                "\"maximum_ns\":%lld}",
                name, mean, (long long)v[v.size() / 2],
                (long long)v[v.size() * 99 / 100], (long long)v.back());
  };
  report("clock_pair_delta", clocks);
  report("empty_record_copy", commit);
  report("coarse_probe_skeleton", full);
  report("hold_calculation_noinline", calc);
  std::puts("}");
}
