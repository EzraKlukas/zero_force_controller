"""Local-only control. Hardware starts unconfigured; the motion controller starts inactive."""
from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import SetEnvironmentVariable
from launch_ros.actions import Node

share = Path(get_package_share_directory("zfc_bringup"))
description = (share / "urdf" / "ethercat.urdf").read_text()

robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="screen",
        parameters=[{"robot_description": description}],
        )

controller_manager_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        output="screen",
        parameters=[str(share / "config" / "controllers.yaml")],
        remappings=[
            ("~/robot_description", "/robot_description"),
            ],
        )

zero_force_controller_spawner = Node(
            package="controller_manager", executable="spawner",
            arguments=["zero_force_controller", "--inactive",
                       "--controller-manager", "/controller_manager",
                       "--controller-manager-timeout", "60"],
            output="screen",
        )

def generate_launch_description():
    return LaunchDescription([
        SetEnvironmentVariable("ROS_LOCALHOST_ONLY", "1"),
        robot_state_publisher_node,
        controller_manager_node,
        zero_force_controller_spawner
    ])
