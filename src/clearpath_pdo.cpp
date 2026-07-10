#include "clearpath_pdo.hpp"

#include <stdexcept>
#include <string>

namespace {

// RxPDO 1600 register mappings
constexpr std::uint16_t IDX_CONTROLWORD_U16 = 0x6040;
constexpr std::uint8_t SUB_CONTROLWORD = 0x00;
constexpr std::uint16_t IDX_MODEOP_I8 = 0x6060;
constexpr std::uint8_t SUB_MODEOP = 0x00;
constexpr std::uint16_t IDX_TARGETPOS_I32 = 0x607A;
constexpr std::uint8_t SUB_TARGETPOS = 0x00;
constexpr std::uint16_t IDX_TARGETVEL_I32 = 0x60FF;
constexpr std::uint8_t SUB_TARGETVEL = 0x00;
constexpr std::uint16_t IDX_TARGETTRQ_I16 = 0x6071;
constexpr std::uint8_t SUB_TARGETTRQ = 0x00;

// TxPDO 1A00 register mappings
constexpr std::uint16_t IDX_STATUSWORD_U16 = 0x6041;
constexpr std::uint8_t SUB_STATUSWORD = 0x00;
constexpr std::uint16_t IDX_MODEDISPLAY_I8 = 0x6061;
constexpr std::uint8_t SUB_MODEDISPLAY = 0x00;
constexpr std::uint16_t IDX_ACTUALPOS_I32 = 0x6064;
constexpr std::uint8_t SUB_ACTUALPOS = 0x00;
constexpr std::uint16_t IDX_ACTUALVEL_I32 = 0x606C;
constexpr std::uint8_t SUB_ACTUALVEL = 0x00;
constexpr std::uint16_t IDX_ACTUALTRQ_I16 = 0x6077;
constexpr std::uint8_t SUB_ACTUALTRQ = 0x00;

void CheckOffset(int offset, const char *what) {
  if (offset < 0) {
    throw std::runtime_error(std::string("PDO registration failed: ") + what);
  }
}

} // namespace

void Clearpath::RemapPDOs(ec_slave_config_t *sc) {
  if (!sc) {
    throw std::runtime_error("Clearpath::RemapPDOs: null slave config");
  }

  static ec_pdo_entry_info_t rx_entries[] = {
      {0x6040, 0x00, 16}, // Controlword
      {0x6060, 0x00, 8},  // Modes of operation
      {0x607A, 0x00, 32}, // Target position
      {0x60FF, 0x00, 32}, // Target velocity
      {0x6071, 0x00, 16}, // Target torque
  };

  static ec_pdo_entry_info_t tx_entries[] = {
      {0x6041, 0x00, 16}, // Statusword
      {0x6061, 0x00, 8},  // Modes of operation display
      {0x6064, 0x00, 32}, // Position actual value
      {0x606C, 0x00, 32}, // Velocity actual value
      {0x6077, 0x00, 16}, // Torque actual value
  };

  static ec_pdo_info_t pdos[] = {
      {0x1600, 5, rx_entries},
      {0x1A00, 5, tx_entries},
  };

  static ec_sync_info_t syncs[] = {
      {2, EC_DIR_OUTPUT, 1, &pdos[0], EC_WD_ENABLE},
      {3, EC_DIR_INPUT, 1, &pdos[1], EC_WD_DISABLE},
      {0xff, EC_DIR_INVALID, 0, nullptr, EC_WD_DISABLE},
  };

  const int ret = ecrt_slave_config_pdos(sc, EC_END, syncs);
  if (ret != 0) {
    throw std::runtime_error("ecrt_slave_config_pdos failed for ClearPath: " +
                             std::to_string(ret));
  }
}

