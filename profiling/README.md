# ROS 2 cycle profiling

The instrumented `profile_control_node` runs Controller Manager's read → update
→ write loop with the same hardware and application plugins as normal bringup.
Its scheduling code follows the installed Humble Controller Manager 2.54.0;
CMake requires that exact version so an upgrade requires reviewing the loop.
The default profiling configuration uses `hold_only=true`. Launch leaves
hardware unconfigured and the controller inactive.

Build from the repository root with ROS Humble sourced:

```bash
colcon build --base-paths packages --build-base build/profile \
  --install-base build/profile-install --executor sequential \
  --cmake-args -DBUILD_TESTING=ON -DZFC_PROFILING=COARSE
source build/profile-install/setup.bash
```

`OFF` removes cycle probes; `COARSE` records manager, hardware, controller and
ramp-calculation boundaries; `FINE` also measures nested EtherCAT API, decoding,
readiness and diagnostic work. Use a separate build/install directory for each
level. Probes perturb execution; no fixed per-clock correction is applied.

For a later supervised collection, set an unused absolute output path and
capacity before launching (these commands do not activate hardware):

```bash
mkdir -p profiling/results/run-01
export ZFC_TRACE_PATH="$PWD/profiling/results/run-01/timing.bin"
export ZFC_TRACE_CAPACITY=180000
export ZFC_RUN_ID=1
ros2 launch zfc_profiling profile.launch.py
```

Follow the [current controller and SI bringup procedure](../docs/controller-design.md)
for hardware readiness, deliberate controller activation, and shutdown. Hold
mode seeds the measured position and never advances either motion logic. Allow capacity
for startup and warmup as well as the desired capture. Stop the controller,
deactivate/unconfigure hardware, then shut down the launch normally. Traces
are written only after the cycle producer stops; SIGKILL loses them. Exclusive
file creation prevents overwriting an existing trace. Buffer exhaustion drops
new samples and records a final drop count.

`ZFC_DIAGNOSTIC_MODE=production` is the default; `quiet` suppresses changed-command
records but retains fault/status diagnostics. Record this setting in the manifest.
There is no cyclic allocation, file writing or background trace consumer.
Controller telemetry has its own bounded queue and non-RT publishing timer;
it is separate from the binary cycle trace. Both motion plugins retain the same
controller/calculation probe boundaries, but profiling launch loads only the
inactive hold-only zero-force plugin. Calibration is a separate plugin, never a
`do_calibrate` parameter. See the controller design for the OFF/FINE no-IgH
build/test commands; full backend regressions still require the genuine SDK.

Capture environment and process metadata before/after a run with:

```bash
python3 profiling/analysis/manifest.py profiling/results/run-01/manifest.json \
  --run-id 1 --level COARSE --diagnostics production --phase hold \
  --build build/profile --binary build/profile-install/zfc_profiling/lib/zfc_profiling/profile_control_node
```

Optional `--pid` and `--tid` add process/thread scheduling, memory and library
information. Set `motion_occurred` from observation; its default `null` means
unknown. Keep terminal diagnostic logs and phase observations with the capture.
The inventory script makes read-only EtherCAT queries; it does not activate a master.

The [schema](schema.md) defines clocks, stages, phase flags and missing data.
`analysis/trace.py INPUT OUTPUT.csv` checks binary integrity and exports fields.
`notebooks/ros2_control_timing.ipynb` reads run directories under `ZFC_DATA_DIR`
and reports period/jitter, execution/slack/overruns, mapped deadlines, stage
statistics, tails and nested EtherCAT timings. `ZFC_PLOT_DIR` sets its output
folder. The optional `analysis/execute_notebook.py` uses a fresh local kernel.
No measured results are committed as part of this workbench.

Lightweight validation needs NumPy and pandas:

```bash
python3 -m unittest discover -s profiling/analysis -p 'test_*.py'
python3 profiling/analysis/fixture.py /tmp/zfc-fixtures
```

The committed `fixtures/synthetic-cm` is artificial data for schema tests only.
Notebook dependencies are listed in `analysis/requirements.txt`. Static notebook
validation is sufficient during code cleanup; running Jupyter or collecting
hardware data is not required. `analysis/validate.sh` runs the offline C++ test
matrix for all three probe levels using the fake IgH test backend.
