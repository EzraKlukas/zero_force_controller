# Timing schema 1

Canonical field order: `packages/zfc_ethercat_core/include/timing_fields.inc`.
Every field is a signed, little-endian 64-bit integer. The C++ record is a
trivially copyable `std::array<int64_t, 67>`: **536 bytes**, alignment 8, no
pointers, strings, floating-point values or implicit padding. The current
writer requires this little-endian host; do not interpret a foreign ABI by
casting arbitrary bytes. Python reads explicit `<i8` values.

The file starts with eight little-endian int64 values (64 bytes):

| Index | Meaning |
|---|---|
| 0 | magic `0x5a464354494d4531` |
| 1 | schema version, 1 |
| 2 | record bytes, 536 |
| 3 | successfully retained record count |
| 4 | final dropped-record count, including a lost tail |
| 5 | profiling level: 1 COARSE, 2 FINE |
| 6 | field count, 67 |
| 7 | reserved, must be zero |

No partial-record salvage is automatic. The converter rejects truncation,
trailing bytes, unsupported layout, mixed identities/levels and nonmonotonic
cycles/timestamps. Gaps and final drops are reported separately. Zero timestamps
mean **unavailable/not executed**, never a measured zero-duration stage.
FINE duration fields are unavailable in COARSE even though their bytes are zero.

## Fields and clocks

`schema`, `run_id`, `variant`, `level`, `diagnostic_mode`, `cycle`, `phase`,
`controller_active` identify samples. Variants: 0 unspecified, 1 matched
standalone, 2 profiling CM, 3 stock CM validation, 4 original DriveLogic.
Diagnostic modes: 0 production, 1 quiet. Phase: 0 inactive, 1 startup, 2 ready
warm-up/unclaimed hold, 3 active matched hold (or DriveLogic acquisition),
4 reserved commanded motion, 5 fault, 6 reserved shutdown. Motion/post-motion
segments require observer labels; phase 3 alone does not prove no movement.
Current lifecycle shutdown exchanges are not committed as cycle records.

`*_entry`, `*_exit` stage timestamps use CLOCK_MONOTONIC_RAW. Fields ending in
`_ns` containing a substage name are integer durations on that clock, except
explicitly named MONOTONIC/system timestamps, actual period and ROS period.

- `deadline_mono_ns`: absolute CLOCK_MONOTONIC deadline; directly scheduled
  in standalone, mapped from system time in profiling CM.
- `cycle_mono_ns`, `write_exit_mono_ns`: CLOCK_MONOTONIC observations.
- `deadline_system_ns`, `cycle_system_ns`, `write_exit_system_ns`: CM system
  clock mapping/audit observations, not a clock for duration subtraction.
- `clock_mapping_window_ns`: MONOTONIC bracket width around the system-clock
  read used to map the CM deadline. Mapping uncertainty is at least half this
  bracket; the mapping does not certify absence of clock steps.
- `actual_period_ns`: RAW hardware-read-entry difference from the preceding
  read record; first record has zero/unknown period.
- `ros_period_ns`: duration supplied by CM; zero/unavailable for standalone.
- `ready`, `fault`, `wc`, `wc_state`, `statusword`, `mode`, `actual_counts`,
  `target_counts`, `command_change`, `reference_sync`, `cpu`, `trace_drops`,
  `diagnostic_drops`: in-cycle state. Fault IDs follow `FaultReason` in
  `diagnostic_sink.hpp`; WC state follows the installed IgH enum. Some
  metadata is sampled before the write, so diagnostic drop changes can first
  appear on the following record. Retain terminal diagnostic logs too.

Definitions (nominal period = 1,000,000 ns):

```
actual_period_i = hardware_read_entry_i - hardware_read_entry_(i-1)
period_error_i = actual_period_i - 1,000,000
active_span_i = hardware_write_exit_i - hardware_read_entry_i
budget_slack_i = 1,000,000 - active_span_i
wakeup_lateness_i = cycle_mono_ns_i - deadline_mono_ns_i
completion_lateness_i = write_exit_mono_ns_i - deadline_mono_ns_i - 1,000,000
deadline_miss_i = completion_lateness_i > 0
```

