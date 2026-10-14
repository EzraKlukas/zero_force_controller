from pathlib import Path
import importlib.util
import math
import xml.etree.ElementTree as ET
import pytest
import xacro
import yaml

ROOT = Path(__file__).resolve().parents[1]


@pytest.mark.parametrize("backend", ["ethercat", "gazebo"])
def test_model(backend):
    robot = ET.fromstring(xacro.process_file(str(ROOT / "urdf/stage.urdf.xacro"),
                                            mappings={"backend": backend}).toxml())
    system = robot.find("ros2_control")
    assert system.attrib == {"name": "StageSystem", "type": "system"}
    assert len(robot.findall("ros2_control")) == 1
    assert [(j.attrib["name"], j.attrib["type"]) for j in robot.findall("joint")
            if j.attrib["type"] != "fixed"] == [("carriage", "prismatic")]
    assert robot.find("joint[@name='world_to_base']/parent").attrib["link"] == "world"
    joint = robot.find("joint[@name='carriage']")
    assert joint.find("axis").attrib["xyz"] == "0 0 1"
    assert float(joint.find("limit").attrib["lower"]) == (-.25 if backend == "gazebo" else 0.)
    assert len(system.findall(".//command_interface")) == 1
    assert len(system.findall(".//state_interface")) == 5
    assert [s.attrib["name"] for s in system.findall("sensor/state_interface")] == [
        "force.x", "force.y", "force.z"]
    assert system.find("joint/command_interface").attrib["name"] == "position"
    assert system.find(".//state_interface[@name='effort']") is None
    sensor_joint = robot.find("joint[@name='load_cell_joint']")
    assert sensor_joint.attrib["type"] == "fixed"
    assert sensor_joint.find("child").attrib["link"] == "load_cell_link"
    assert robot.find("joint[@name='tool_mount']/parent").attrib["link"] == "load_cell_link"
    # rpy=(0,-pi/2,0) maps local +X to world +Z.
    pitch = float(sensor_joint.find("origin").attrib["rpy"].split()[1])
    assert math.isclose(-math.sin(pitch), 1)
    plugin = system.find("hardware/plugin").text
    if backend == "gazebo":
        assert plugin == "gz_ros2_control/GazeboSimSystem"
        assert system.findall("hardware/param") == []
        assert [float(p.text) for p in system.findall("joint/command_interface/param")] == [-.25, .25]
        assert float(joint.find("limit").attrib["velocity"]) == .2
        assert robot.find("gazebo[@reference='tool_mount']/preserveFixedJoint").text == "true"
        sensor = robot.find("gazebo[@reference='load_cell_joint']")
        assert sensor.find("preserveFixedJoint").text == "true"
        assert sensor.find("sensor/force_torque/frame").text == "child"
        parameters = robot.findall("gazebo/plugin/parameters")
        assert len(parameters) == 2
        assert all(Path(p.text).is_absolute() for p in parameters)
        assert [Path(p.text).name for p in parameters] == ["controllers.yaml", "gazebo.yaml"]
    else:
        assert plugin == "zfc_ethercat_hardware/EthercatHardware"
        assert robot.findall("gazebo") == []
        assert system.findall("joint/command_interface/param") == []
        hardware = {p.attrib["name"]: p.text for p in system.findall("hardware/param")}
        assert hardware["m_per_count"] == "2e-07"
        assert hardware["velocity_from_encoder"] == "true"
        assert "encoder_zero_counts" not in hardware


def test_invalid_backend_rejected():
    with pytest.raises(xacro.XacroException):
        xacro.process_file(str(ROOT / "urdf/stage.urdf.xacro"),
                           mappings={"backend": "typo"})
    with pytest.raises(xacro.XacroException):
        xacro.process_file(str(ROOT / "urdf/stage.urdf.xacro"),
                           mappings={"backend": "gazebo", "controllers_file": "relative.yaml"})


def test_configuration():
    configs = {p.stem: yaml.safe_load(p.read_text()) for p in (ROOT / "config").glob("*.yaml")}
    shared = configs["controllers"]
    assert shared["controller_manager"]["ros__parameters"]["update_rate"] == 1000
    assert "hardware_components_initial_state" not in shared["controller_manager"]["ros__parameters"]
    hw = configs["hardware"]["controller_manager"]["ros__parameters"]
    assert hw["hardware_components_initial_state"] == {"unconfigured": ["StageSystem"]}
    assert "hardware_components_initial_state" not in configs["gazebo"]["controller_manager"]["ros__parameters"]
    params = shared["zero_force_controller"]["ros__parameters"]
    assert "do_calibrate" not in params
    assert params["inertial_force_coefficient_kg"] == 0
    calibration = shared["calibration_sequencer_controller"]["ros__parameters"]
    assert calibration["center_zone_half_width_m"] == 0.0002
    assert calibration["base_velocity_mps"] == 0.1
    assert calibration["jerk_mps3"] == 1000.0
    assert calibration["initial_acceleration_mps2"] == 0.2
    assert calibration["acceleration_increment_mps2"] == 0.2
    assert calibration["max_acceleration_mps2"] == 2.0
    installation = configs["hardware_calibration"]
    assert installation["m_per_count"] == 2e-7
    assert installation["conventions_confirmed"] is False
    assert installation["soft_bounds_enabled"] is False
    assert "encoder_zero_counts" not in installation
    force = shared["load_cell_broadcaster"]["ros__parameters"]
    assert "sensor_name" not in force
    assert force["interface_names"] == {"force": {
        "x": "load_cell/force.x", "y": "load_cell/force.y", "z": "load_cell/force.z"}}


