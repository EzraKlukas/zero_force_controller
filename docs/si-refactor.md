# SI interface migration — 6 October 2026

Reference checkout: main at `88772b5`. Ubuntu 22.04 Distrobox, ROS 2 Humble;
no Jetson, IgH SDK, EtherCAT master or simulator was used. Existing README edits
and root-level review drafts were preserved. Installed sources are now
`packages/zfc_bringup/urdf/stage.urdf.xacro` and that package's `config/*.yaml`.
The root `urdf/` and `config/` remain the supplied review snapshots.

The controller contract is `carriage/position` (command and state, m),
`carriage/velocity` (state, m/s), and `load_cell/force.x/y/z` (states, N).
There is one world-anchored vertical prismatic joint and one StageSystem.
The fixed sensor joint connects the carriage to the distal tool and is preserved
in the prepared Gazebo branch. No motor torque is exported as prismatic effort.
Geometry, masses, travel and sensor placement are provisional. This model does
not validate calibration physics or the physical force path.

Changed areas: bringup model/config/launch/tests; EtherCAT adapter calibration,
SI buffers and claim gating; controller/sequencer and tests; shared timing package;
core/profiling build dependencies and profiling launch/config/schema reader.
The unfinished count-domain zero-force prototype is archived in
`docs/legacy_zero_force_dynamics.hpp`, outside installed controller headers.
Zero-force dynamics and calibration analysis remain unfinished.

Installation calibration is separate from experiment tuning. Configuration
rejects missing/nonfinite values, zero scales, feedback overflow, unrepresentable
travel endpoints and unconfirmed conventions before any IgH call. Initialization
does not access hardware. Position uses `q=s*(counts-c0)`; commands use
`round(c0+q/s)`, with finite/travel/int32 checks before casting and travel checked
again after rounding. Raw velocity has its own independently measured signed
scale; it is never presumed counts/s. Each force channel has a signed scale and
offset. No measured values were available, so calibration remains NaN and
`conventions_confirmed=false`.

Confirm the stable lower-datum encoder value, signed metres/count, raw velocity
unit and sign, and the ELM X/Y/Z channel-to-frame mapping and affine force
calibrations. The draft `load_cell_link` +X points upward, +Y lateral and +Z
toward the wall; confirm parent-on-child force sign and actual mounting/load path.
Only the reviewed direct X/Y/Z mapping is supported. A different axis order or
cross-channel coupling needs an explicit calibration change, not silent relabeling.
No activation re-zero, homing or retreat behavior was introduced.

PDOs and the core retain native units. The actual raw command bound remains
`kMaximumVelocity=1000` counts per accepted cycle; the obsolete parser's “10”
message was misleading. The obsolete parameter/parser is removed. Raw limit
switch direction and residual following-error checks remain unchanged for either
sign of s. Diagnostics retain raw torque/velocity/channels, validity, switch
states, statusword/mode, bus state/counters and readiness. They are not controller
state interfaces. Startup/fault states export NaN; invalid sensors still enter the
existing stop. Both prepare and perform command-mode switching reject premature
or faulted claims. A controller NaN remains a stop sentinel; drive outputs on
fault come exclusively from the existing bounded stop sequence.

The calibration recurrence still uses nominal dt=0.001, irrespective of accepted
period jitter. Gaps above 1.5 ms are counted; nonpositive periods or gaps above
10 ms fault. Converted legacy values, once s is measured:

| SI parameter | Legacy configured value converted with a=abs(s) |
| --- | --- |
| center_zone_half_width_m | 1000*a |
| base_velocity_mps magnitude | 500*a/dt |
| jerk_mps3 | 5*a/dt³ |
| initial_acceleration_mps2 | a/dt² |
| acceleration_increment_mps2 | a/dt² |
| max_acceleration_mps2 | 10*a/dt² |
| cycles_per_acceleration_increase | 5 (unchanged) |

To preserve the original positive-count first leg, set the velocity sign to
sign(s); a positive SI velocity always starts upward. All other entries above are
magnitudes. Controller parameters contain no encoder conversion settings.
Compensated SI sums and a center-boundary roundoff tolerance of 1e-9 times the
zone width prevent floating-point drift changing legacy center crossings.
Completion retains the final step then holds; normal deactivation holds measured
position and failed deactivation preserves the NaN sentinel.
Shared defaults are hold-only with unset trajectory values; enabling calibration
without setting the SI trajectory is rejected.

Offline build/test commands from the repository root:

```bash
source /opt/ros/humble/setup.bash
colcon build --base-paths packages \
  --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --packages-select zfc_timing zfc_zero_force_controller zfc_bringup zfc_profiling \
  --build-base /tmp/zfc-si-build --install-base /tmp/zfc-si-install \
  --cmake-args -DBUILD_TESTING=ON
source /tmp/zfc-si-install/setup.bash
ROS_LOCALHOST_ONLY=1 ROS_LOG_DIR=/tmp/zfc-si-ros-log colcon test \
  --base-paths packages --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --packages-select zfc_timing zfc_zero_force_controller zfc_bringup zfc_profiling \
  --build-base /tmp/zfc-si-build --install-base /tmp/zfc-si-install
colcon test-result --test-result-base /tmp/zfc-si-build --verbose
git diff --check
```

Results: all four selected packages built. Colcon reports 25 tests for OFF,
zero errors, failures or skips, including native ROS YAML parsing and loading the stock
force-only broadcaster with exactly three force state claims. Controller linkage
contains no EtherCAT/core library. Both launch descriptions construct without
execution; the installed Gazebo selection exits with the intended deferral error.
Python/package/plugin/XML/YAML syntax and whitespace checks passed.

