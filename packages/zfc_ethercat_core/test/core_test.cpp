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
  EthercatSystem core;
  CHECK(!core.configured());
  core.release();
  core.release();
  CHECK(core.read(0) == 0);
  core.write({});
  CHECK(core.shutdown());
}
