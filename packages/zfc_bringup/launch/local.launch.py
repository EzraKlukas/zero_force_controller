"""Physical inactive startup or Fortress with a plugin-owned controller manager."""
import os
import math
from pathlib import Path
import xacro
from ament_index_python.packages import get_package_share_directory, get_package_prefix
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction, SetEnvironmentVariable, ExecuteProcess, RegisterEventHandler, EmitEvent, LogInfo
from launch.event_handlers import OnProcessExit
from launch.events import Shutdown
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def build_physical_nodes(backend, controllers_file, hardware_file, calibration_file):
    # Check before expanding Xacro or constructing any physical process.
    if backend == "gazebo":
        raise RuntimeError("gazebo must use simulation_nodes; no physical manager was launched")
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
        analysis_node(False),
        Node(package="robot_state_publisher", executable="robot_state_publisher",
             output="screen", parameters=[{"robot_description": description}]),
        Node(package="controller_manager", executable="ros2_control_node",
             output="screen", parameters=[controllers_file, hardware_file],
             remappings=[("~/robot_description", "/robot_description")]),
    ]
    # Broadcasters, like motion, require explicit activation after valid data.
    for name in ("zero_force_controller", "calibration_sequencer_controller",
                 "joint_state_broadcaster", "load_cell_broadcaster"):
        nodes.append(Node(package="controller_manager", executable="spawner",
            arguments=[name, "--inactive", "--controller-manager", "/controller_manager",
                       "--controller-manager-timeout", "60"], output="screen"))
    return nodes


def analysis_node(simulation, tool_mass=.2):
    share = Path(get_package_share_directory('zfc_calibration_analysis'))
    return Node(package='zfc_calibration_analysis', executable='calibration_analysis',
                parameters=[str(share/'config/analysis.yaml'),
                            {'use_sim_time': simulation, 'backend': 'gazebo' if simulation else 'ethercat',
                             'known_downstream_mass_kg': tool_mass+.05}], output='screen')


