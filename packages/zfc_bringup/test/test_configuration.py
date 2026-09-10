from pathlib import Path
import importlib.util
import xml.etree.ElementTree as ET
import yaml

ROOT = Path(__file__).resolve().parents[1]


def test_configuration():
    robot = ET.parse(ROOT / "urdf" / "ethercat.urdf").getroot()
    system = robot.find("ros2_control")
    assert system.attrib == {"name": "EthercatSystem", "type": "system"}
    assert len(system.findall(".//command_interface")) == 1
    assert len(system.findall(".//state_interface")) == 25
    config = yaml.safe_load((ROOT / "config" / "controllers.yaml").read_text())
    assert config["controller_manager"]["ros__parameters"]["update_rate"] == 1000
    assert config["controller_manager"]["ros__parameters"]["hardware_components_initial_state"] == {
        "unconfigured": ["EthercatSystem"]
    }
    params = config["linear_shuttle_controller"]["ros__parameters"]
    assert params["increment_counts_per_update"] == 10
    assert params["updates_per_leg"] == 1000
    assert params["repeat"] is False
    spec = importlib.util.spec_from_file_location("zfc_local_launch", ROOT / "launch" / "local.launch.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    assert len(module.generate_launch_description().entities) == 3