Enabled profiling was also checked in an isolated build:

```bash
source /opt/ros/humble/setup.bash
colcon build --base-paths packages \
  --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --packages-select zfc_timing zfc_zero_force_controller zfc_bringup zfc_profiling \
  --build-base /tmp/zfc-si-fine-build --install-base /tmp/zfc-si-fine-install \
  --cmake-args -DBUILD_TESTING=ON -DZFC_PROFILING=FINE
source /tmp/zfc-si-fine-install/setup.bash
ROS_LOCALHOST_ONLY=1 ROS_LOG_DIR=/tmp/zfc-si-fine-ros-log colcon test \
  --base-paths packages --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --packages-select zfc_timing zfc_zero_force_controller zfc_bringup zfc_profiling \
  --build-base /tmp/zfc-si-fine-build --install-base /tmp/zfc-si-fine-install
colcon test-result --test-result-base /tmp/zfc-si-fine-build --verbose
```

FINE builds the same four packages and also reports 25 tests with zero errors,
failures or skips, including the recorder
test that rejects active-cycle allocation and checks schema-2 output. CMake
reports harmless unused `ZFC_PROFILING` argument warnings for packages other than
`zfc_timing`; the profiling level propagates through that shared library's target.
The separate existing Python analysis command
`python3 -m unittest discover -s profiling/analysis -p 'test_*.py'`
cannot import `pandas` in this Distrobox. This is an existing environment
dependency, not an analysis-test failure caused by the migration; no dependency
was installed to mask it.

The explicit ignore list also excludes physical runtime dependencies from
colcon's local overlay checks. The physical plugin still genuinely requires IgH.
Offline checks cover SI/count rounding/overflow, negative scales, independent
velocity and force calibration, invalid installation data, controller NaN stops,
hold/restart/deactivation and period policy, full legacy trajectory equivalence
within one count for both polarities, YAML isolation, both Xacro branches and
Humble control-resource parsing. Invalid backend values fail Xacro expansion.
`local.launch.py backend:=gazebo` exits before constructing physical nodes or a
standalone manager. This branch is preparation only; Gazebo integration,
spawning/worlds/bridges/adapters and servo dynamics are deferred.

Baseline failures, before edits: `colcon build --packages-up-to
zfc_zero_force_controller` failed in core CMake discovery because IgH was absent;
the bringup pytest independently failed with
`KeyError: increment_counts_per_update` (stale assertions against absent
parameters). Several existing plugin tests also assumed a previous shuttle API
and a 10-count bound; these were corrected while retaining applicable backend
safety cases.

Hardware-dependent tests were updated but cannot run here. On a Jetson with the
genuine IgH SDK, enable `-DZFC_HARDWARE_TESTS=ON` in the full colcon build/test.
These regressions reuse existing test-only ELF interposition and exercise startup
claims, ownership, NaN/ELM/communication/drive faults, raw switch direction,
command bounds, startup timing, shutdown and release behavior. They do not
validate real hardware. No fake production backend or IgH substitute was added.

For a short Jetson smoke test:

1. Measure/review installation calibration and safe travel, verify switch
   wiring/polarity and sensor conventions, and provide an absolute calibration
   YAML. Keep `do_calibrate=false`. Check restraint, stop availability and sole
   master ownership before enabling the vertical drive.
2. Build all packages with genuine IgH and run the hardware-dependent tests:
   `colcon build --base-paths packages --cmake-args -DBUILD_TESTING=ON
   -DZFC_HARDWARE_TESTS=ON`, source the overlay, then `colcon test --base-paths
   packages` and inspect `colcon test-result --verbose`.
3. Launch `ros2 launch zfc_bringup local.launch.py backend:=ethercat
   hardware_calibration_file:=/absolute/installation.yaml`. Confirm StageSystem
   unconfigured and all three controllers inactive. Confirm missing calibration
   refuses configuration without acquiring a master before proceeding.
4. Explicitly configure/activate StageSystem using
   `ros2 control set_hardware_component_state StageSystem inactive`, then
   `... StageSystem active`. Wait for `event=startup-ready` and valid channel/bus
   diagnostics. Confirm the raw hold equals measured position and the SI datum
   did not change. Premature motion claims must be refused.
5. Only after valid data, activate joint_state_broadcaster and
   load_cell_broadcaster with `ros2 control switch_controllers --strict --activate
   joint_state_broadcaster load_cell_broadcaster`. Check finite position/velocity
   and the three force axes. Torque axes are unmeasured/unclaimed; do not interpret
   them as measured torque. Leave zero_force_controller inactive; optionally
   activate its hold-only mode under supervision after checking the measured hold.
6. Deactivate any active controllers, set StageSystem inactive then unconfigured,
   and stop launch normally. Verify disabled-voltage completion and one master
   release. Inspect the historical commissioning record for post-disable motion
   and DC limitations.

The active read/update/write path adds bounded arithmetic and no allocation,
blocking I/O or new scheduling authority. Calibration parsing, timing-buffer
allocation and diagnostic thread startup occur outside active cycles. Existing
lifecycle shutdown can block for its bounded 120-cycle exchange/sleep sequence;
fault stopping remains cycle-driven. Real 1 kHz latency, FIFO priority, memory
locking, affinity, DC synchronization and mechanical stopping require Jetson
verification. No Distrobox check establishes them.
