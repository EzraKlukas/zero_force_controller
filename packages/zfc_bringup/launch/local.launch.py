"""Physical inactive startup or Fortress with a plugin-owned controller manager."""
import os
import math
import hashlib
import yaml
from pathlib import Path
import xacro
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from zfc_operator.launch_helpers import network_actions, relay_node, plot_node, clock_node


def build_physical_nodes(backend, controllers_file, hardware_file, calibration_file, analysis_file='', relay=True, plot=False, rate=100.):
    # Check before expanding Xacro or constructing any physical process.
    if backend == "gazebo":
        raise RuntimeError("gazebo must use simulation_nodes; no physical manager was launched")
    if backend != "ethercat":
        raise RuntimeError("backend must be ethercat or gazebo; invalid values never select hardware")
    for path in (controllers_file, hardware_file, calibration_file):
        if not Path(path).is_absolute():
            raise RuntimeError("Controller, hardware, and calibration files must be absolute paths")
    hardware_settings = yaml.safe_load(Path(hardware_file).read_text())
    initial = hardware_settings.get('controller_manager', {}).get('ros__parameters', {}).get('hardware_components_initial_state', {})
    if 'StageSystem' in initial.get('inactive', []):
        raise RuntimeError('StageSystem must start unconfigured; remove it from the inactive startup list')
    share = Path(get_package_share_directory("zfc_bringup"))
    description = xacro.process_file(str(share / "urdf" / "stage.urdf.xacro"),
        mappings={"backend": backend, "controllers_file": controllers_file,
                  "hardware_calibration_file": calibration_file}).toxml()
    nodes = [
        analysis_node(False, analysis_file=analysis_file, physical_files={
            'controllers_file': controllers_file, 'hardware_file': hardware_file, 'installation_file': calibration_file}),
        Node(package="robot_state_publisher", executable="robot_state_publisher",
             output="screen", parameters=[{"robot_description": description, "use_sim_time": False}]),
        Node(package="controller_manager", executable="ros2_control_node",
             output="screen", parameters=[controllers_file, hardware_file, {'use_sim_time': False,
                 'hardware_components_initial_state': {'unconfigured': ['StageSystem']}}],
             remappings=[("~/robot_description", "/robot_description")]),
    ]
    # Broadcasters, like motion, require explicit activation after valid data.
    for name in ("zero_force_controller", "calibration_sequencer_controller",
                 "joint_state_broadcaster", "load_cell_broadcaster"):
        nodes.append(Node(package="controller_manager", executable="spawner",
            arguments=[name, "--inactive", "--controller-manager", "/controller_manager",
                       "--controller-manager-timeout", "60"], parameters=[{'use_sim_time': False}], output="screen"))
    if relay:
        nodes.append(relay_node(False, rate, plot))
    if plot:
        nodes.append(plot_node())
        if not relay:
            nodes.append(clock_node(False))
    return nodes


def analysis_node(simulation, tool_mass=.2, analysis_file='', physical_files=None):
    share = Path(get_package_share_directory('zfc_calibration_analysis'))
    selected = analysis_file or str(share/('config/analysis.yaml' if simulation else 'config/hardware.yaml'))
    if not Path(selected).is_absolute():
        raise RuntimeError('analysis_file must be absolute')
    configured = yaml.safe_load(Path(selected).read_text()).get('calibration_analysis', {}).get('ros__parameters', {})
    if configured.get('backend', 'gazebo' if simulation else 'ethercat') != ('gazebo' if simulation else 'ethercat'):
        raise RuntimeError('analysis_file backend must match the selected launch backend')
    settings = {'use_sim_time': simulation, 'backend': 'gazebo' if simulation else 'ethercat'}
    if simulation:
        settings['known_downstream_mass_kg'] = tool_mass+.05
    if physical_files:
        for name, path in physical_files.items():
            settings[name] = path
            settings[name+'_sha256'] = hashlib.sha256(Path(path).read_bytes()).hexdigest()
    return Node(package='zfc_calibration_analysis', executable='calibration_analysis',
                parameters=[selected, settings], output='screen')


def gazebo_dependencies():
    # Resolve only after selecting Gazebo. Physical launch/import never needs
    # the optional packages, Fortress executable, or simulation launch helpers.
    import shutil
    from ament_index_python.packages import get_package_prefix, PackageNotFoundError
    prefixes, missing = {}, []
    for package in ('zfc_simulation', 'gz_ros2_control', 'ros_gz_sim', 'ros_gz_bridge'):
        try:
            prefixes[package] = get_package_prefix(package)
        except PackageNotFoundError:
            missing.append(package)
    executable = shutil.which('ign')
    if executable is None:
        missing.append('ign (Gazebo Fortress executable)')
    if missing:
        raise RuntimeError('Gazebo backend dependencies missing: '+', '.join(missing)+
            '. Build/source the simulation overlay with ZFC_WITH_SIMULATION=1 '
            '(include zfc_simulation), and provide the matching Humble/Fortress runtime. '
            'Use backend:=ethercat for hardware-only operation; no backend processes were started.')
    return prefixes, executable


