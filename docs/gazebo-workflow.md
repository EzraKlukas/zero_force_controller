# Fortress lab demonstration

The next handoff adds one asynchronous analysis node; see
[calibration-workflow.md](calibration-workflow.md). The original bringup evidence
below remains historical. New simulation force-enable/ack bridges inhibit all
input writers during calibration; the installed plot layout also includes
`/calibration_analysis/state` progress/result telemetry.

This is the simulation bringup handoff after controller separation, starting
from clean `a427138` on 8 October 2026. No physical hardware was started, no IgH
SDK was used, and no fitting/coordinator node or actuator dynamics was added.
Canonical resources remain under `packages/zfc_bringup`.

## Build and checks

Run at the repository root, in a fresh terminal (do not mix OFF/FINE overlays):

```bash
source /opt/ros/humble/setup.bash
colcon build --base-paths packages \
  --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --build-base /tmp/zfc-prompt2-build --install-base /tmp/zfc-prompt2-install \
  --cmake-args -DZFC_PROFILING=OFF --event-handlers console_direct+
source /tmp/zfc-prompt2-install/setup.bash
ROS_LOCALHOST_ONLY=1 ROS_DOMAIN_ID=74 ROS_LOG_DIR=/tmp/zfc-prompt2-test-log \
  colcon test --base-paths packages \
  --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --build-base /tmp/zfc-prompt2-build --install-base /tmp/zfc-prompt2-install \
  --event-handlers console_direct+
colcon test-result --test-result-base /tmp/zfc-prompt2-build --verbose
python3 packages/zfc_bringup/test/headless_integration.py
python3 -m pytest -q profiling/analysis/test_trace.py
git diff --check
```

For profiling, use a fresh terminal and repeat those build/test commands with
`-DZFC_PROFILING=FINE`, `/tmp/zfc-prompt2-fine-build`,
`/tmp/zfc-prompt2-fine-install`, and `/tmp/zfc-prompt2-fine-test-log`.
The existing probes and profiling tools are unchanged. The global profiling
flag is consumed by zfc_timing; other packages may emit an unused-CMake-variable
warning without a build failure. Jetson physical profiling still requires
genuine IgH; `zfc_simulation` can be excluded from
physical-only builds. Genuine SDK-dependent backend protection regressions
were not compiled/run here.

The integration script is opt-in, not an unconditional CTest dependency. It
uses ROS domain 73 and a unique Ignition partition; do not use that domain for
another experiment during the check. There is a 240 s overall watchdog,
bounded service/test waits, and SIGINT/TERM/KILL process-group teardown.
Its server log is `/tmp/zfc-gazebo-acceptance.log`; `--log` changes that path.

## Launch and startup

Source the overlay in every command terminal. For a lab session, use the same
environment in all terminals; it isolates Gazebo transport from other servers:

```bash
source /opt/ros/humble/setup.bash
source /tmp/zfc-prompt2-install/setup.bash
export ROS_LOCALHOST_ONLY=1 ROS_DOMAIN_ID=71 IGN_PARTITION=zfc_lab
ros2 launch zfc_bringup local.launch.py backend:=gazebo plot:=true
```

For unattended use:

```bash
ros2 launch zfc_bringup local.launch.py backend:=gazebo gui:=false plot:=false
```

`ign gazebo -r -s` loads the installed local `worlds/stage.sdf`; no Fuel
downloads are needed. A separate GUI connects to the server. The stage is
created from robot_state_publisher's installed Xacro description. **Only the
stock Gazebo ros2_control plugin owns `/controller_manager`**; no standalone
`ros2_control_node` runs in this branch. Shared `controllers.yaml` and
`gazebo.yaml` are both plugin parameter files. Physics steps and control are
1 ms; controllers, broadcasters, robot_state_publisher, bridge and helper nodes
use simulation time. PlotJuggler's ROS node is configured asynchronously by
the plot relay after its streamer starts; embedded sample stamps are primary.

