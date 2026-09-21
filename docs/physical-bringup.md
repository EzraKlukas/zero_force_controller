# Physical bring-up investigation — 2026-09-10

One default moving shuttle run completed, after two successful 30-second
no-motion acceptance holds. No second moving run was attempted. The controller
and hardware were deactivated, the master released, and launch stopped normally.
All positions below are raw ClearPath motor counts.

## Starting state and scope

Repository: `/home/jetson/ezra-zfc` (the directory containing `CMakeLists.txt`,
`packages/` and `README.md`, never `/`). Starting branch `main`, commit
`8acc9ba96a2c0c48569895ff0475f0beb92c1cb3`; origin
`git@github.com:EzraKlukas/zero_force_controller.git`. There were no tracked
changes. The user's untracked, empty file `ros2` was preserved unchanged
(SHA256 `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855`).
Work continued on `debug/ros2-control-physical-bringup`. Instrumentation was
committed as `f3a6590`; the tested startup correction as `e03ca8b`. A subsequent
local documentation commit retains this report and evidence. The final working
tree has no tracked changes; only the original untracked `ros2` remains. No reset, push, package
installation, operating-system change, SDO write, state-force command or
watchdog/limit bypass was performed.

The operator authorized hardware activation and one bounded default trajectory,
confirmed adequate unobstructed travel and verified limits, and had physical
stop/power removal available. An old launch (2816, CM 2817) was inspected with
hardware unconfigured/controller inactive, cleaned up and stopped with SIGINT
before any new master acquisition. Subsequent tests were strictly sequential.
No ROS launch ran as root and no SIGKILL was used.

Installed environment: Ubuntu 22.04.5 ARM64, ROS Humble,
ros2_control/controller_manager/hardware_interface/controller_interface 2.54.0,
pluginlib 5.1.4, IgH 1.5.3 (`/opt/etherlab`), GCC 14.3.0, C++20, kernel
`5.15.136-rt-tegra` PREEMPT_RT. No missing dependencies were found.
The exact unsandboxed normal-user launch shell had `realtime` and `ethercat`
groups, rtprio soft/hard 99 and unlimited soft/hard memlock. The unprivileged
`chrt --fifo 50 sh -c 'chrt --pid $$'` probe succeeded. The dedicated PAM limits
file already contained the four documented realtime limits.
`/dev/EtherCAT0` was `crw-rw---- root ethercat` (489,0). `sudo -n ethercat`
required a password; direct read-only CLI access worked through the existing
group. Initial sandbox group/device visibility differed, so physical inspection
and execution used the authorized normal-user shell outside that sandbox.

## Precise cause and experiments

Blocking EtherCAT startup inside `on_activate()` is incompatible with both
relevant scheduling paths in this installed Controller Manager:

1. **Automatic activation during construction:** the plugin finished enabling
   CSP before Controller Manager performed its memory-locking/thread startup.
   The resulting 108 ms interval without PDO exchange exceeded the ClearPath
   Sync Manager watchdog. The second CM receive reported incomplete WC and
   Switch On Disabled, triggering the plugin's stop/error path.
2. **Manual activation after CM startup:** the same blocking lifecycle exchange
   held Resource Manager serialization for about 15 seconds. When CM resumed,
   its accumulated deadlines caused consecutive catch-up cycles about 89 µs
   apart. The next receive found WC=0 even though the drive still reported
   CSP Operation Enabled. The stale supplied period was 15.3 seconds. The WC
   gate latched first; merely ignoring a large ROS period would not fix this.