def simulation_nodes(controllers_file, gui, plot, tool_mass, force_ui=False, relay=True, rate=100., analysis_file=''):
    prefixes, executable = gazebo_dependencies()
    from launch.actions import ExecuteProcess, RegisterEventHandler, EmitEvent, LogInfo
    from launch.event_handlers import OnProcessExit
    from launch.events import Shutdown
    share = Path(get_package_share_directory("zfc_bringup"))
    if not Path(controllers_file).is_absolute():
        raise RuntimeError("controllers_file must be absolute")
    if not math.isfinite(tool_mass) or not 0 < tool_mass <= 10:
        raise RuntimeError("tool_mass_kg must be finite, positive, and at most 10 kg")
    description = xacro.process_file(str(share / "urdf/stage.urdf.xacro"),
        mappings={"backend": "gazebo", "controllers_file": controllers_file,
                  "backend_file": str(share / "config/gazebo.yaml"),
                  "tool_mass_kg": str(tool_mass)}).toxml()
    plugin_path = os.pathsep.join([str(Path(prefixes["zfc_simulation"]) / "lib"),
                                  os.environ.get("LD_LIBRARY_PATH", ""),
                                  os.environ.get("IGN_GAZEBO_SYSTEM_PLUGIN_PATH", "")])
    server = ExecuteProcess(cmd=[executable, "gazebo", "-r", "-s", "-v", "3",
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
    actions = [server, analysis_node(True, tool_mass, analysis_file),
        RegisterEventHandler(OnProcessExit(target_action=server,
            on_exit=[EmitEvent(event=Shutdown(reason="Gazebo server exited"))])),
        RegisterEventHandler(OnProcessExit(target_action=spawn, on_exit=after_spawn)),
        RegisterEventHandler(OnProcessExit(target_action=spawner, on_exit=require_success)),
        RegisterEventHandler(OnProcessExit(target_action=startup, on_exit=require_success)),
        Node(package="robot_state_publisher", executable="robot_state_publisher",
             parameters=[{"robot_description": description, "use_sim_time": True}], output="screen"),
        Node(package="ros_gz_bridge", executable="parameter_bridge",
             parameters=[{"config_file": str(share / "config/bridges.yaml"), "use_sim_time": True}],
             output="screen"), spawn, startup]
    if relay:
        actions.append(relay_node(True, rate, plot))
    if gui:
        actions.append(ExecuteProcess(cmd=[executable, "gazebo", "-g", "-v", "2"], output="screen"))
    if plot:
        actions.append(plot_node())
        if not relay:
            actions.append(clock_node(True))
        actions.append(LogInfo(msg="PlotJuggler: confirm Start Streaming, then the preselected /plot topics with header stamps. Activate motion only after SIMULATION_READY."))
    if force_ui:
        actions.append(Node(package="zfc_simulation", executable="force_input",
            arguments=["--gui"], parameters=[{"use_sim_time": True}], output="screen"))
    return actions


def setup(context):
    values = {name: LaunchConfiguration(name).perform(context)
              for name in ("backend", "controllers_file", "hardware_file", "hardware_calibration_file")}
    def boolean(name):
        value = LaunchConfiguration(name).perform(context).lower()
        if value not in ("true", "false"):
            raise RuntimeError(name+" must be true or false")
        return value == "true"
    actions = network_actions(LaunchConfiguration('network_mode').perform(context))
    rate = float(LaunchConfiguration('plot_rate_hz').perform(context))
    if not math.isfinite(rate) or not 1 <= rate <= 1000:
        raise RuntimeError('plot_rate_hz must be finite in [1,1000]')
    analysis_file = LaunchConfiguration('analysis_file').perform(context)
    if values["backend"] == "gazebo":
        return actions + simulation_nodes(values["controllers_file"], boolean("gui"), boolean("plot"),
                                float(LaunchConfiguration("tool_mass_kg").perform(context)), boolean("force_ui"),
                                boolean('relay'), rate, analysis_file)
    return actions + build_physical_nodes(values["backend"], values["controllers_file"],
                                values["hardware_file"], values["hardware_calibration_file"], analysis_file,
                                boolean('relay'), boolean('plot'), rate)


def generate_launch_description():
    share = Path(get_package_share_directory("zfc_bringup"))
    return LaunchDescription([
        DeclareLaunchArgument('network_mode', default_value='inherit'),
        DeclareLaunchArgument("backend", default_value="ethercat"),
        DeclareLaunchArgument("gui", default_value="true"),
        DeclareLaunchArgument("plot", default_value="false"),
        DeclareLaunchArgument('relay', default_value='true'),
        DeclareLaunchArgument('plot_rate_hz', default_value='100.0'),
        DeclareLaunchArgument('analysis_file', default_value=''),
        DeclareLaunchArgument("force_ui", default_value="false"),
        DeclareLaunchArgument("tool_mass_kg", default_value="0.2"),
        DeclareLaunchArgument("controllers_file", default_value=str(share / "config" / "controllers.yaml")),
        DeclareLaunchArgument("hardware_file", default_value=str(share / "config" / "hardware.yaml")),
        DeclareLaunchArgument("hardware_calibration_file", default_value=str(share / "config" / "hardware_calibration.yaml")),
        OpaqueFunction(function=setup),
    ])
