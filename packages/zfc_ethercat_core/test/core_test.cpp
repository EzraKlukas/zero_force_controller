#include "count_command.hpp"
#include <array>
#include <cstdlib>
#include <iostream>
#define CHECK(x)                                                               \
  do {                                                                         \
    if (!(x)) {                                                                \
      std::cerr << __LINE__ << ": " #x "\n";                                   \
      std::exit(1);                                                            \
    }                                                                          \
  } while (false)
int main() {
  using namespace zfc;
  Clearpath::PDO::TxPDOs motor{};
  Clearpath::Command command{};
  const std::array<std::uint16_t, 4> states{0x40, 0x21, 0x23, 0x27};
  const std::array<std::uint16_t, 4> controls{6, 7, 15, 15};
  for (unsigned i = 0; i < 4; ++i) {
    motor.statusword = states[i];
    motor.actual_position = 123;
    motor.mode_display = 8;
    CHECK(CiA402::UpdateCSPEnableState(motor, &command) == (i == 3));
    CHECK(command.controlword == controls[i]);
    CHECK(command.target_position == 123);
  }
  std::int32_t out{};
  CHECK(!ToCounts(NAN, out));
  CHECK(!ToCounts(INFINITY, out));
  CHECK(!ToCounts(0.5, out));
  CHECK(!ToCounts(2147483648.0, out));
  CHECK(ToCounts(-2147483648.0, out));
  CHECK(ValidateCommand(10, 0, motor, 10, out) == CommandResult::valid);
  CHECK(ValidateCommand(11, 0, motor, 10, out) ==
        CommandResult::excessive_increment);
  motor.actual_position = 0;
  motor.digital_input = 2;
  CHECK(ValidateCommand(10, 0, motor, 10, out) == CommandResult::limit);
  CHECK(ValidateCommand(-10, 0, motor, 10, out) == CommandResult::valid);
  CHECK(ValidateCommand(5, 10, motor, 10, out) == CommandResult::limit);
  motor.digital_input = 1;
  CHECK(ValidateCommand(-10, 0, motor, 10, out) == CommandResult::limit);
  StopSequence stop;
  stop.start(motor);
  for (int i = 0; i < 120; ++i) {
    CHECK(!stop.done());
    const auto c = stop.next();
    CHECK(c.target_position == 0);
    CHECK(c.target_velocity == 0);
    CHECK(c.target_torque == 0);
    CHECK(c.controlword == (i < 20 ? 15 : i < 70 ? 6 : 0));
  }
  CHECK(stop.done());
  CHECK(stop.next().controlword == 0);
  motor.statusword = 0x40;
  stop.start(motor);
  CHECK(stop.next().controlword == 6);
  Elm3604::Feedback elm{};
  elm.x.number_of_samples = elm.y.number_of_samples = elm.z.number_of_samples =
      1;
  EthercatState bus{};
  bus.have_master = bus.have_domain = bus.have_elm3604 = bus.have_clearpath =
      true;
  bus.master.link_up = 1;
  bus.master.slaves_responding = 3;
  bus.domain.wc_state = EC_WC_COMPLETE;
  bus.ek1100.online = bus.ek1100.operational = bus.elm3604.online =
      bus.elm3604.operational = bus.clearpath.online =
          bus.clearpath.operational = 1;
  bus.drive_operation_enabled_csp = true;
  CHECK(ReadyToRecord(bus, elm));
  elm.z.error = true;
  CHECK(!ReadyToRecord(bus, elm));
  elm.z.error = false;
  bus.ek1100.operational = 0;
  CHECK(!ReadyToRecord(bus, elm));
  // Signed raw data and packed status decoding, using actual slave accessors.
  std::array<std::uint8_t, 64> bytes{};
  Elm3604::PdoOffsets elm_offsets{};
  auto &x = elm_offsets.x;
  x.sample_offset = 0;
  x.number_of_samples_offset = 4;
  x.error_offset = x.underrange_offset = x.overrange_offset = x.diag_offset =
      x.txpdo_state_offset = x.cycle_counter_offset = 5;
  x.error_bit = 0;
  x.underrange_bit = 1;
  x.overrange_bit = 2;
  x.diag_bit = 4;
  x.txpdo_state_bit = 5;
  x.cycle_counter_bit = 6;
  elm_offsets.y = elm_offsets.z = x;
  elm_offsets.y.sample_offset = 8;
  elm_offsets.z.sample_offset = 12;
  EC_WRITE_S32(bytes.data(), -123);
  EC_WRITE_U8(bytes.data() + 4, 1);
  EC_WRITE_U8(bytes.data() + 5, 0x80);
  EC_WRITE_S32(bytes.data() + 8, -456);
  EC_WRITE_S32(bytes.data() + 12, 789);
  auto decoded = Elm3604::ReadFeedback(bytes.data(), elm_offsets);
  CHECK(decoded.x.raw_sample == -123 && decoded.y.raw_sample == -456 &&
        decoded.z.raw_sample == 789);
  CHECK(decoded.x.input_cycle_counter == 2 && ElmChannelValid(decoded.x));
  EC_WRITE_U8(bytes.data() + 5, 0x21);
  decoded = Elm3604::ReadFeedback(bytes.data(), elm_offsets);
  CHECK(decoded.x.error && decoded.x.txpdo_state &&
        !ElmChannelValid(decoded.x));
  Clearpath::PdoOffsets motor_offsets{};
  motor_offsets.rx.controlword = 0;
  motor_offsets.rx.mode_op = 2;
  motor_offsets.rx.target_position = 3;
  motor_offsets.rx.target_velocity = 7;
  motor_offsets.rx.target_torque = 11;
  command = {15, 8, -123456, -789, -42};
  Clearpath::WriteCommand(bytes.data(), motor_offsets, command);
  CHECK(EC_READ_U16(bytes.data()) == 15 && EC_READ_S8(bytes.data() + 2) == 8);
  CHECK(EC_READ_S32(bytes.data() + 3) == -123456 &&
        EC_READ_S32(bytes.data() + 7) == -789 &&
        EC_READ_S16(bytes.data() + 11) == -42);
  motor_offsets.tx.statusword = 16;
  motor_offsets.tx.mode_display = 18;
  motor_offsets.tx.actual_position = 19;
  motor_offsets.tx.actual_velocity = 23;
  motor_offsets.tx.actual_torque = 27;
  motor_offsets.tx.digital_input = 29;
  EC_WRITE_U16(bytes.data() + 16, 0x27);
  EC_WRITE_S8(bytes.data() + 18, 8);
  EC_WRITE_S32(bytes.data() + 19, INT32_MIN);
  EC_WRITE_S32(bytes.data() + 23, -999);
  EC_WRITE_S16(bytes.data() + 27, -123);
  EC_WRITE_U32(bytes.data() + 29, 0x30003);
  motor = Clearpath::ReadTxPDOs(bytes.data(), motor_offsets);
  CHECK(CiA402::IsOperationEnabledCSP(motor));
  CHECK(motor.actual_position == INT32_MIN && motor.actual_velocity == -999 &&
        motor.actual_torque == -123);
  CHECK(motor.negative_limit_reached() && motor.positive_limit_reached());
  CHECK(motor.raw_input_a_line_on() && motor.raw_input_b_line_on());
  EthercatSystem core;
  CHECK(!core.configured());
  core.release();
  core.release();
  CHECK(core.read(0) == 0);
  core.write({});
  CHECK(core.shutdown());
}
