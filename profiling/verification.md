# Profiling evidence — 2026-09-14

Status: offline validation and supervised no-motion hardware characterization
completed. Motion profiling was not run. The pre-existing launch was stopped
with the authorized normal SIGINT and every profiling process released master 0
normally; final read-only checks showed master Idle/inactive, three PREOP slaves,
link UP, zero lost frames and zero EtherCAT errors.

Dedicated branch: `profiling/ab-cycle-timing`. Implementation/tests commit:
`2a4ddb3`; analysis/schema/documentation commit: `c201cd8`; hardware-launch and
matched-controller updates are uncommitted pending final review. Nothing was
pushed. Existing physical evidence documentation remains unchanged.

## Executed validation

| Check | Result |
|---|---|
| Original root RelWithDebInfo build/CTest | 1/1 passed |
| Original five-package colcon suite | 26 reported tests, no failures/errors/skips |
| Final OFF root / colcon | 2/2 and 29 reported tests passed |
| Final COARSE root / colcon | 2/2 and 29 reported tests passed |
| Final FINE root / colcon | 2/2 and 29 reported tests passed |
| Converter/fixture unit tests | 3/3 passed |
| OFF core read/write disassembly | no profiling calls |
| Matched standalone ldd | core, IgH, platform C/C++; no ROS/RCL/DDS |
| Fresh-kernel notebook on fixtures | all cells executed; 9 PNG plots and summary CSV generated |
| Fake-IgH original DriveLogic executable, 3 s capture | 3,003 records, 0 trace drops, 0 missing cycles, 0 fault records |
| Fake-IgH matched executable, 30 s warm-up + 1 s capture | 31,004 records, 0 trace drops, 0 missing cycles, 0 faults; shutdown confirmed, diagnostic drops 0 |
| FINE fake-IgH RM/controller test | 2,015 records, 2,000 exact command changes, 0 trace drops/missing cycles/fault records; all nested probes nonzero on applicable cycles |

All executable fake runs used in-memory IgH interposition. They are functional
checks, not an empirical measurement of hardware cycle feasibility. The fake
backend records order with `std::string`, so its API timings are not production
transport timings. The FINE RM test does not execute the outer CM loop and does
not validate the copied profiling CM executable against stock.

Root/colcon build scripts and command outputs are retained in ignored
`profiling/results/preflight/`. The final reusable command is:

```bash
cd /home/jetson/ezra-zfc
bash profiling/analysis/validate.sh
python3 -m unittest discover -s profiling/analysis -p 'test_*.py'
ZFC_DATA_DIR=/home/jetson/ezra-zfc/profiling/fixtures \
  profiling/.venv/bin/python profiling/analysis/execute_notebook.py
python3 profiling/analysis/trace.py profiling/fixtures/synthetic-cm/timing.bin \
  profiling/results/fixture.csv
```

Colcon ran outside the sandbox after the initial sandbox subprocess stall.
The first COARSE test inventory omitted the new timing test due to a stale
CTest file; forced CMake reconfiguration and rerun brought it to 29. The
validation script now passes `--cmake-force-configure`. Intermediate parallel
builds encountered an old installed probe header while that API was being
edited; all final builds/tests used the refreshed headers and passed.

Notebook dependencies were installed only into `profiling/.venv`. The host has
no ensurepip, so venv creation used `--without-pip --system-site-packages` and
the existing system pip module. The initial latest matplotlib-inline package
was incompatible with host Matplotlib 3.5.1; pinning 0.1.7 fixed execution. The
kernel needed localhost sockets outside the sandbox. No system package,
PAM/limits, kernel, governor, IRQ, EtherCAT or safety setting was changed.

## Preliminary profiler cost

Pinned **CPU 2**, ordinary SCHED_OTHER scheduling, memory locked; 100,000
iterations per build. These are microbenchmarks, separate from an untuned
hardware baseline. Trace record = **536 bytes**. At benchmark capacity 100,000,
each trace buffer = 53,600,000 bytes; default runtime capacity 180,000 requires
96,480,000 bytes, in addition to other application memory. The benchmark also
allocates a separate copy-test buffer and four sample vectors before timing.

Final COARSE measurements, raw ns (two bounding clock reads retained):

| Operation | Mean | Median | p99 | Maximum observed |
|---|---:|---:|---:|---:|
| Adjacent RAW clock pair delta | 56.329 | 64 | 96 | 16,992 |
| Empty record append/copy | 129.591 | 96 | 448 | 28,992 |
| COARSE probe skeleton + begin/commit | 1,079.830 | 1,024 | 1,408 | 120,608 |
| Noinline matched hold calculation | 57.260 | 64 | 96 | 672 |

