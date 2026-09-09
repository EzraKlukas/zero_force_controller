#include "fake_igh.hpp"
#include <cassert>
struct ec_master {};
struct ec_domain {};
struct ec_slave_config {
  unsigned position;
};
namespace {
ec_master master;
ec_domain domain;
ec_slave_config slaves[] = {{0}, {1}, {2}};
} // namespace
namespace fake_igh {
void reset() {
  data.fill(0);
  offsets.fill(0);
  requests = releases = sends = next_offset = 0;
  link = complete = elm_valid = true;
  drive_fault = wrong_identity = fail_domain = fail_activate = fail_sdo = false;
  initial_position = 123;
  order.clear();
}
} // namespace fake_igh
using namespace fake_igh;
extern "C" {
ec_master_t *ecrt_request_master(unsigned index) {
  assert(index == 0);
  ++requests;
  return &master;
}
void ecrt_release_master(ec_master_t *) { ++releases; }
ec_domain_t *ecrt_master_create_domain(ec_master_t *) {
  return fail_domain ? nullptr : &domain;
}
int ecrt_master_get_slave(ec_master_t *, std::uint16_t pos,
                          ec_slave_info_t *info) {
  *info = {};
  info->vendor_id = pos == 2 ? 0xc96 : 2;
  info->product_code = pos == 0 ? 0x044c2c52 : pos == 1 ? 0x50219349 : 1;
  if (wrong_identity)
    info->product_code = 0;
  return 0;
}
ec_slave_config_t *ecrt_master_slave_config(ec_master_t *, std::uint16_t alias,
                                            std::uint16_t pos, std::uint32_t,
                                            std::uint32_t) {
  assert(alias == 0 && pos < 3);
  return &slaves[pos];
}
int ecrt_slave_config_pdos(ec_slave_config_t *, unsigned,
                           const ec_sync_info_t *) {
  return 0;
}
int ecrt_slave_config_sdo8(ec_slave_config_t *, std::uint16_t, std::uint8_t,
                           std::uint8_t) {
  return fail_sdo ? -1 : 0;
}
int ecrt_slave_config_sdo16(ec_slave_config_t *, std::uint16_t, std::uint8_t,
                            std::uint16_t) {
  return fail_sdo ? -1 : 0;
}
void ecrt_slave_config_dc(ec_slave_config_t *sc, std::uint16_t assign,
                          std::uint32_t cycle, std::int32_t shift,
                          std::uint32_t sync1, std::int32_t) {
  assert(cycle == 1000000);
  assert(sc->position == 1
             ? (assign == 0x0700 && shift == 0 && sync1 == 20000)
             : (assign == 0x0300 && shift == 250000 && sync1 == 0));
}
int ecrt_domain_reg_pdo_entry_list(ec_domain_t *,
                                   const ec_pdo_entry_reg_t *entry) {
  for (; entry->index; ++entry) {
    *entry->offset = next_offset;
    if (entry->bit_position)
      *entry->bit_position = 0;
    if ((entry->index & 0xF) == 0 && entry->subindex == 1)
      data[next_offset] = 1;
    next_offset += 4;
  }
  return 0;
}
int ecrt_slave_config_reg_pdo_entry(ec_slave_config_t *, std::uint16_t index,
                                    std::uint8_t, ec_domain_t *, unsigned *) {
  offsets[index] = next_offset;
  next_offset += 4;
  return offsets[index];
}
int ecrt_master_activate(ec_master_t *) {
  EC_WRITE_S32(data.data() + offsets[0x6064], initial_position);
  EC_WRITE_U16(data.data() + offsets[0x6041], 0x40);
  return fail_activate ? -1 : 0;
}
std::uint8_t *ecrt_domain_data(ec_domain_t *) { return data.data(); }
void ecrt_master_application_time(ec_master_t *, std::uint64_t time) {
  assert(time > 0);
  order += 'A';
}
void ecrt_master_receive(ec_master_t *) {
  order += 'R';
  if (drive_fault)
    EC_WRITE_U16(data.data() + offsets[0x6041], 8);
  data[0] = elm_valid ? 1 : 0;
}
void ecrt_domain_process(ec_domain_t *) { order += 'P'; }
void ecrt_master_state(const ec_master_t *, ec_master_state_t *state) {
  *state = {};
  state->link_up = link;
  state->slaves_responding = 3;
  state->al_states = 8;
}
void ecrt_domain_state(const ec_domain_t *, ec_domain_state_t *state) {
  *state = {};
  state->working_counter = 6;
  state->wc_state = complete ? EC_WC_COMPLETE : EC_WC_INCOMPLETE;
}
void ecrt_slave_config_state(const ec_slave_config_t *,
                             ec_slave_config_state_t *state) {
  *state = {};
  state->online = state->operational = 1;
  state->al_state = 8;
}
void ecrt_master_sync_reference_clock_to(ec_master_t *, std::uint64_t) {
  order += 'F';
}
void ecrt_master_sync_slave_clocks(ec_master_t *) { order += 'S'; }
void ecrt_domain_queue(ec_domain_t *) { order += 'Q'; }
void ecrt_master_send(ec_master_t *) {
  order += 'T';
  ++sends;
  const auto cw = controlword();
  EC_WRITE_U16(data.data() + offsets[0x6041], cw == 0    ? 0x40
                                              : cw == 6  ? 0x21
                                              : cw == 7  ? 0x23
                                              : cw == 15 ? 0x27
                                                         : 0x40);
  EC_WRITE_S8(data.data() + offsets[0x6061], 8);
  if (cw == 15)
    EC_WRITE_S32(data.data() + offsets[0x6064], target());
}
}