def simulation_nodes(controllers_file, gui, plot, tool_mass, force_ui=False):
    share = Path(get_package_share_directory("zfc_bringup"))
    if not Path(controllers_file).is_absolute():
        raise RuntimeError("controllers_file must be absolute")
    if not math.isfinite(tool_mass) or not 0 < tool_mass <= 10:
        raise RuntimeError("tool_mass_kg must be finite, positive, and at most 10 kg")
    description = xacro.process_file(str(share / "urdf/stage.urdf.xacro"),
        mappings={"backend": "gazebo", "controllers_file": controllers_file,
                  "backend_file": str(share / "config/gazebo.yaml"),
                  "tool_mass_kg": str(tool_mass)}).toxml()
    plugin_path = os.pathsep.join([str(Path(get_package_prefix("zfc_simulation")) / "lib"),
                                  os.environ.get("LD_LIBRARY_PATH", ""),
                                  os.environ.get("IGN_GAZEBO_SYSTEM_PLUGIN_PATH", "")])
    server = ExecuteProcess(cmd=["ign", "gazebo", "-r", "-s", "-v", "3",
                                str(share / "worlds/stage.sdf")],
        additional_env={"IGN_GAZEBO_SYSTEM_PLUGIN_PATH": plugin_path}, output="screen")
    spawn = Node(package="ros_gz_sim", executable="create", output="screen",
        arguments=["-world", "zfc", "-topic", "/robot_description",
                   "-name", "stage", "-allow_renaming", "false"],
        parameters=[{"use_sim_time": True}])
    spawner = Node(package="controller_manager", executable="spawner", output="screen",
        arguments=["zero_force_controller", "calibration_sequencer_controller",
                   "joint_state_broadcaster", "load_cell_broadcaster", "--inactive",
                   "--controller-manager-timeout", "60"],
        parameters=[{"use_sim_time": True}])
    startup = Node(package="zfc_simulation", executable="simulation_ready", output="screen",
        parameters=[{"use_sim_time": True, "tool_mass_kg": tool_mass}])
    def after_spawn(event, context):
        if context.is_shutdown:
            return []
        if event.returncode != 0:
            return [EmitEvent(event=Shutdown(reason="Stage creation failed"))]
        return [spawner]
    def require_success(event, context):
        if context.is_shutdown:
            return []
        if event.returncode != 0:
            return [EmitEvent(event=Shutdown(reason="Simulation startup gate/spawner failed"))]
        return []
    actions = [server, analysis_node(True, tool_mass),
        RegisterEventHandler(OnProcessExit(target_action=server,
            on_exit=[EmitEvent(event=Shutdown(reason="Gazebo server exited"))])),
        RegisterEventHandler(OnProcessExit(target_action=spawn, on_exit=after_spawn)),
        RegisterEventHandler(OnProcessExit(target_action=spawner, on_exit=require_success)),
        RegisterEventHandler(OnProcessExit(target_action=startup, on_exit=require_success)),
        Node(package="robot_state_publisher", executable="robot_state_publisher",
             parameters=[{"robot_description": description, "use_sim_time": True}], output="screen"),
        Node(package="ros_gz_bridge", executable="parameter_bridge",
             parameters=[{"config_file": str(share / "config/bridges.yaml"), "use_sim_time": True}],
             output="screen"), spawn, startup,
        Node(package="zfc_simulation", executable="plot_relay",
             parameters=[{"use_sim_time": True, "configure_plotjuggler": plot}], output="screen")]
    if gui:
        actions.append(ExecuteProcess(cmd=["ign", "gazebo", "-g", "-v", "2"], output="screen"))
    if plot:
        actions.append(Node(package="plotjuggler", executable="plotjuggler",
            arguments=["--layout", str(share / "plot/stage.xml"),
                       "--nosplash", "--disable_opengl"], output="screen"))
        actions.append(LogInfo(msg="PlotJuggler: confirm Start Streaming, then the preselected /plot topics with header stamps. Activate motion only after SIMULATION_READY."))
    if force_ui:
        actions.append(Node(package="zfc_simulation", executable="force_input",
            arguments=["--gui"], parameters=[{"use_sim_time": True}], output="screen"))
    return actions


def setup(context):
    values = {name: LaunchConfiguration(name).perform(context)
              for name in ("backend", "controllers_file", "hardware_file", "hardware_calibration_file")}
    if values["backend"] == "gazebo":
        def boolean(name):
            value = LaunchConfiguration(name).perform(context).lower()
            if value not in ("true", "false"):
                raise RuntimeError(name+" must be true or false")
            return value == "true"
        return simulation_nodes(values["controllers_file"], boolean("gui"), boolean("plot"),
                                float(LaunchConfiguration("tool_mass_kg").perform(context)), boolean("force_ui"))
    return build_physical_nodes(values["backend"], values["controllers_file"],
                                values["hardware_file"], values["hardware_calibration_file"])


def generate_launch_description():
    share = Path(get_package_share_directory("zfc_bringup"))
    return LaunchDescription([
        SetEnvironmentVariable("ROS_LOCALHOST_ONLY", "1"),
        DeclareLaunchArgument("backend", default_value="ethercat"),
        DeclareLaunchArgument("gui", default_value="true"),
        DeclareLaunchArgument("plot", default_value="false"),
        DeclareLaunchArgument("force_ui", default_value="false"),
        DeclareLaunchArgument("tool_mass_kg", default_value="0.2"),
        DeclareLaunchArgument("controllers_file", default_value=str(share / "config" / "controllers.yaml")),
        DeclareLaunchArgument("hardware_file", default_value=str(share / "config" / "hardware.yaml")),
        DeclareLaunchArgument("hardware_calibration_file", default_value=str(share / "config" / "hardware_calibration.yaml")),
        OpaqueFunction(function=setup),
    ])