Zero minor/major page faults and zero voluntary context switches in each final
measured window; 22 involuntary switches in COARSE and 69 in FINE. Trace drops
were zero. FINE build running the **same COARSE skeleton**, not its additional
hardware subprobes: mean 1,088.973 ns, median 1,024 ns, p99 1,408 ns, maximum
117,024 ns. This is not a claim that complete FINE instrumentation costs that
amount. Complete per-front-end profiler perturbation remains to be measured.
No sample was adjusted by subtracting mean clock cost.

Earlier trials are retained too: the largest skeleton observation across the
four preliminary/final 100,000-iteration trials was **640,352 ns**. Do not hide
that tail by quoting only the final lower maximum. Ordinary scheduling and
concurrent background/build activity were present in these microbenchmarks.
They are not FIFO/50 feasibility trials, independent controlled replicates, or
WCET evidence. The small hold calculation is near the timestamp resolution.

Exact benchmark command pattern (choose a fresh output path each time):

```bash
ZFC_TRACE_PATH=/home/jetson/ezra-zfc/profiling/results/preflight/overhead-coarse-final.bin \
ZFC_TRACE_CAPACITY=100000 taskset -c 2 build/profiling-coarse/profiler_bench
```

Final JSONs: `results/preflight/overhead-{coarse,fine}-final.json`; earlier
JSONs omit `-final`. Their corresponding `.bin` traces are retained, ignored.

## Evidence paths and limits

- Host inventory, versions, scheduling, affinity, locked memory, topology,
  hashes and flags: `results/preflight/environment.json`.
- Fake executable traces/logs/manifests:
  `results/offline-matched/`, `results/offline-drivelogic/`,
  `results/offline-plugin-fine/`.
- Committed small examples: `fixtures/synthetic-{standalone,cm}/`.
- Notebook source: `notebooks/zfc_ab_timing.ipynb`.
- Executed synthetic notebook: `results/zfc_ab_timing.executed.ipynb`.
- Synthetic plots/statistics: `results/plots/`.

## Hardware no-motion evidence

All captures used RelWithDebInfo, COARSE probes, SCHED_FIFO priority 50 when the
kernel permitted it, the existing EtherCAT topology, full readiness, actual
position hold at 838 counts, `ROS_LOCALHOST_ONLY=1`, zero trace drops and zero
fault records. Each process was stopped with SIGINT and printed
`shutdown-confirmed`; master release was verified afterward. The stock
`ros2_control_node` validation reached the same ready state and shut down
cleanly without a profiler trace.

| Run | Records / active cycles | period error p99 / max (ns) | active span p99 / max (ns) | misses |
|---|---:|---:|---:|---:|
| matched standalone, production | 100,870 / 90,000 | 11,818 / 105,792 | 53,152 / 81,984 | 0 |
| profiling CM, production (run 03) | 95,723 / 35,239 | 20,576 / 123,072 | 71,700 / 228,736 | 0 |
| profiling CM, quiet diagnostics | 140,700 / 56,157 | 18,368 / 41,184 | 69,088 / 83,744 | 0 |

The production CM run has fewer active cycles because controller activation was
performed after hardware readiness; run 02 is retained as a second production
replicate (37,657 active cycles). Hold-only makes no command changes, so physical
diagnostic construction/push samples are zero in both diagnostic modes; the
fake-IgH FINE fixture exercises 2,000 changed-command records without motion.

For the matched production CM run 03, mean exclusive stages were: CM bookkeeping
1,021 ns before read, read wrapper 1,637 ns, hardware read 16,697 ns, dispatch to
controller 3,329 ns, controller 429 ns (Shuttle calculation 166 ns), remaining
update 347 ns, dispatch to write 1,060 ns, hardware write 7,152 ns, remaining
write 385 ns and post-write bookkeeping 196 ns. These are measured partitions;
the total A/B difference also includes scheduler lateness, adapter work and
unexplained residual and is not labelled ROS overhead.

The standalone matched run had mean active span 20,725 ns; CM run 03 had
29,347 ns. Maximum observed values are finite-sample observations, not WCET or
hard-real-time proof. The tested no-motion tails left roughly 0.9 ms of active
budget and had no mapped deadline misses, but longer controlled background-load
replicates and commanded-motion phases remain the most valuable next stress test.

Raw traces and manifests are under ignored `profiling/results/hw-*`; the
executed notebook and hardware plots are under ignored
`profiling/results/zfc_ab_timing.executed.ipynb` and
`profiling/results/plots-hardware/`. Motion remains gated by the physical
confirmation requirements in the task and was not performed.
