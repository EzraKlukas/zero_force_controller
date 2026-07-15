# zero_force_controller

C++20 IgH userspace bring-up application for a combined EK1100,
ELM3604-0002, and ClearPath EC EtherCAT topology. The current scope is
integrated communication only: read ELM3604 X1-X3, read ClearPath feedback,
enable the ClearPath in CSP, command a valid CSP hold target by default, and
write one combined CSV after shutdown.

This is not a force controller yet. It does not implement force control, PID,
impedance or admittance control, filtering, load-cell calibration, or
conversion to physical units.

## Topology

Verified target topology:

```text
0:0  EK1100
     vendor  0x00000002
     product 0x044c2c52

0:1  ELM3604-0002
     vendor  0x00000002
     product 0x50219349

0:2  ClearPath EC
     vendor  0x00000c96
     product 0x00000001
```

The application uses one EtherCAT master and one process-data domain for all
three slaves.

## ELM3604 X1-X3

X1/channel 1, X2/channel 2, and X3/channel 3 are configured for the three load
cell axes. The ELM PDO assignment is intentionally limited to:

```text
TxPDO 0x1A00: channel-1 status
TxPDO 0x1A01: channel-1 sample
TxPDO 0x1A02: channel-2 status
TxPDO 0x1A03: channel-2 sample
TxPDO 0x1A04: channel-3 status
TxPDO 0x1A05: channel-3 sample
sample objects: X=0x6001:01, Y=0x6011:01, Z=0x6021:01, signed 32-bit
```

The CSV stores each sample as the unmodified signed 32-bit raw PDO value. No
voltage, force, alignment, sign-extension, or engineering-unit conversion is
inferred.

The ELM3604 is an IEPE sensor terminal. Electrical compatibility with the load
cell or its signal conditioner must be verified separately.

## ClearPath CSP

The ClearPath PDO mapping, CiA-402 enable sequence, and distributed-clock setup
are adapted from the working motor project. The ClearPath DC configuration is:

```text
AssignActivate: 0x0300
SYNC0 cycle:    1000000 ns
SYNC0 shift:    250000 ns
SYNC1:          disabled
```

The loop waits until the link is up, exactly three slaves respond, the master
reports OP, the domain working counter is complete, the ELM3604 and ClearPath
configs are online and operational, the drive is Operation Enabled, and the
ClearPath mode display is CSP.

After CSP enablement, the initial target position is seeded from actual
position. By default the application holds that position and commands zero
target velocity and zero target torque.

The custom ClearPath TxPDO `0x1A00` also includes `0x60FD:00`, the unsigned
32-bit digital input word. `CycleInputs::motor` exposes the configured logical
limit states through `negative_limit_reached()` and
`positive_limit_reached()`. It also exposes `raw_input_a_line_on()` and
`raw_input_b_line_on()` for wiring diagnostics. Raw A/B line states are not
used as logical limits because they do not include the ClearView limit mapping
or inversion.

ClearView 3.0 must separately map physical Input A to the negative limit and
physical Input B to the positive limit, with inversion configured for the
chosen normally-open or normally-closed wiring. This application exposes those
limit states and records them for diagnostics, but it does not yet implement a
software-side directional motion policy. The ClearPath drive's configured limit
response is not a substitute for a safety-rated emergency stop or STO
implementation.

Use `--position-step-per-cycle <counts>` to reproduce the earlier constant
motion test. Positive and negative values are accepted, and stepping starts
only after Operation Enabled with CSP mode displayed.

On SIGINT, SIGTERM, timeout, or duration completion, the application stops
incrementing, holds the current target, keeps velocity and torque commands at
zero, sends a bounded shutdown/disable command sequence for several more
process-data exchanges, then releases the master. This is not an emergency-stop
implementation.

## Control Insertion Point

`DriveLogic` receives only typed data:

```cpp
struct CycleInputs {
  Elm3604::Feedback force;
  Clearpath::PDO::TxPDOs motor;
  std::uint64_t sample_index;
  std::uint64_t scheduled_time_ns;
  std::int64_t wakeup_latency_ns;
};
```

It updates a typed `Clearpath::Command`. It does not receive `ec_master_t`,
`ec_domain_t`, process-data memory, or raw PDO offsets.

## Build

With an installed IgH userspace library, such as `/opt/etherlab` on the
Jetson:

```sh
cmake -S . -B build
cmake --build build
```

For offline host compilation against the supplied IgH source/build tree:

```sh
cmake -S . -B build -DIGH_MASTER_ROOT=../igh_general
cmake --build build
```

Do not copy host-built IgH libraries to the ARM64 Jetson. The Jetson should
link against its own installed ARM64 IgH userspace library.

`--help` does not request the EtherCAT master:

```sh
./build/zero_force_controller --help
```

## Run On The Jetson

No-motion bring-up:

```sh
sudo ./build/zero_force_controller \
    --duration 10 \
    --output combined_capture.csv
```

Explicit motion test:

```sh
sudo ./build/zero_force_controller \
    --duration 10 \
    --output combined_capture.csv \
    --position-step-per-cycle 10
```

Supported options:

```text
--help
--duration <seconds>
--output <path>
--startup-timeout <seconds>
--position-step-per-cycle <counts>
```

The loop frequency is fixed at 1000 Hz.

## CSV

The output is written only after EtherCAT shutdown. The cyclic loop records to
preallocated memory and does not write files.

Columns:

```text
sample_index,scheduled_time_ns,actual_time_ns,wakeup_latency_ns,
elm_x_raw_sample,elm_x_number_of_samples,elm_x_input_cycle_counter,
elm_x_error,elm_x_underrange,elm_x_overrange,elm_x_diag,elm_x_txpdo_state,
elm_y_raw_sample,elm_y_number_of_samples,elm_y_input_cycle_counter,
elm_y_error,elm_y_underrange,elm_y_overrange,elm_y_diag,elm_y_txpdo_state,
elm_z_raw_sample,elm_z_number_of_samples,elm_z_input_cycle_counter,
elm_z_error,elm_z_underrange,elm_z_overrange,elm_z_diag,elm_z_txpdo_state,
motor_statusword,motor_mode_display,motor_actual_position,
motor_actual_velocity,motor_actual_torque,motor_digital_inputs,
motor_negative_limit_reached,motor_positive_limit_reached,
motor_raw_input_a_line_on,motor_raw_input_b_line_on,motor_controlword,
motor_mode_command,motor_target_position,motor_target_velocity,
motor_target_torque
```

The five digital-input columns are intended for offline checks after shutdown:
if raw Input A/B changes but the logical limit bit does not, check ClearView
mapping and inversion; if neither raw nor logical bits change, check wiring,
supply, connector, PDO mapping, and communication; if the logical negative and
positive bits follow the wrong switches, check the ClearView assignments and
physical switch assignments.
