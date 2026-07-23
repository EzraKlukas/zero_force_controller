# zero_force_controller

C++20 IgH userspace EtherCAT application for the current `ezra-zfc` zero-force
control checkpoint. The controller has reached a useful physical milestone:
with the verified EK1100, ELM3604-0002, ClearPath EC, load-cell, and limit
switch setup, the system can balance the measured raw load-cell signal well in
practice.

This checkpoint is intentionally not an SI-unit force controller yet. The
ELM3604 samples are still raw signed 32-bit PDO counts, the load cell has not
been calibrated into engineering units here, and the ClearPath commands are
still motor position/count increments rather than calibrated forces applied to
the load cell. The current controller does, however, subtract the measured
inertial load-cell bias caused by stage acceleration before applying the
zero-force proportional update. Treat the current controller gains as empirical
raw-count to motor-count tuning parameters for the present hardware setup.

## Current Behavior

The application:

- configures one EtherCAT master and one process-data domain for EK1100,
  ELM3604-0002, and ClearPath EC;
- reads three ELM3604 channels from X1-X3 as raw signed 32-bit samples;
- enables the ClearPath drive in Cyclic Synchronous Position mode;
- captures a startup raw X-axis baseline over 1000 samples;
- estimates the raw X-axis noise level over the next 1000 samples;
- subtracts the measured acceleration-induced X-axis load-cell bias from the
  raw X-axis deviation before the proportional update;
- commands position increments proportional to the corrected X-axis deviation
  outside that noise band;
- applies a simple drag term to damp the accumulated motor-count velocity;
- reverses/returns when a configured ClearPath logical limit is reached;
- publishes decimated in-process telemetry to a non-realtime consumer thread;
- writes a combined CSV after shutdown.

The control path is therefore:

```text
ELM3604 raw X count -> raw-count baseline error
                    -> subtract acceleration-induced inertial bias
                    -> motor-count acceleration
                    -> damped motor-count step
                    -> ClearPath target position
```

No conversion is performed from raw ADC/load-cell counts to newtons, and no
conversion is performed from ClearPath target position/counts to applied force.
The acceleration subtraction is only a raw-count inertial-bias correction for
the present mechanism.

## Inertial Bias Compensation

The latest acceleration sweep measured the proportionality between settled
linear-stage acceleration and the X-axis load-cell response:

```text
inertial_bias_gain = 0.000165970552 raw X counts / (motor count / s^2)
linearity check: F = 0.000167351549 a - 13.52, R^2 = 0.99941
settled groups used: 14 / 20
```

At the fixed 1 kHz control rate, the controller's per-cycle acceleration state
is in motor counts / ms^2. Converting the fitted gain into those units gives:

```text
0.000165970552 * 1,000,000 = 165.970552
```

`DriveLogic` therefore uses `k_af = 166` raw X counts per
motor count / ms^2 and estimates:

```text
external_force_counts =
    measured_load_cell_offset - k_af * motor_acceleration_per_cycle
```

That corrected raw-count value is compared with the startup RMS noise band and
then multiplied by `--kp` to choose the next motor-count acceleration command.
This is still a raw-count controller, not a calibrated force-in-newtons loop.

## Acceleration Sweep

`DriveLogic::InertiaCalibrationNextCommand()` is the calibration motion used to
generate the discrete-acceleration data. It moves the linear stage through
complete cycles around the post-startup initial position while stepping the
maximum per-cycle acceleration target from low to high settings.

The sweep constants are:

```text
zero_accel_position_range = 1000 motor counts
base_position_step        = 500 motor counts / cycle
accel_step                = 5 motor counts / cycle^2
cycles_per_accel          = 10 complete cycles per target
max_const_accel_target    = 20 motor counts / cycle^2
```

Within the center range the command is held at constant velocity so acceleration
is near zero. Outside that range the function ramps acceleration toward the
current discrete target, reverses around the travel cycle, and advances to the
next acceleration target after the configured number of complete cycles. The
resulting CSV is analyzed offline with phase-normalized cycle-triggered
averages; settled positive and negative acceleration plateaus are paired so
each group's residual DC load-cell offset cancels before fitting the inertial
bias gain.

## Verified Topology

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

The readiness gate expects exactly these three slaves, with the master link up,
the process-data domain complete, both slave configs online and operational,
the ClearPath drive Operation Enabled, CSP displayed, and valid ELM samples.

## ELM3604 X1-X3

X1/channel 1, X2/channel 2, and X3/channel 3 are configured for the three load
cell axes. The application maps:

```text
TxPDO 0x1A00: channel-1 status
TxPDO 0x1A01: channel-1 sample
TxPDO 0x1A21: channel-2 status
TxPDO 0x1A22: channel-2 sample
TxPDO 0x1A42: channel-3 status
TxPDO 0x1A43: channel-3 sample

sample objects:
  X = 0x6001:01
  Y = 0x6011:01
  Z = 0x6021:01
  type = signed 32-bit raw PDO
```

