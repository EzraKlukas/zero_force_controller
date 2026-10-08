# SI controllers and trial contract — 8 October 2026

The asynchronous analysis node now reuses this capture/parameter contract; see
[calibration-workflow.md](calibration-workflow.md) for actions, fitting evidence,
application and failure/restart semantics. Neither C++ update state machine nor
installation/session conversion was changed by that task.

Starting checkout: clean `e7453b5`, repository root, Ubuntu 22.04 Distrobox,
ROS 2 Humble. No on-disk AGENTS.md was found; supplied working agreements apply.
No hardware, IgH SDK, simulator, fitting node or coordinator was used. No commit
or push was made. Canonical assets are exclusively
`packages/zfc_bringup/{urdf,config,launch}`; there are no duplicate root assets.

## Ownership and implementation

`zfc_zero_force_controller/ZeroForceController` (instance
`zero_force_controller`) and
`zfc_calibration_controller/CalibrationSequencerController` (instance
`calibration_sequencer_controller`) both exclusively claim `carriage/position`.
Both can be configured inactive; only one can own the command. Humble
ResourceManager rejects a second claim. States are shared:
`carriage/position` (m), `carriage/velocity` (m/s), and
`load_cell/force.x` (N). Interface names are configurable at initialization.
The backend also exports force.y/z for the force-only broadcaster, not invented
torque axes. No readiness/validity interfaces are controller dependencies.

Each plugin has a normal controller header/source for ROS lifecycle, generated
parameters, loaned interfaces and telemetry, plus an ordinary-C++ logic header.
`zfc::Inputs` contains position, velocity, force, timestamp ns and period ns;
`zfc::Snapshot` contains measured inputs, position command and diagnostics.
Logic activation/reset/update and the capture producer have no ROS calls,
allocation, locks, transport dependencies or I/O. The existing shared
`zfc_timing` package and OFF/FINE functionality remain intact.

## Installation versus session calibration

`hardware_calibration.yaml` is installation data, not controller tuning.
`m_per_count` replaces the previous sensitivity name. The supplied magnitude
is approximately 2e-7 m/count; its positive sign is NOT verified.
`conventions_confirmed=false` and all three signed force sensitivities remain
unset, so hardware configuration refuses acquisition of an EtherCAT master.
Initialization never accesses hardware.

There is no persisted `encoder_zero_counts`. Before motion claims, the first
valid stationary startup position is confirmed by two consecutive ready samples
with identical encoder counts and raw velocity equal to zero (only a zero test,
not an assumed unit conversion). That first count is the session reference:

```text
q = m_per_count * (counts - session_reference_counts)
counts_command = round(session_reference_counts + q_command / m_per_count)
```

The reference freezes through controller changes and hardware reactivation.
Cleanup, shutdown/error release or reinitialization ends the session and clears
it. A native-count discontinuity faults instead of re-zeroing. Detection is
conservative and must be checked against real servo catch-up; the command bound
is not a measured physical speed limit. A small encoder reset indistinguishable
from allowed motion cannot be
identified from position samples alone; verifying drive reset reporting remains
a hardware task. Unobserved movement greater than 1,000 counts on hardware
reactivation requires explicit session reinitialization.

Raw PDO velocity units remain unknown. Default `velocity_from_encoder=true`
uses encoder differences divided by measured CLOCK_MONOTONIC elapsed time.
It does not multiply a raw velocity by 1 kHz. This is a cyclic sample-time
estimate, not synchronized encoder-latch timing or a filtered speed estimate.
Optional `velocity_from_encoder=false` requires an independently measured,
finite, nonzero signed `velocity_mps_per_raw_unit`.

Force is `force_*_newtons_per_count * (raw - force_*_zero_counts)` per channel.
Signed sensitivities are required installation calibration; electrical offsets
are optional and default to zero. Controller baseline capture absorbs a constant
offset, but does not turn this signal into unloaded absolute force.
Confirm X/Y/Z channel mapping, electrical/load signs, parent-on-child convention
and mounting/load path. The provisional sensor frame +X is upward. Controller
response polarity does not substitute for verifying hardware conventions.