def test_optional_velocity_offsets_and_invalid_installation_boolean(tmp_path):
    calibration = yaml.safe_load((ROOT / "config/hardware_calibration.yaml").read_text())
    calibration.pop("velocity_mps_per_raw_unit")
    path = tmp_path / "installation.yaml"
    path.write_text(yaml.safe_dump(calibration))
    robot = ET.fromstring(xacro.process_file(str(ROOT / "urdf/stage.urdf.xacro"),
        mappings={"hardware_calibration_file": str(path)}).toxml())
    assert robot.find("ros2_control/hardware/param[@name='force_x_zero_counts']").text == "0.0"
    calibration["soft_bounds_enabled"] = "typo"
    path.write_text(yaml.safe_dump(calibration))
    with pytest.raises(xacro.XacroException):
        xacro.process_file(str(ROOT / "urdf/stage.urdf.xacro"),
            mappings={"hardware_calibration_file": str(path)})


def test_launch_gazebo_and_invalid_backend_exit_before_nodes():
    spec = importlib.util.spec_from_file_location("zfc_launch", ROOT / "launch/local.launch.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    for backend, message in (("gazebo", "simulation_nodes"), ("typo", "invalid")):
        with pytest.raises(RuntimeError, match=message):
            module.build_physical_nodes(backend, "/unused", "/unused", "/unused")


def test_world_bridge_and_simulation_only_policy():
    world = ET.parse(ROOT / "worlds/stage.sdf").getroot().find("world")
    assert float(world.find("physics/max_step_size").text) == .001
    assert {p.attrib["filename"] for p in world.findall("plugin")} >= {
        "ignition-gazebo-physics-system", "ignition-gazebo-user-commands-system",
        "ignition-gazebo-scene-broadcaster-system", "ignition-gazebo-forcetorque-system"}
    bridges = yaml.safe_load((ROOT / "config/bridges.yaml").read_text())
    clock = next(b for b in bridges if b["ros_topic_name"] == "/clock")
    assert clock["direction"] == "GZ_TO_ROS"
    assert clock["gz_type_name"] == "ignition.msgs.Clock"
    for name in ("zero_force_controller", "calibration_sequencer_controller"):
        assert yaml.safe_load((ROOT / "config/gazebo.yaml").read_text())[name]["ros__parameters"]["finite_fault_hold"] is True
        assert yaml.safe_load((ROOT / "config/hardware.yaml").read_text())[name]["ros__parameters"]["finite_fault_hold"] is False


def test_plot_layout_contract():
    root = ET.parse(ROOT.parent / "zfc_operator/plot/stage.xml").getroot()
    plugin = root.find("Plugins/plugin")
    assert plugin.attrib["ID"] == "ROS2 Topic Subscriber"
    assert plugin.find("use_header_stamp").attrib["value"] == "true"
    assert plugin.find("selected_topics").attrib["value"] == "/plot/measured;/plot/zero_force;/plot/calibration;/calibration_analysis/state"
    assert root.find("previouslyLoaded_Streamer").attrib["name"] == "ROS2 Topic Subscriber"
    plotted = {c.attrib["name"] for c in root.findall(".//Tab//curve")}
    assert root.find(".//plotmatrix") is None
    for topic in ("zero_force", "calibration"):
        assert f"/plot/{topic}/inertial_compensation_n" in plotted
        assert f"/plot/{topic}/state/reference_acceleration_mps2" in plotted
        assert f"/plot/{topic}/state/phase" in plotted


@pytest.mark.parametrize('backend', ['ethercat', 'gazebo'])
@pytest.mark.parametrize('relay,plot', [(False, False), (True, False), (True, True), (False, True)])
def test_launch_backend_time_and_gui_independence(backend, relay, plot):
    from ament_index_python.packages import get_package_share_directory
    from launch import LaunchContext
    from launch_ros.actions import Node
    from launch_ros.utilities import evaluate_parameters
    spec = importlib.util.spec_from_file_location('bringup_launch', ROOT/'launch/local.launch.py')
    module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module)
    share = Path(get_package_share_directory('zfc_bringup'))
    if backend == 'ethercat':
        actions = module.build_physical_nodes(backend, str(share/'config/controllers.yaml'), str(share/'config/hardware.yaml'),
            str(share/'config/hardware_calibration.yaml'), relay=relay, plot=plot)
    else:
        try:
            module.gazebo_dependencies()
        except RuntimeError as error:
            pytest.skip('optional Gazebo runtime not built/sourced: '+str(error))
        actions = module.simulation_nodes(str(share/'config/controllers.yaml'), False, plot, .2, relay=relay)
    context = LaunchContext()
    nodes = [n for n in actions if isinstance(n, Node)]
    packages = [n.node_package for n in nodes]
    assert packages.count('zfc_calibration_analysis') == 1
    assert sum(n.node_executable == 'plot_relay' for n in nodes) == int(relay)
    if plot and not relay:
        helper = next(n for n in nodes if n.node_executable == 'operator_panel')
        assert evaluate_parameters(context, helper._Node__parameters)[0]['use_sim_time'] == (backend == 'gazebo')
    assert packages.count('plotjuggler') == int(plot)
    analysis = next(n for n in nodes if n.node_package == 'zfc_calibration_analysis')
    evaluated = evaluate_parameters(context, analysis._Node__parameters)
    assert evaluated[-1]['use_sim_time'] == (backend == 'gazebo')
    if backend == 'ethercat':
        assert 'zfc_simulation' not in packages and 'ros_gz_bridge' not in packages
        assert 'known_downstream_mass_kg' not in evaluated[-1]
        assert str(evaluated[0]).endswith('hardware.yaml')
        manager = next(n for n in nodes if n.node_executable == 'ros2_control_node')
        parameters = evaluate_parameters(context, manager._Node__parameters)[-1]
        assert list(parameters['hardware_components_initial_state.unconfigured']) == ['StageSystem']
        assert parameters['use_sim_time'] is False


