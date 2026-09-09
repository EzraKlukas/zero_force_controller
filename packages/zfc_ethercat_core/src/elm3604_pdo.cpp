// Beckhoff ELM3604-0002 PDO mapping and process-data access.
//
// This module configures the X1-X3 status/sample PDOs and decodes their raw
// process-data representation into Elm3604::Feedback. The decoded sample
// values are still raw signed counts.

#include "elm3604_pdo.hpp"

#include <cstdio>

namespace {

constexpr std::uint8_t kNumberOfSamplesSubindex = 0x01;
constexpr std::uint8_t kErrorSubindex = 0x09;
constexpr std::uint8_t kUnderrangeSubindex = 0x0A;
constexpr std::uint8_t kOverrangeSubindex = 0x0B;
constexpr std::uint8_t kDiagSubindex = 0x0D;
constexpr std::uint8_t kTxPdoStateSubindex = 0x0E;
constexpr std::uint8_t kCycleCounterSubindex = 0x0F;



Elm3604::Channel ReadChannel(const std::uint8_t *domain_pd,
                             const Elm3604::ChannelPdoOffsets &offsets) {
  Elm3604::Channel channel{};
  channel.number_of_samples =
      EC_READ_U8(domain_pd + offsets.number_of_samples_offset);
  channel.error = EC_READ_BIT(domain_pd + offsets.error_offset,
                              offsets.error_bit);
  channel.underrange = EC_READ_BIT(domain_pd + offsets.underrange_offset,
                                   offsets.underrange_bit);
  channel.overrange = EC_READ_BIT(domain_pd + offsets.overrange_offset,
                                  offsets.overrange_bit);
  channel.diag = EC_READ_BIT(domain_pd + offsets.diag_offset,
                             offsets.diag_bit);
  channel.txpdo_state = EC_READ_BIT(domain_pd + offsets.txpdo_state_offset,
                                    offsets.txpdo_state_bit);
  // The input-cycle counter is a two-bit field inside a packed status byte.
  const std::uint8_t packed_counter =
      EC_READ_U8(domain_pd + offsets.cycle_counter_offset);
  channel.input_cycle_counter = static_cast<std::uint8_t>(
      (packed_counter >> offsets.cycle_counter_bit) & 0x03U);
  channel.raw_sample = EC_READ_S32(domain_pd + offsets.sample_offset);
  return channel;
}

} // namespace