Startup zero is NOT a lower stop or an absolute mechanical datum.
Gazebo's model now has illustrative bounds [-0.25,0.25] m around a known
mid-travel simulation startup. Hardware does not
inherit those command limits. Optional installation `soft_bounds_enabled`,
`soft_lower_m`, `soft_upper_m` are measured session-relative bounds with
general signed lower < upper; disabled by default. With no absolute travel
measurement the physical switches remain authoritative. An arbitrary startup
zero cannot make robot_state_publisher's model TF an absolute physical pose;
the session-to-model offset remains unmeasured. No homing/retreat was added.

PDOs/core stay native. SI commands are checked finite, against int32 range before
casting and against optional bounds both before and after rounding. The existing
1,000-count accepted-cycle command bound, raw switch-direction/following-error,
startup, watchdog, CiA-402, ownership, communication and bounded-stop checks are
retained. Negative m_per_count never changes raw switch polarity. Invalid
feedback/commands export NaN and fault; NaN is never sent as a drive position.
Raw status/velocity/torque/channels, switches, bus counters and readiness remain
backend diagnostics, including the new encoder_discontinuity reason.

## Settings and zero-force phases

Generated schemas are `src/parameters.yaml` in each controller package.
All numeric defaults are finite software/simulation tuning, NOT commissioned
hardware gains or proof of clearance. Structural `joint_name=carriage` and
`force_interface=load_cell/force.x` are read-only after initialization.
Settings can change while inactive and are revalidated/copied on activation;
no unload is needed. Active changes are rejected before the generated listener
updates its cache. No listener or parameter lookup occurs in update().

Common settings:

| Parameter | Default and meaning |
| --- | --- |
| trial_id | 0 auto; a positive integer assigns a manual/coordinator ID |
| excursion_limit_m | 0.06 m from each activation position; verify physical clearance |
| use_position_bounds | false hardware/shared, true in prepared Gazebo overlay |
| lower_position_m, upper_position_m | 0, 0.5 m, only when enabled; signed bounds allowed |
| stationary_velocity_mps | 0.001 m/s activation/stationary tolerance |

Zero-force settings:

| Parameter | Default and units |
| --- | --- |
| hold_only | false; true selects measured-position hold without force response |
| baseline_duration_s, noise_duration_s | 1 s each, sampled with nominal 1 ms recurrence |
| acceleration_per_force | 0.1 (m/s²)/N, bounded [0,100], requires SI tuning |
| force_response_sign | -1; only ±1 accepted by logic |
| damping_per_s | 5 1/s, exponential velocity damping, bounded [0,1000] |
| inertial_force_coefficient_kg | 0 kg: explicitly uncompensated; signed, bounded ±1000 |
| noise_multiplier, minimum_deadband_n | 3 RMS multiples and 0.05 N |
| max_acceleration_mps2, max_velocity_mps | 0.5 m/s², 0.02 m/s |
| max_force_n | 1000 N input bound; not a calibrated sensor rating |

Phases: baseline (1), noise (2), compliant (3), optional hold (4), fault (5).
Baseline/noise hold measured position and require stationary feedback. Baseline
uses an online mean; RMS uses a scaled stable accumulation of squared deviations
from the FROZEN baseline, including drift. Each new activation clears both.
This implements the empirical approach of historical DriveLogic at `650501a`,
not the unfinished `docs/legacy_zero_force_dynamics.hpp` prototype.

```text
residual = force - baseline - inertial_force_coefficient_kg * previous_command_acceleration
deadband = max(minimum_deadband_n, noise_multiplier * noise_rms_n)
error = sign(residual) * max(abs(residual) - deadband, 0)
response = clamp(force_response_sign * acceleration_per_force * error, ±max_acceleration)
velocity = bounded((previous_velocity + response*dt) * exp(-damping_per_s*dt))
position += velocity*dt
```

