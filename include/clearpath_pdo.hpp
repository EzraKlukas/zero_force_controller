#pragma once

#include <cstdint>

#include <ecrt.h>

class Clearpath {
public:
  static constexpr std::uint16_t kAlias = 0;
  static constexpr std::uint16_t kPosition = 2;
  static constexpr std::uint32_t kVendorId = 0x00000c96;
  static constexpr std::uint32_t kProductCode = 0x00000001;

  static constexpr std::uint16_t kDcAssignActivate = 0x0300;
  static constexpr std::uint32_t kSync0ShiftNs = 250000;

  struct PDO {
    struct RxPDOs {
      std::uint16_t controlword = 0;
      std::int8_t mode_op = 0;
      std::int32_t target_position = 0;
      std::int32_t target_velocity = 0;
      std::int16_t target_torque = 0;
      std::uint32_t digital_output = 0;
    } rx;

    struct TxPDOs {
      static constexpr std::uint32_t kNegativeLimitReachedMask =
          1U << 0U;
      static constexpr std::uint32_t kPositiveLimitReachedMask =
          1U << 1U;
      static constexpr std::uint32_t kRawInputALineOnMask =
          1U << 16U;
      static constexpr std::uint32_t kRawInputBLineOnMask =
          1U << 17U;

      std::uint16_t statusword = 0;
      std::int8_t mode_display = 0;
      std::int32_t actual_position = 0;
      std::int32_t actual_velocity = 0;
      std::int16_t actual_torque = 0;
      std::uint32_t digital_input = 0;
      std::int32_t following_error = 0;
      std::uint16_t error_code = 0;

      [[nodiscard]] constexpr bool negative_limit_reached() const noexcept {
        return (digital_input & kNegativeLimitReachedMask) != 0U;
      }

      [[nodiscard]] constexpr bool positive_limit_reached() const noexcept {
        return (digital_input & kPositiveLimitReachedMask) != 0U;
      }

      [[nodiscard]] constexpr bool raw_input_a_line_on() const noexcept {
        return (digital_input & kRawInputALineOnMask) != 0U;
      }

      [[nodiscard]] constexpr bool raw_input_b_line_on() const noexcept {
        return (digital_input & kRawInputBLineOnMask) != 0U;
      }
    } tx;
  };

  struct Command {
    std::uint16_t controlword = 0;
    std::int8_t mode_op = 0;
    std::int32_t target_position = 0;
    std::int32_t target_velocity = 0;
    std::int16_t target_torque = 0;
  };

  struct PdoOffsets {
    struct RxPDOs {
      int controlword = -1;
      int mode_op = -1;
      int target_position = -1;
      int target_velocity = -1;
      int target_torque = -1;
      int digital_output = -1;
    } rx;

    struct TxPDOs {
      int statusword = -1;
      int mode_display = -1;
      int actual_position = -1;
      int actual_velocity = -1;
      int actual_torque = -1;
      int digital_input = -1;
      int following_error = -1;
      int error_code = -1;
    } tx;
  };

  static void RemapPDOs(ec_slave_config_t *sc);
  static PdoOffsets ConfigurePDOOffsets(ec_slave_config_t *sc,
                                        ec_domain_t *domain);
  static PDO::TxPDOs ReadTxPDOs(const std::uint8_t *domain_pd,
                                const PdoOffsets &pdo_offsets);
  static void WriteCommand(std::uint8_t *domain_pd,
                           const PdoOffsets &pdo_offsets,
                           const Command &command);
};
