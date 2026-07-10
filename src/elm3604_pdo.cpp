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

} // namespace

bool Elm3604::ConfigurePDOs(ec_slave_config_t *sc) {
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
  };

  ec_pdo_info_t elm3604_pdos[] = {
      {kChannel1StatusTxPdo, 9, elm3604_pdo_entries + 0},
      {kChannel1SampleTxPdo, 1, elm3604_pdo_entries + 9},
  };

  ec_sync_info_t elm3604_syncs[] = {
      {0, EC_DIR_OUTPUT, 0, nullptr, EC_WD_DISABLE},
      {1, EC_DIR_INPUT, 0, nullptr, EC_WD_DISABLE},
      {2, EC_DIR_OUTPUT, 0, nullptr, EC_WD_DISABLE},
      {3, EC_DIR_INPUT, 2, elm3604_pdos, EC_WD_DISABLE},
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
  const ec_pdo_entry_reg_t domain_regs[] = {
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1StatusObject,
       kNumberOfSamplesSubindex, &offsets->number_of_samples_offset,
       &offsets->number_of_samples_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1StatusObject,
       kErrorSubindex, &offsets->error_offset, &offsets->error_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1StatusObject,
       kUnderrangeSubindex, &offsets->underrange_offset,
       &offsets->underrange_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1StatusObject,
       kOverrangeSubindex, &offsets->overrange_offset,
       &offsets->overrange_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1StatusObject,
       kDiagSubindex, &offsets->diag_offset, &offsets->diag_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1StatusObject,
       kTxPdoStateSubindex, &offsets->txpdo_state_offset,
       &offsets->txpdo_state_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1StatusObject,
       kCycleCounterSubindex, &offsets->cycle_counter_offset,
       &offsets->cycle_counter_bit},
      {kAlias, kPosition, kVendorId, kProductCode, kChannel1SampleObject,
       kChannel1SampleSubindex, &offsets->sample_offset, nullptr},
      {},
  };

  if (ecrt_domain_reg_pdo_entry_list(domain, domain_regs) != 0) {
    std::fprintf(stderr,
                 "PDO entry registration failed for ELM3604 X1 entries.\n");
    return false;
  }

  if (offsets->number_of_samples_bit != 0) {
    std::fprintf(stderr,
                 "ELM3604 0x6000:01 begins at bit %u; refusing 8-bit read.\n",
                 offsets->number_of_samples_bit);
    return false;
  }

  return true;
}

Elm3604::Channel1 Elm3604::ReadChannel1(const std::uint8_t *domain_pd,
                                        const Elm3604::PdoOffsets &offsets) {
  Elm3604::Channel1 channel{};
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
  const std::uint8_t packed_counter =
      EC_READ_U8(domain_pd + offsets.cycle_counter_offset);
  channel.input_cycle_counter = static_cast<std::uint8_t>(
      (packed_counter >> offsets.cycle_counter_bit) & 0x03U);
  channel.raw_sample = EC_READ_S32(domain_pd + offsets.sample_offset);
  return channel;
}
