# Local IgH EtherCAT with ros2_control

A minimal ROS 2 Humble application for the Jetson's coupled EK1100,
ELM3604-0002 and ClearPath EC system. Controller Manager owns the sole active
1 kHz software cycle: **hardware read → synchronous controller update → hardware
write**. Command/state handles point to in-process `double` storage; DDS is
used for local management services only. There is no remote-node, GUI, host
networking or VPN dependency.

The default trajectory commands **raw motor counts**, not radians or metres:
activation captures actual position `P` and writes `P`; updates 1–1000 write
`P + 10*i`; updates 1001–2000 write `P + 10000 - 10*(i-1000)`; all later
updates hold `P`. Each leg spans 10,000 counts and takes one second **when
updates run at 1 kHz**. This specifies commanded position; physical tracking
must be verified. ELM values are signed raw PDO samples, not volts or newtons.

Launch leaves hardware **unconfigured** and loads the trajectory controller
**inactive**. Activate hardware explicitly, then wait for `startup-ready` and a
30-second fault-free hold before activating the controller. The operator explicitly activates motion after the physical
checks below. The default is one round trip, not indefinite repetition.

## Layout and ownership

```text
packages/
  zfc_ethercat_core/               IgH transport, PDOs, CiA-402, timing probes
  zfc_ethercat_hardware/           SystemInterface, lifecycle, diagnostics
  zfc_linear_shuttle_controller/
    include/zfc_linear_shuttle_controller/
      linear_shuttle_controller.hpp
      ramp_command_generator.hpp
    src/linear_shuttle_controller.cpp
    test/ramp_command_generator_test.cpp
  zfc_bringup/                     local launch, YAML, URDF, integration tests
  zfc_profiling/                   instrumented Controller Manager, hold config
profiling/
  analysis/                       trace reader, manifest, fixture, tests
  notebooks/ros2_control_timing.ipynb
  fixtures/synthetic-cm/           artificial reader example
  README.md, schema.md
docs/
  verification.md                 offline validation instructions
  physical-bringup.md             historical ROS hardware commissioning
  physical-evidence/              ROS commissioning records
```

`zfc_ethercat_core` owns master 0, one domain, PDO offsets, snapshots,
distributed-clock cadence and device readiness. The hardware component uses
this library for IgH transport; it has no application entry point.

`zfc_ethercat_hardware/EthercatHardware` is one `SystemInterface` for the
entire coupled bus. It adapts lifecycle, validates the interface contract and
commands, owns the motion safety gate and exports scalar diagnostics. It has
no EtherCAT worker thread. A preallocated SPSC queue feeds a non-realtime
diagnostic consumer that never accesses IgH.
`zfc_linear_shuttle_controller/LinearShuttleController`
claims only the target-count command and reads actual counts and readiness.
It has no EtherCAT calls. Its header-only `RampCommandGenerator` state machine has no ROS calls
or heap storage. Bring-up supplies a direct robot-description parameter,
controller configuration and local spawner.

## Installed API and timing contract

Verified here: Ubuntu 22.04.5 ARM64, `ROS_DISTRO=humble`, `ros2_control`,
`controller_manager`, `hardware_interface` and `controller_interface` 2.54.0,
pluginlib 5.1.4, IgH headers/library under `/opt/etherlab`, C++20 with GCC 14.3.
No missing build dependencies were found and no system packages were installed.
The running kernel is `5.15.136-rt-tegra` with PREEMPT_RT.