Clearpath::PdoOffsets
Clearpath::ConfigurePDOOffsets(ec_slave_config_t *sc, ec_domain_t *domain) {
  Clearpath::PdoOffsets offsets{};

  offsets.rx.controlword = ecrt_slave_config_reg_pdo_entry(
      sc, IDX_CONTROLWORD_U16, SUB_CONTROLWORD, domain, nullptr);
  CheckOffset(offsets.rx.controlword, "rx.controlword");

  offsets.rx.mode_op = ecrt_slave_config_reg_pdo_entry(
      sc, IDX_MODEOP_I8, SUB_MODEOP, domain, nullptr);
  CheckOffset(offsets.rx.mode_op, "rx.mode_op");

  offsets.rx.target_position = ecrt_slave_config_reg_pdo_entry(
      sc, IDX_TARGETPOS_I32, SUB_TARGETPOS, domain, nullptr);
  CheckOffset(offsets.rx.target_position, "rx.target_position");

  offsets.rx.target_velocity = ecrt_slave_config_reg_pdo_entry(
      sc, IDX_TARGETVEL_I32, SUB_TARGETVEL, domain, nullptr);
  CheckOffset(offsets.rx.target_velocity, "rx.target_velocity");

  offsets.rx.target_torque = ecrt_slave_config_reg_pdo_entry(
      sc, IDX_TARGETTRQ_I16, SUB_TARGETTRQ, domain, nullptr);
  CheckOffset(offsets.rx.target_torque, "rx.target_torque");

  offsets.tx.statusword = ecrt_slave_config_reg_pdo_entry(
      sc, IDX_STATUSWORD_U16, SUB_STATUSWORD, domain, nullptr);
  CheckOffset(offsets.tx.statusword, "tx.statusword");

  offsets.tx.mode_display = ecrt_slave_config_reg_pdo_entry(
      sc, IDX_MODEDISPLAY_I8, SUB_MODEDISPLAY, domain, nullptr);
  CheckOffset(offsets.tx.mode_display, "tx.mode_display");

  offsets.tx.actual_position = ecrt_slave_config_reg_pdo_entry(
      sc, IDX_ACTUALPOS_I32, SUB_ACTUALPOS, domain, nullptr);
  CheckOffset(offsets.tx.actual_position, "tx.actual_position");

  offsets.tx.actual_velocity = ecrt_slave_config_reg_pdo_entry(
      sc, IDX_ACTUALVEL_I32, SUB_ACTUALVEL, domain, nullptr);
  CheckOffset(offsets.tx.actual_velocity, "tx.actual_velocity");

  offsets.tx.actual_torque = ecrt_slave_config_reg_pdo_entry(
      sc, IDX_ACTUALTRQ_I16, SUB_ACTUALTRQ, domain, nullptr);
  CheckOffset(offsets.tx.actual_torque, "tx.actual_torque");

  return offsets;
}

Clearpath::PDO::TxPDOs
Clearpath::ReadTxPDOs(const std::uint8_t *domain_pd,
                      const Clearpath::PdoOffsets &pdo_offsets) {
  Clearpath::PDO::TxPDOs tx{};
  tx.statusword = EC_READ_U16(domain_pd + pdo_offsets.tx.statusword);
  tx.mode_display = EC_READ_S8(domain_pd + pdo_offsets.tx.mode_display);
  tx.actual_position = EC_READ_S32(domain_pd + pdo_offsets.tx.actual_position);
  tx.actual_velocity = EC_READ_S32(domain_pd + pdo_offsets.tx.actual_velocity);
  tx.actual_torque = EC_READ_S16(domain_pd + pdo_offsets.tx.actual_torque);
  return tx;
}

void Clearpath::WriteCommand(std::uint8_t *domain_pd,
                             const Clearpath::PdoOffsets &pdo_offsets,
                             const Clearpath::Command &command) {
  EC_WRITE_U16(domain_pd + pdo_offsets.rx.controlword, command.controlword);
  EC_WRITE_S8(domain_pd + pdo_offsets.rx.mode_op, command.mode_op);
  EC_WRITE_S32(domain_pd + pdo_offsets.rx.target_position,
               command.target_position);
  EC_WRITE_S32(domain_pd + pdo_offsets.rx.target_velocity,
               command.target_velocity);
  EC_WRITE_S16(domain_pd + pdo_offsets.rx.target_torque,
               command.target_torque);
}