After creation succeeds, one spawner loads/configures all four controllers
inactive. `simulation_ready` waits on manager services, all configured
controllers, available/unclaimed interfaces, advancing clock, and at least
three finite sensor samples matching the known stationary downstream weight.
It strictly activates **only** joint_state_broadcaster and load_cell_broadcaster,
then verifies finite stationary joint and broadcaster force feedback. Look for
`SIMULATION_READY`, or `/simulation/ready` (transient-local Bool). Startup has
a 60 s wall deadline; creation/spawner/readiness failures shut launch down.
No fixed startup sleeps or automatic motion activation are used.

`backend:=typo` fails before any processes are constructed. `backend:=ethercat`
still leaves StageSystem **unconfigured** and all controllers **inactive**.
Never select that backend in this Distrobox for this workflow.

## Coordinate, mass and force path

World -> fixed base -> vertical prismatic carriage -> preserved fixed
load_cell_joint -> load_cell_link -> preserved fixed tool_mount -> tool_link.
The actual target entity is `stage::tool_link`, type LINK (3), id 0 by name.
Both fixed joints and the target link survive the installed URDF-to-SDF parser.
Simple collisions are separated, not overlapping; box inertias are positive.

Simulation q=0 is a **known mid-travel initial position**, 0.25 m above this
illustrative model's lower datum. Its known mechanical bounds are [-0.25,0.25]
m; +q is world +Z, upward. A roughly -9.81 micrometre stationary constraint
offset was observed. Activation always takes the actual measured position.
This coordinate convention does not imply that hardware has +/-25 cm clearance:
the real stationary startup reference and physical TF offset are unmeasured.
Model geometry, travel, inertias and sensor placement remain provisional.

Tool mass defaults to 0.20 kg; the 0.05 kg sensor link is also downstream of
load_cell_joint, giving a known 0.25 kg sensed mass. `tool_mass_kg:=0.4`, for
example, changes both model mass/inertia and readiness's gravity expectation.
It must be finite, positive and <=10 kg. Update manual compensation accordingly.
Carriage mass is 2 kg and is upstream of the sensor.

The sensor uses child frame, parent_to_child measurement direction. Child +X
maps to world +Z, +Y to world +Y, +Z to world -X. In the verified simulation,
stationary support force is **+2.4525 N on X**. A +1 N world-Z tool push reduces
that reading to about +1.45 N, so negative baseline-relative residual commands
upward acceleration with response_sign=-1. These are simulation conventions,
not confirmed electrical hardware channel/sign calibration. The controller
exports/claims only force.x/y/z, never fictitious torque interfaces. The
broadcaster's message has the standard WrenchStamped shape; unused torque
fields are not measured controller channels.

## Manual activation and strict switching

```bash
ros2 control list_controllers
ros2 control list_hardware_interfaces
# External force must be released; use a new increasing explicit trial ID.
ros2 param set /calibration_sequencer_controller trial_id 41
ros2 control switch_controllers --strict --switch-timeout 5 \
  --activate calibration_sequencer_controller
ros2 topic echo /calibration_sequencer_controller/trial_status --once \
  --qos-durability transient_local
# Wait for trial_id=41, phase=12, completed/successful/capture_complete=true,
# zero drop counts. A latched PREVIOUS trial status is not this trial's completion.
# Completion is a stationary hold, NOT a return to the activation origin.
ros2 param set /zero_force_controller inertial_force_coefficient_kg 0.25
ros2 param set /zero_force_controller trial_id 42
ros2 control switch_controllers --strict --switch-timeout 5 \
  --deactivate calibration_sequencer_controller --activate zero_force_controller
# Wait for phase=3 after the one-second baseline and one-second noise capture.
ros2 control switch_controllers --strict --switch-timeout 5 \
  --deactivate zero_force_controller
```

