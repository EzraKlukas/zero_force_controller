from pathlib import Path
import os
import xacro

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import SetEnvironmentVariable
from launch_ros.actions import Node


def generate_launch_description():
    share = Path(get_package_share_directory("zfc_bringup"))
    diagnostic_mode = os.environ.get("ZFC_DIAGNOSTIC_MODE", "production")
    calibration_file = os.environ.get("ZFC_HARDWARE_CALIBRATION_FILE",
                                     str(share / "config" / "hardware_calibration.yaml"))
    if not Path(calibration_file).is_absolute():
        raise RuntimeError("ZFC_HARDWARE_CALIBRATION_FILE must be absolute")
    description = xacro.process_file(str(share / "urdf" / "stage.urdf.xacro"),
        mappings={"backend": "ethercat", "diagnostic_mode": diagnostic_mode,
                  "hardware_calibration_file": calibration_file}).toxml()
    return LaunchDescription([
        SetEnvironmentVariable("ROS_LOCALHOST_ONLY", "1"),
        Node(
            package="zfc_profiling",
            executable="profile_control_node",
            output="screen",
            parameters=[str(share / "config" / "controllers.yaml"),
                        str(share / "config" / "hardware.yaml"),
                        str(Path(get_package_share_directory("zfc_profiling")) /
                         "config" / "hold_controllers.yaml"),
                        {"robot_description": description}],
        ),
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["zero_force_controller", "--inactive",
                       "--controller-manager", "/controller_manager",
                       "--controller-manager-timeout", "60"],
            output="screen",
        ),
    ])
