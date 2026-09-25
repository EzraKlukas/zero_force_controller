from pathlib import Path
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import SetEnvironmentVariable
from launch_ros.actions import Node


def generate_launch_description():
    share = Path(get_package_share_directory("zfc_bringup"))
    description = (share / "urdf" / "ethercat.urdf").read_text()
    diagnostic_mode = os.environ.get("ZFC_DIAGNOSTIC_MODE", "production")
    description = description.replace(
        '<param name="max_increment_counts">10</param>',
        '<param name="max_increment_counts">10</param>\n'
        f'      <param name="diagnostic_mode">{diagnostic_mode}</param>')
    return LaunchDescription([
        SetEnvironmentVariable("ROS_LOCALHOST_ONLY", "1"),
        Node(
            package="zfc_profiling",
            executable="profile_control_node",
            output="screen",
            parameters=[str(Path(get_package_share_directory("zfc_profiling")) /
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
