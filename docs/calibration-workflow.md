# Simulated calibration workflow

Two motion controllers retain their small allocation-free C++ logic headers:
`calibration_sequencer_controller` runs trajectory/settling/hold;
`zero_force_controller` captures fresh baseline/noise then controls compliance.
One non-real-time Python `calibration_analysis` node coordinates existing capture,
standard Controller Manager/parameter services, fitting and files. Neither update()
gained ROS actions, service waits, fitting or file I/O. This is simulated validation,
not physical commissioning or installation-calibration validation.

Starting checkout: clean `1c0cdc4`, no on-disk AGENTS.md; supplied agreements apply.
Canonical installed resources remain under packages/zfc_bringup. No root model/
config duplicates, commits, pushes, hardware tests or fake production backend.

## Build and demonstration

From the repository root, in a fresh shell:

```bash
source /opt/ros/humble/setup.bash
colcon build --base-paths packages \
  --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --build-base /tmp/zfc-prompt3-build --install-base /tmp/zfc-prompt3-install \
  --cmake-args -DZFC_PROFILING=OFF --event-handlers console_direct+
source /tmp/zfc-prompt3-install/setup.bash
export ROS_LOCALHOST_ONLY=1 ROS_DOMAIN_ID=71 IGN_PARTITION=zfc_lab
ros2 launch zfc_bringup local.launch.py backend:=gazebo plot:=true
```

Use gui:=false plot:=false unattended. Wait for SIMULATION_READY; only broadcasters
activate automatically, both motion controllers remain inactive. Analysis starts
idle in both launch paths using backend-appropriate time. Physical actions/applying
are deliberately rejected pending commissioning; StageSystem remains unconfigured
and all controllers inactive.

Source the same overlay/domain/partition in every terminal. Default goals apply a
valid fit but DO NOT activate zero-force; sequencer retains stationary hold:

```bash
ros2 action send_goal /calibration_analysis/run_calibration \
  zfc_interfaces/action/RunCalibration '{}' --feedback
ros2 topic echo /calibration_analysis/state --once
ros2 param get /zero_force_controller inertial_force_coefficient_kg
ros2 control list_controllers
export ZFC_TRIAL_DIR=/tmp/zfc-calibration-trials/REPLACE_WITH_RETURNED_TRIAL_ID
python3 -m json.tool "$ZFC_TRIAL_DIR/metadata.json"
ros2 run zfc_calibration_analysis analyze_trial "$ZFC_TRIAL_DIR"
ros2 control switch_controllers --strict --switch-timeout 5 \
  --deactivate calibration_sequencer_controller --activate zero_force_controller
```

Wait for /plot/zero_force/state/phase=3 and valid feedback (baseline=1, noise=2).
Then enable RELEASED force input; calibration does not replace trial baseline:

```bash
ros2 topic pub --once /simulation/force_enable std_msgs/msg/Bool '{data: true}'
ros2 run zfc_simulation force_input --force 1 --duration 0.6 --timeout 15 \
  --ros-args -p use_sim_time:=true
ros2 run zfc_simulation force_input --force -1 --duration 0.6 --timeout 15 \
  --ros-args -p use_sim_time:=true
ros2 run zfc_simulation force_input --force 0 --duration 0.1 --timeout 15 \
  --ros-args -p use_sim_time:=true
```

Positive world-Z push reduces support force.x and produces upward response;
negative reverses it. Release is backed by the independent 0.5 s wall watchdog.
Optional force_ui:=true reuses the slider; close it before CLI pulses because its
zero heartbeats compete with a second writer. Optional automatic handoff inhibits
force through new baseline/noise, then enables released input after valid phase3:

```bash
ros2 action send_goal /calibration_analysis/run_calibration \
  zfc_interfaces/action/RunCalibration '{activate_zero_force_after: true}' --feedback
ros2 control switch_controllers --strict --switch-timeout 5 --deactivate zero_force_controller
ros2 service call /calibration_analysis/apply_result zfc_interfaces/srv/ApplyCalibration \
  "{result_file: '$ZFC_TRIAL_DIR/result.yaml'}"
```

Apply requires zero-force inactive and never switches/starts controllers. Custom
result YAML includes units/provenance, not a general ros2 param load file. No shared
defaults, installation sensitivity, encoder/session reference or baseline changes.
A new session starts coefficient0 unless explicitly applied again.

Installed Humble send_goal requests cancellation on Ctrl-C. Wait for its FINAL
result, not “Goal canceled” (request acknowledgment). Alternatively:

