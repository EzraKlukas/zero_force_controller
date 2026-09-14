#include "cycle_timing.hpp"
#include "matched_shuttle.hpp"
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <new>
#include <unistd.h>
static bool reject_allocation = false;
void *operator new(std::size_t n) {
  if (reject_allocation)
    std::abort();
  auto *p = std::malloc(n);
  if (!p)
    throw std::bad_alloc();
  return p;
}
void operator delete(void *p) noexcept { std::free(p); }
void operator delete(void *p, std::size_t) noexcept { std::free(p); }
#define CHECK(x)                                                               \
  do {                                                                         \
    if (!(x)) {                                                                \
      std::fprintf(stderr, "line %d: %s\n", __LINE__, #x);                     \
      std::abort();                                                            \
    }                                                                          \
  } while (false)
int main() {
  using namespace zfc::timing;
  Record storage[2];
  Buffer buffer(storage, 2);
  Record r;
  r[cycle] = 7;
  CHECK(buffer.append(r));
  r[cycle] = 8;
  CHECK(buffer.append(r));
  for (unsigned i = 0; i < 10000; ++i)
    CHECK(!buffer.append(r));
  CHECK(buffer.size() == 2 && buffer.drops() == 10000);
  CHECK(storage[0][cycle] == 7 && storage[1][cycle] == 8);
  Buffer empty(nullptr, 0);
  CHECK(!empty.append(r) && empty.drops() == 1);
  zfc::Shuttle s;
  CHECK(s.configure({}));
  for (int start : {123, -456}) {
    CHECK(s.activate(start));
    for (int i = 1; i <= 3000; ++i) {
      CHECK(s.update(1000000));
      CHECK(s.target() == start + (i <= 1000   ? i * 10
                                   : i <= 2000 ? (2000 - i) * 10
                                               : 0));
    }
  }
  zfc::Parameters p;
  p.hold_only = true;
  CHECK(s.configure(p));
  for (int start : {123, -456}) {
    CHECK(s.activate(start));
    for (int i = 0; i < 3000; ++i) {
      CHECK(s.update(1000000));
      CHECK(s.target() == start);
    }
    CHECK(!s.update(0));
    CHECK(!s.update(10000001));
    CHECK(!s.activate(std::numeric_limits<double>::quiet_NaN()));
  }
#if ZFC_PROFILE_LEVEL
  char path[128];
  std::snprintf(path, sizeof(path), "/tmp/zfc-timing-test-%d.bin", getpid());
  setenv("ZFC_TRACE_PATH", path, 1);
  setenv("ZFC_TRACE_CAPACITY", "1024", 1);
  initialize();
  managed_loop = true;
  reject_allocation = true;
  for (unsigned i = 0; i < 1024; ++i) {
    begin();
    mark(hardware_read_entry);
    mark(hardware_read_exit);
    { FineSpan probe(receive_api_ns); }
    { HardwareWrite probe; }
    finish();
  }
  reject_allocation = false;
  flush();
  std::remove(path);
#endif
  CHECK(raw_ns() > 0);
  std::printf("record_bytes=%zu fields=%zu level=%d\n", sizeof(Record),
              std::size_t(field_count), ZFC_PROFILE_LEVEL);
}