The installed Humble headers define `on_init(HardwareInfo)`, exported handle
vectors and `read/write(Time, Duration)` on `SystemInterface`, and synchronous
`ControllerInterface::update(Time, Duration)`. Plugin descriptions are exported
through `pluginlib_export_plugin_description_file` and the ament resource index.
The [matching 2.54.0 Controller Manager source](https://github.com/ros-controls/ros2_control/blob/2.54.0/controller_manager/src/ros2_control_node.cpp)
confirms read/update/write order and `lock_memory`/`thread_priority` support.
Passing `robot_description` directly is supported by this version, although it
prints a deprecation warning. No robot_state_publisher is required.

The shared read path sets application time, samples entry timing, receives
frames, processes the domain, decodes both devices, then polls master/domain/
slave states. The write path writes PDO commands, synchronizes the reference
clock every other exchange to a fresh `CLOCK_MONOTONIC` reading, synchronizes
slave clocks on every exchange, queues the domain and sends.

Humble gives plugins ROS/system-time timestamps rather than the scheduler's
monotonic deadline, so the hardware adapter samples `CLOCK_MONOTONIC` at read
entry. It never feeds the ROS epoch into IgH. The **clock basis, ordering, DC
settings and every-other-cycle reference synchronization are preserved**; the
application-time sample reflects actual entry in the CM path. Validating the
resulting DC phase under other deployment loads remains a commissioning task.
The physical acceptance measurements are in [the bring-up report](docs/physical-bringup.md).

Hardware/controller rates are fixed to 1000 Hz in this pass. The supplied
period is checked, not used to integrate motion: observations above 1.5 ms are
counted; a nonpositive period or a gap over 10 ms stops the trajectory. Hardware
also checks the elapsed monotonic read-to-read gap. Jitter never causes extra
steps, larger increments or time-based catch-up. Humble itself may schedule
catch-up cycles. During startup, calls less than 0.5 ms after the previous
exchange skip the entire read/write exchange, without sleeping or advancing a
trajectory. After readiness such a catch-up faults and starts the bounded stop
at the next eligible exchange. This prevents a burst from consuming a PDO
response before its frame can return. Startup ignores a supplied period that
includes lifecycle blocking; it independently enforces actual monotonic gaps
and the startup deadline. Runtime period/WC/ELM/drive guards remain enabled.

## Hardware lifecycle and failure handling

| Transition/path | Behavior |
| --- | --- |
| `on_init` | Parse finite startup timeout `(0,300]` seconds, require 1000 Hz and maximum increment 10, validate all interface names; initialize memory only. No master request. |
| `on_configure` | Request master 0, verify identities at 0:0 / 0:1 / 0:2, create domain/configs, queue original ELM SDOs/PDOs and ClearPath CSP PDOs, set original DC parameters. Defer master activation/domain memory until `on_activate`. Partial failures release ownership. |
| `on_activate` | Activate IgH, get domain memory, initialize disabled output and arm startup; return promptly without a loop or sleep. Each ordinary CM read/write advances one CiA-402 startup step, mirroring actual position. Full readiness must arrive within 20 s. Hardware lifecycle `active` during startup does not mean `ethercat/ready=1`; the controller cannot claim motion until ready. The first exchange handoff is measured and bounded to 10 ms. |
| Active `read` | One shared receive/process operation; copy feedback and readiness into preallocated state handles. Latch faults immediately and clear `ready`; never log, allocate, sleep or publish. |
| Active `write` | Validate count command, drive/bus gate and limits; then shared PDO/DC/queue/send. Faults replace motion immediately with the stop sequence. No sleeps, logging, allocation or publication. |
| Controller stop/unload | The realtime command-mode switch releases the claim and captures actual as the hold target. Stale controller storage is ignored. Reclaiming reseeds both hardware and controller. Controller update errors mark the command invalid; the stop switch preserves the hardware fault response. |
| Hardware deactivate | Capture current actual position; exchange up to 20 hold, 50 shutdown (`0x0006`), 50 disable-voltage (`0x0000`) cycles, followed by a feedback confirmation exchange. Never enable a drive merely to stop it. Failure to confirm complete WC/link and Switch On Disabled returns an error. |
| Active fault | The same bounded stop sequencer advances once per CM write (up to 120 cycles plus confirmation), without sleeping. Ready stays false and motion commands are ignored. After sending disable-voltage, return hardware `ERROR` to Resource Manager. |
| Error / cleanup / shutdown | Error releases after the active stop, or completes the bounded lifecycle stop if entered during a lifecycle failure. Cleanup/shutdown release resources, clear pointers, state/commands/counters and flags. Repeated cleanup is safe. Destructor is a final best-effort stop/release fallback. |

Readiness means link up, **exactly three responding slaves**, complete domain
WC, EK1100/ELM/ClearPath online and operational, ClearPath Operation Enabled
with mode display 8, and all three ELM channels having at least one sample,
no error and no invalid TxPDO state. This preserves the original ELM validity
criterion; it is not calibration or an analog saturation check. There is no
automatic active fault reset/re-enable. Reconfigure/reactivate only after
investigating the cause.

The hardware accepts only finite integral doubles representable as `int32_t`,
which are exact in a double. It rejects fractional values, overflow, steps over
10 counts and commands farther into a logical asserted limit. Both target
change and target relative to actual position are checked, including while
holding without a claimed controller. Emergency hold reseeding to actual is an
intentional exception to the ordinary increment bound; forwarding the stale
trajectory is not permitted.

Active faults return `OK` while sending the bounded stop, then `ERROR`; this
is deliberate because Humble can invoke `on_error` directly from the I/O call.
Returning an error on the first bad sample could stop all subsequent exchanges
before shutdown frames were sent. Fault counters and ready=0 are visible
during this interval. Counters reset on cleanup/error recovery. The first-fault record survives
error cleanup and is reset only on explicit configuration. A subsequent loss
of WC or drive state cannot overwrite the first cause. Explicit
lifecycle exchanges occur under Humble Resource Manager serialization, not
concurrently with active I/O. Do not run hardware lifecycle services while a
motion controller is active; deactivate the controller first.

This software is **not a safety-rated emergency stop or STO**. A lost link,
stalled process, SIGKILL, power loss or missed schedule can prevent any software
stop command from reaching the drive. The physical stop/STO and drive watchdog
must be verified independently. Software hold cannot remove kinetic energy
instantaneously. Stop confirmation is best-effort, not a safety guarantee.

## Raw interfaces and parameters

| Resource | Command | State |
| --- | --- | --- |
| `clearpath_axis` | `target_position_counts` | `actual_position_counts`, `actual_velocity_raw`, `actual_torque_raw`, `statusword`, `mode_display`, `negative_limit`, `positive_limit` |
| `elm3604` | none | `x_raw_counts`, `y_raw_counts`, `z_raw_counts`, `x_valid`, `y_valid`, `z_valid` |
| `ethercat` | none | `ready`, `link_up`, `slaves_responding`, `working_counter`, `working_counter_complete`, `communication_fault`, `read_calls`, `write_calls`, `communication_faults`, `invalid_commands`, `excessive_period_observations`, `limit_rejections` |

Each full name is `resource/interface`. Drive/system resources use Humble GPIO
entries and ELM uses a sensor entry, avoiding a fictitious SI-unit kinematic
joint. No joint_state_broadcaster is loaded. CLI interface listings show
availability/claims, not changing scalar values; a future custom broadcaster
can expose these raw diagnostics honestly. There is no telemetry publication
in this control path.

```yaml
increment_counts_per_update: 10  # integer 1..10
updates_per_leg: 1000            # positive; total excursion must fit int32
initial_direction: 1            # exactly +1 or -1
repeat: false
hold_only: false                 # true seeds and holds actual position
expected_update_rate_hz: 1000
```

Parameters are read during configure, never in update. Unsupported rates,
invalid signs, zero/negative increments or leg lengths and excessive excursions
are rejected. Activation also checks the actual-position-dependent endpoint
for overflow. To change parameters, stop/unload the controller, edit YAML,
then load/configure again. Reactivation restarts from the newly measured
actual position, not an earlier run's origin.

## Build and offline verification on the Jetson

Use a local Jetson terminal. Only one Controller Manager may own master 0.

```bash
cd /home/jetson/ezra-zfc
source /opt/ros/humble/setup.bash
printf '%s\n' "$ROS_DISTRO"        # must be humble
export ROS_LOCALHOST_ONLY=1

colcon list --base-paths packages
colcon build --base-paths packages --build-base build/colcon \
  --install-base install --symlink-install --executor sequential --cmake-args -DBUILD_TESTING=ON
source install/setup.bash
colcon test --base-paths packages --build-base build/colcon \
  --install-base install --executor sequential --event-handlers console_direct+
colcon test-result --test-result-base build/colcon --verbose
```

For a different IgH installation, append `-DIGH_MASTER_ROOT=/path/to/igh-master`
to the CMake arguments. Keep ARM64 binaries on the Jetson.

All required ROS binary dependencies were installed here. On another Humble
Jetson, this command installs **only missing** binary dependencies; run it
manually after reviewing the printed package list:

```bash
required=(ros-humble-ros2-control ros-humble-controller-manager
  ros-humble-hardware-interface ros-humble-controller-interface
  ros-humble-pluginlib ros-humble-ros2controlcli ros-humble-launch-ros
  ros-humble-ament-cmake ros-humble-ament-cmake-gtest ros-humble-ament-cmake-pytest)
missing=()
for pkg in "${required[@]}"; do
  dpkg-query -W -f='${Status}\n' "$pkg" 2>/dev/null | grep -qx 'install ok installed' || missing+=("$pkg")
done
printf 'Missing ROS dependencies: %s\n' "${missing[*]:-none}"
if ((${#missing[@]})); then sudo apt-get install "${missing[@]}"; fi
```

`colcon`, CMake, a C++20 compiler, Python pytest/YAML and the
existing compatible IgH kernel/userspace installation are also prerequisites.
Do not replace the working IgH installation as part of this integration.

## Realtime deployment

Controller Manager 2.54.0 requests FIFO priority 50 and memory locking with
the supplied YAML. Confirm its success messages; do not treat a successful
launch as proof of realtime operation. The physical test shell had rtprio
soft/hard limits 99, unlimited memlock, and membership in `realtime` and
`ethercat`. An unprivileged FIFO/50 probe and the actual CM thread were verified.
The hardware touches 8 KiB on the CM thread
on its first read, and its fixed state/command storage is initialized before
activation. This does not prove that every middleware or runtime page is
resident; verify memory locking and page-fault behavior under deployment load.

An administrator can create a dedicated `realtime` group, add the operator,
and place the following in `/etc/security/limits.d/99-zfc-realtime.conf`.
Log out and back in afterward. These are instructions, not changes made by
this repository:

```text
@realtime soft rtprio 99
@realtime hard rtprio 99
@realtime soft memlock unlimited
@realtime hard memlock unlimited
```

Grant the operator access to `/dev/EtherCAT0` through the site's existing
IgH udev/group configuration. Do not make it world-writable. Verify device
ownership and the exact launch shell before every physical test:

```bash
id; id -nG
ulimit -Sr; ulimit -Hr; ulimit -Sl; ulimit -Hl
prlimit --pid $$ --rtprio --memlock
chrt --fifo 50 sh -c 'chrt --pid $$'
# Once CM is running (use its PID from the launch log):
ps -L -p <pid> -o pid,tid,stat,cls,rtprio,pri,psr,pcpu,comm
cat /proc/<pid>/status   # require nonzero VmLck and no mlock failure
```
 PREEMPT_RT is
already present on this Jetson; kernel/IRQ tuning is a deployment task.

CPU affinity is optional deployment policy, not embedded in these packages.
For a reproducible initial experiment, select a suitable CPU after inspecting
IRQ placement and run, for example, `taskset -c 2 ros2 launch zfc_bringup
local.launch.py`. This pins the launched process tree, including management
threads; it is not full CPU/IRQ isolation. Record the selected CPU and verify
threads with `ps -L -p <controller-manager-pid> -o tid,cls,rtprio,psr,comm`.
Do not choose a core blindly based on this example.

## Conservative physical test and local bring-up

1. Clear the mechanism and secure cables. Verify at least 10,000 counts of
   unobstructed travel in the selected initial direction and a clear return
   path. Establish the physical meaning/sign of one motor count separately.
2. Verify negative/positive logical limit mapping and wiring in ClearView,
   including inversion and which physical direction each input stops. Confirm
   physical stop/STO operation and watchdog behavior using the existing
   commissioning procedure before enabling this application.
3. Keep the operator at the physical stop. Remove people and loose items from
   the travel envelope. A software command, terminal or Ctrl-C is not a
   substitute for the physical stop.
4. Verify master/slave state and realtime/device permissions. Stop any other
   EtherCAT application. Launch initially with the trajectory inactive.
5. Confirm active hardware, inactive controller and available raw interfaces.
   Wait for `ZFC event=startup-ready`, then at least 30 seconds of `status`
   records with reason=none, ready=1, WC=4/state=2, all slaves=1/1/8,
   cia=4/mode=8, limits=0/0 and claimed=0. ELM X/Y/Z must each have samples,
   error=0 and TxPDO-state=0. Verify target=actual at startup and stable hold.
   These records come from the diagnostic consumer, with no DDS data path.
6. Activate once. Expect two seconds of commanded motion and then hold.
   Stop immediately for wrong direction, unexpected motion, limit assertion,
   fault, jitter or loss of readiness. Do not automatically retry a fault.
7. Deactivate the controller, then the hardware. Confirm drive voltage-disable
   behavior. Only then exit and inspect results. Repeat/restart/limit/DC tests
   require deliberate operator supervision.

Read-only IgH checks (these do not activate or command the master):

```bash
sudo ethercat master -m 0
sudo ethercat slaves -m 0
sudo ethercat domains -m 0
ls -l /dev/EtherCAT0
```

Expect positions 0/1/2 to be EK1100, ELM3604-0002 and ClearPath EC, respectively.
The configured `ethercat` group can run these read-only commands without sudo.
PREOP before the application configures the bus can be normal. With the
application active, require OP, link up and complete working counter.

In the first local terminal, after the checklist and permission setup:

```bash
cd /home/jetson/ezra-zfc
source /opt/ros/humble/setup.bash
source install/setup.bash
export ROS_LOCALHOST_ONLY=1
ros2 launch zfc_bringup local.launch.py
```

This variable restricts ROS discovery to the Jetson. IgH EtherCAT frames use
the separately configured EtherCAT master NIC; ROS discovery settings do not
configure or replace EtherCAT traffic.

In a second **local Jetson** terminal:

```bash
cd /home/jetson/ezra-zfc
source /opt/ros/humble/setup.bash
source install/setup.bash
export ROS_LOCALHOST_ONLY=1
# Launch starts hardware unconfigured, with the trajectory inactive.
# This returns promptly; readiness progresses over the next several seconds:
ros2 control set_hardware_component_state EthercatSystem active -c /controller_manager
ros2 control list_hardware_components -c /controller_manager
ros2 control list_hardware_interfaces -c /controller_manager
ros2 control list_controllers -c /controller_manager

# Wait for startup-ready and the complete 30-second hold checklist.
# Only then, once, start the one-round-trip motion:
ros2 control set_controller_state linear_shuttle_controller active -c /controller_manager
ros2 control list_controllers -c /controller_manager

# Stops the trajectory and holds current actual position:
ros2 control set_controller_state linear_shuttle_controller inactive -c /controller_manager

# Repeating the active command deliberately starts a new round trip from actual.
# For a complete stop, after deactivating the controller:
ros2 control set_hardware_component_state EthercatSystem inactive -c /controller_manager
ros2 control list_hardware_components -c /controller_manager
sudo ethercat slaves -m 0

# Release master/domain ownership:
ros2 control set_hardware_component_state EthercatSystem unconfigured -c /controller_manager
```

Then press Ctrl-C in the launch terminal. On normal signal-driven shutdown,
Controller Manager also invokes hardware shutdown; explicit deactivation is
preferred so that its result can be checked while the process is alive. If a
stop fails or the system is unresponsive, use the physical stop/STO. Do not
rely on SIGKILL for safe shutdown. After a fault, inspect the drive/bus and
restart bring-up only when the cause is understood.

Expected management output names `EthercatSystem` as unconfigured and
`linear_shuttle_controller` as inactive immediately after launch. Explicit
hardware activation exposes interfaces while bounded startup is still underway;
require the separate ready flag before motion. Activation
claims `clearpath_axis/target_position_counts`. The controller remains active
while holding after its round trip; completion does not unload it. No 1 kHz
console formatting occurs on the control thread and no raw-value DDS topic is
produced. The diagnostic consumer emits startup/fault/stop events, 1 Hz status,
and a record for each changed claimed target during this acceptance pass. Its
4096-entry fixed queue never blocks the control thread; `dropped` must remain
zero when using the log to prove an exact command sequence. Each record has
`CLOCK_MONOTONIC` nanoseconds, lifecycle phase, first reason, call counts, CM
period, actual read interval, bus/slave states, CiA-402 feedback, target, limits,
claim/sequencing/stop state and ELM channels. ELM fields are
`raw/samples/cycle_counter/error/txpdo_state/underrange/overrange/diag`.
`max_tracking_counts` is maximum absolute commanded-target versus last sampled
actual position while claimed; it is not a mapped drive following-error object.
`changes=1000` and `changes=2000` identify default reversal and return.

## Verification limits

[The verification record](docs/verification.md) distinguishes executed offline
checks from hardware-only work. The test-only IgH backend is linked into the
integration-test executable, never into installed plugins. It emulates process data to exercise the real core and loaded plugins;
it does not establish physical timing, electrical compatibility, drive tracking,
DC lock, limit wiring, actual watchdog response or stop/STO behavior.

[The physical bring-up report](docs/physical-bringup.md) records the completed
single trajectory, earlier failures, and remaining DC and post-disable movement
limitations. Voltage disable does not establish mechanical position restraint.

## Cycle profiling

The [profiling workbench](profiling/README.md) retains opt-in OFF/COARSE/FINE
probes and an instrumented Controller Manager 2.54.0 executable. Its launch
uses the same application plugin with `hold_only=true`, hardware unconfigured
and controller inactive. The notebook summarizes cycle execution, read,
controller, write, period error, deadlines and overruns for ROS 2 captures.

To read the implementation, start with `zfc_bringup/config/controllers.yaml`,
then the controller's interface declarations and lifecycle callbacks in
`linear_shuttle_controller.cpp`, its `update()`, the count-step generator in
`ramp_command_generator.hpp`, and finally `EthercatHardware::write()` and
`EthercatSystem::write()`. The controller claims one command interface; only
Controller Manager invokes it. Parameters are loaded outside the update loop.
