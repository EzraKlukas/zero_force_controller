#include "cycle_timing.hpp"
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
  FILE *file = std::fopen(path, "rb");
  CHECK(file);
  std::int64_t header[8]{};
  CHECK(std::fread(header, sizeof(header), 1, file) == 1);
  CHECK(header[0] == 0x5a464354494d4531LL && header[1] == 2);
  CHECK(header[2] == sizeof(Record) && header[3] == 1024);
  CHECK(header[4] == 0 && header[5] == ZFC_PROFILE_LEVEL);
  CHECK(header[6] == field_count && header[7] == 0);
  Record first;
  CHECK(std::fread(&first, sizeof(first), 1, file) == 1);
  CHECK(first[schema] == 2 && first[level] == ZFC_PROFILE_LEVEL);
  CHECK(std::fclose(file) == 0);
  std::remove(path);
#endif
  CHECK(raw_ns() > 0);
  std::printf("record_bytes=%zu fields=%zu level=%d\n", sizeof(Record),
              std::size_t(field_count), ZFC_PROFILE_LEVEL);
}