Startup SDOs configure X1-X3 as 0-10 V, DC-coupled inputs with IEPE current
off, no filter, decimation 1, and raw extended range off. Electrical
compatibility with the load cell or its signal conditioner must still be
verified separately from this software.

## ClearPath CSP

The ClearPath PDO mapping provides:

```text
RxPDO 0x1600:
  0x6040:00 controlword
  0x6060:00 mode of operation
  0x607A:00 target position
  0x60FF:00 target velocity
  0x6071:00 target torque

TxPDO 0x1A00:
  0x6041:00 statusword
  0x6061:00 mode display
  0x6064:00 actual position
  0x606C:00 actual velocity
  0x6077:00 actual torque
  0x60FD:00 digital inputs
```

Distributed-clock settings:

```text
ClearPath AssignActivate: 0x0300
ClearPath SYNC0 cycle:    1000000 ns
ClearPath SYNC0 shift:    250000 ns
ClearPath SYNC1:          disabled

ELM3604 AssignActivate:   0x0700
ELM3604 SYNC0 cycle:      1000000 ns
ELM3604 SYNC1 delay:      20000 ns
```

After CSP enablement, the first target position is seeded from actual position
to avoid a jump.

## Limit Switches

The ClearPath digital input word exposes both logical limit states and raw
Input A/B line states:

- logical negative limit: bit 0
- logical positive limit: bit 1
- raw Input A line: bit 16
- raw Input B line: bit 17

ClearView 3.0 must map physical Input A/B to the desired negative/positive
limit functions and configure inversion for the chosen wiring. The software
uses the logical limit bits for control decisions. Raw A/B bits are captured in
the CSV for wiring diagnostics only.

When a logical limit is reached during active balancing, the controller stops
the balancing update and commands a return toward the position captured after
the raw-count setpoint window. This behavior is a bounded control response, not
a safety-rated emergency stop or STO implementation.

## Build

With an installed IgH userspace library, such as `/opt/etherlab` on the Jetson:

```sh
cmake -S . -B build
cmake --build build
```

For offline host compilation against a local IgH source/build tree:

```sh
cmake -S . -B build -DIGH_MASTER_ROOT=../igh_general
cmake --build build
```

Do not copy host-built IgH libraries to the ARM64 Jetson. The Jetson should
link against its own installed ARM64 IgH userspace library.

The executable also links the platform thread library for the telemetry
consumer thread.

`--help` does not request the EtherCAT master:

```sh
./build/zero_force_controller --help
```

## Run On The Jetson

No active balancing, useful for acquisition and checkout:

```sh
sudo ./build/zero_force_controller \
    --duration 10 \
    --output combined_capture.csv
```

Raw-count zero-force balancing checkpoint:

```sh
sudo ./build/zero_force_controller \
    --duration 30 \
    --output combined_capture.csv \
    --kp 0.5 \
    --drag 0.01
```

Supported options:

```text
--help
--duration <seconds>
--output <path>
--startup-timeout <seconds>
--position-step-per-cycle <counts>
--kp <raw-count-to-motor-count gain>
--drag <damping fraction>
```

`--position-step-per-cycle` is retained as a parsed/CSV-recorded option from
earlier bounded motion tests. The current raw-count zero-force control path uses
`--kp` and `--drag`; it does not use `--position-step-per-cycle` for balancing.

The loop frequency is fixed at 1000 Hz. The cyclic loop records to preallocated
memory and does not write files until after EtherCAT shutdown.

## Runtime Telemetry

The 1 kHz loop emits a telemetry frame every 10 cycles into a fixed-capacity
single-producer/single-consumer queue. The frame includes the raw ELM feedback,
ClearPath feedback, the command selected for that cycle, controller phase,
raw-count setpoint/noise/error values, wakeup latency, timing overrun count,
readiness state, and producer-side queue drop count.

A separate non-realtime consumer thread drains the queue about every 20 ms and
prints the newest frame once per second. On shutdown it drains any remaining
frames and prints a summary with total frames popped, drain cycles containing
data, the last sequence/sample index, and the last producer drop count.

This telemetry is intentionally status-oriented. It is decimated, may drop
frames if the consumer falls behind, and is not a replacement for the
post-shutdown CSV capture.

## CSV

The output is written only after EtherCAT shutdown. Header lines record the
topology, requested duration, loop frequency, ClearPath mode, raw ELM sample
objects, sample count, and timing overrun count.

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

## SI-Unit Work Remaining

The main remaining translation work is:

- calibrate the load-cell/signal-conditioner/ELM3604 chain from raw counts to
  force units;
- establish axis signs and cross-axis coupling/alignment conventions;
- characterize how commanded ClearPath target-position changes translate into
  applied load-cell force in the actual mechanism;
- replace empirical `--kp`/`--drag` tuning with documented physical units or a
  deliberately unitless controller interface;
- validate latency, scheduling margin, and shutdown behavior under the final
  realtime deployment conditions.