The effective acceleration limit also applies to damping/clipping changes.
For reviewed support force, negative residual with sign=-1 commands upward
acceleration. Prior EFFECTIVE command acceleration is used for compensation.
The zero coefficient explicitly permits uncompensated experiments before
analysis exists; it is not a fitted mass. No count-domain gain was reused.
Measured and commanded excursion/bounds, finite inputs/settings and scheduling
are checked. Invalid state latches a NaN position until a new valid activation.

## Calibration reference and stationary completion

Calibration settings use approximate |m_per_count|=2e-7 and nominal dt=.001:

| Parameter | Default |
| --- | --- |
| center_zone_half_width_m | 0.0002 m |
| base_velocity_mps | +0.1 m/s, positive starts upward |
| jerk_mps3 | 1000 m/s³ |
| initial_acceleration_mps2, acceleration_increment_mps2 | 0.2 m/s² each |
| max_acceleration_mps2 | 2.0 m/s² recurrence ramp limit |
| cycles_per_acceleration_increase | 5 |
| settling_acceleration_mps2, settling_timeout_s | 0.2 m/s², 5 s |
| tracking_tolerance_m, stationary_duration_s | 0.0001 m, 0.1 s |

Trajectory (10) preserves the original center crossings, acceleration ramp,
nominal 1 kHz recurrence and final accepted step. For count-equivalent tests:
displacement, speed, acceleration and jerk scale by |s|, |s|/dt, |s|/dt²,
|s|/dt³; both initial/incremental acceleration scale by |s|/dt². To reproduce
the old positive-count first leg use speed sign=sign(s). Crossing groups count
passes in the configured initial direction, including a negative first leg.
Full recurrence equivalence is tested within one encoder count for both signs.

Effective reference velocity is the position-command difference / nominal dt;
acceleration is the successive reference-velocity difference / nominal dt.
It includes initial speed insertion and center-zone clipping, which can exceed
the internal ramp limit. This telemetry is NOT measured acceleration or a claim
of physical jerk/acceleration-limited servo behavior.

A conservative turning/settling excursion envelope is checked before starting,
then measured and commanded limits are checked every cycle. Settling (11)
decelerates the reference to zero, then requires consecutive stationary feedback
and tracking tolerance. Timeout faults. Complete (12) holds stationary; progress
is 1. It still claims position until manually deactivated. Unexpected subsequent
motion faults, but the latched completion describes the finished trial at its
completion time; check current feedback before handoff. Normal deactivation
seeds the command from measured position; faulty feedback preserves NaN.

Both logics integrate with NOMINAL dt=.001, not measured-period integration.
Periods >1.5 ms increment excessive_periods; nonpositive or >10 ms periods and
backward timestamps fault. Resetting ROS time requires deliberate reactivation.

## Telemetry and trial identity

Both controllers publish `~/telemetry` as `zfc_interfaces/msg/TelemetryBatch`
and `~/trial_status` as `zfc_interfaces/msg/TrialStatus`.
Each activation captures sequence 1, then one record per active control update,
through completion/fault. Sequence gaps reveal queue loss.
No DDS/service/file operation, waiting or parameter lookup occurs in update().

`ControllerState` fields:

| Fields | Meaning |
| --- | --- |
| stamp, trial_id, sequence | supplied ROS/simulation timestamp, uint64 trial ID and per-trial sequence |
| phase, fault_code, valid | numeric state/fault and feedback/command validity |
| position_m, velocity_mps, force_n | measured SI position/speed/selected force axis |
| reference_position_m, reference_velocity_mps, reference_acceleration_mps2 | actual discrete command reference and effective derivatives |
| baseline_force_n, noise_rms_n, residual_force_n | zero-force diagnostics; zero/not applicable in calibration |
| progress, excessive_periods | phase/ramp progress and scheduling-jitter counter |

Idle=0; other phase numbers are listed above. Fault codes: none=0, feedback=1,
period=2, bounds=3, settings=4, settling_timeout=5.
`TelemetryBatch` has stamp, at most 256 samples, dropped_samples and
failed_publication_samples. A preallocated 8192-record SPSC queue drops new
samples when full; at 1 kHz it covers approximately 8.192 s of undrained capture.
A 20 ms executor wall timer drains/publishes reliable batches outside update().
DDS may allocate/block there; it cannot block the control producer.

