# Offline validation

For the current SI checkout and no-IgH Distrobox commands, see
[controller design and current verification](controller-design.md). The records below predate that
interface; full builds require genuine IgH, and fake-IgH plugin tests now require
`-DZFC_HARDWARE_TESTS=ON`.

From the repository root with ROS Humble sourced:

```bash
colcon list --base-paths packages
colcon build --base-paths packages --build-base build/colcon \
  --install-base install --executor sequential --cmake-args -DBUILD_TESTING=ON
source install/setup.bash
ROS_LOCALHOST_ONLY=1 ROS_LOG_DIR=/tmp/zfc-test-log colcon test \
  --base-paths packages --build-base build/colcon --install-base install \
  --executor sequential
colcon test-result --test-result-base build/colcon --verbose
python3 -m unittest discover -s profiling/analysis -p 'test_*.py'
git diff --check
```

Core tests cover PDOs, CiA-402, readiness, command validation and stop sequencing.
Controller tests check each count step, reversal, restart, repetition, invalid
parameters, overflow and period rejection. Plugin tests exercise lifecycle,
interface ownership, hold, faults and the full ramp using a test-only fake IgH
backend. It cannot access a physical master and is not installed. Configuration
tests parse URDF, YAML and launch descriptions without starting nodes.

Timing tests check fixed-capacity storage, drops and allocation-free recording
when probes are enabled. Python tests cover synthetic trace integrity, stage
partitioning, missing deadlines and statistics. See [profiling](../profiling/README.md)
for the probe-level build matrix and schema.

These checks do not establish physical tracking, DC synchronization, watchdog,
limit wiring, STO or mechanical restraint. The [historical ROS commissioning
record](physical-bringup.md) retains the observed post-disable displacement and
DC limitations; it is not a test of the current checkout.

## Cleanup validation — 2026-09-21

Validated on branch `main`, starting at `36fcba8`, without hardware execution.
Fresh build/install directories avoided stale installed files.

```bash
# Run for each level OFF and FINE, with lower=off or fine:
colcon build --base-paths packages --build-base build/cleanup-$lower \
  --install-base build/cleanup-$lower-install --executor sequential \
  --cmake-args -DBUILD_TESTING=ON -DZFC_PROFILING=$level --no-warn-unused-cli
source build/cleanup-$lower-install/setup.bash
ROS_LOCALHOST_ONLY=1 ROS_LOG_DIR=/tmp/zfc-cleanup-test-log colcon test \
  --base-paths packages --build-base build/cleanup-$lower \
  --install-base build/cleanup-$lower-install --executor sequential
colcon test-result --test-result-base build/cleanup-$lower --verbose
```

Both levels built all five packages and reported 30 tests, zero errors,
failures or skips. COARSE built/tested `--packages-select zfc_ethercat_core`
in `build/cleanup-coarse` with `build/cleanup-coarse-install`: two tests passed.
The enabled recorder tests check allocation-free recording and schema-2 output.

Four Python analysis tests passed; the synthetic schema-2 trace exported to CSV.
Both launch descriptions were imported and constructed without starting nodes;
profiling YAML confirmed hold-only operation and unconfigured hardware. Package
and plugin XML, Python sources, notebook JSON/code cells and shell syntax parsed.
`nbformat` was unavailable in the system interpreter; Jupyter was not launched.
Formatting checks on the moved controller/diagnostics code and changed core
lifecycle/timing-test files, local Markdown links and `git diff --check` passed.

The initial sandboxed colcon process stalled after CMake completed; offline
builds/tests succeeded outside the sandbox. Launch parsing initially encountered
a read-only default ROS log directory and passed with `ROS_LOG_DIR` under `/tmp`.
No system configuration or hardware state was changed.