bool Elm3604::ConfigurePDOs(ec_slave_config_t *sc) {
  // The ELM3604 PDO indexes are sparse by channel in the Beckhoff object
  // dictionary. Keep these entries aligned with the constants in the header.
  ec_pdo_entry_info_t elm3604_pdo_entries[] = {
      // 0x1A00: PAI TxPDO-Map Status Ch.1
      {0x6000, 0x01, 8},  // No of Samples
      {0x6000, 0x09, 1},  // Error
      {0x6000, 0x0A, 1},  // Underrange
      {0x6000, 0x0B, 1},  // Overrange
      {0x0000, 0x00, 1},  // Gap
      {0x6000, 0x0D, 1},  // Diag
      {0x6000, 0x0E, 1},  // TxPDO State
      {0x6000, 0x0F, 2},  // Input cycle counter
      {0x0000, 0x00, 16}, // Gap

      // 0x1A01: PAI TxPDO-Map Samples 1 Ch.1
      {0x6001, 0x01, 32}, // Channel-1 sample

      // 0x1A02: PAI TxPDO-Map Status Ch.2
      {0x6010, 0x01, 8},  // No of Samples
      {0x6010, 0x09, 1},  // Error
      {0x6010, 0x0A, 1},  // Underrange
      {0x6010, 0x0B, 1},  // Overrange
      {0x0000, 0x00, 1},  // Gap
      {0x6010, 0x0D, 1},  // Diag
      {0x6010, 0x0E, 1},  // TxPDO State
      {0x6010, 0x0F, 2},  // Input cycle counter
      {0x0000, 0x00, 16}, // Gap

      // 0x1A03: PAI TxPDO-Map Samples 1 Ch.2
      {0x6011, 0x01, 32}, // Channel-2 sample

      // 0x1A04: PAI TxPDO-Map Status Ch.3
      {0x6020, 0x01, 8},  // No of Samples
      {0x6020, 0x09, 1},  // Error
      {0x6020, 0x0A, 1},  // Underrange
      {0x6020, 0x0B, 1},  // Overrange
      {0x0000, 0x00, 1},  // Gap
      {0x6020, 0x0D, 1},  // Diag
      {0x6020, 0x0E, 1},  // TxPDO State
      {0x6020, 0x0F, 2},  // Input cycle counter
      {0x0000, 0x00, 16}, // Gap

      // 0x1A05: PAI TxPDO-Map Samples 1 Ch.3
      {0x6021, 0x01, 32}, // Channel-3 sample
  };

  ec_pdo_info_t elm3604_pdos[] = {
      {kChannel1StatusTxPdo, 9, elm3604_pdo_entries + 0},
      {kChannel1SampleTxPdo, 1, elm3604_pdo_entries + 9},
      {kChannel2StatusTxPdo, 9, elm3604_pdo_entries + 10},
      {kChannel2SampleTxPdo, 1, elm3604_pdo_entries + 19},
      {kChannel3StatusTxPdo, 9, elm3604_pdo_entries + 20},
      {kChannel3SampleTxPdo, 1, elm3604_pdo_entries + 29},
  };

  ec_sync_info_t elm3604_syncs[] = {
      {0, EC_DIR_OUTPUT, 0, nullptr, EC_WD_DISABLE},
      {1, EC_DIR_INPUT, 0, nullptr, EC_WD_DISABLE},
      {2, EC_DIR_OUTPUT, 0, nullptr, EC_WD_DISABLE},
      {3, EC_DIR_INPUT, 6, elm3604_pdos, EC_WD_DISABLE},
      {0xFF, EC_DIR_INVALID, 0, nullptr, EC_WD_DISABLE},
  };

  const int ret = ecrt_slave_config_pdos(sc, EC_END, elm3604_syncs);
  if (ret != 0) {
    std::fprintf(stderr, "Failed to configure ELM3604 PDO assignment: %d\n",
                 ret);
    return false;
  }
  return true;
}

bool Elm3604::RegisterPDOEntries(ec_domain_t *domain,
                                 Elm3604::PdoOffsets *offsets) {
  // Register each status bit and sample object separately so the cyclic loop
  // can decode channel health along with the raw sample value.
  const ec_pdo_entry_reg_t domain_regs[] = {
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1StatusObject,
       kNumberOfSamplesSubindex, &offsets->x.number_of_samples_offset,
       &offsets->x.number_of_samples_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1StatusObject,
       kErrorSubindex, &offsets->x.error_offset, &offsets->x.error_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1StatusObject,
       kUnderrangeSubindex, &offsets->x.underrange_offset,
       &offsets->x.underrange_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1StatusObject,
       kOverrangeSubindex, &offsets->x.overrange_offset,
       &offsets->x.overrange_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1StatusObject,
       kDiagSubindex, &offsets->x.diag_offset, &offsets->x.diag_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1StatusObject,
       kTxPdoStateSubindex, &offsets->x.txpdo_state_offset,
       &offsets->x.txpdo_state_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1StatusObject,
       kCycleCounterSubindex, &offsets->x.cycle_counter_offset,
       &offsets->x.cycle_counter_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1SampleObject,
       kSampleSubindex, &offsets->x.sample_offset, nullptr},

      {kAlias, kPosition, kVendorId, kProductCode, kChannel2StatusObject,
       kNumberOfSamplesSubindex, &offsets->y.number_of_samples_offset,
       &offsets->y.number_of_samples_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel2StatusObject,
       kErrorSubindex, &offsets->y.error_offset, &offsets->y.error_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel2StatusObject,
       kUnderrangeSubindex, &offsets->y.underrange_offset,
       &offsets->y.underrange_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel2StatusObject,
       kOverrangeSubindex, &offsets->y.overrange_offset,
       &offsets->y.overrange_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel2StatusObject,
       kDiagSubindex, &offsets->y.diag_offset, &offsets->y.diag_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel2StatusObject,
       kTxPdoStateSubindex, &offsets->y.txpdo_state_offset,
       &offsets->y.txpdo_state_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel2StatusObject,
       kCycleCounterSubindex, &offsets->y.cycle_counter_offset,
       &offsets->y.cycle_counter_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel2SampleObject,
       kSampleSubindex, &offsets->y.sample_offset, nullptr},

      {kAlias, kPosition, kVendorId, kProductCode, kChannel3StatusObject,
       kNumberOfSamplesSubindex, &offsets->z.number_of_samples_offset,
       &offsets->z.number_of_samples_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel3StatusObject,
       kErrorSubindex, &offsets->z.error_offset, &offsets->z.error_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel3StatusObject,
       kUnderrangeSubindex, &offsets->z.underrange_offset,
       &offsets->z.underrange_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel3StatusObject,
       kOverrangeSubindex, &offsets->z.overrange_offset,
       &offsets->z.overrange_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel3StatusObject,
       kDiagSubindex, &offsets->z.diag_offset, &offsets->z.diag_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel3StatusObject,
       kTxPdoStateSubindex, &offsets->z.txpdo_state_offset,
       &offsets->z.txpdo_state_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel3StatusObject,
       kCycleCounterSubindex, &offsets->z.cycle_counter_offset,
       &offsets->z.cycle_counter_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel3SampleObject,
       kSampleSubindex, &offsets->z.sample_offset, nullptr},
      {},
  };

  if (ecrt_domain_reg_pdo_entry_list(domain, domain_regs) != 0) {
    std::fprintf(stderr,
                 "PDO entry registration failed for ELM3604 X1-X3 entries.\n");
    return false;
  }

  if (offsets->x.number_of_samples_bit != 0 ||
      offsets->y.number_of_samples_bit != 0 ||
      offsets->z.number_of_samples_bit != 0) {
    std::fprintf(stderr,
                 "ELM3604 number-of-samples entry is not byte-aligned; "
                 "refusing 8-bit read.\n");
    return false;
  }

  return true;
}