`TrialStatus` is reliable transient-local depth 1 (late readers get the latest
terminal trial), independent of plot reception. Fields: stamp, trial_id,
final_sequence, dropped_samples, failed_publication_samples, phase, fault_code,
completed, successful, capture_complete. A separate terminal slot survives even
if the final sample overflows. Status publication failures retain/retry the slot.
completed means stationary calibration completion, not ordinary deactivation;
successful additionally requires valid final state. capture_complete requires
no producer drops or publication exceptions. It is NOT a receiver acknowledgment
or durable dataset: a future recorder must check all sequences through
final_sequence, persist them, and verify trial success/loss counts.
Node/process loss can lose in-memory capture. No fitting/persistence node exists.

`trial_id=0` automatically increases IDs within a controller object's lifetime;
nonzero manual IDs must strictly increase there. For globally stable experiment
IDs assign explicit positive IDs (ROS parameter supports int64 range) while
inactive. Wait for the previous terminal status to drain before restarting the
SAME controller, otherwise activation refuses without overwriting its capture.
Controller switches do not modify the hardware session reference.

## Manual startup/switching (later supervised use only)

Physical launch still leaves StageSystem UNCONFIGURED and all four controllers
INACTIVE. This task did not execute the following physical commands.
Review installation signs/scales, restraint, switches, clearance and stop access
first; the checked-in calibration deliberately refuses configuration.

```bash
ros2 launch zfc_bringup local.launch.py backend:=ethercat \
  hardware_calibration_file:=/absolute/reviewed-installation.yaml
ros2 control list_hardware_components
ros2 control list_controllers
# Explicitly configure then activate ONLY after review:
ros2 control set_hardware_component_state StageSystem inactive
ros2 control set_hardware_component_state StageSystem active
# Wait for session-reference, startup-ready, finite SI data and healthy diagnostics.
ros2 control switch_controllers --strict --activate joint_state_broadcaster load_cell_broadcaster
# Hold-only smoke test; leave calibration inactive:
ros2 param set /zero_force_controller hold_only true
ros2 control switch_controllers --strict --activate zero_force_controller
ros2 control switch_controllers --strict --deactivate zero_force_controller
# Await its terminal status before reactivating it.
# Deliberate motion trial ONLY with separately verified clearance/settings:
ros2 param set /calibration_sequencer_controller trial_id 42
ros2 control switch_controllers --strict --activate calibration_sequencer_controller
ros2 topic echo /calibration_sequencer_controller/trial_status \
  --qos-reliability reliable --qos-durability transient_local --once
# Require completed/successful and current stationary/valid feedback.
# Prepare inactive zero-force tuning (example only: enables compliant mode):
ros2 param set /zero_force_controller hold_only false
ros2 control switch_controllers --strict --deactivate calibration_sequencer_controller \
  --activate zero_force_controller
# End safely; also deactivate broadcasters before ending the hardware session:
ros2 control switch_controllers --strict --deactivate zero_force_controller \
  joint_state_broadcaster load_cell_broadcaster
ros2 control set_hardware_component_state StageSystem inactive
ros2 control set_hardware_component_state StageSystem unconfigured
```

Verify disabled-voltage completion and single master release. Historical
[commissioning](physical-bringup.md) includes post-disable motion and DC caveats;
it is not validation of this checkout. On Jetson build/test all packages with
genuine IgH and `-DZFC_HARDWARE_TESTS=ON` before this short hold-only smoke test.
Do not run the motion-trial example until SI gains, clearance and conventions
are independently reviewed. Gazebo launch/spawning/worlds/bridges and force
interaction are now in [gazebo-workflow.md](gazebo-workflow.md); actuator dynamics
and analysis orchestration remain separate tasks.

## Exact offline verification

From repository root, in fresh shells for OFF and FINE:

```bash
source /opt/ros/humble/setup.bash
# OFF:
colcon build --base-paths packages --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --build-base /tmp/zfc-prompt1-off-build --install-base /tmp/zfc-prompt1-off-install \
  --cmake-args -DBUILD_TESTING=ON -DZFC_PROFILING=OFF --no-warn-unused-cli
source /tmp/zfc-prompt1-off-install/setup.bash
ROS_LOCALHOST_ONLY=1 ROS_LOG_DIR=/tmp/zfc-prompt1-off-log colcon test --base-paths packages \
  --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --build-base /tmp/zfc-prompt1-off-build --install-base /tmp/zfc-prompt1-off-install
colcon test-result --test-result-base /tmp/zfc-prompt1-off-build --verbose
# FINE (fresh shell, source Humble first):
colcon build --base-paths packages --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --build-base /tmp/zfc-prompt1-fine-build --install-base /tmp/zfc-prompt1-fine-install \
  --cmake-args -DBUILD_TESTING=ON -DZFC_PROFILING=FINE --no-warn-unused-cli
source /tmp/zfc-prompt1-fine-install/setup.bash
ROS_LOCALHOST_ONLY=1 ROS_LOG_DIR=/tmp/zfc-prompt1-fine-log colcon test --base-paths packages \
  --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --build-base /tmp/zfc-prompt1-fine-build --install-base /tmp/zfc-prompt1-fine-install
colcon test-result --test-result-base /tmp/zfc-prompt1-fine-build --verbose
python3 -m unittest discover -s profiling/analysis -p 'test_*.py'
git diff --check
```

Results: six packages build at each level; OFF and FINE each report 41 tests,
0 errors/failures/skips. Four existing Python analysis tests pass with pandas.
Both Xacro branches/URDF control resources and YAML parse; invalid backends,
relative controller paths and invalid installation Booleans fail. Tests cover
SI rounding/overflow/negative scale, stationary frozen origin/elapsed velocity,
invalid calibration, both logic state machines, polarity/inertia/RMS,
NaN/bounds/period/reset, ResourceManager exclusivity, inactive editing,
stationary/latched telemetry completion, concurrent queue/drop handling and
allocation-free logic/capture. Both controller libraries have no EtherCAT/core
linkage. Python launch/model checks do not start hardware or a simulator.

Baseline separately: `git archive e7453b5` was extracted into
`/tmp/zfc-prompt1-baseline.9Kmzmb`; the same ignore list with
`/tmp/zfc-prompt1-baseline-{build,install}` and OFF built four packages and
passed 25 tests, no errors/failures/skips. No baseline offline failure was found.
The older missing-pandas report in the initial SI migration is not present here.
Genuine-IgH/core and SDK-dependent fake-IgH protection tests were NOT compiled
or run. Their fixtures were updated for the session reference; that is not
backend regression validation. Enable ZFC_HARDWARE_TESTS on Jetson to run them.

Outstanding: verify encoder polarity, force sensitivities/signs/frame/load path,
raw velocity units if using the PDO conversion, physical travel/session-relative
soft bounds and absolute TF offset. Real 1 kHz latency, scheduling, locking,
affinity, bus/DC timing and stopping need Jetson checks. Non-RT telemetry timer
delivery depends on executor scheduling; queue/drop/status diagnostics expose
backlog. Existing hardware lifecycle shutdown remains bounded but blocking.
The original controller-only checks did not validate a simulator or hardware.
Current headless simulation acceptance results are separately recorded in the
Gazebo workflow; no hardware validation is claimed.

Simulation ROS plumbing adds structural read-only `finite_fault_hold` (default
false, true only in gazebo.yaml and requiring use_sim_time). It freezes a finite
output on the first logic fault, without changing NaN/fault telemetry or ERROR
returns. Physical hardware.yaml explicitly keeps false, preserving bounded-stop
semantics. Both controller fault paths are regression-tested with invalid sensor
feedback. PlotState is an optional non-RT visualization wrapper: Header, original
ControllerState and reconstructed inertial_compensation_n. The original full-rate
capture and terminal status remain authoritative; see the workflow for preview,
decimation, plotting and recording semantics.
