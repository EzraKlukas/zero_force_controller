# Jetson hardware, host plotting and operator workflow

This workflow starts at the repository root on the current checkout. Resources
remain package-owned. The Jetson owns EtherCAT, the sole controller manager,
full-rate recording/fitting/application, and plotting decimation. The laptop owns
PlotJuggler and a Python/PyQt panel. No physical operation was executed during
development. Commands under preparation/motion/shutdown below are for supervised
on-site execution after commissioning review, not part of network preflight.

## Build and source each architecture

Use Ubuntu 22.04 / ROS 2 Humble in the host distrobox. Run from the checkout root;
do not copy x86 binaries to the Jetson. Prerequisites must already be provisioned:
Humble controller-manager messages and tools, rclpy, sensor/geometry/action
messages; on the host PyQt5, PlotJuggler and its ROS2 streamer; on the Jetson the
genuine IgH header/library/kernel/master setup, xacro/robot_state_publisher,
joint-state and force-only broadcasters, physical controllers, numpy,
pandas, PyYAML and matplotlib. No install, firewall, routes, shell startup files
or production middleware changes are performed by the repository tools.

Host-only build (does not discover IgH or Gazebo):

```bash
source /opt/ros/humble/setup.bash
colcon --log-base log-host build --base-paths packages \
  --packages-select zfc_interfaces zfc_operator \
  --build-base build-host --install-base install-host \
  --cmake-args -DBUILD_TESTING=OFF
source "$PWD/install-host/setup.bash"
ros2 pkg executables zfc_operator
```

Jetson, from its user-supplied checkout root, with genuine IgH already available:

```bash
source /opt/ros/humble/setup.bash
export ZFC_WITH_SIMULATION=0
colcon --log-base log-jetson build --base-paths packages \
  --packages-select zfc_timing zfc_interfaces zfc_operator zfc_ethercat_core \
  zfc_ethercat_hardware zfc_zero_force_controller zfc_calibration_controller \
  zfc_calibration_analysis zfc_bringup \
  --build-base build-jetson --install-base install-jetson \
  --cmake-args -DBUILD_TESTING=ON -DZFC_HARDWARE_TESTS=ON -DZFC_PROFILING=OFF
source "$PWD/install-jetson/setup.bash"
```

Bringup's Gazebo dependencies are optional and disabled when
`ZFC_WITH_SIMULATION` is unset or `0`; set `ZFC_WITH_SIMULATION=1` **before
colcon/rosdep** for a simulation build including `zfc_simulation`. This is a
package-manifest environment condition, not a `--cmake-args` switch. It does not
select the launch backend: `backend:=gazebo` checks its packages/Fortress
executable at launch and reports missing dependencies before starting processes.
Hardware launch resolves no simulation package paths or simulation-only imports.

The optional-dependency fix was checked in a fresh host overlay containing seven
shared/bringup packages, with `zfc_simulation` discovered but unselected and absent
from the sourced package registry. Bringup reported 41 tests: 37 passed and four
Gazebo-runtime cases skipped as expected. Installed physical launch actions were
constructed without execution; selecting Gazebo reported the missing helper
before starting processes. With the simulator overlay sourced, all 26 launch/
configuration tests and the existing headless Gazebo integration passed. Genuine
IgH packages were excluded because the SDK is unavailable on this host; no
physical activation or motion was executed. Build/test logs are under
`/tmp/zfc-bringup-hardware-only-{build,tests}.log`.

If IgH is outside standard discovery locations, supply the measured paths using
`-DEtherCAT_INCLUDE_DIR=... -DEtherCAT_LIBRARY=...` or the existing
`-DIGH_MASTER_ROOT=...` mechanism. Do not substitute a fabricated SDK. Building
does not commission the physical backend. SDK protection tests and on-site
timing/stop acceptance are separate from the offline fixtures described below.
Jetson launch does not need PlotJuggler/PyQt at runtime when headless; no GUI
module is imported by the relay. Package manifests describe optional operator
executables too; a blanket dependency installer is not a headless build recipe.

Both architectures must rebuild/source the same `zfc_interfaces` definitions
(RunCalibration, OperatorCommand, ApplyCalibration, AnalysisState, PlotState,
MeasuredState and telemetry types) and the same operator checkout. Humble
standard manager/action interfaces must also match. In every CLI/launch shell,
source Humble and the correct architecture overlay before network setup.