def test_analysis_override_and_network_validation(tmp_path):
    from launch import LaunchContext
    from launch_ros.utilities import evaluate_parameters
    from zfc_operator.launch_helpers import network_actions
    spec = importlib.util.spec_from_file_location('bringup_launch', ROOT/'launch/local.launch.py')
    module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module)
    custom = tmp_path/'reviewed.yaml'; custom.write_text('calibration_analysis: {ros__parameters: {backend: ethercat}}')
    node = module.analysis_node(False, analysis_file=str(custom))
    assert str(evaluate_parameters(LaunchContext(), node._Node__parameters)[0]) == str(custom)
    with pytest.raises(RuntimeError, match='absolute'):
        module.analysis_node(False, analysis_file='relative.yaml')
    custom.write_text('calibration_analysis: {ros__parameters: {backend: gazebo}}')
    with pytest.raises(RuntimeError, match='backend'):
        module.analysis_node(False, analysis_file=str(custom))
    with pytest.raises(ValueError):
        network_actions('invalid')


@pytest.mark.parametrize('enabled', [None, '0', '1'])
def test_optional_simulation_manifest(enabled):
    from catkin_pkg.package import parse_package
    package = parse_package(str(ROOT/'package.xml'))
    package.evaluate_conditions({} if enabled is None else {'ZFC_WITH_SIMULATION': enabled})
    dependencies = {d.name for d in package.exec_depends if d.evaluated_condition}
    simulation = {'zfc_simulation', 'gz_ros2_control', 'ros_gz_sim', 'ros_gz_bridge'}
    assert (dependencies & simulation) == (simulation if enabled == '1' else set())
    assert {'zfc_operator', 'zfc_calibration_analysis', 'zfc_ethercat_hardware'} <= dependencies


def test_hardware_launch_never_resolves_simulation(monkeypatch):
    from ament_index_python import packages
    spec = importlib.util.spec_from_file_location('hardware_only_launch', ROOT/'launch/local.launch.py')
    module = importlib.util.module_from_spec(spec)
    original = packages.get_package_prefix
    def hardware_prefix(name):
        assert name not in ('zfc_simulation', 'gz_ros2_control', 'ros_gz_sim', 'ros_gz_bridge')
        return original(name)
    monkeypatch.setattr(packages, 'get_package_prefix', hardware_prefix)
    spec.loader.exec_module(module)
    nodes = module.build_physical_nodes('ethercat', str(ROOT/'config/controllers.yaml'),
        str(ROOT/'config/hardware.yaml'), str(ROOT/'config/hardware_calibration.yaml'))
    assert not any(n.node_package in ('zfc_simulation', 'ros_gz_sim', 'ros_gz_bridge') for n in nodes)


@pytest.mark.parametrize('missing', ['zfc_simulation', 'gz_ros2_control', 'ros_gz_sim', 'ros_gz_bridge', 'ign'])
def test_missing_gazebo_runtime_fails_before_nodes(monkeypatch, missing):
    import shutil
    from ament_index_python import packages
    spec = importlib.util.spec_from_file_location('optional_gazebo_launch', ROOT/'launch/local.launch.py')
    module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module)
    def prefix(name):
        if name == missing:
            raise packages.PackageNotFoundError(name)
        return '/unused/runtime'
    monkeypatch.setattr(packages, 'get_package_prefix', prefix)
    monkeypatch.setattr(shutil, 'which', lambda _: None if missing == 'ign' else '/unused/ign')
    with pytest.raises(RuntimeError, match=missing) as error:
        module.simulation_nodes('/unused/controllers.yaml', False, False, .2)
    assert 'ZFC_WITH_SIMULATION=1' in str(error.value)
    assert 'no backend processes were started' in str(error.value)
