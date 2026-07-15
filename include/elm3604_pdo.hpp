#pragma once

#include <cstdint>

#include <ecrt.h>

class Elm3604 {
public:
  static constexpr std::uint16_t kAlias = 0;
  static constexpr std::uint16_t kPosition = 1;
  static constexpr std::uint32_t kVendorId = 0x00000002;
  static constexpr std::uint32_t kProductCode = 0x50219349;

  static constexpr std::uint16_t kChannel1StatusObject = 0x6000;
  static constexpr std::uint16_t kChannel1SampleObject = 0x6001;
  static constexpr std::uint16_t kChannel1StatusTxPdo = 0x1A00;
  static constexpr std::uint16_t kChannel1SampleTxPdo = 0x1A01;

  static constexpr std::uint16_t kChannel2StatusObject = 0x6010;
  static constexpr std::uint16_t kChannel2SampleObject = 0x6011;
  static constexpr std::uint16_t kChannel2StatusTxPdo = 0x1A21;
  static constexpr std::uint16_t kChannel2SampleTxPdo = 0x1A22;

  static constexpr std::uint16_t kChannel3StatusObject = 0x6020;
  static constexpr std::uint16_t kChannel3SampleObject = 0x6021;
  static constexpr std::uint16_t kChannel3StatusTxPdo = 0x1A42;
  static constexpr std::uint16_t kChannel3SampleTxPdo = 0x1A43;

  static constexpr std::uint8_t kSampleSubindex = 0x01;

  struct Channel {
    std::int32_t raw_sample = 0;
    std::uint8_t number_of_samples = 0;
    std::uint8_t input_cycle_counter = 0;
    bool error = false;
    bool underrange = false;
    bool overrange = false;
    bool diag = false;
    bool txpdo_state = false;
  };

  struct Feedback {
    Channel x;
    Channel y;
    Channel z;
  };

  struct ChannelPdoOffsets {
    unsigned int number_of_samples_offset = 0;
    unsigned int number_of_samples_bit = 0;

    unsigned int error_offset = 0;
    unsigned int error_bit = 0;

    unsigned int underrange_offset = 0;
    unsigned int underrange_bit = 0;

    unsigned int overrange_offset = 0;
    unsigned int overrange_bit = 0;

    unsigned int diag_offset = 0;
    unsigned int diag_bit = 0;

    unsigned int txpdo_state_offset = 0;
    unsigned int txpdo_state_bit = 0;

    unsigned int cycle_counter_offset = 0;
    unsigned int cycle_counter_bit = 0;

    unsigned int sample_offset = 0;
  };

  struct PdoOffsets {
    ChannelPdoOffsets x;
    ChannelPdoOffsets y;
    ChannelPdoOffsets z;
  };

  static bool ConfigurePDOs(ec_slave_config_t *sc);
  static bool RegisterPDOEntries(ec_domain_t *domain, PdoOffsets *offsets);
  static Feedback ReadFeedback(const std::uint8_t *domain_pd,
                               const PdoOffsets &offsets);
};
