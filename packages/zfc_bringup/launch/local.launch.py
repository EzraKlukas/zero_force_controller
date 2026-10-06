"""Physical startup only. All controllers start inactive."""
from pathlib import Path
import xacro
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction, SetEnvironmentVariable
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def build_physical_nodes(backend, controllers_file, hardware_file, calibration_file):
    # Check before expanding Xacro or constructing any physical process.
    if backend == "gazebo":
        raise RuntimeError("Gazebo simulation bringup is deferred; no hardware or standalone controller manager was launched.")
    if backend != "ethercat":
        raise RuntimeError("backend must be ethercat or gazebo; invalid values never select hardware")
    for path in (controllers_file, hardware_file, calibration_file):
        if not Path(path).is_absolute():
            raise RuntimeError("Controller, hardware, and calibration files must be absolute paths")
    share = Path(get_package_share_directory("zfc_bringup"))
    description = xacro.process_file(str(share / "urdf" / "stage.urdf.xacro"),
        mappings={"backend": backend, "controllers_file": controllers_file,
                  "hardware_calibration_file": calibration_file}).toxml()
    nodes = [
        Node(package="robot_state_publisher", executable="robot_state_publisher",
             output="screen", parameters=[{"robot_description": description}]),
        Node(package="controller_manager", executable="ros2_control_node",
             output="screen", parameters=[controllers_file, hardware_file],
             remappings=[("~/robot_description", "/robot_description")]),
    ]
    # Broadcasters, like motion, require explicit activation after valid data.
    for name in ("zero_force_controller", "joint_state_broadcaster", "load_cell_broadcaster"):
        nodes.append(Node(package="controller_manager", executable="spawner",
            arguments=[name, "--inactive", "--controller-manager", "/controller_manager",
                       "--controller-manager-timeout", "60"], output="screen"))
    return nodes


def setup(context):
    values = {name: LaunchConfiguration(name).perform(context)
              for name in ("backend", "controllers_file", "hardware_file", "hardware_calibration_file")}
    return build_physical_nodes(values["backend"], values["controllers_file"],
                                values["hardware_file"], values["hardware_calibration_file"])


def generate_launch_description():
    share = Path(get_package_share_directory("zfc_bringup"))
    return LaunchDescription([
        SetEnvironmentVariable("ROS_LOCALHOST_ONLY", "1"),
        DeclareLaunchArgument("backend", default_value="ethercat"),
        DeclareLaunchArgument("controllers_file", default_value=str(share / "config" / "controllers.yaml")),
        DeclareLaunchArgument("hardware_file", default_value=str(share / "config" / "hardware.yaml")),
        DeclareLaunchArgument("hardware_calibration_file", default_value=str(share / "config" / "hardware_calibration.yaml")),
        OpaqueFunction(function=setup),
    ])
