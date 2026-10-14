"""Non-RT inputs, clock restart and asynchronous panel service fixtures."""
from pathlib import Path
import importlib.util
import math
import sys
import time
from types import SimpleNamespace as S
import pytest
sys.path.insert(0, str(Path(__file__).parents[1]))
from zfc_operator.streams import Source, joint_values
from zfc_operator.cyclone_profile import profile
from zfc_operator.launch_helpers import network_actions


def test_source_malformed_stale_reversal_recovery():
    source = Source()
    assert source.accept(S(sec=1, nanosec=0), (1.,), now=10.)
    assert source.fresh(1000000000, .5, now=10.1)
    assert not source.fresh(1000000000, .5, now=10.6)
    assert not source.fresh(2000000000, .5, now=10.1)
    assert not source.accept(S(sec=0, nanosec=0), (1.,), now=11.)
    assert source.value is None
    assert source.accept(S(sec=0, nanosec=1), (1.,), now=11.1)
    assert not source.accept(S(sec=1, nanosec=0), (math.nan,))
    assert not source.accept(S(sec=1, nanosec=-1), (1.,))


@pytest.mark.parametrize('names,positions,velocities', [(['other'], [0.], [0.]), (['carriage'], [], [0.]),
    (['carriage'], [0.], []), (['carriage', 'carriage'], [0., 0.], [0., 0.])])
def test_joint_input_validation(names, positions, velocities):
    with pytest.raises(ValueError):
        joint_values(S(name=names, position=positions, velocity=velocities))


def test_network_environment(monkeypatch):
    monkeypatch.delenv('ROS_LOCALHOST_ONLY', raising=False)
    assert network_actions('inherit')[0].value[0].text == '1'
    monkeypatch.setenv('ROS_LOCALHOST_ONLY', '0')
    assert network_actions('inherit')[0].value[0].text == '0'
    assert network_actions('isolated')[0].value[0].text == '1'
    assert network_actions('network')[0].value[0].text == '0'
    with pytest.raises(ValueError):
        network_actions('typo')


def test_cyclone_versioned_profile():
    import xml.etree.ElementTree as ET
    for version in ('0.9.1', '0.10.2'):
        document = profile(version, '192.168.55.2', '192.168.55.1')
        ET.fromstring(document)
        assert '<ParticipantIndex>auto' in document
        assert '<AllowMulticast>false' in document
        assert document.count('192.168.55.2') == 2
    tail = profile('0.10.2', '100.64.1.2', '100.70.56.124')
    assert '192.168.55.' not in tail
    with pytest.raises(ValueError):
        profile('11.0.1', '127.0.0.1', '127.0.0.2')
    with pytest.raises(ValueError):
        profile('0.10.2', '0.0.0.0', '192.168.55.1')


def test_fastdds_interface_allowlist():
    from zfc_operator.fastdds_profile import profile as fast_profile
    import xml.etree.ElementTree as ET
    document = fast_profile('2.6.10', '192.168.55.2')
    ET.fromstring(document)
    assert '<useBuiltinTransports>false' in document
    assert '<address>127.0.0.1' in document
    assert '<address>192.168.55.2' in document


def test_host_launch_has_no_acquisition_nodes():
    from launch import LaunchContext
    from launch_ros.actions import Node
    from launch.utilities import perform_substitutions
    spec = importlib.util.spec_from_file_location('host_launch', Path(__file__).parents[1]/'launch/host.launch.py')
    module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module)
    context = LaunchContext()
    context.launch_configurations.update(backend='ethercat', network_mode='inherit', plot='true', panel='true')
    packages = [n.node_package for n in module.setup(context) if isinstance(n, Node)]
    assert packages == ['plotjuggler', 'zfc_operator']


def spin(executor, predicate, timeout=5.):
    deadline = time.monotonic()+timeout
    while not predicate() and time.monotonic() < deadline:
        executor.spin_once(timeout_sec=.005)
    assert predicate()


