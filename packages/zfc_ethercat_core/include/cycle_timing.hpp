#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#ifndef ZFC_PROFILE_LEVEL
#define ZFC_PROFILE_LEVEL 0
#endif
namespace zfc::timing {
enum Field : std::size_t {
#define ZFC_TIMING_FIELD(name) name,
#include "timing_fields.inc"
#undef ZFC_TIMING_FIELD
  field_count
};
struct Record {
  std::array<std::int64_t, field_count> v{};
  std::int64_t &operator[](Field f) noexcept { return v[f]; }
  std::int64_t operator[](Field f) const noexcept { return v[f]; }
};
static_assert(std::is_trivially_copyable_v<Record>);
static_assert(sizeof(Record) == field_count * sizeof(std::int64_t));
// One producer, retained until the producer has stopped. No cyclic consumer.
class Buffer {
public:
  Buffer(Record *storage, std::size_t capacity) noexcept
      : data_(storage), capacity_(capacity) {}
  Record *append(const Record &r) noexcept {
    if (size_ == capacity_) {
      ++drops_;
      return nullptr;
    }
    data_[size_] = r;
    return &data_[size_++];
  }
  std::size_t size() const noexcept { return size_; }
  std::uint64_t drops() const noexcept { return drops_; }

private:
  Record *data_;
  std::size_t capacity_, size_ = 0;
  std::uint64_t drops_ = 0;
};
std::int64_t raw_ns() noexcept;
std::int64_t mono_ns() noexcept;
std::int64_t system_ns() noexcept;
#if ZFC_PROFILE_LEVEL
extern thread_local Record current;
extern thread_local bool in_cycle;
extern thread_local bool managed_loop;
// Non-RT only. Environment: ZFC_TRACE_PATH, ZFC_TRACE_CAPACITY, ZFC_RUN_ID,
// ZFC_VARIANT. Preallocate and touch all records before locking memory.
void initialize();
void flush(); // Only after ALL producers stop. Also called at process exit.
void begin() noexcept;
void finish() noexcept;
void after_sleep() noexcept;
void map_system_deadline(std::int64_t deadline) noexcept;
inline void mark(Field f) noexcept {
  if (in_cycle)
    current[f] = raw_ns();
}
inline void value(Field f, std::int64_t v) noexcept {
  if (in_cycle)
    current[f] = v;
}
#else
inline void initialize() {}
inline void flush() {}
inline void begin() noexcept {}
inline void finish() noexcept {}
inline void after_sleep() noexcept {}
inline void map_system_deadline(std::int64_t) noexcept {}
inline void mark(Field) noexcept {}
inline void value(Field, std::int64_t) noexcept {}
#endif
struct HardwareRead {
  HardwareRead() noexcept {
#if ZFC_PROFILE_LEVEL
    if (!managed_loop)
      begin();
#endif
    mark(hardware_read_entry);
  }
  ~HardwareRead() { mark(hardware_read_exit); }
};
struct HardwareWrite {
  HardwareWrite() noexcept { mark(hardware_write_entry); }
  ~HardwareWrite() {
    mark(hardware_write_exit);
#if ZFC_PROFILE_LEVEL
    value(write_exit_mono_ns, mono_ns());
    if (!managed_loop)
      finish();
#endif
  }
};
struct Boundary {
  Field exit;
  Boundary(Field a, Field b) noexcept : exit(b) { mark(a); }
  ~Boundary() { mark(exit); }
};
struct FineSpan {
#if ZFC_PROFILE_LEVEL == 2
  Field field;
  std::int64_t start;
  explicit FineSpan(Field f) noexcept
      : field(f), start(in_cycle ? raw_ns() : 0) {}
  ~FineSpan() {
    if (start)
      current[field] += raw_ns() - start;
  }
#else
  explicit FineSpan(Field) noexcept {}
#endif
};
} // namespace zfc::timing
#if ZFC_PROFILE_LEVEL == 2
#define ZFC_FINE(field, ...)                                                   \
  {                                                                            \
    zfc::timing::FineSpan zfc_fine_span(zfc::timing::field);                   \
    __VA_ARGS__;                                                               \
  }
#else
#define ZFC_FINE(field, ...)                                                   \
  { __VA_ARGS__; }
#endif

#if ZFC_PROFILE_LEVEL
#define ZFC_VALUE(field, ...) zfc::timing::value(field, __VA_ARGS__)
#else
#define ZFC_VALUE(...) ((void)0)
#endif
