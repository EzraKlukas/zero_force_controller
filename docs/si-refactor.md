# SI interface and model boundary

Current controller/session design and exact OFF/FINE checks are in
[controller-design.md](controller-design.md), based on clean `e7453b5`,
8 October 2026. The initial SI migration inspected `main@88772b5` on
6 October; its persistent lower-datum origin and combined calibration/zero-force
controller have been superseded. Root review `urdf/` and `config/` directories
were deliberately removed; canonical files are in `packages/zfc_bringup`.

The shared contract is `carriage/position` command/state (m),
`carriage/velocity` state (m/s), and `load_cell/force.x/y/z` states (N).
One StageSystem and one world-anchored upward prismatic carriage are retained.
The fixed sensor joint to a distal tool is preserved in the prepared Gazebo
branch. No actuator torque is exposed as prismatic effort and no measured
sensor torque is invented. Dimensions, inertias, travel and sensor placement
are provisional, not measured hardware or calibration-physics validation.

Backend selection rejects invalid Xacro values without fallback:
EtherCAT uses the existing physical plugin; the prepared Gazebo branch selects
stock gz_ros2_control/GazeboSimSystem. `controllers_file` is an absolute shared
YAML path; the Gazebo plugin also receives its simulation overlay. Hardware
startup settings, including `unconfigured: [StageSystem]`, do not leak into it.
No simulation launch, adapter, spawning, world, bridge or dynamics is supplied.
The physical launch expands/publishes robot_description, loads both physical
YAMLs and leaves four controllers inactive and StageSystem unconfigured.
Broadcasters require explicit activation after valid data.

Installation settings remain separate from experiment tuning.
Position sensitivity is `m_per_count`, approximately 2e-7 m/count with
unverified sign. Session origin is acquired at valid stationary startup and
frozen across motion controller switches/hardware reactivation; it is not a
persisted lower-stop datum. Cleanup/reinitialization ends that reference.
Unexpected detectable encoder discontinuities stop instead of silently
re-zeroing. Optional measured hardware soft limits use signed session
coordinates; physical switches remain authoritative when absolute travel is
unknown. Gazebo's illustrative [0,0.5] m travel does not constrain hardware
commands. The absolute model-to-session TF offset remains unmeasured.

PDOs/core retain native units. Conversion and finite/int32/bounds/rounding
checks occur only in the physical adapter. Velocity defaults to encoder
differences over measured monotonic elapsed time; the alternative raw PDO
conversion requires independent scale/unit/sign verification. Required force
sensitivities are unset; electrical offsets are optional signal origins, not
an unloaded-force calibration. Confirm mounting, channel/frame/load signs;
the draft load_cell_link +X is upward. Configuration rejects unconfirmed/
missing/nonfinite required calibration before acquiring the master.
Initialization accesses no hardware.

The obsolete max_increment_counts parameter is gone; the actual native
per-accepted-cycle bound remains 1,000 counts. Raw switch-direction/following-
error, startup, watchdog, CiA-402, communications, validity, bounded-stop and
ownership checks remain. Backend readiness/faults gate motion claims without
controller-facing ready/validity interfaces. Invalid state exports NaN and
starts the existing stop; controller NaN never reaches a drive target.
Diagnostics retain statusword, mode, raw channels/torque/velocity, switches,
bus counters and readiness.

ZeroForceController now implements compliant SI logic derived from historical
DriveLogic (`650501a`), not the unfinished archived prototype. Calibration
recurrence/tests moved to the separate calibration plugin, preserving nominal
1 ms integration and count equivalence before bounded stationary settling.
Generated controller schemas permit inactive edits and reject active changes.
Current finite defaults and typed/batched trial capture are documented in the
controller design; they are not fitted or hardware-tuned values.

Verification records are separate: the isolated starting `e7453b5` offline
suite passed 25 tests, while the current OFF/FINE suites each pass 41 tests and
the four existing pandas-based analysis tests pass. Initial `88772b5`
migration baseline failures were absent IgH discovery and stale bringup
parameter assertions; those are historical, not current offline failures.
The former missing-pandas environment issue is resolved in this Distrobox.
No genuine-IgH or SDK-dependent fake-IgH protection suite was run here.
Enable `-DZFC_HARDWARE_TESTS=ON` with genuine IgH on Jetson.

See the controller design for exact build/test and manual startup/switch
commands. A short Jetson smoke test must retain unconfigured/inactive startup,
review installation signs/scales/clearance first, explicitly enable hardware,
wait for a frozen session reference and healthy data, then activate broadcasters
and supervised hold-only control. Leave calibration inactive. Deactivate
controllers/hardware, unconfigure and verify disabled-voltage/single release.
The [historical commissioning record](physical-bringup.md) retains post-disable
motion and DC limitations. Real scheduling/latency, memory locking, affinity,
bus/DC timing, mechanical restraint and stop behavior require physical review.