```bash
ros2 pkg prefix zfc_interfaces
ros2 interface show zfc_interfaces/action/RunCalibration
ros2 interface show zfc_interfaces/msg/MeasuredState
ros2 interface show zfc_interfaces/srv/OperatorCommand
ros2 pkg prefix controller_manager_msgs
python3 -c 'from rclpy.utilities import get_rmw_implementation_identifier; print(get_rmw_implementation_identifier())'
dpkg-query -W 'ros-humble-rmw-*' 'ros-humble-fastrtps' 'ros-humble-cyclonedds'
```

Compare actual output on both computers; package presence, versions, usernames,
checkout locations and interface addresses are not presumed. Stale sourced
overlays are a common source of incompatible custom types.

## Wired networking before hardware

Jetson wired address is `192.168.55.1`. On the host OS **and inside the distrobox**:

```bash
ip -4 route get 192.168.55.1
ip -brief -4 address
readlink /proc/self/ns/net
```

Read `dev` and `src` from the route, then inspect that actual interface with
`ip -4 address show dev "$ZFC_WIRED_INTERFACE"`. Set `ZFC_HOST_WIRED_ADDRESS`
from the observed source address; do not assume `.100` or a USB interface name.
Compare namespace identifiers and route/address output outside/inside the box.
Different namespaces require a reachable interface/address and functional DDS
there; an SSH connection from the host OS does not prove the box can carry DDS.
On the Jetson inspect its route to the discovered host address similarly. Use
the operator network interface, never the dedicated EtherCAT NIC. Review the
current middleware's NIC allowlist even if its default discovery already works.

Select the existing working RMW on the wire first. Set the following session
variables on **both machines and every CLI shell before ROS initialization**:

```bash
: "${ZFC_DOMAIN:?Set the same reviewed domain on both computers}"
: "${ZFC_RMW:?Set the same installed working RMW on both computers}"
export ROS_DOMAIN_ID="$ZFC_DOMAIN"
export RMW_IMPLEMENTATION="$ZFC_RMW"
export ROS_LOCALHOST_ONLY=0
ros2 daemon stop
ros2 daemon start
```

Keep any vendor configuration compatible and applied to all processes, including
PlotJuggler's late-created streamer. Domain/RMW are not changed by launch.
`network_mode:=inherit` honors `ROS_LOCALHOST_ONLY`, falling back to `1` only
when absent; `isolated` selects `1`, `network` selects `0` for launched children.
An explicit launch option cannot fix an already initialized CLI/daemon with a
different environment. Prefer setting the environment consistently first.

For an existing `rmw_fastrtps_cpp` or `rmw_fastrtps_dynamic_cpp` deployment using
installed Fast DDS 2.x, generate a repository/session profile on each machine:

```bash
# Host: address discovered above, in the distrobox namespace
ros2 run zfc_operator fastdds_profile \
  --local-address "$ZFC_HOST_WIRED_ADDRESS" --output /tmp/zfc-host-fastdds.xml
export FASTRTPS_DEFAULT_PROFILES_FILE=/tmp/zfc-host-fastdds.xml
# Jetson (in its own shell):
ros2 run zfc_operator fastdds_profile \
  --local-address 192.168.55.1 --output /tmp/zfc-jetson-fastdds.xml
export FASTRTPS_DEFAULT_PROFILES_FILE=/tmp/zfc-jetson-fastdds.xml
```