Elm3604::Feedback Elm3604::ReadFeedback(
    const std::uint8_t *domain_pd, const Elm3604::PdoOffsets &offsets) {
  Elm3604::Feedback feedback{};
  feedback.x = ReadChannel(domain_pd, offsets.x);
  feedback.y = ReadChannel(domain_pd, offsets.y);
  feedback.z = ReadChannel(domain_pd, offsets.z);
  return feedback;
}

bool Elm3604::ConfigureStartupSdos(ec_slave_config_t* sc) {
  if (sc == nullptr) {
    std::fprintf(stderr, "ELM3604 configuration is null.\n");
    return false;
  }

  constexpr std::uint16_t kChannelSettings[] = {
      0x8000,  // X1
      0x8010,  // X2
      0x8020,  // X3
  };

  // These SDOs describe the analog input electrical mode only. They do not
  // calibrate the load cell or convert raw samples into force units.
  constexpr std::uint16_t kInterfaceZeroToTenVolts = 108;
  constexpr std::uint16_t kDcCoupling = 0;
  constexpr std::uint8_t kIepeCurrentOff = 0;
  constexpr std::uint16_t kNoFilter = 0;
  constexpr std::uint16_t kDecimationOne = 1;
  constexpr std::uint16_t kRawExtendedRange = 0;

  for (const std::uint16_t index : kChannelSettings) {
    if (ecrt_slave_config_sdo16(
            sc, index, 0x01, kInterfaceZeroToTenVolts) < 0 ||
        ecrt_slave_config_sdo16(
            sc, index, 0x03, kDcCoupling) < 0 ||
        ecrt_slave_config_sdo8(
            sc, index, 0x07, kIepeCurrentOff) < 0 ||
        ecrt_slave_config_sdo16(
            sc, index, 0x16, kNoFilter) < 0 ||
        ecrt_slave_config_sdo16(
            sc, index, 0x18, kDecimationOne) < 0 ||
        ecrt_slave_config_sdo16(
            sc, index, 0x19, kNoFilter) < 0 ||
        ecrt_slave_config_sdo16(
            sc, index, 0x2E, kRawExtendedRange) < 0) {
      std::fprintf(
          stderr,
          "Failed to queue ELM3604 startup SDOs for 0x%04X.\n",
          index);
      return false;
    }
  }

  return true;
}