def test_relay_decimation_deactivation_reactivation_and_unconfigured():
    import rclpy
    from rclpy.node import Node
    from rclpy.executors import SingleThreadedExecutor
    from sensor_msgs.msg import JointState
    from geometry_msgs.msg import WrenchStamped
    from zfc_interfaces.msg import MeasuredState, PlotState, TelemetryBatch, ControllerState
    from zfc_operator.relay import PlotRelay
    rclpy.init(args=['--ros-args', '-p', 'rate_hz:=50.0', '-p', 'freshness_s:=0.1'])
    relay, peer = PlotRelay(), Node('relay_fixture')
    executor = SingleThreadedExecutor(); executor.add_node(relay); executor.add_node(peer)
    measured, reference = [], []
    peer.create_subscription(MeasuredState, '/plot/measured', measured.append, 100)
    peer.create_subscription(PlotState, '/plot/zero_force', reference.append, 100)
    try:
        spin(executor, lambda: bool(measured))
        assert not measured[-1].valid
        def sensors():
            stamp = peer.get_clock().now().to_msg()
            joint = JointState(name=['carriage'], position=[.1], velocity=[0.]); joint.header.stamp = stamp
            force = WrenchStamped(); force.header.stamp = stamp; force.wrench.force.x = 2.
            relay.joints(joint); relay.forces(force)
        sensors()
        spin(executor, lambda: measured[-1].valid)
        state = ControllerState(trial_id=1, sequence=1, valid=True, phase=3)
        state.stamp = peer.get_clock().now().to_msg()
        relay.receive('zero_force_controller', TelemetryBatch(samples=[state]))
        spin(executor, lambda: reference and reference[-1].state.trial_id == 1)
        assert reference[-1].state.valid
        spin(executor, lambda: not measured[-1].valid)
        sensors()
        spin(executor, lambda: reference[-1].state.trial_id == 0 and measured[-1].valid)
        assert math.isnan(reference[-1].state.reference_position_m)
        state.trial_id = 2; state.stamp = peer.get_clock().now().to_msg()
        relay.receive('zero_force_controller', TelemetryBatch(samples=[state]))
        spin(executor, lambda: reference[-1].state.trial_id == 2)
        state.trial_id = 1
        relay.receive('zero_force_controller', TelemetryBatch(samples=[state]))
        assert relay.controllers['zero_force_controller'][0].trial_id == 2
        # Freshness transition publishes invalid once, never stale-as-fresh.
        spin(executor, lambda: not measured[-1].valid)
        count = len(measured)
        deadline = time.monotonic()+.1
        while time.monotonic() < deadline:
            executor.spin_once(timeout_sec=.01)
        assert len(measured) == count
    finally:
        executor.shutdown(); relay.destroy_node(); peer.destroy_node(); rclpy.shutdown()


def test_plot_clock_late_start_reject_and_restart():
    import rclpy
    from rclpy.node import Node
    from rclpy.executors import SingleThreadedExecutor
    from rcl_interfaces.msg import SetParametersResult
    from rcl_interfaces.srv import SetParameters
    from zfc_operator.plot_clock import PlotClock
    rclpy.init()
    client, server = Node('clock_fixture'), Node('clock_server')
    client.declare_parameter('configure_plotjuggler', True)
    clock = PlotClock(client)
    executor = SingleThreadedExecutor(); executor.add_node(client); executor.add_node(server)
    values = []
    def callback(request, response):
        values.append(request.parameters[0].value.bool_value)
        response.results = [SetParametersResult(successful=len(values) > 1)]
        return response
    try:
        clock.tick(); assert clock.future is None # Start Streaming not clicked.
        service = server.create_service(SetParameters, '/plotjuggler/set_parameters', callback)
        spin(executor, clock.client.service_is_ready)
        clock.tick(); spin(executor, lambda: len(values) == 1 and clock.future is None)
        clock.tick(); spin(executor, lambda: len(values) == 2 and clock.future is None)
        assert values == [False, False]
        server.destroy_service(service)
        service = server.create_service(SetParameters, '/plotjuggler/set_parameters', callback)
        clock.tick(); spin(executor, lambda: len(values) >= 3)
        assert values[-1] is False
    finally:
        executor.shutdown(); client.destroy_node(); server.destroy_node(); rclpy.shutdown()


