# zero_force_controller

C++20 IgH userspace bring-up application for a combined EK1100,
ELM3604-0002, and ClearPath EC EtherCAT topology. The current scope is
integrated communication only: read ELM3604 X1, read ClearPath feedback,
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

## ELM3604 X1

Only X1/channel 1 is configured. The ELM PDO assignment is intentionally
limited to:

```text
TxPDO 0x1A00: channel-1 status
TxPDO 0x1A01: channel-1 sample
sample object: 0x6001:01, signed 32-bit
```

The CSV stores the `0x6001:01` sample as the unmodified signed 32-bit raw PDO
value. No voltage, force, alignment, sign-extension, or engineering-unit
conversion is inferred.

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
  Elm3604::Channel1 force;
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
elm_raw_sample,elm_number_of_samples,elm_input_cycle_counter,
elm_error,elm_underrange,elm_overrange,elm_diag,elm_txpdo_state,
motor_statusword,motor_mode_display,motor_actual_position,
motor_actual_velocity,motor_actual_torque,motor_controlword,
motor_mode_command,motor_target_position,motor_target_velocity,
motor_target_torque
```
