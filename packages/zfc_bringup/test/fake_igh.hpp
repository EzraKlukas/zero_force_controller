#pragma once
#include <array>
#include <cstdint>
#include <ecrt.h>
#include <string>
// Test-only in-memory backend. No file/device/network access, even on
// configure.
namespace fake_igh {
inline std::array<std::uint8_t, 1024> data{};
inline std::array<unsigned, 65536> offsets{};
inline unsigned requests = 0, releases = 0, sends = 0, next_offset = 0;
inline bool link = true, complete = true, elm_valid = true, drive_fault = false,
            wrong_identity = false;
inline bool fail_domain = false, fail_activate = false, fail_sdo = false;
inline std::string order;
inline std::int32_t initial_position = 123;
void reset();
inline std::int32_t target() {
  return EC_READ_S32(data.data() + offsets[0x607A]);
}
inline std::uint16_t controlword() {
  return EC_READ_U16(data.data() + offsets[0x6040]);
}
} // namespace fake_igh
