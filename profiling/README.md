# A/B cycle profiling

See [verification.md](verification.md) for exact checks, profiler costs, hardware evidence and limitations.

The initial dataset contains supervised no-motion COARSE captures for matched
standalone and profiling-only Controller Manager paths, plus production and
quiet diagnostic configurations. The notebook has been executed in a clean
kernel over the captured runs. These are finite empirical observations, not a
WCET proof or hard-real-time guarantee. The physical evidence in
`docs/physical-bringup.md` and `docs/physical-evidence/` is retained unchanged.

## Scope and comparison labels

A: `matched_hold_runner` and the ROS controller with `hold_only=true` execute
the same ROS-independent `zfc::Shuttle` from `zfc_ethercat_core`. The existing
controller include forwards to that implementation. Hold is a distinct workload
from the default moving Shuttle. Default production parameters remain 10 counts,
1000 updates outward, 1000 return, repeat false, hold_only false. The matched
standalone binary has **no motion option** and no ROS/RCL/DDS dependency.

B: original `zero_force_controller`/DriveLogic has additive profiling probes;
its algorithm, CLI and zero-force behavior are retained. Its wrapper includes
its existing decimated telemetry work. Its noise-window completion contains a
pre-existing formatted `std::cout` call in `FindSetPoint`; the acquisition
boundary must be analyzed separately. No physical DriveLogic trial is authorized
or has been attempted here. B is not a ROS overhead comparison.

C: hardware parameter `diagnostic_mode=production` is the default;
`diagnostic_mode=quiet` suppresses only changed-command record construction and
queue pushes. Faults, startup, safety state, counters and 1 Hz status remain.
The shared diagnostic implementation moved to the ROS-independent core, with a
compatibility include in the hardware package. A no-motion hold emits no
changing commands, so it cannot establish the jitter impact of 2,000 verbose
motion records. That requires an authorized later trial or a separately labelled
synthetic diagnostic-load experiment.

## Exact installed source and scheduler

Locally verified: ROS Humble; ros2_control/Controller Manager/hardware_interface/
controller_interface 2.54.0; IgH 1.5.3 in `/opt/etherlab`; GCC 14.3.0; Cortex-A78AE,
6 CPUs; kernel `5.15.136-rt-tegra`, `/sys/kernel/realtime=1`.
The old root and colcon application flags had **no optimization flag**. New
isolated application builds use GCC 14.3 and RelWithDebInfo (`-O2 -g -DNDEBUG`).
Core assertion tests explicitly use `-UNDEBUG` so optimized testing cannot
silently remove their assertions. Installed CM/RM libraries are distribution
binaries; their exact build flags/compiler are unavailable from their stripped
ELF files (no `.comment` section). Their versions and hashes are recorded,
not represented as locally rebuilt with GCC 14.3.

Inspected upstream **2.54.0**, not Rolling:

