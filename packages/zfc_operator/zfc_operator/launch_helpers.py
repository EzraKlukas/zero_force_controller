"""No domain/RMW changes: caller chooses the same environment for every shell."""
import os
from pathlib import Path
from ament_index_python.packages import get_package_share_directory
from launch.actions import SetEnvironmentVariable
from launch_ros.actions import Node


def network_actions(mode):
    if mode not in ('inherit', 'isolated', 'network'):
        raise ValueError('network_mode must be inherit, isolated, or network')
    value = os.environ.get('ROS_LOCALHOST_ONLY', '1') if mode == 'inherit' else ('1' if mode == 'isolated' else '0')
    if value not in ('0', '1'):
        raise ValueError('ROS_LOCALHOST_ONLY must be 0 or 1')
    return [SetEnvironmentVariable('ROS_LOCALHOST_ONLY', value)]


def relay_node(simulation, rate=100., configure=False):
    return Node(package='zfc_operator', executable='plot_relay', output='screen',
                parameters=[{'use_sim_time': simulation, 'rate_hz': rate, 'configure_plotjuggler': configure,
                             'require_active_hardware': not simulation}])


def plot_node():
    share = Path(get_package_share_directory('zfc_operator'))
    return Node(package='plotjuggler', executable='plotjuggler', output='screen',
                arguments=['--layout', str(share/'plot/stage.xml'), '--nosplash', '--disable_opengl'])


def clock_node(simulation):
    return Node(package='zfc_operator', executable='operator_panel', arguments=['--headless'], output='screen',
                parameters=[{'use_sim_time': simulation, 'backend': 'gazebo' if simulation else 'ethercat',
                             'configure_plotjuggler': True}])