The coefficient here is manually supplied known simulation mass, not a fitted
installation result. Zero/uncompensated is also an explicitly supported default.
Attempting to activate the second motion controller without deactivating the
first fails strictly: both claim the sole `carriage/position` command.
Deactivate/release forces and wait stationary before a reverse handoff; settings
are editable while inactive, not active. An optional visual manager is
`ros2 run rqt_controller_manager rqt_controller_manager`.

Stock unclaimed actuated joints get zero velocity. With a controller fault,
`finite_fault_hold=true` in the simulation overlay freezes a finite measured
position once (or retains the last finite command if feedback is invalid).
Pure logic/telemetry still reports the fault and NaN reference, and update returns
ERROR. This Humble manager logs ERROR but does **not** automatically unclaim the
controller: explicitly deactivate it using the command above before tuning or
restarting. Hardware overlay/default uses false and preserves the original
NaN bounded-stop sentinel. No non-finite reference enters Gazebo physics.

Pause via GUI or:

```bash
ign service -s /world/zfc/control --reqtype ignition.msgs.WorldControl \
  --reptype ignition.msgs.Boolean --timeout 3000 --req 'pause: true'
# Resume with the same command and 'pause: false'.
```

Pause freezes clock, recurrence and trial sequence. Service switches may time
out while paused because they require a control update. Initially **reset by a
full session restart**: release/close force inputs, Ctrl-C launch, then relaunch;
do not use GUI world reset mid-trial. This also restarts in-memory trial IDs.

## Actual physics force input

Optional UI, initially zero:

```bash
ros2 launch zfc_bringup local.launch.py backend:=gazebo plot:=true force_ui:=true
# Or, with an already running launch:
ros2 run zfc_simulation force_input --gui --ros-args -p use_sim_time:=true
```

The signed slider is bounded +/-10 N; push-up/down select +/-1 N and Release
selects zero. **Use one input writer at a time.** Close the UI before CLI pulses
or calibration; its zero heartbeats would otherwise replace CLI commands.

```bash
ros2 run zfc_simulation force_input --force 1 --duration 0.6 --timeout 15 \
  --ros-args -p use_sim_time:=true
ros2 run zfc_simulation force_input --force -1 --duration 0.6 --timeout 15 \
  --ros-args -p use_sim_time:=true
ros2 run zfc_simulation force_input --force 0 --duration 0.1 \
  --ros-args -p use_sim_time:=true
# Raw sustained CLI input (Ctrl-C -> independent heartbeat timeout):
ros2 topic pub -r 20 /simulation/force_input ros_gz_interfaces/msg/EntityWrench \
  '{entity: {name: "stage::tool_link", type: 3}, wrench: {force: {z: 1.0}}}'
```

Pulses follow ROS/simulation time and have a finite wall watchdog. The UI can
release immediately while paused. The world helper accepts signed world-Z
force only, no torques/X/Y, on the exact named target. It applies an actual
external world wrench at the tool link origin (the model COM), every unpaused
physics step. The sensor therefore sees the transmitted physical load; no
sensor feedback is overwritten and no command interface is claimed.

Installed ApplyLinkWrench's instantaneous topic lasts one physics step;
its persistent topic appends forces rather than replacing them, with a separate
clear topic. Those APIs cannot atomically provide this replacement+heartbeat
behavior. The small **simulation-only world system** uses the same Link wrench
API with one mutex-protected replacement command. Force changes do not accumulate;
release, invalid target/nonfinite input, or 0.5 s steady-wall-time heartbeat
expiry produces zero. During pause force is not applied; an expired command is
zero on resume. Gazebo Link::AddWorldForce requires a WorldPose component and
silently did nothing on this preserved fixed link; AddWorldWrench avoids that
requirement, since this tool's COM is its origin. This is not a hardware adapter
or an actuator model. Its mutex/transport publication/allocation are simulation
work and have no hard realtime guarantee.

## Plotting and recording