- [ros2_control_node.cpp](https://github.com/ros-controls/ros2_control/blob/2.54.0/controller_manager/src/ros2_control_node.cpp), SHA256 `ca6192e765b4ad433e9cd9053ca8209982f6367e301afd7f99620baa3c4eed92`.
- [controller_manager.cpp](https://github.com/ros-controls/ros2_control/blob/2.54.0/controller_manager/src/controller_manager.cpp), SHA256 `2b5218bf6d3c1409ead9bfa84d7241167ea4f7e0abf0665ca20bcfb7af493bee`.
- [resource_manager.cpp](https://github.com/ros-controls/ros2_control/blob/2.54.0/hardware_interface/src/resource_manager.cpp), SHA256 `6f04a609c65b175b9be51af02d5fd6577df614c2e95958a82b79100fb7f01faa`.

There are no matching cycle tracepoints in these sources. CM read/write call
RM sequentially; RM holds `resources_lock_` across component dispatch. Controller
update dispatch uses the installed synchronous implementation.

`zfc_profiling/profile_control_node` links the installed CM library and requires
version 2.54.0 exactly. Its source retains the upstream Apache license and
copies the original initialization and loop. It is **profiling-only** and is
never substituted in `zfc_bringup/local.launch.py`.

Differences from stock:

1. Trace environment parsing, allocation and page touching before `rclcpp::init`.
2. Producer TLS setup before the first loop; record begin/metadata/probes around
   public read/update/write and sleep; a post-write record commit before sleep.
3. A bracketed system-to-monotonic deadline map and a system-time audit sample.
4. After sleep, its RAW exit timestamp is stored into the preceding record.
5. Post-join trace flush. No `/opt/ros` file is modified.

The installed loop uses **accumulated `system_clock` deadlines**, not an absolute
MONOTONIC sleep. The copied executable retains that behavior, the `cm->now()`
call order, period calculation, executor, memory-lock/FIFO/affinity handling,
sim-time branch and shutdown ordering. The profiling hardware continues to use
MONOTONIC application time; standalone retains its scheduled MONOTONIC basis.
Do not silently replace CM scheduling with a monotonic loop and call it stock.
See [schema.md](schema.md) for mapping uncertainty and exclusive partitions.
A stock `ros2_control_node` validation hold was run after the profiling trials;
it reached the same full-ready state and shut down cleanly without faults.

## Build and offline checks

From `/home/jetson/ezra-zfc`:

```bash
source /opt/ros/humble/setup.bash
export ROS_LOCALHOST_ONLY=1
bash profiling/analysis/validate.sh
```

The script creates separate `build/profiling-{off,coarse,fine}` root builds,
`build/profiling-*-colcon` builds and `build/profiling-*-install` overlays. It
runs root and colcon tests in each mode. Do not rebuild an overlay during a
physical trial. Ignore CMake's downstream "ZFC_PROFILING unused" warning: the
setting belongs to the core; its PUBLIC `ZFC_PROFILE_LEVEL` definition is exported
to every linked front end. Verify all final `flags.make` values in each manifest.

Tests cover exact 2000-step sequence and restart, matched hold equivalence
through loaned ROS handles, original fake-IgH faults/readiness/release, quiet-mode
fault behavior, record layout, full-buffer drop/no-overwrite, allocation-free
probe/commit loops, malformed-file rejection and exclusive partition closure.
Append-only storage has no wrap operation. It counts overflow attempts instead.
The fake backend is test-only and is not installed. Its string-based call-order
recording can allocate and is not suitable for measuring production RT overhead.

The new `fake_igh_preload` library can interpose the same fake symbols into the
real standalone executable for an offline smoke test. Always label such records
synthetic; never mistake fake working counter 6 for physical WC4.

## Capturing traces

These variables are read before cycling:

```text
ZFC_TRACE_PATH       absolute output .bin path; must not already exist
ZFC_TRACE_CAPACITY   records, default 180000 (536 bytes each)
ZFC_RUN_ID           nonnegative integer, unique per run
ZFC_VARIANT          1 matched standalone, 2 profiling CM, 3 stock CM, 4 DriveLogic
```

No trace file is written during active cycling. Preserve stdout/stderr separately.
A full buffer drops every subsequent sample without overwriting the first cause;
zero retained-record gaps do not prove the tail was retained. Inspect the header
final drop count. OFF adds no cycle probes and ignores these trace variables.

Prepare a manifest before and after a trial, supplying the **actual RT TID**:

```bash
python3 profiling/analysis/manifest.py profiling/results/RUN/manifest.json \
  --run-id 1 --variant 1 --level COARSE --phase pre-run \
  --build build/profiling-coarse-colcon \
  --binary build/profiling-coarse/matched_hold_runner --pid PID --tid RT_TID
```

The collector records commands and their return codes, versions, source state,
hashes, actual flags, scheduler/priority/affinity, VmLck/limits, process/thread
fault/switch counters, governors/frequency snapshots, IRQ affinities where
accessible, kernel, topology/master state, and explicit unavailable values.
Add controller parameters, observer start/end and phase intervals, motion
observation, warm-up/capture durations, and shutdown/master-release confirmation
to the final run manifest. The collector alone does not establish those facts.
Capture before/after counters for deltas; do not treat process-lifetime counts
as capture-window counts. `/proc/.../sched` was unavailable in this kernel;
CPU sampling detects only a lower bound on migrations. `perf` exists but no
sampling tracer was used in a primary timing trial.

## Hardware gate and remaining work

Read-only preflight outside the sandbox verified the normal `jetson` account's
`realtime`/`ethercat` groups, rtprio 99, unlimited memlock, and unprivileged
SCHED_FIFO/50. Master 0 was Idle/inactive, link UP, exactly EK1100 / ELM3604-0002 /
ClearPath EC in PREOP, zero transmit errors and lost frames.

The pre-existing launch was stopped normally before hardware work. Captures used
the current CPUs 0–5 baseline; CPU 2 was used only for the offline microbenchmark.
Each physical run verified full readiness, zero trace drops, no fault records,
normal shutdown and master release. Run 02 and run 03 are separate production
CM replicates; the standalone and quiet captures are separate variants.

Remaining work is longer repeated holds under controlled representative
CPU/IRQ/background-output load, plus any separately authorized commanded-motion
phase. The current no-motion hold cannot exercise changed-command diagnostic
output, and finite captures cannot establish WCET.
- In-cycle interface-read/write and adapter-validation inner scopes are still
  combined in measured wrapper remainders. Shutdown exchanges and separate
  DriveLogic `CalculateNextCommand` time need finer attribution. The current
  DriveLogic calculation bracket includes FindSetPoint, limit and return policy.
- Measure complete hardware-specific profiler perturbation, not only the
  included coarse probe skeleton. Add matched app samples to the notebook;
  synthetic plots are not an A/B hardware result.
- Motion remains gated by explicit operator review of post-disable displacement,
  braking/restraint, the startup DC warning, clear default envelope and physical
  stop/power removal. No motion request or automatic retry is implemented here.
  Physical DriveLogic motion needs separate authorization.

Do not run two control paths concurrently, use sudo for a controller, change
IgH/PDO/DC/watchdog/drive safety settings, or loosen a guard to obtain clean data.
The pre-existing post-disable displacement and DC warning remain unresolved.

## Notebook

Dependencies are local to `profiling/.venv`, not system packages. This host has
system NumPy/Pandas/Matplotlib/SciPy but no ensurepip; a supported local setup is:

```bash
python3 -m venv --without-pip --system-site-packages profiling/.venv
profiling/.venv/bin/python -m pip install -r profiling/analysis/requirements.txt
ZFC_DATA_DIR=/home/jetson/ezra-zfc/profiling/fixtures \
  profiling/.venv/bin/python profiling/analysis/execute_notebook.py
python3 profiling/analysis/trace.py profiling/fixtures/synthetic-cm/timing.bin \
  profiling/results/fixture.csv
```

Use a real run directory instead of `fixtures` for hardware analysis. The
executor starts a **fresh Jupyter kernel** with a repository-local kernelspec;
it does not modify a user/system registry. Output notebook:
`results/zfc_ab_timing.executed.ipynb`; plots and summary CSV: `results/plots/`.
Raw captures, generated plots/notebooks and virtualenv are ignored by Git.
The two tiny fixtures are deterministic synthetic examples, visibly labelled.

Plots cover histograms, ECDFs, log survival tails, time series/rolling maxima,
exclusive stage distributions and budget shares, FINE nested stages and
correlations. Summary tables retain maximum observed and applicable quantiles.
Confidence intervals resample independent runs only, requiring at least three;
adjacent cycles are not independent experimental replicates. Current A/B
comparison tables require manifest-level matching of conditions by the operator;
they do not yet automatically enforce every fairness constraint.
