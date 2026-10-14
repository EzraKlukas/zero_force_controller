"""Host tools only: no acquisition, relay, analysis or controller manager."""
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from zfc_operator.launch_helpers import network_actions, plot_node


def setup(context):
    def value(name):
        return LaunchConfiguration(name).perform(context)
    def boolean(name):
        text = value(name)
        if text not in ('true', 'false'):
            raise ValueError(name+' must be true or false')
        return text == 'true'
    backend = value('backend')
    if backend not in ('ethercat', 'gazebo'):
        raise ValueError('backend must be ethercat or gazebo')
    actions = network_actions(value('network_mode'))
    if boolean('plot'):
        actions.append(plot_node())
    if boolean('panel') or boolean('plot'):
        actions.append(Node(package='zfc_operator', executable='operator_panel', output='screen',
            arguments=[] if boolean('panel') else ['--headless'],
            parameters=[{'backend': backend, 'use_sim_time': backend == 'gazebo',
                         'configure_plotjuggler': boolean('plot')}]))
    return actions


def generate_launch_description():
    return LaunchDescription([DeclareLaunchArgument('backend', default_value='ethercat'),
        DeclareLaunchArgument('network_mode', default_value='inherit'),
        DeclareLaunchArgument('plot', default_value='true'), DeclareLaunchArgument('panel', default_value='true'),
        OpaqueFunction(function=setup)])