The matching installed-version sources explain the ordering and catch-up:
[ros2_control_node.cpp 2.54.0](https://github.com/ros-controls/ros2_control/blob/2.54.0/controller_manager/src/ros2_control_node.cpp)
constructs Controller Manager before starting its cyclic thread and increments
an accumulated next deadline. [System error handling 2.54.0](https://github.com/ros-controls/ros2_control/blob/2.54.0/hardware_interface/src/system.cpp)
transitions to unconfigured after `on_error()` returns SUCCESS. Thus the
unavailable interfaces were a consequence of the hardware I/O error, not the
initial cause or a failure to load the controller.

The causal diagnosis combines measured application/kernel state and the CM
implementation; no wire-level packet capture was performed.

### Instrumentation-only reproduction

Checkpoint `f3a6590` retained the old lifecycle and added first-cause diagnostics.
[Complete automatic launch log](physical-evidence/reproduce-auto.log.txt):

- Activation entered at monotonic `69185726881532` ns and reached readiness at
  `69196551047912` ns: approximately 10.824 seconds of blocking startup.
- Ready snapshot: target/actual 938, WC 4/complete, all slave configs OP,
  mode 8 and Operation Enabled, valid X/Y/Z, neither limit asserted.
- First CM write at `69196659220070` ns; measured activation-to-read handoff
  108,001,625 ns. Its first receive still contained complete WC.
- First cause on read 2/write 1 at `69196659992125` ns: `incomplete_wc`, WC=2,
  statusword 4688 (`0x1250`, Switch On Disabled). Actual consecutive read
  interval was 907,483 ns; supplied period was 1,019,679 ns.
- Kernel at 10:26:30 explicitly reported slave 0-2 AL status `0x001B`,
  **“Sync manager watchdog”**. Read-only registers showed divider 2498 at
  `0x0400` and watchdog time 1000 at `0x0420`: 40 ns × (2498+2) × 1000 = 100 ms.
- `on-error` appeared at read/write 102 after the bounded stop. The hardware
  became unconfigured, withdrawing interfaces. The controller stayed inactive.

[Manual activation experiment](physical-evidence/reproduce-manual.log.txt)
used the same binary, with initial hardware state unconfigured:

- First write followed activation by only 256,552 ns, rejecting a universal
  100 ms handoff delay explanation.
- Second read had WC=0, supplied period 15,302,850,036 ns and actual read
  interval 89,378 ns. Drive remained Operation Enabled/mode 8; slave configs
  remained OP. This identifies a different manifestation of lifecycle blocking.
- The old stop sequence was also compressed by catch-up callbacks.
- The ROS CLI automatically retried its timed-out lifecycle request, causing a
  second **no-trajectory** initialization. That experiment ended with a CLI
  error and normal SIGINT cleanup; it is not counted as a successful hold.
  All subsequent physical tests used a single asynchronous service request
  with no retry and waited for its result.

### Hypothesis ledger

| Hypothesis | Evidence for / against | Test and result | Conclusion |
| --- | --- | --- | --- |
| Missing RT permissions or TS update thread | Earlier environment needed permissions; actual launch shell now has rtprio 99/unlimited memlock | Unprivileged FIFO probe passed; old and new CM update threads observed FF/50 | Not the reproduced first cause |
| Stale overlay | Could explain inconsistent lifecycle behavior | All three package prefixes were this repository's `install/`; mapped libraries and hashes matched freshly built plugins | Rejected |
| Wrong topology/identity | Would prevent correct PDO/WC readiness | Read-only slave inspection and core checks found the expected identities; startup achieved WC4/all OP | Rejected for these runs |
| Blocking lifecycle startup | Startup took 10–19 seconds | Automatic and manual scheduling paths measured separately | Proven upstream cause |
| Watchdog during automatic handoff | Measured 108 ms no-exchange handoff | Read watchdog registers; kernel explicitly reported 0x001B at failure | Proven automatic-path mechanism |
| Stale ROS period alone | Manual second period was 15.3 s | First latched reason was WC=0; drive still CSP; monotonic spacing only 89 µs | Real secondary hazard, insufficient explanation alone |
| CM catch-up after manual activation | Long serialization plus 89/73 µs resumed intervals | Same binary with late activation reproduced WC0; corrected incremental startup removed it | Supported manual-path mechanism |
| Genuine runtime scheduling gap despite FIFO | Plausible under load | Original first-fault interval was 0.907 ms automatic, 0.089 ms manual; corrected motion max 1.137 ms | No >10 ms runtime gap observed; guard retained |
| Transient incomplete WC unrelated to handoff | WC was the first reported failure | Failures aligned exactly with watchdog/catch-up handoffs; corrected runs retained strict WC checks and stayed complete | WC symptom explained; no permission to ignore future loss |
| Drive unexpectedly leaving CSP | Automatic run showed Switch On Disabled | Kernel correlated that loss with watchdog; manual first fault still CSP | Consequence in automatic case, not independent initial fault |
| Invalid ELM sample | Required gate could reject status changes | First-fault samples met original samples/error/TxPDO-state criterion; corrected runs retained it | Rejected as first cause; saturation caveat below |
| Humble error/lifecycle bug | All interfaces vanished | Version-matched error semantics and latched I/O fault explain transition to unconfigured | Expected error consequence |
| Plugin sequencing/readiness gate | Could fault before exchange is valid | Startup now gates readiness by bounded deadline; runtime checks unchanged; fake backend tests sequencing/faults | Old lifecycle exposed runtime gates at an invalid handoff |

## Correction and ownership

Core configuration and master activation are separate lifecycle operations.

The ROS plugin configures resources without activating master/domain exchange.
`on_activate()` activates IgH, obtains memory and arms startup, then returns
without sleeping or a multi-cycle loop. Normal CM read/write calls perform
one receive/process and one PDO/DC/queue/send, advancing the existing CiA-402
logic and mirroring actual position until all readiness gates pass. The
20-second startup deadline remains bounded. Controller activation/claim is
rejected while hardware is not ready. YAML intentionally starts hardware
unconfigured so CM's thread and memory setup precede activation.

Supplied startup periods may include lifecycle work, so actual monotonic entry
intervals are measured separately. The first handoff and actual gaps retain
10 ms bounds. Calls less than 0.5 ms after the preceding exchange cannot send
another frame: startup skips the whole exchange; an active occurrence faults
and sends the stop at the next eligible exchange. This avoids rapid catch-up
sends without another clock/sleep/thread. Full runtime WC, link, slave, CSP,
ELM, command, limit and period gates remain enabled. No controller trajectory
logic, increments, leg lengths, rates, repeat setting or PDO watchdog changed.

Diagnostics retained: explicit first-reason enum and frozen snapshot, lifecycle
phase, monotonic timestamp, read/write counts, ROS period, actual interval,
master/domain/all slave state, CiA-402/status/mode, actual/target, limits, ELM
sample details, claim/sequencing and stop-cycle state. The first fault is
queued only after the first stop command has been sent. A preallocated 4096
record SPSC queue feeds a non-RT consumer; it performs all formatting/output,
never any EtherCAT operations. It records startup/stop/fault events, 1 Hz status
and changed claimed commands, allowing exact replay of this single trajectory.
No DDS was introduced in the control-data path. Diagnostic drops were zero.
Temporary single-request observer scripts lived in `/tmp`; the acceptance
script is retained [as a non-executable text record](physical-evidence/acceptance-session.py.txt).
The archived script's process inventory lists the current ROS executable name.
Archived text logs preserve all lines with trailing whitespace trimmed; original
byte captures remain under ignored `log/physical-bringup/`.
The observer creates a persistent attempt marker before switching the controller active
and has no automatic retry path.

## Offline verification

See [current validation instructions](verification.md). The historical physical
records below describe the ROS hardware commissioning session, not validation
of the current checkout.

## Physical acceptance

The first corrected no-motion test achieved ready after 14.299 seconds of CM
cycles. Activation took 0.668 ms; the first write was 0.366 ms after the armed
event. Target/actual at ready were 938. It held ready for at least 30.699 seconds
in the recorded samples, with WC4, all OP, mode8/Operation Enabled, valid ELM,
limits0/0, unclaimed target and inactive controller. Services responded and
normal deactivate/unconfigure succeeded. [Complete log](physical-evidence/fixed-hold.log.txt)
and [management evidence](physical-evidence/fixed-hold-observer.txt).

Before the sole moving run the overlay was rebuilt and sourced again. Its
hardware plugin SHA256 was and remains
`6d02de8c52bd4eeb02346143b2b4118e54737e41023b43542cf2fc2d00e7601b`.
Mapped hardware/controller libraries came from this repository's symlinked
colcon build; the core came from its install prefix. Actual running parameters
were read through services and checked: 10, 1000, +1, false, 1000 Hz, with both
controller and CM update rates 1000 Hz.

Second startup: activation-enter to armed **0.499 ms**; armed to first write
**0.298 ms**, total enter-to-first-write **0.798 ms**. Read-entry handoff was
0.139 ms. Startup reached ready in **18.624 seconds**, within the unchanged
20-second bound. Ready-to-motion hold was **30.744 seconds**, with every
acceptance condition checked again. CM PID 11208, update TID 11224 was `FF/50`;
`VmLck=1060760 kB`. [Thread and loaded-library evidence](physical-evidence/single-motion-process.txt).

### Exactly one moving round trip

[Complete launch log, including all 2000 changed commands](physical-evidence/single-motion.log.txt),
[management/parameter/initial-position evidence](physical-evidence/single-motion-observer.txt),
and [boundary records](physical-evidence/single-motion-results.json).

| Boundary | Trajectory update | CM read/write count | Target counts | Sampled actual counts |
| --- | ---: | --- | ---: | ---: |
| Activation seed | 0 | read 49370, preceding write 49369 | 938 | 938 |
| First outbound command | 1 | 49371/49371 | 948 | 938 |
| Outbound endpoint/reversal | 1000 | 50370/50370 | 10938 | 10827 |
| First return command | 1001 | 50371/50371 | 10928 | 10837 |
| Command return | 2000 | 51370/51370 | 938 | 1048 |
| Settled final powered hold | still 2000 | 55000/55000 | 938 | 938 |

The controller switch seeds the target during CM update; the first incremental
command occurs on its next update. The 2000 changed commands occupied
consecutive writes with no gaps: exactly +10 for updates 1–1000, then exactly
−10 for 1001–2000. Outbound command endpoint occurred 0.999912383 s after
activation; return leg lasted 1.000032659 s; total to command return was
1.999945042 s. Four subsequent 1 Hz hold records retained command count 2000
and target 938, with settled actual 938; last recorded powered hold was 3.630 s
after command return. No restart occurred.

Encoder feedback demonstrated physical outward and return travel: sampled
actual range during the changing commands was 938–10914. Maximum observed
absolute target minus last actual sample was **115 counts**. This is a sampled
command/feedback discrepancy, including sample timing, not the drive's native
following-error object. Exact actual reversal timing was not separately latched.
Motion-period range was 0.874038–1.132242 ms; monotonic read interval range was
0.870741–1.137202 ms. The maximum interval through later powered hold was
1.188593 ms. Excessive-period observations (>1.5 ms) were zero.

The controller stayed active and claimed only
`clearpath_axis/target_position_counts`. All 2000 records and powered hold
samples reported link up, exactly three slaves, WC4/complete, all configs OP,
CSP Operation Enabled, valid X/Y/Z, limits0/0 and no first fault. No diagnostic
record was dropped. Management services remained responsive, including after
completion. No second controller activation was sent.

### Shutdown and limitations

Controller deactivation succeeded in 3.108 ms and the command interface became
unclaimed. Hardware deactivation took 123.390 ms, including the existing
20-hold/50-shutdown/50-disable sequence and feedback confirmation.
`shutdown-confirmed` recorded complete WC and statusword4688 (`0x1250`, Switch
On Disabled). Cleanup/unconfigure succeeded in 2.765 ms. Launch exited normally.
Final CLI state: master Idle/inactive, link UP, three slaves PREOP, no process
domain and no remaining Controller Manager owner; master transmit errors and lost
frames were zero.

**Post-disable displacement:** final powered hold actual/target were both938;
shutdown confirmation actual was1072, and a later read-only `0x6064:0` upload
reported1077. This is movement after drive holding was removed, outside the
powered trajectory acceptance. Its mechanical cause was not established. Do
not infer that disable voltage mechanically holds this mechanism; review load,
braking/restraint and stop behavior with the operator before further motion.
No attempt was repeated in response to this observation.

The [full kernel log](physical-evidence/kernel-after-tests.txt) is retained,
including intermediate failures. Corrected startup still produced unmatched
startup datagrams and, on the moving-run launch, a “Slave did not sync after
5000 ms” warning before reaching OP. No such warning or WC/drive fault occurred
during accepted ready/motion/hold. After confirmed voltage disable and master
release at 10:46:34, IgH reported a pending AL-state datagram error and ClearPath
watchdog 0x001B while transitioning back to PREOP. This post-release event is
not hidden or counted as a fault-free complete process lifetime. No watchdog
configuration was changed. DC phase/lock quality and release transition deserve
separate commissioning; this test establishes the stated PDO/CSP readiness,
not a measured DC phase bound.

ELM readiness preserves the existing definition: sample count >0, error=0,
TxPDO-state=0. Z reported raw0 with underrange/diag asserted, and other channels
also had diag asserted. These flags are visible in every retained record; this
is not a calibrated or saturation-free analog-input acceptance.

No physical limit collision, forced link loss, watchdog reconfiguration, STO
challenge, repeat trajectory or long-duration load/jitter profiling was performed. Limits/STO/travel were operator-verified prerequisites,
not re-tested by driving into stops. Offline injected faults cover software
responses only. The application remains non-safety-rated. The next physical
step requires operator review of post-disable movement and DC commissioning,
not an automatic repeat of this successful trajectory.

## Reproduction and final repository structure

The [README procedure](../README.md#conservative-physical-test-and-local-bring-up)
contains exact local shell, build, overlay, diagnostics and lifecycle commands.
Run from `/home/jetson/ezra-zfc`; source `/opt/ros/humble/setup.bash` and
`install/setup.bash`, set `ROS_LOCALHOST_ONLY=1`, launch normally, explicitly
activate hardware, wait for startup-ready plus 30 seconds of verified hold,
then deliberately activate the controller once. Stop controller, stop hardware,
verify disable, unconfigure, then Ctrl-C launch. No additional dependencies are
needed on this Jetson. Local-only ROS discovery does not alter IgH master traffic.

See the [README layout](../README.md#layout-and-ownership) for current packages.
