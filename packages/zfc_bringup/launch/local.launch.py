"""Local-only control. Hardware starts unconfigured; the motion controller starts inactive."""
from pathlib import Path
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import SetEnvironmentVariable
from launch_ros.actions import Node


def generate_launch_description():
    share = Path(get_package_share_directory("zfc_bringup"))
    description = (share / "urdf" / "ethercat.urdf").read_text()
    return LaunchDescription([
        SetEnvironmentVariable("ROS_LOCALHOST_ONLY", "1"),
        Node(
            package="controller_manager", executable="ros2_control_node",
            output="screen",
            parameters=[str(share / "config" / "controllers.yaml"),
                        {"robot_description": description}],
        ),
        Node(
            package="controller_manager", executable="spawner",
            arguments=["zero_force_controller", "--inactive",
                       "--controller-manager", "/controller_manager",
                       "--controller-manager-timeout", "60"],
            output="screen",
        ),
    ])