```bash
ros2 service call /calibration_analysis/run_calibration/_action/cancel_goal \
  action_msgs/srv/CancelGoal '{}'
ros2 topic echo /calibration_analysis/state
ros2 control list_controllers
```

Client timeout/disconnection is not cancellation. Do not terminate analysis during
a run and mistake process exit for controller stop acknowledgment.

## State, recording and fit contract

```text
idle -> inhibit/physics ack -> inactive/stationary -> snapshot/ID/arm subscription
     -> STRICT sequencer activation -> capture -> terminal/exact final-sequence drain
     -> stationary hold / worker fit+files -> inactive-zero atomic set/readback
     -> [optional STRICT handoff / fresh baseline+noise / released-force enable]
     -> complete
cancel/error -> inhibit / checked deactivate / inactive+stationary verify
             -> incomplete files / canceled or failed; NEVER automatic zero-force
```

Overlaps are rejected. Positive int64 IDs exceed wall-time nanoseconds and observed/
configured IDs. Subscription exists from startup and is armed before activation,
retaining sequence1. Known old deliveries are quarantined; unexpected identities
fail. Existing synchronized ControllerState batches, NOT a broadcaster time join,
supply source trial/sequence/stamp/phase, measured q/v/F and reference q/v/effective a.
Every batch/terminal drop and failed-publication count is checked. Sequence1 through
matching TrialStatus.final_sequence must arrive exactly once; terminal may precede
final batches. Service completion or phase12 alone is insufficient. Invalid/fault,
non-finite feedback, gaps/duplicates/order errors, time reversal/repetition, excessive
time gaps and capacity overflow reject capture. Only activation/first update may
share a source timestamp.

Defaults: 120,000 records, 120 s wall capture, 8 s services/drain, 15 s baseline,
30 s worker deadline, 10 ms maximum source gap. A SingleThreadedExecutor with
reentrant async callbacks yields rclpy futures/steady-clock timers: no nested spins
or blocking service waits. One worker fits/writes CSV/JSON/YAML/plots; new jobs/runs
are rejected until it drains. Python allocations/GIL, DDS and disk latency are
non-RT; bounded recording/producer queues expose backlog. Worker cannot preempt
a blocked OS write.

STRICT responses and lists verify ownership. Humble activation ERROR leaves a
controller unconfigured; cleanup uses configure-only recovery to inactive, never
activation retry. Missing services/rejected stop/configure reports STOP UNVERIFIED,
stop_acknowledged=false and blocks further runs. Cancellation cannot recall a
dispatched parameter transaction; an already-applied VALID coefficient may remain
(reported by applied), but cleanup never activates motion and saves incomplete data.

Simulation interlock: /simulation/force_enable Bool ROS_TO_GZ ignition.msgs.Boolean;
/simulation/force_enabled Bool GZ_TO_ROS Boolean, acknowledged after physics steps.
Disable clears queued force and rejects wrench writers; re-enable starts zero.
Existing UI resets its slider. Analysis requires fresh inhibited ack/applied zero
through trajectory, drain, fitting and baseline; it never claims position or
overwrites sensor feedback.

Fit only F_x=b+k_a*a_reference_effective, the actual reference velocity change /
nominal1ms. It matches zero-force's previous effective-command compensation.
Measured q/v check tracking, never replace the regressor. Signed kg coefficient is
effective for this force path/reference, NOT total carriage/rotor mass. Historical
650501a raw k_af=166 is not SI; no missing historical fit evidence is fabricated.
Use trajectory phase10 only; split at acceleration/phase changes to exclude
clipping/insertion spikes. Exclude first50ms/last10ms of plateaus and +/-20ms around
reference reversals. Baseline, settling11 and complete12 are excluded. Require
|a|0.1..2.1m/s², >=8 samples/plateau, >=3 plateaus AND three distinct levels per
positive/negative branch. Equal-weight plateau means fit slope/intercept. Branch
slopes must independently have the reviewed sign and differ <=15% of combined k.

Criteria: expected sign+1 for simulation support-force path; |k|<=10kg; R²>=0.95;
selected-sample residual RMS<=0.05N; trajectory position error<=0.002m; plateau
velocity error<=0.025m/s (allows ~10ms stock lag at2m/s² without changing regressor).
Uncertainty is ONE standard error across plateau means, not 1kHz independent samples
or systematic physical uncertainty. Criteria are checked read-only startup settings
in installed zfc_calibration_analysis/config/analysis.yaml; restart with reviewed
alternative config to tune. Trajectory tuning stays in existing inactive controller
schemas. No friction/velocity terms or production notebook execution.

