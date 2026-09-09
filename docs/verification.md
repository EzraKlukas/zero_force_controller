# Verification record — 2026-09-09

## Git and environment

Started with a clean working tree on `main` at
`50a64c6c7dbf8ebe3cc9e3580263f03cfbc5210e`. `origin` is
`git@github.com:EzraKlukas/zero_force_controller.git`. Fetched `origin/main`
before any source edits and created `ros2-control-integration` at that commit.
No networking proof-of-concept branch was merged. Nothing was pushed.
A second fetch at completion confirmed `origin/main` still points to the same
commit, which is also the implementation branch's merge base.

Local implementation checkpoints:

- `65d73fd`: extract shared ROS-independent EtherCAT core and retain standalone.
- `81236c8`: add synchronous Humble hardware/controller/bring-up and offline tests.
- The following documentation commit records this verification and runbook;
  `git log -3 --oneline` identifies all three local checkpoints.

Observed environment: Ubuntu 22.04.5 ARM64; ROS Humble; ros2_control,
controller_manager, hardware_interface and controller_interface 2.54.0;
pluginlib 5.1.4; GCC 14.3; IgH `/opt/etherlab`; PREEMPT_RT kernel
`5.15.136-rt-tegra`. Inspected the installed Humble lifecycle, interface export,
controller update and pluginlib export APIs before implementation, and checked
matching versioned Controller Manager/Resource Manager source for cycle order,
lifecycle serialization and supported runtime parameters.

No system packages or OS settings were changed. The build dependencies were
present. The session has no `/dev/EtherCAT*` device exposed. No real master was
requested and no physical motion test or live launch was performed.

## Executed checks

| Command/check | Result |
| --- | --- |
| `git status --short`, `git branch --show-current`, `git rev-parse HEAD`, `git remote -v` | Initial tree clean; expected repository/main commit confirmed. |
| `git fetch origin main`, `git switch -c ros2-control-integration origin/main` | Requested branch created from fetched main. |
| `printenv ROS_DISTRO`, `/etc/os-release`, installed headers and `dpkg-query -W` | Humble/Ubuntu and APIs verified before coding. |
| `cmake -S . -B build/compat -DBUILD_TESTING=ON` | Success. |
| `cmake --build build/compat -j2` | Success after final core changes. |
| `ctest --test-dir build/compat --output-on-failure` | 1/1 CTest entry passed. |
| `build/compat/zero_force_controller --help` | Exit 0; help path returns before constructing/configuring the core. |
| `colcon list --base-paths packages` | All five intended packages discovered. |
| `colcon build --base-paths packages --build-base build/colcon --install-base install --executor sequential --cmake-args -DBUILD_TESTING=ON` | All five packages built and installed successfully. |
| `source install/setup.bash` then installed standalone `--help` | Exit 0. |
| `ldd` on compatibility and installed standalone executables | Only core, IgH and platform C/C++ libraries; no rclcpp, controller_manager or DDS. |
| `readelf -d install/zfc_ethercat_core/lib/libzfc_ethercat_core.so` | Installed RUNPATH includes discovered `/opt/etherlab/lib`. |
| Ament index queries for `hardware_interface__pluginlib__plugin` and `controller_interface__pluginlib__plugin` | Both installed plugin descriptions discovered. |
| `colcon test --base-paths packages --build-base build/colcon --install-base install --executor sequential --event-handlers console_direct+` | All suites passed after fixes. |
| `colcon test-result --test-result-base build/colcon --verbose` | **21 tests, 0 errors, 0 failures, 0 skipped** (includes CTest suite entries). |
| ElementTree parsing of all package/plugin XML and real Humble URDF parser | Passed. |
| Bring-up pytest: YAML, URDF, launch import and LaunchDescription construction | Passed without starting nodes. |
| `clang-format --dry-run --Werror` on new C++ sources/headers | Passed. No pre-existing formatter/linter/CI configuration was present. Preserved slave/DriveLogic files were not reformatted. |
| `git diff --check` | Passed. |
| Search of packages/runbook for VPN code or fixed remote addresses | No matches. |

The test run used `ROS_LOCALHOST_ONLY=1` and
`ROS_LOG_DIR=/tmp/zfc-offline-ros-log`. Colcon build/test needed execution
outside the tool sandbox: sandboxed colcon runs stalled waiting for already
completed CMake subprocesses. The exact same workspace build progressed
normally outside the sandbox. That execution only built repository artifacts
and ran offline tests; it did not install packages or configure real hardware.

Intermediate failures were corrected, not ignored: exported CMake target
namespace, a missing integration-test include, installed IgH RUNPATH, and a
test expecting the old target instead of the latest measured hold position.
The final test-result report above is from the corrected installed artifacts.
A spawner `--help` attempt inside the sandbox hit its read-only ROS log path;
the supported flags were checked from installed spawner source instead. The
ROS CLI controller/hardware state command help succeeded.

## Offline coverage

The 18 individual cases are represented by four CTest entries (the colcon
summary also counts wrappers):

- Core/slave test: CiA-402 enable words and seed behavior, readiness including
  EK1100 OP and ELM validity, signed PDO encoding/decoding, packed ELM status
  fields, raw/logical digital inputs, integer command validation, overflow,
  increment/limit rejection, shutdown phase boundaries and repeated release.
- Four trajectory cases: every default command and exact reversal/final hold,
  restart at a new position, negative direction/repetition, measured-period
  observations and rejection, invalid parameters, and both int32 endpoints.
- Twelve plugin/integration cases: installed pluginlib loading; `on_init`
  without master access; loaned state/command handles; shared core cycle/DC
  ordering and single ownership; hold on command unclaim; invalid/excessive
  commands; communication/drive/ELM loss; limit rejection; bounded startup
  timeout; partial configure failures and release exactly once; and real
  Humble Resource Manager `read → plugin update → write` through all 2000
  commands plus final hold.
- Python configuration case: 25 states and one command, default YAML settings,
  installed package discovery and three launch actions.

`zfc_bringup/test/fake_igh.cpp` interposes **all ecrt symbols used by the core**
in the test executable. It supplies an in-memory domain and simulated feedback;
it cannot open a device. It is not installed and is never linked into any
runtime target. Configuration/read/write tests execute the production shared
core and loaded plugins against this backend, not a copy of their sources.

## Not run / physical acceptance still required

- No real `ethercat master/slaves` or physical Controller Manager launch:
  the sandbox exposes no EtherCAT device and this work intentionally avoids
  requesting physical master ownership or enabling motion.
- No 1 kHz physical DC lock/jitter, drive tracking or position-scale validation.
- No limit wiring, travel-envelope, STO, drive watchdog, communication-loss or
  loaded-mechanism shutdown test. The simulated backend does not prove these.
- No scheduling/memory-lock success under final deployment permissions or
  representative Jetson load. This shell's `ulimit -r` is 0; administrator
  provisioning and verification are required before enabling motion.
- No full A/B profiling, telemetry broadcaster, remote networking or SI
  calibration; these are intentionally outside this pass.

The [README](../README.md) contains the final package tree, ownership and
lifecycle decisions, exact build/dependency/Jetson commands, expected output,
and conservative physical acceptance checklist. Physical validation remains
a commissioning requirement; offline success is not a safety certification.