`plot:=true` opens PlotJuggler with installed `plot/stage.xml` and the installed
ROS2 plugins. Confirm **Start Streaming? -> Yes** and then the preselected
`/plot/zero_force` and `/plot/calibration` topics with **Use header stamp** checked.
The twelve named tabs cover measured/reference position and velocity, force/
baseline, residual/inertial compensation, effective reference acceleration,
phase/progress for both controllers. No ROS distribution upgrade or
pal_statistics dependency is needed; installed Humble headers do not contain
REGISTER_ROS2_CONTROL_INTROSPECTION.

This installation already discovers `/opt/ros/humble/lib/plotjuggler_ros`.
Do not also pass that directory as `--plugin_folders`: duplicate plugin loading
caused a reproducible startup crash during development. The launch uses the
installed default discovery and saved-streamer prompt, which opens offscreen
without that crash. Actual views are Tab/Container panes. You may rearrange/save a
personal dashboard once streaming. Plot-stream timestamps/decimation are tested,
but this Distrobox has no DISPLAY/WAYLAND or virtual X server: actual Gazebo
GUI rendering and interactive PlotJuggler curves still require a lab display.
PlotJuggler's saved layout/streamer prompt and force UI start under QT_QPA_PLATFORM=offscreen;
that is a limited smoke check, not an interactive GUI validation.

| ROS topic | Schema and nominal rate |
|---|---|
| /clock | rosgraph_msgs/Clock, each 1 ms physics step; sole ROS time source |
| /joint_states | sensor_msgs/JointState, position m / velocity m/s, 1 kHz |
| /load_cell_broadcaster/wrench | geometry_msgs/WrenchStamped, frame load_cell_link, 1 kHz; force-only resource backing |
| /simulation/raw_load_cell | geometry_msgs/WrenchStamped, 1 kHz diagnostic bridge of the actual FT sensor |
| /simulation/force_input | ros_gz_interfaces/EntityWrench, 20 Hz heartbeat, world +Z N, LINK name target |
| /simulation/applied_force | std_msgs/Float64, per-physics-step helper command N; confirm effect separately in sensor feedback |
| /simulation/ready | std_msgs/Bool, transient-local startup result, not a continuous health monitor |
| /{controller}/telemetry | zfc_interfaces/TelemetryBatch, every control sample in <=256-sample batches drained by 20 ms wall timer, reliable |
| /{controller}/trial_status | zfc_interfaces/TrialStatus, reliable transient-local terminal status |
| /plot/{zero_force,calibration} | zfc_interfaces/PlotState, timestamp-decimated <=100 Hz per trial, plus idle measured preview before first activation |

PlotState has Header, original ControllerState in `state`, and
`inertial_compensation_n = force - baseline - residual` outside update, meaningful
only in valid compliant phase (zero otherwise). Idle previews are phase=0,
trial=0, valid=false, with NaN references, not fabricated active commands.
Plotting decimation never removes records from full-rate telemetry. ControllerState
and TrialStatus fields/phases/reference semantics remain in
[controller-design.md](controller-design.md). Sequence starts at **1**. Consumers
must check continuity through final_sequence and loss/status fields; successful
plotting alone is not capture acknowledgment or durable storage.

`config/bridges.yaml` is explicit and one-way:
Gazebo /clock -> ROS /clock (ignition.msgs.Clock);
/load_cell -> /simulation/raw_load_cell (ignition.msgs.Wrench);
ROS /simulation/force_input -> /world/zfc/force_input (ignition.msgs.EntityWrench);
/world/zfc/applied_force -> /simulation/applied_force (ignition.msgs.Double).
No reverse clock bridge or motion command bridge exists.

Example recording, started before activation, with a new unused output path:

```bash
ros2 bag record --use-sim-time -o /tmp/zfc-trial-41 \
  /clock /joint_states /load_cell_broadcaster/wrench \
  /calibration_sequencer_controller/telemetry /calibration_sequencer_controller/trial_status \
  /zero_force_controller/telemetry /zero_force_controller/trial_status \
  /plot/calibration /plot/zero_force /simulation/force_input /simulation/applied_force
# Ctrl-C recording; stop simulation before replay (one clock authority).
ros2 bag info /tmp/zfc-trial-41
ros2 bag play /tmp/zfc-trial-41
# Open the saved layout in a sourced overlay and start the ROS2 subscriber:
ros2 run plotjuggler plotjuggler --layout \
  /tmp/zfc-prompt2-install/zfc_bringup/share/zfc_bringup/plot/stage.xml --disable_opengl
```