The generator reads the installed version, refuses unsupported major versions
and refuses to overwrite a file. It keeps UDP on the selected operator address
plus loopback, disabling builtin transports for this session. The syntax follows
the [Fast DDS 2.6 interface allowlist](https://fast-dds.docs.eprosima.com/en/v2.6.10/fastdds/transport/whitelist.html).
If production already has reviewed vendor settings, integrate/review this
allowlist rather than discarding those settings. Restart the ROS daemon after
changing vendor configuration, then validate with the harmless preflight below.

Run simultaneously, **with no hardware launch running**:

```bash
# Jetson:
ros2 run zfc_operator network_probe --name jetson --peer host --timeout 30
# Host distrobox:
ros2 run zfc_operator network_probe --name host --peer jetson --timeout 30
```

Each process talks and listens using `std_msgs/String`, provides a Trigger
service and calls its peer's Trigger service. Both must report peer topic and
service reply PASS. This verifies both directions; ping/SSH alone does not.
Repeat after environment/profile changes and with the actual deployment RMW.
Existing firewall/Tailscale ACLs must permit the selected DDS traffic between
these two operator addresses. Review targeted UDP permissions with the site
administrator; never disable the firewall or open the EtherCAT NIC to DDS.

Troubleshoot discovery with `ros2 node list`, `ros2 topic info -v
/zfc_preflight/host`, `ros2 service list -t`, source/type parity, and domain/RMW
inspection. For real measurements use `ros2 topic info -v /plot/measured` and
`ros2 topic echo /plot/measured --qos-reliability reliable`. Broadcaster readers
use sensor-data BEST_EFFORT, compatible with reliable or BEST_EFFORT publishers;
decimated plot outputs are reliable/volatile depth 10, compatible with the
stock PlotJuggler subscriber. The inspected
[ROS2 streamer 2.3.1 source](https://raw.githubusercontent.com/PlotJuggler/plotjuggler-ros-plugins/2.3.1/src/DataStreamROS2/datastream_ros2.cpp)
adapts subscription reliability/durability to publisher offers and creates its
node when streaming starts. Trial status/analysis status use reliable
transient-local; CLI late readers should request that durability explicitly.

## Optional Cyclone unicast and Tailscale

Only use already-installed Humble-compatible Cyclone on **both** machines after
review, not an automatic middleware replacement. The generator reads sourced
vendor XML/CMake metadata or the installed Ubuntu ROS package version, accepts
0.9.x/0.10.x, checks that the selected
IPv4 address can bind in this namespace, and emits `Interfaces/NetworkInterface`,
multicast disabled, reciprocal peers plus the local selected address, automatic
participant indices 0..32. Local peers retain discovery between local processes.
These fields were checked against tagged
[0.9.1](https://raw.githubusercontent.com/eclipse-cyclonedds/cyclonedds/0.9.1/etc/cyclonedds.xsd)
and [0.10.2](https://raw.githubusercontent.com/eclipse-cyclonedds/cyclonedds/0.10.2/etc/cyclonedds.xsd)
schemas, not Rolling documentation. Generation is not runtime parser/network
validation: start the preflight with the **installed** runtime on both hosts and
reject configuration warnings/errors before commissioning. Cyclone was absent
from the development distrobox; this genuine-runtime check remains on-site.

```bash
# Wired host:
ros2 run zfc_operator cyclone_profile --local-address "$ZFC_HOST_WIRED_ADDRESS" \
  --peer-address 192.168.55.1 --output /tmp/zfc-host-cyclone.xml
# Wired Jetson:
ros2 run zfc_operator cyclone_profile --local-address 192.168.55.1 \
  --peer-address "$ZFC_HOST_WIRED_ADDRESS" --output /tmp/zfc-jetson-cyclone.xml
# Each shell uses its OWN file; common reviewed domain remains unchanged:
export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp
export CYCLONEDDS_URI=file:///tmp/zfc-host-cyclone.xml   # Jetson: jetson file
export ROS_LOCALHOST_ONLY=0
ros2 daemon stop
ros2 daemon start
```

For Tailscale, inspect `ip -4 route get 100.70.56.124` and `ip -brief -4 address`
on the host and the reciprocal route on Jetson. Confirm the distrobox can bind
the observed Tailscale address. Generate **separate** profiles: host local
`$ZFC_HOST_TAILSCALE_ADDRESS`, peer `100.70.56.124`; Jetson local `100.70.56.124`,
peer `$ZFC_HOST_TAILSCALE_ADDRESS`. Do not include `192.168.55.1` in these peer
profiles unless intentional routing has separately been configured/reviewed.
Use the same domain, installed RMW/version and appropriate reciprocal session
files, restart daemons and rerun both preflight processes. No bridge stack,
system routes, firewall edits or shell startup edits are added here.

## Review physical profiles before preparation

The supplied installation deliberately has unconfirmed conventions/missing
force sensitivities. The supplied controller numeric defaults are simulation
tuning. The physical analysis overlay deliberately contains invalid/unreviewed
fit criteria and unknown downstream mass. These are startup/observation gates,
not commissioned defaults. Do not flip review flags to bypass measurement.

Provide absolute, reviewed installation/controller/hardware/analysis files.
The physical analysis file starts from
`zfc_calibration_analysis/config/hardware.yaml`: supply **all** fit criteria
(including signed expected slope, acceleration interval, plateau guards,
coverage, tracking/gap/residual/branch/R²/coefficient bounds), feedback freshness
and stationary thresholds, verified `coordinate_convention`, `force_convention`
and `calibration_profile_id`; only then set the three review flags true.
Unknown downstream mass remains `-1.0` in parameters and `null` in metadata.
Record an independently supplied mass only if known. No 0.25 kg assumption or
simulation tolerance/sign becomes a hardware criterion.

Installation review includes encoder sign/scale and frozen session zero, signed
X/Y/Z Newton/count sensitivities and electrical offsets, force channel/frame
mapping, parent-on-child force convention and mounting/load path. Session zero
is not a lower stop or absolute pose. Verify travel/restraint/switches/clearance,
controller excursion and gains, actual nominal 1 ms control recurrence suitability,
effective command acceleration meaning and sufficient bidirectional plateau
coverage. Controller schema and backend activation checks remain authoritative.
Physical `finite_fault_hold` and every `use_sim_time` must be false. Manager
memory locking/thread priority/affinity, scheduling/bus latency and bounded stop
must be reviewed on Jetson; host/Gazebo tests do not establish them.

Launch hashes the actual installation/controller/hardware files. Preparation
rechecks those hashes and compares running controller parameters against the
reviewed settings (excluding coordinator trial IDs and applied inertial coefficient).
Changed profile files require deliberate relaunch. Provenance records the supplied
profile/conventions and file hashes. Saved application requires matching backend,
SI units, conventions/profile, valid signed fit, quality/coverage and the existing
effective-command acceleration source. A simulated coefficient is rejected on
hardware. Application is atomic while zero-force is inactive and read back.

## Start headless, then host tools

In the Jetson shell with the matching network environment and sourced overlay:

```bash
: "${ZFC_INSTALLATION_FILE:?Absolute reviewed installation YAML}"
: "${ZFC_CONTROLLERS_FILE:?Absolute reviewed controller YAML}"
: "${ZFC_HARDWARE_FILE:?Absolute reviewed physical manager/controller overlay}"
: "${ZFC_ANALYSIS_FILE:?Absolute reviewed physical analysis YAML}"
ros2 launch zfc_bringup local.launch.py backend:=ethercat network_mode:=inherit \
  plot:=false relay:=true plot_rate_hz:=100.0 \
  hardware_calibration_file:="$ZFC_INSTALLATION_FILE" \
  controllers_file:="$ZFC_CONTROLLERS_FILE" hardware_file:="$ZFC_HARDWARE_FILE" \
  analysis_file:="$ZFC_ANALYSIS_FILE"
```

StageSystem starts **unconfigured**, four controllers configured **inactive**;
no motion starts and no GUI starts. Analysis and the optional headless relay
start on Jetson. Empty/stale plot data is expected until preparation. `relay:=false`
disables visualization independently of `plot`; it does not disable capture.

In the sourced host distrobox with the same network environment:

```bash
ros2 launch zfc_operator host.launch.py backend:=ethercat network_mode:=inherit
# Optional: panel only, or plotting only
ros2 launch zfc_operator host.launch.py backend:=ethercat plot:=false
ros2 launch zfc_operator host.launch.py backend:=ethercat panel:=false
```

Run one chosen host launch, not all three. The plotting-only variant runs a
headless clock/configuration helper. None starts another controller manager,
analysis node or relay. Confirm PlotJuggler **Start Streaming**, the ROS2 Topic
Subscriber, header stamps, and `/plot/measured`, `/plot/zero_force`,
`/plot/calibration`, `/calibration_analysis/state`. Streamer configuration retries
asynchronously for late Start/restarts, checks parameter responses, and explicitly
sets `use_sim_time=false`, including after a simulated session. Host tools are
non-RT; Qt updates remain on the GUI thread, ROS callbacks on an executor worker.

Local Gazebo convenience remains:

```bash
ros2 launch zfc_bringup local.launch.py backend:=gazebo plot:=true force_ui:=true
# A separate host launch for simulation must select backend:=gazebo.
```

Gazebo manager/controllers/broadcasters/analysis/relay/host streamer use simulation
time. Force-input and simulation readiness remain in `zfc_simulation`; plotting
helpers/layout belong to `zfc_operator`. The old simulator relay executable and
installed bringup layout path remain compatibility entry points to one source.

## Prepare, observe, calibrate, apply and cancel

Use the panel or these equivalent CLI requests from a matched shell. Keep
physical restraints/stop access and on-site supervision ready before Prepare:

```bash
ros2 service call /calibration_analysis/operator_command zfc_interfaces/srv/OperatorCommand \
  "{command: prepare}"
ros2 control list_hardware_components
ros2 control list_hardware_interfaces
ros2 control list_controllers
ros2 topic echo /plot/measured --once
```

Prepare validates reviewed profiles and inactive motion, uses standard manager
services to configure/activate StageSystem, verifies actual physical plugin and
SI interface availability, activates sensor broadcasters only, and waits for fresh
finite stationary feedback. Broadcasters are the ROS feedback path; checking
finite ROS measurements requires their sensor-only activation. No motion claim
is made. Failed preparation never retries motion activation; hardware may remain
powered/holding, which the result explicitly reports. Inspect lifecycle/interfaces
and resolve the cause before any deliberate retry.

Observation is **“streaming; motion controllers inactive; drive holding.”**
Unclaimed EtherCAT `write()` retains EnableOperation and a position target.
Inactive motion is neither free carriage nor motor release nor zero-force
compliance. The panel has no drive-release button. Current hardware `read()`
returns without acquisition when `active_` is false; deactivation performs bounded
shutdown. Therefore inactive/motor-disabled lifecycle does **not** provide live
sensor streaming. True motor-off acquisition would require a separately
commissioned backend lifecycle/drive-state mode retaining cyclic sensor exchanges,
validity/encoder-session handling and reviewed brake/gravity/stop behavior. This
refactor does not implement or physically validate that mode.

For calibration, clear external contact and explicitly affirm it for this request;
sensor readings cannot prove absence of human contact. Keep contact clear through
trajectory and any fresh baseline/noise capture. Measured gravity/support force
is not applied teleop force zero. The simulator force inhibit/ack stays simulation-only.

```bash
ros2 action send_goal /calibration_analysis/run_calibration zfc_interfaces/action/RunCalibration \
  '{external_contact_clear: true, activate_zero_force_after: false}' --feedback
```

The coordinator verifies physical lifecycle/interfaces, fresh stationary SI
feedback and reviewed settings; arms the existing synchronized full-rate capture
before STRICT sequencer activation. Recording/fitting/application remain local
to Jetson. On success it applies the coefficient with zero-force inactive and
leaves the sequencer holding. Optional `activate_zero_force_after: true` performs
the existing checked handoff and a new baseline/noise capture before compliance.
Contact confirmation is an operator instruction/affirmation, not a sensor interlock
proving clearance. Independent physical stop arrangements remain necessary.

```bash
# Apply never starts motion; path is ON JETSON, not the laptop:
: "${ZFC_RESULT_FILE:?Absolute result.yaml path returned by an accepted Jetson trial}"
ros2 service call /calibration_analysis/apply_result zfc_interfaces/srv/ApplyCalibration \
  "{result_file: '$ZFC_RESULT_FILE'}"
# Explicit new zero-force start, reviewed parameters, fresh baseline/noise:
ros2 service call /calibration_analysis/operator_command zfc_interfaces/srv/OperatorCommand \
  '{command: start_zero_force, external_contact_clear: true}'
# Stop motion controllers and VERIFY observation; drive continues holding:
ros2 service call /calibration_analysis/operator_command zfc_interfaces/srv/OperatorCommand \
  '{command: observe}'
```

Operations are serialized with action/apply/prepare/start/observe; competing
requests are rejected. Direct manager/parameter CLI writes bypass serialization;
do not issue them concurrently with a trial. Zero-force start assigns a fresh
trial ID, performs checked ownership/handoff, waits for valid new baseline/noise
and never automatically retries a rejected activation. An uncompensated zero
coefficient is explicit controller tuning, not a physical mass fit.

Cancel in the panel or Ctrl-C the action CLI, then wait for its **FINAL result**.
A cancellation request acknowledgment is not cleanup/stop acknowledgment. To
cancel an existing trial after a panel reconnect, use the panel Cancel button or:

```bash
ros2 service call /calibration_analysis/run_calibration/_action/cancel_goal \
  action_msgs/srv/CancelGoal '{}'
ros2 topic echo /calibration_analysis/state \
  --qos-reliability reliable --qos-durability transient_local
ros2 control list_controllers
```

Require final canceled/failed status, `operation_pending=false`,
`stop_acknowledged=true`, both motion controllers inactive and fresh stationary
feedback. STOP UNVERIFIED remains visible and blocks new motion operations until
on-site inspection/session recovery. Cancellation can leave an already-applied
valid coefficient, but never activates zero-force in cleanup. The ROS observation
button is not an emergency stop.

If UI/network disappears, Jetson control, drive hold, bounded trial/capture,
fitting and requested handoff continue under the existing backend/controller
fault behavior and coordinator deadlines. UI disconnection is not cancellation.
There is no network watchdog that promises motor stop and no auto-reactivation
on reconnect. A successful default calibration can leave sequencer hold; an
explicit handoff can leave zero-force active. Reconnect/inspect actual states,
cancel if needed and verify cleanup before shutting down analysis.

## Timestamps, files and shutdown

Relay defaults to a 100 Hz wall timer outside RT, configurable via `plot_rate_hz`.
Broadcaster joint names/lengths, finite q/v/three force axes, source progression
and wall/source age are checked. `/plot/measured` keeps the joint header time
and separate `force_stamp`; their pairing is **not synchronous**. Flags distinguish
stale/unavailable sources; values become NaN. It does not continuously republish
an old sample as fresh. Physical launch additionally requires a recent active
StageSystem report with available SI state interfaces: fresh broadcaster headers
alone cannot make frozen inactive-hardware values live acquisition. The relay
polls lifecycle state asynchronously at 250 ms, expiring reports after 1 s;
this is an observation gate with executor/network latency, not a control interlock
or proof of individual PDO sensor sample age. Controller reference/compensation stays in distinct
channels; after telemetry expires compatibility channels revert to broadcaster
measurements with unavailable references and trial zero, then recover on a new
activation without mixing trial identities.

PlotJuggler uses source headers, not laptop arrival time. Network latency changes
arrival/rendering; do not interpret it as synchronous force/joint sampling or
servo latency. In the aggregate measured stream the force curve is paired at the
joint header time; `force_stamp` retains the independent force source time.
Keep both host clocks reasonably aligned for useful wall-time
comparison; source freshness is evaluated on Jetson. The panel also detects loss
of arriving status/plot data. Full-rate TelemetryBatch sequence/source timestamps,
terminal/drop counts and durable recorder acknowledgment remain capture evidence;
PlotJuggler delivery is never capture validation. Host subscriptions cover only
decimated plots/status and low-rate manager service replies.

Default local recording is `/tmp/zfc-calibration-trials/<trial-id>/` on Jetson:
`samples.csv`, `plateaus.csv`, `metadata.json`, `result.yaml`, `regression.png`.
Set reviewed analysis `output_directory` to an absolute persistent data location
when durability beyond reboot/tmp cleanup is required. No path or measurement
is inferred from the laptop. Verify metadata complete/drop/final-sequence/fit
and application outcome, then archive under the site's data procedure. Offline:
`ros2 run zfc_calibration_analysis analyze_trial "$ZFC_TRIAL_DIRECTORY"`.

Shutdown on-site only, after final cancellation/cleanup or successful observe:

```bash
ros2 control list_controllers
ros2 control switch_controllers --strict \
  --deactivate joint_state_broadcaster load_cell_broadcaster
ros2 control set_hardware_component_state StageSystem inactive
ros2 control set_hardware_component_state StageSystem unconfigured
```

Verify genuine backend shutdown-confirmed/disabled-voltage completion and single
master release, then terminate the Jetson launch and host tools. Failed shutdown
or stale/missing status is STOP UNVERIFIED; use the site's physical stop/recovery
procedure, never equate launch exit with confirmed drive stop. Deactivation can
allow gravity/post-disable movement; restraints and physical stop review precede
these commands. No such commands were executed during development.

## Verification and remaining physical work

Offline fixtures never load a fake production hardware plugin. They exercise
standard lifecycle/manager services, fresh/malformed/stale sources, calibration
capture/fit/application/handoff and failure cleanup. Build host-only packages
and full offline OFF/FINE variants in separate sourced shells:

```bash
source /opt/ros/humble/setup.bash
colcon --log-base /tmp/zfc-operator-off-log build --base-paths packages \
  --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --build-base /tmp/zfc-operator-off-build --install-base /tmp/zfc-operator-off-install \
  --cmake-args -DBUILD_TESTING=ON -DZFC_PROFILING=OFF --no-warn-unused-cli
source /tmp/zfc-operator-off-install/setup.bash
ROS_LOCALHOST_ONLY=1 ROS_DOMAIN_ID=93 ROS_LOG_DIR=/tmp/zfc-operator-off-test-log \
  colcon --log-base /tmp/zfc-operator-off-test-log test --base-paths packages \
  --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --build-base /tmp/zfc-operator-off-build --install-base /tmp/zfc-operator-off-install \
  --executor sequential
colcon test-result --test-result-base /tmp/zfc-operator-off-build --verbose
python3 packages/zfc_bringup/test/headless_integration.py --log /tmp/zfc-operator-headless-gazebo.log
python3 packages/zfc_bringup/test/calibration_integration.py --log /tmp/zfc-operator-calibration-gazebo.log
python3 -m unittest discover -s profiling/analysis -p 'test_*.py'
git diff --check
```

For FINE use a **fresh shell**, `/tmp/zfc-operator-fine-{build,install,log}`,
`-DZFC_PROFILING=FINE`, and isolated test domain 95. These domains are test
fixtures, not a deployment domain selection. Rebuild/source interfaces on both
architectures before using the changed action/status definitions.

Genuine IgH compilation/protection tests, Jetson scheduling/affinity/RT memory
behavior, physical calibration/motion/stop/motor-off acquisition, real two-host
wired/Tailscale DDS, and interactive PlotJuggler curves require on-site validation.
No Jetson credentials/alias was supplied, so no SSH was attempted. If later
authorized with an existing configured alias/account for `192.168.55.1`, SSH is
limited to read-only OS/ROS/package/interface inventory with normal host-key
verification and existing credentials; do not deploy/edit/activate/stop/install
through it as part of this workflow.

### Development results

The operator-workflow baseline built nine offline packages excluding both EtherCAT
packages. Its final OFF and FINE suites each reported **120 tests, zero errors,
failures or skips**. The host-only `zfc_interfaces`/`zfc_operator` build/test
reports **18 tests, zero failures**, without IgH/Gazebo discovery. Four existing
profiling analysis tests and `git diff --check` pass. Test-only ROS domains and
standard-service fixtures never load a production/fake StageSystem plugin.

Existing headless Gazebo integration passed after fixing controller plotting
decimation across 20 ms telemetry batches; its full-rate terminal capture remains
29,422 consecutive records. Existing calibration/action integration passed fit,
checked application/handoff, fresh baseline, cancellation, reuse and explicit
STOP UNVERIFIED on the known stock Fortress backward-reset stall. These are
simulation observations, not physical measurements. Logs:
`/tmp/zfc-operator-headless-{gazebo,result}.log` and
`/tmp/zfc-operator-calibration-{gazebo,result}.log`.

Two **local** preflight processes using the installed Fast DDS **2.6.12** parsed
the generated loopback-only allowlist and both passed peer topic/service traffic.
This does not validate the wired/Tailscale deployment. Installed host
PlotJuggler **3.17.2**, ROS plugins **2.3.1** were inventoried; the PyQt panel
started/closed offscreen with only expected platform messages (bounded timeout
exit 124). The shared layout loaded in an isolated offscreen PlotJuggler smoke
run, including its ROS2 streamer/parser plugins, before the expected timeout
exit 124; interactive streaming/curves remain unverified. Async fixture tests
cover late/restarted/rejected clock configuration.
No interactive display/curve validation or genuine Cyclone runtime was available.

Initial unrelated C++ formatting, calibration-document frontmatter/CLI edits and
the existing commented localhost override were preserved. No commits, pushes,
branch deletion, hardware access, software installation or system network/security
changes were performed. Physical control/update/read/write code is unchanged by
this operator workflow work.