Reference downstream mass: sensor0.05kg+tool0.20kg=0.25kg, not upstream carriage2kg.
Static force+2.4525N; load_cell_link +X=world+Z, parent_to_child child frame. Preserved
fixed sensor/tool joints define the path; tool_mass_kg launch updates metadata.

Trial directory /tmp/zfc-calibration-trials/<trial-id>/:

- samples.csv: trial ID, sequence, source time_ns, phase, measured SI q/v/F and
  reference q/v/effective a, including early/settling/final samples.
- plateaus.csv: selected mean a/F, counts and source-time intervals.
- metadata.json: parameters/backend/model/frame/mass/session/criteria, recorded/
  final/drop counts, complete flag/fit and checked application/readback outcome.
- result.yaml: schema, units, provenance, fit; canceled/failed trials unusable.
- regression.png: source-time force/model and plateau regression scatter.

Offline analyze_trial uses the SAME pure fit_samples function, refusing explicitly
incomplete capture. Full-rate batches remain authoritative; plot streams ~100Hz.
AnalysisState/action feedback:10Hz and latched final; Header, trial ID, stage/code,
progress, recorded/dropped/final counts, stop acknowledgment/detail, CalibrationResult.
Stage codes idle0/preparing1/stopping2/recording3/draining4/analyzing5/applying6/
baseline7/complete8/canceled9/failed10. Result: validity/reason, signed kg slope,
N intercept, R², N residual RMS, kg standard error, sample/plateau counts, branch
slopes, tracking RMS and explicit acceleration source.

PlotJuggler installed layout adds analysis progress/stage/coefficient/R². Confirm
Start Streaming and preselected /plot/zero_force, /plot/calibration and
/calibration_analysis/state using header stamps; no second GUI framework. Optional:

```bash
ros2 bag record --use-sim-time -o /tmp/zfc-demo-bag /clock \
  /calibration_sequencer_controller/telemetry /calibration_sequencer_controller/trial_status \
  /zero_force_controller/telemetry /zero_force_controller/trial_status \
  /calibration_analysis/state /plot/calibration /plot/zero_force
```

Stop live launch before replay, source custom overlay, replay recorded /clock
without another clock publisher. Plot playback is not durable-capture proof.

## Exact checks and evidence

```bash
source /opt/ros/humble/setup.bash
source /tmp/zfc-prompt3-install/setup.bash
ROS_LOCALHOST_ONLY=1 ROS_DOMAIN_ID=84 ROS_LOG_DIR=/tmp/zfc-prompt3-test-log \
  colcon test --base-paths packages \
  --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --build-base /tmp/zfc-prompt3-build --install-base /tmp/zfc-prompt3-install \
  --event-handlers console_direct+
colcon test-result --test-result-base /tmp/zfc-prompt3-build --verbose
python3 packages/zfc_bringup/test/calibration_integration.py --log /tmp/zfc-calibration-final-acceptance.log
python3 packages/zfc_bringup/test/calibration_integration.py --default-goal \
  --log /tmp/zfc-calibration-default-acceptance.log
python3 packages/zfc_bringup/test/calibration_integration.py --startup-only \
  --log /tmp/zfc-calibration-restart.log
python3 packages/zfc_bringup/test/headless_integration.py --log /tmp/zfc-prompt3-legacy-acceptance.log
python3 -m unittest discover -s profiling/analysis -p 'test_*.py'
python3 profiling/analysis/trace.py profiling/fixtures/synthetic-cm/timing.bin /tmp/zfc-prompt3-timing-fixture.csv
git diff --check
```

FINE in a FRESH shell, not layered over OFF:

```bash
source /opt/ros/humble/setup.bash
colcon build --base-paths packages \
  --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --build-base /tmp/zfc-prompt3-fine-build --install-base /tmp/zfc-prompt3-fine-install \
  --cmake-args -DZFC_PROFILING=FINE --event-handlers console_direct+
source /tmp/zfc-prompt3-fine-install/setup.bash
ROS_LOCALHOST_ONLY=1 ROS_DOMAIN_ID=85 ROS_LOG_DIR=/tmp/zfc-prompt3-fine-test-log \
  colcon test --base-paths packages \
  --packages-ignore zfc_ethercat_core zfc_ethercat_hardware \
  --build-base /tmp/zfc-prompt3-fine-build --install-base /tmp/zfc-prompt3-fine-install \
  --event-handlers console_direct+
colcon test-result --test-result-base /tmp/zfc-prompt3-fine-build --verbose
```