The bag includes the recorded /clock; do not add a second replay clock publisher.
Source the custom-message overlay before plotting/replay. Record the plot topics
for convenience, but retain full batches/status for later analysis. The example
is a workflow command, not a claim of persisted dataset validation here.

## Installed versions and observed limitations

ROS Humble on Ubuntu 22.04; Fortress/ignition-gazebo6 **6.18.0**;
gz_ros2_control/demos **0.7.21**; ros_gz bridge/sim/interfaces **0.244.26**;
PlotJuggler **3.17.2**, ROS plugins **2.3.1**, messages **0.2.3**;
rqt_controller_manager **2.54.2**. These versions, the force-torque demo's sensor
declaration, plugin library names and ignition message types were inspected.

OFF and FINE builds succeed with hardware packages excluded; each suite reports
47 tests, zero errors/failures/skips. Offline suites
cover Xacro branches/URDF resources, YAML, claims, legacy SI recurrence,
baseline/RMS/polarity, telemetry and finite simulation versus physical NaN
fault paths. Headless integration checks one manager, advancing clock, inactive
motion startup, valid broadcaster feedback, strict ownership conflicts,
calibration, stationary handoff, pause, +/- pushes, CLI pulse, release/expiry,
unclaimed hold, bounded fault and clean teardown.
The existing timing-analysis regressions also pass: four tests, using synthetic
profiling fixtures, not measured hardware data or calibration fitting.

Observed calibration: **29,422** contiguous records in approximately 29.421 s,
no producer drops/publication failures; F.x **2.0025..4.9525 N**; tracking RMS
**0.000582 m**, max **0.000990 m**; terminal measured velocity ~2.8e-8 m/s.
The stock position servo gain 0.1 creates roughly 10 ms tracking lag, not perfect
instantaneous position tracking. The 0.10 m/s draft velocity limit caused
Fortress to remain saturated downward after a turn, then trip excursion bounds.
The simulation-only limit is now **0.20 m/s** for servo headroom; physical 0.10
m/s and controller/trajectory limits were not changed. No custom dynamics was
needed. The initial/reference clipping acceleration spikes are real changes in
the discrete reference, not measured physical acceleration.

FT arrives asynchronously through stock Ignition callbacks; update has no
per-sample sensor-age guarantee. One acceptance run's best sampled lag relative
to measured velocity differences was 0..1 ms across runs (search 0..10 ms), with
~0.0036..0.0071 N RMS
against the known 0.25 kg inertial expectation. This is an observation, **not a
sensor latency guarantee or fitted calibration**. Position reference lag means
force need not match current reference acceleration; later analysis must account
for timestamps and actual tracking. Noise is unrealistically tiny and inertia,
contacts, rigidity, motor/servo/bus timing and load path remain idealized.

Hardware force scales/signs/channel mapping, encoder polarity, raw velocity units,
real travel/session-relative bounds and absolute TF datum remain unresolved.
This simulation demonstrates the software interface/workflow, not hardware
safety, measured calibration physics or hardware validation.

Relevant stock implementations: [GazeboSimSystem 0.7.21](https://github.com/ros-controls/gz_ros2_control/blob/0.7.21/gz_ros2_control/src/gz_system.cpp),
[Fortress Link force API](https://github.com/gazebosim/gz-sim/blob/ign-gazebo6/src/Link.cc),
[ROS2 plotting streamer 2.3.1](https://github.com/PlotJuggler/plotjuggler-ros-plugins/blob/2.3.1/src/DataStreamROS2/datastream_ros2.cpp).
