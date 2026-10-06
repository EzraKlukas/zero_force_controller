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
    assert joint.find("limit").attrib["lower"] == "0.0"
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
    assert params["do_calibrate"] is False
    for key in ("center_zone_half_width_m", "base_velocity_mps", "jerk_mps3",
                "initial_acceleration_mps2", "acceleration_increment_mps2",
                "max_acceleration_mps2"):
        assert math.isnan(params[key])
    force = shared["load_cell_broadcaster"]["ros__parameters"]
    assert "sensor_name" not in force
    assert force["interface_names"] == {"force": {
        "x": "load_cell/force.x", "y": "load_cell/force.y", "z": "load_cell/force.z"}}


def test_launch_gazebo_and_invalid_backend_exit_before_nodes():
    spec = importlib.util.spec_from_file_location("zfc_launch", ROOT / "launch/local.launch.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    for backend, message in (("gazebo", "deferred"), ("typo", "invalid")):
        with pytest.raises(RuntimeError, match=message):
            module.build_physical_nodes(backend, "/unused", "/unused", "/unused")