Installed Humble/rclcpp16.0.21, ControllerManager2.54.2, Fortress6.18.0,
gz_ros2_control0.7.21, ros_gz0.244.26, PlotJuggler3.17.2/ROSplugins2.3.1;
numpy1.21.5/pandas1.3.5/scipy1.8.0/matplotlib3.5.1. Eight packages build OFF/FINE.
Final OFF and FINE suites each report **84 tests, 0 errors/failures/skips**;
34 fit/capture/coordinator tests are included. Both Xacro/URDF branches, YAML,
controller claims/state machines, allocation-free capture and existing timing
tests pass. Automatic and default-false/manual handoff demonstrations pass;
actual backward-time reset is an explicitly UNVERIFIED-stop limitation below.
Full session restart and installed offline replay pass. Exact-source final trial:
1791501819710442630, k=0.2499219855kg, residual RMS=0.000293756N, 19,449 selected
samples/90 plateaus; durable files under /tmp/zfc-calibration-trials/<ID>/.
Offscreen plot:=true force_ui:=true startup reached SIMULATION_READY and loaded
the updated layout/plugins before the expected 15s timeout (exit124); interactive
curves remain unavailable without a display. All owned processes were cleaned up.

Development checks separately: one initial test invocation omitted the hardware
ignore list and encountered the expected absent SDK; corrected commands above
exclude both packages. A frozen-reference test assertion conflicted with the
established measured-position baseline hold and was corrected, without changing
controller logic. A 6s bad-fit fixture deadline assumed plot/disk latency and
failed under concurrent load; its bounded allowance is now20s (production worker
deadline remains30s). No current baseline controller/simulation failure is claimed;
the established Prompt-2 runtime suite was rerun successfully.

Known-mass evidence: k≈0.249922kg (0.031% error, target<=5%), b≈2.45250N,
R²≈0.99999991, residual RMS≈0.00029N; ~19,450 selected samples/90 plateaus.
29,422 consecutive records include activation1/final stationary sequence; no drops.
Tracking RMS0.000582m/max≈0.000990m. Branches≈0.24996/0.249975kg; statistical
uncertainty≈8e-6kg, not a physical error budget. New simulation data, not old evidence.
Checks cover exclusive claims, actual next-activation compensation, baseline hold,
signed push/release, interlock challenge, overlap/active-apply rejection, cancellation,
incomplete files, invalid activation/malformed identity; standard-service fixtures
cover timeouts/unavailable services, rejected parameters, bad fit and time jumps
while subscriptions/cancellation remain responsive. Prompt-2 runtime suite passes.
Opt-in scripts isolate domains/partitions, bound lifetime240s and clean only owned
process groups. Four pandas timing tests pass. SYNTHETIC fixture12 records/no drops
or gaps, partition closes: execution26,000ns/slack974,000ns/artificial±100ns period
error. This is accounting validation, not measured Gazebo/Jetson latency.

## Limitations and recovery

Pause freezes experiment time; long pauses reach explicit wall timeout. Reset via
FULL session shutdown/restart. Actual Fortress time_only reset was fault-injected:
physics/ForceTorque warn on negative dt and stock control stalls until former time
catches up. STRICT deactivation can time out: analysis reports STOP UNVERIFIED,
inhibits force and blocks new actions, NOT a successful stop or zero-force activation.
Full shutdown/restart restores idle analysis/inactive motion/coefficient0. Never
silently resume/re-zero after GUI time reset; missing services cannot prove a stop.

Stock idealized response has ~10ms lag; plateau fitting is not arbitrary-frequency
or physical servo validation. Synchronized read/update stamps do not prove actual
asynchronous sensor sample age. Baseline commands measured position each tick;
reference-world gravity creep is ~20µm over2s (test-bounded), not perfectly frozen
position. Geometry/masses/inertias/travel are provisional. No display is available;
interactive GUI/PlotJuggler curves remain a separate lab check.

Commissioning still requires measured force scales/signs/frame/load path, encoder
polarity/session TF/travel, SI tuning, latency/affinity/bus timing and bounded-stop
checks on Jetson/IgH. Genuine SDK/core/backend regressions were unavailable. Physical
startup and disabled analysis action are gates, not hardware validation.