The stock executable supplies no observable deadline: its lateness/miss fields
are **unknown**. CM-mapped deadline results must retain mapping uncertainty and
be checked for clock steps; `use_sim_time=true` is outside the measurement
protocol. A long actual period is not a completion miss. No clock-cost
subtraction is applied to raw samples. RAW and MONOTONIC can differ slightly
in rate; durations across these clock domains are never subtracted.

## Exclusive CM stack

Implemented in `analysis/trace.py:cm_partition`, valid for exactly one active
controller and one hardware system:

| Stage | Interval(s) |
|---|---|
| Pre-read loop bookkeeping | cycle entry → CM read entry |
| CM/RM read wrapper | CM read entry → hardware read entry **plus** hardware read exit → CM read exit |
| Hardware read body | hardware read entry → hardware read exit |
| Read-to-controller dispatch | CM read exit → controller entry |
| Controller body | controller entry → controller exit |
| Remaining CM update | controller exit → CM update exit |
| Update-to-write dispatch | CM update exit → hardware write entry |
| Hardware write body | hardware write entry → hardware write exit |
| Remaining CM/RM write | hardware write exit → CM write exit |
| Post-write bookkeeping | CM write exit → sleep entry |

The stack closes to cycle entry → sleep entry. It includes parameter-time
sampling around the public calls, dispatch, and probe perturbation. CM/RM
orchestration is measured in wrapper/dispatch intervals, not inferred as all
A/B difference. Internal RM mutex wait cannot be separated without additional
library probes. The hardware-read-return-to-controller gap excludes the
already-accounted read-wrapper return portion.

Sleep entry → sleep exit is separate: it includes commit and scheduling wait;
subtract the measured commit interval to present an approximate wait-only
component. The small after-commit/before-sleep dispatch is not separately
probed. `sleep_exit` is filled after wake into the previously committed slot;
there is no consumer before all producers stop. No idle interval is called
framework overhead. Standalone sleep boundaries currently remain unavailable.

Hardware adapter read/write remainder is body minus corresponding core body.
Controller wrapper remainder is body minus Shuttle/DriveLogic calculation.
These are nested partitions; they must not be stacked again alongside parent
hardware/controller bodies. The current controller remainder combines state
handle access, command handle writes and validation. It does not yet split
those individual operations. Likewise adapter validation/safety is currently
a remainder, not a separately clocked inner scope.

FINE read: application-time API, master receive API, domain process, ELM PDO
decode, motor PDO decode, state polling, readiness calculation. FINE write:
PDO encoding, conditional reference synchronization, slave synchronization,
domain queue, master send API. Diagnostics: record construction and SPSC push.
Core totals also include untimed state copies, branch work and probe cost.
Receive/send are application/kernel API times, **not wire transit time**.

`commit_exit - commit_entry` measures retained-record copy plus its clock
bracket. Complete instrumentation additionally costs record initialization,
all clock/CPU reads, scalar stores and dispatch. The included microbenchmark
is an explicitly named probe skeleton; it is not yet a measurement of the
entire hardware-specific profiler perturbation.

## Storage and concurrency

A single serialized cycle producer writes an append-only preallocated array.
Capacity defaults to 180,000 records (96,480,000 bytes, about 92 MiB), with a
hard configuration limit of 2,000,000. It never wraps or overwrites earlier
records: every attempt after capacity increments a drop counter. Allocate
startup + warm-up + capture + shutdown margin, not just the capture interval.
Allocation and page touching happen before activation. Cycle code performs no
new allocation, mutex acquisition, formatting, file I/O, ROS publication or
DDS calls. The existing diagnostic SPSC consumer remains independent.

Trace serialization is post-run only. Normal shutdown is required; SIGKILL
loses the in-memory trace. First-cause production diagnostics remain separately
queued/printed. Output uses exclusive file creation to avoid overwriting prior
evidence. No background trace writer adds file-I/O load to the trial.
