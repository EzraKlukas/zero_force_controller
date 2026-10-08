# Zero-force stage control

ROS 2 Humble transport-independent SI controllers for a vertical stage.
[Controller design, parameters, telemetry and exact offline checks](docs/controller-design.md)
is the current handoff. [SI model/backend notes](docs/si-refactor.md) describe the
boundary; [historical commissioning](docs/physical-bringup.md) is not validation
of this checkout.

Two mutually exclusive plugins share `carriage/position`:
`zero_force_controller` performs empirical compliant motion and
`calibration_sequencer_controller` performs the nominal 1 kHz SI calibration
trajectory with stationary completion. Both consume position/velocity and the
configured force axis. Pure logic headers have no ROS or EtherCAT dependency.
Typed trial telemetry is captured through a bounded preallocated queue.

Canonical model/config/launch sources live only in
`packages/zfc_bringup/{urdf,config,launch}`. The model has one fixed-world,
upward prismatic carriage and a preserved fixed force-sensor joint to the distal
tool. Geometry, masses, 0.5 m model travel and sensor placement are provisional.
No motor torque is exposed as prismatic effort or fictitious sensor torque.

Installation calibration is separate from experiment settings.
Approximate `m_per_count=2e-7` has unverified sign; force sensitivities remain
unset and conventions unconfirmed. Hardware configuration is deliberately
blocked. Hardware startup zero is a frozen stationary session reference, NOT
the model's lower mechanical datum. Optional measured signed hardware bounds
do not inherit the model limits, and the absolute physical TF offset is unknown.
Raw PDO units remain native; velocity defaults to encoder differences over
measured monotonic elapsed time.

Physical launch leaves StageSystem unconfigured and both motion controllers
and both broadcasters inactive. Numeric controller defaults are finite software
tuning, not commissioned gains or assurance of travel clearance. Profiling uses
an inactive hold-only zero-force controller.

Offline OFF/FINE controller/model builds and tests work without IgH; ignore
`zfc_ethercat_core` and `zfc_ethercat_hardware` as documented. Genuine backend
and fake-IgH protection regressions still require the real SDK.

Gazebo integration is deferred. Xacro's prepared Gazebo branch expands/parses
and loads shared controller parameters plus the simulation overlay, but
`local.launch.py backend:=gazebo` exits before creating physical nodes or a
standalone manager. No worlds, spawning, bridges, servo dynamics, fitting node
or analysis coordinator are implemented. This model does not validate calibration
physics, hardware force signs or simulator runtime.