def test_relay_hardware_inactive_is_not_live_acquisition():
    import rclpy
    from rclpy.node import Node
    from rclpy.executors import SingleThreadedExecutor
    from sensor_msgs.msg import JointState
    from geometry_msgs.msg import WrenchStamped
    from zfc_interfaces.msg import MeasuredState
    from controller_manager_msgs.srv import ListHardwareComponents
    from controller_manager_msgs.msg import HardwareComponentState, HardwareInterface
    from lifecycle_msgs.msg import State
    from zfc_operator.relay import PlotRelay
    rclpy.init(args=['--ros-args', '-p', 'require_active_hardware:=true'])
    relay, manager = PlotRelay(), Node('relay_hardware_fixture')
    executor = SingleThreadedExecutor(); executor.add_node(relay); executor.add_node(manager)
    states, measured = ['inactive'], []
    def components(_, response):
        response.component = [HardwareComponentState(name='StageSystem', state=State(label=states[0]),
            state_interfaces=[HardwareInterface(name=n, is_available=True) for n in (
                'carriage/position', 'carriage/velocity', 'load_cell/force.x', 'load_cell/force.y', 'load_cell/force.z')])]
        return response
    manager.create_service(ListHardwareComponents, '/controller_manager/list_hardware_components', components)
    manager.create_subscription(MeasuredState, '/plot/measured', measured.append, 100)
    def frozen_values_with_fresh_headers():
        stamp = manager.get_clock().now().to_msg()
        joint = JointState(name=['carriage'], position=[1.], velocity=[0.]); joint.header.stamp = stamp
        force = WrenchStamped(); force.header.stamp = stamp; force.wrench.force.x = 2.
        relay.joints(joint); relay.forces(force)
    manager.create_timer(.02, frozen_values_with_fresh_headers)
    try:
        spin(executor, lambda: measured and 'not active' in measured[-1].detail)
        assert not measured[-1].valid and math.isnan(measured[-1].position_m)
        states[0] = 'active'
        spin(executor, lambda: measured[-1].valid)
        states[0] = 'inactive'
        spin(executor, lambda: not measured[-1].valid)
        assert math.isnan(measured[-1].force_n)
    finally:
        executor.shutdown(); relay.destroy_node(); manager.destroy_node(); rclpy.shutdown()


def test_panel_async_and_serialization():
    import rclpy
    from rclpy.node import Node
    from rclpy.executors import SingleThreadedExecutor
    from zfc_interfaces.srv import OperatorCommand
    from zfc_interfaces.msg import AnalysisState
    from zfc_operator.panel import PanelNode
    rclpy.init()
    reports = []
    panel, server = PanelNode(reports.append), Node('panel_fixture')
    commands = []
    def callback(request, response):
        commands.append(request.command)
        response.success = True; response.stop_acknowledged = True
        response.message = 'streaming; motion controllers inactive; drive holding'
        return response
    server.create_service(OperatorCommand, '/calibration_analysis/operator_command', callback)
    executor = SingleThreadedExecutor(); executor.add_node(panel); executor.add_node(server)
    try:
        spin(executor, panel.operations.service_is_ready)
        panel.status(AnalysisState(backend='ethercat', stop_acknowledged=True))
        panel.enqueue('prepare'); panel.enqueue('start_zero_force')
        panel.dispatch()
        assert panel.pending and not commands
        spin(executor, lambda: not panel.pending)
        assert commands == ['prepare']
        panel.poll(); assert 'drive holding' in reports[-1]['text']
        panel.received = 0.; panel.enqueue('prepare'); panel.dispatch()
        assert commands == ['prepare'] and not panel.pending
    finally:
        executor.shutdown(); panel.destroy_node(); server.destroy_node(); rclpy.shutdown()
