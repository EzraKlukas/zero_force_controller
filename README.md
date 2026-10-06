# Stage model for review

The SI refactor is now implemented in the package sources. See
[migration, offline checks and Jetson smoke test](docs/si-refactor.md) for the
current contract and calibration requirements. The root-level files below are
preserved review inputs; Gazebo integration remains deferred.

This is a proposed interface/model change, not a drop-in replacement for the current hardware plugin. Reference repository: `EzraKlukas/zero_force_controller`, main `88772b5`, inspected 6 October 2026. The supplied Codex prompt implements the SI refactor; actual Gazebo bringup remains a separate task.

## Proposed controller boundary

| Resource | Command | States | Units |
| --- | --- | --- | --- |
| `carriage` (prismatic joint) | `position` | `position`, `velocity` | m, m/s |
| `load_cell` (force sensor) | none | `force.x`, `force.y`, `force.z` | N |

Limit-switch readings, readiness, CiA-402 state and EtherCAT diagnostics stay in the hardware backend and its existing non-real-time diagnostic output. Joint URDF limits describe travel; physical switch enforcement remains an independent backend check. If future controllers need switch-aware retreat, add a separate `carriage_limits` GPIO contract in both backends then. Merely declaring custom switch states in URDF will not make the stock Gazebo plugin populate them.

Prismatic effort means actuator force in N. It cannot mean motor torque in N m on hardware and force in simulation. Omit the optional effort state until torque scaling and transmission mechanics are verified. Ideal conversion, if x=k*theta, is F=tau/k; friction, efficiency and uncertainty complicate an actual force estimate. The declared URDF effort limit is an illustrative joint constraint, not an exported effort interface or proof of backend enforcement.

## Model assumptions to review

- Vertical travel along base +Z, maximum illustrative stroke 0.50 m; position zero is the lower datum. Actual safe travel must be measured, and the backend must explicitly enforce its limits in Humble.
- Carriage mass 2.0 kg; distal tool 0.20 kg; load-cell body 0.05 kg; rail assembly 5.0 kg. These are placeholders with computed box inertias, not measured values or fitted effective mass.
- The stationary rail is fixed to world. A motor visual suggests the bottom-mounted motor in the photograph; rotor dynamics/transmission are omitted.
- Provisional force path: carriage -> fixed load-cell joint -> tool. The sensor measures forces crossing this joint, including supported distal mass; it does not automatically measure the entire carriage's inertia. Confirm the real load-cell mounting and force path before using this model for calibration.
- Sensor frame +X upward, +Y lateral, +Z toward wall. This keeps the current controller's X force axis aligned with stage travel in the draft only. Verify physical channel mapping and force sign. Gazebo measures parent-on-child wrench expressed in the child frame; the physical backend must match that convention.
- The model is dynamic and world-anchored, not marked static. The fixed sensor joint is preserved during URDF-to-SDF conversion. The tool's fixed joint may merge into its parent, retaining its mass.

## Files

- `urdf/stage.urdf.xacro`: canonical conditional model; intended destination `packages/zfc_bringup/urdf/stage.urdf.xacro`.
- `urdf/stage.gazebo.urdf`: expanded Gazebo version for direct review only. Its absolute YAML paths refer to the review workspace; regenerate from Xacro in the repository rather than checking in this expansion.
- `config/controllers.yaml`: common controller types and target SI parameter schema. Motion scales are unresolved, with calibration disabled. Hardware calibration is also unresolved and must prevent physical configuration until filled.
- `config/hardware.yaml`, `config/gazebo.yaml`: backend settings loaded after shared parameters. Gazebo creates its own manager; never also launch the physical manager for it.
- `config/hardware_calibration.yaml`: deliberately unset installation scales/offsets. Axis sign, persistent encoder datum, raw velocity units and force calibrations cannot be inferred from the photo. No automatic homing or datum acquisition is supplied.
- `CODEX_PROMPT.md`: bounded implementation task to run at the repository root after reviewing this model.

`controllers_file` is the shared controller YAML path, not a directory or glob. The Gazebo plugin accepts multiple `<parameters>` elements, which supplies a clean common-plus-backend split. Launch must pass absolute installed paths and set simulation time on robot_state_publisher and other simulation consumers in the later integration task.

## Validation and future integration

Both installed Xacro selections expand and parse through Humble's control-resource parser. Checks confirm one position command, five shared states, a prismatic carriage, hardware-only calibration parameters and a preserved Gazebo sensor joint. All installed YAML files parse. Invalid backends fail expansion without fallback. These checks do not validate SDF conversion, force signs or simulator runtime.

Full Gazebo integration still needs a world with physics and ForceTorque systems, model spawning, its plugin-created manager, controller startup and /clock bridging. Stock position control is adequate for initial interface tests; it is not a measured ClearPath servo model and must not be treated as validated actuator physics for calibration.

After installation, model expansion is:

```bash
xacro "$(ros2 pkg prefix zfc_bringup)/share/zfc_bringup/urdf/stage.urdf.xacro" \
  backend:=gazebo > /tmp/stage.gazebo.urdf
```

The refactoring task does not install or launch that future simulation stack.

Primary references:

- https://control.ros.org/humble/doc/gz_ros2_control/doc/index.html
- https://control.ros.org/humble/doc/ros2_control/hardware_interface/doc/hardware_interface_types_userdoc.html
- https://control.ros.org/humble/doc/ros2_controllers/force_torque_sensor_broadcaster/doc/userdoc.html
