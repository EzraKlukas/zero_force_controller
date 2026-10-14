"""Physical readiness/service fixtures only. No StageSystem plugin/IgH access."""
from dataclasses import asdict
import hashlib
from pathlib import Path
import sys
import time
import yaml
import pytest
sys.path.insert(0, str(Path(__file__).parents[1]))
import rclpy
from rclpy.node import Node
from rclpy.executors import SingleThreadedExecutor
from rclpy.action import ActionClient
from controller_manager_msgs.srv import ListHardwareComponents, SetHardwareComponentState, ListControllers, SwitchController
from controller_manager_msgs.msg import HardwareComponentState, HardwareInterface, ControllerState
from lifecycle_msgs.msg import State
from rcl_interfaces.srv import GetParameters
from rclpy.parameter import Parameter
from sensor_msgs.msg import JointState
from geometry_msgs.msg import WrenchStamped
from rclpy.qos import QoSProfile, DurabilityPolicy
from zfc_interfaces.msg import TelemetryBatch, ControllerState as Sample, TrialStatus
from zfc_interfaces.srv import OperatorCommand, ApplyCalibration
from zfc_interfaces.action import RunCalibration
from zfc_calibration_analysis.node import CalibrationAnalysis, read_result
from zfc_calibration_analysis.analysis import Criteria, Fit, SOURCE
from zfc_calibration_analysis.backends import reviewed_profiles


def spin(executor, predicate, timeout=8.):
    deadline = time.monotonic()+timeout
    while not predicate() and time.monotonic() < deadline:
        executor.spin_once(timeout_sec=.005)
    assert predicate(), 'fixture deadline'


class Manager(Node):
    def __init__(self, failure=''):
        super().__init__('physical_services_fixture')
        self.failure = failure
        self.lifecycle = 'unconfigured'
        self.states = {n: 'inactive' for n in ('zero_force_controller', 'calibration_sequencer_controller', 'joint_state_broadcaster', 'load_cell_broadcaster')}
        self.activations = []
        self.feedback = True
        self.trial = None
        self.sent = False
        self.zero_trial = None
        self.create_service(ListHardwareComponents, '/controller_manager/list_hardware_components', self.components)
        self.create_service(SetHardwareComponentState, '/controller_manager/set_hardware_component_state', self.lifecycle_change)
        self.create_service(ListControllers, '/controller_manager/list_controllers', self.controllers)
        self.create_service(SwitchController, '/controller_manager/switch_controller', self.switch)
        self.create_service(GetParameters, '/controller_manager/get_parameters', self.manager_clock)
        self.joints = self.create_publisher(JointState, '/joint_states', 10)
        self.forces = self.create_publisher(WrenchStamped, '/load_cell_broadcaster/wrench', 10)
        self.samples = self.create_publisher(TelemetryBatch, '/calibration_sequencer_controller/telemetry', 100)
        self.zero_samples = self.create_publisher(TelemetryBatch, '/zero_force_controller/telemetry', 100)
        self.status = self.create_publisher(TrialStatus, '/calibration_sequencer_controller/trial_status', QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL))
        self.create_timer(.02, self.publish)

    def components(self, _, response):
        names = ('carriage/position', 'carriage/velocity', 'load_cell/force.x', 'load_cell/force.y', 'load_cell/force.z')
        response.component = [HardwareComponentState(name='StageSystem', class_type='zfc_ethercat_hardware/EthercatHardware',
            state=State(label=self.lifecycle), state_interfaces=[HardwareInterface(name=n, is_available=self.lifecycle == 'active') for n in names],
            command_interfaces=[HardwareInterface(name='carriage/position', is_available=self.lifecycle == 'active', is_claimed=any(self.states[n] == 'active' for n in ('zero_force_controller', 'calibration_sequencer_controller')))])]
        return response

    def lifecycle_change(self, request, response):
        response.ok = self.failure != 'activation'
        if response.ok:
            self.lifecycle = request.target_state.label
        response.state = State(label=self.lifecycle)
        return response

    def manager_clock(self, request, response):
        response.values = [Parameter('use_sim_time', value=False).to_parameter_msg().value]
        return response

    def controllers(self, _, response):
        response.controller = [ControllerState(name=n, state=s, claimed_interfaces=['carriage/position'] if s == 'active' and 'controller' in n else []) for n, s in self.states.items()]
        return response

    def switch(self, request, response):
        assert request.strictness == SwitchController.Request.STRICT
        response.ok = self.failure != 'switch'
        if response.ok:
            for n in request.deactivate_controllers:
                self.states[n] = 'inactive'
            for n in request.activate_controllers:
                self.states[n] = 'active'; self.activations.append(n)
        return response

    def publish(self):
        if self.feedback and self.lifecycle == 'active' and self.states['joint_state_broadcaster'] == 'active':
            joint = JointState(name=['carriage'], position=[0.], velocity=[0.]); joint.header.stamp = self.get_clock().now().to_msg()
            self.joints.publish(joint)
            force = WrenchStamped(); force.header.stamp = joint.header.stamp; force.wrench.force.x = 2.45
            self.forces.publish(force)
        if self.trial and not self.sent and self.states['calibration_sequencer_controller'] == 'active':
            rows = []
            for i in range(1600):
                a = [.2, -.2, .4, -.4, .8, -.8, 1.2, -1.2][i//200]
                sample = Sample(trial_id=self.trial, sequence=i+1, valid=True, phase=10, force_n=2.45+.25*a,
                    velocity_mps=.05, reference_velocity_mps=.05, reference_acceleration_mps2=a)
                sample.stamp.sec, sample.stamp.nanosec = divmod(i*1000000, 1000000000)
                rows.append(sample)
            for start in range(0, len(rows), 256):
                self.samples.publish(TelemetryBatch(samples=rows[start:start+256]))
            self.status.publish(TrialStatus(trial_id=self.trial, final_sequence=len(rows), completed=True, successful=True, capture_complete=True))
            self.sent = True
        zero_trial = self.zero_trial or (self.zero_node.get_parameter('trial_id').value if hasattr(self, 'zero_node') else None)
        if zero_trial and self.states['zero_force_controller'] == 'active':
            sample = Sample(trial_id=zero_trial, sequence=1, valid=self.failure != 'baseline', phase=5 if self.failure == 'baseline' else 3)
            sample.stamp = self.get_clock().now().to_msg()
            self.zero_samples.publish(TelemetryBatch(samples=[sample]))


def fixture(tmp_path, failure=''):
    root = Path(__file__).parents[2]/'zfc_bringup/config'
    controllers = yaml.safe_load((root/'controllers.yaml').read_text())
    hardware = yaml.safe_load((root/'hardware.yaml').read_text())
    installation = yaml.safe_load((root/'hardware_calibration.yaml').read_text())
    installation.update(conventions_confirmed=True, force_x_newtons_per_count=1., force_y_newtons_per_count=1., force_z_newtons_per_count=1.)
    settings = dict(backend='ethercat', installation_reviewed=True, controllers_reviewed=True, analysis_reviewed=True,
        coordinate_convention='fixture signed session q; positive upward', force_convention='fixture parent-on-child +X upward',
        calibration_profile_id='test-only', known_downstream_mass_kg=-1., output_directory=str(tmp_path/'trials'), service_timeout_s=.5)
    settings.update(asdict(Criteria()), feedback_timeout_s=.5, stationary_velocity_mps=.001)
    for key, document in (('installation_file', installation), ('controllers_file', controllers), ('hardware_file', hardware)):
        path = tmp_path/(key+'.yaml'); path.write_text(yaml.safe_dump(document))
        settings[key] = str(path); settings[key+'_sha256'] = hashlib.sha256(path.read_bytes()).hexdigest()
    args = ['--ros-args']
    for key, value in settings.items():
        args.extend(['-p', key+':='+str(value).lower() if isinstance(value, bool) else key+':='+str(value)])
    rclpy.init(args=args)
    analysis, manager = CalibrationAnalysis(), Manager(failure)
    nodes = [analysis, manager]
    for name in ('calibration_sequencer_controller', 'zero_force_controller'):
        node = Node(name)
        params = dict(controllers[name]['ros__parameters']); params.update(hardware[name]['ros__parameters'])
        for key, value in params.items():
            if key != 'use_sim_time':
                node.declare_parameter(key, value)
        nodes.append(node)
    manager.zero_node = next(n for n in nodes if n.get_name() == 'zero_force_controller')
    for name in ('joint_state_broadcaster', 'load_cell_broadcaster'):
        node = Node(name)
        def declare(parameters, prefix=''):
            for key, value in parameters.items():
                if isinstance(value, dict):
                    declare(value, prefix+key+'.')
                else:
                    node.declare_parameter(prefix+key, value)
        declare(controllers[name]['ros__parameters'])
        nodes.append(node)
    executor = SingleThreadedExecutor()
    for node in nodes:
        executor.add_node(node)
    return analysis, manager, nodes, executor, settings


def close(nodes, executor):
    executor.shutdown()
    for node in nodes:
        if isinstance(node, CalibrationAnalysis):
            node.close()
        node.destroy_node()
    rclpy.shutdown()


def test_physical_unreviewed_headless_startup_without_simulation_defaults():
    rclpy.init(args=['--ros-args', '-p', 'backend:=ethercat'])
    node = CalibrationAnalysis()
    try:
        assert node.settings['known_downstream_mass_kg'] == -1.
        assert node.criteria.expected_coefficient_sign == 0
        assert node.criteria.maximum_residual_rms_n == 0.
        assert node.settings['stationary_velocity_mps'] == 0.
        assert not node.stop_acknowledged and not node.physical_feedback()
        assert not any(s.topic_name.startswith('/simulation/') for s in node.subscriptions)
        assert not any(p.topic_name.startswith('/simulation/') for p in node.publishers)
        assert not node.get_parameter('use_sim_time').value
    finally:
        node.close(); node.destroy_node(); rclpy.shutdown()


@pytest.mark.parametrize('failure', ['', 'activation', 'switch'])
def test_prepare_sensor_only_and_failure(tmp_path, failure):
    analysis, manager, nodes, executor, settings = fixture(tmp_path, failure)
    try:
        client = nodes[-1].create_client(OperatorCommand, '/calibration_analysis/operator_command')
        spin(executor, client.service_is_ready)
        future = client.call_async(OperatorCommand.Request(command='prepare'))
        spin(executor, future.done)
        assert future.result().success == (not failure), future.result().message
        assert not any('controller' in n for n in manager.activations)
        if not failure:
            assert analysis.physical_feedback() and analysis.stationary()
            assert 'drive holding' in future.result().message
            assert analysis.model_metadata()['known_downstream_mass_kg'] is None
            assert analysis.force_enabled is None # No fake /simulation acknowledgments.
            manager.feedback = False
            spin(executor, lambda: not analysis.physical_feedback())
            assert not analysis.stationary()
    finally:
        close(nodes, executor)


def test_explicit_zero_force_start_and_observe(tmp_path):
    analysis, manager, nodes, executor, _ = fixture(tmp_path)
    try:
        client = nodes[-1].create_client(OperatorCommand, '/calibration_analysis/operator_command')
        spin(executor, client.service_is_ready)
        prepare = client.call_async(OperatorCommand.Request(command='prepare')); spin(executor, prepare.done)
        assert prepare.result().success
        missing_contact = client.call_async(OperatorCommand.Request(command='start_zero_force')); spin(executor, missing_contact.done)
        assert not missing_contact.result().success and 'Clear external contact' in missing_contact.result().message
        assert not any('controller' in n for n in manager.activations)
        start = client.call_async(OperatorCommand.Request(command='start_zero_force', external_contact_clear=True))
        spin(executor, start.done)
        assert start.result().success, start.result().message
        assert manager.states['zero_force_controller'] == 'active'
        assert analysis.zero_sample.trial_id == manager.zero_node.get_parameter('trial_id').value
        observe = client.call_async(OperatorCommand.Request(command='observe')); spin(executor, observe.done)
        assert observe.result().success and observe.result().stop_acknowledged
        assert 'drive holding' in observe.result().message
        assert manager.lifecycle == 'active' # Observation does not release/deactivate hardware.
    finally:
        close(nodes, executor)


@pytest.mark.parametrize('handoff,failure', [(False, ''), (True, ''), (True, 'baseline')])
def test_hardware_run_apply_and_checked_handoff(tmp_path, handoff, failure):
    analysis, manager, nodes, executor, _ = fixture(tmp_path, failure)
    try:
        commands = nodes[-1].create_client(OperatorCommand, '/calibration_analysis/operator_command')
        spin(executor, commands.service_is_ready)
        prepared = commands.call_async(OperatorCommand.Request(command='prepare')); spin(executor, prepared.done)
        assert prepared.result().success, prepared.result().message
        action = ActionClient(nodes[-1], RunCalibration, '/calibration_analysis/run_calibration')
        spin(executor, action.server_is_ready)
        goal_future = action.send_goal_async(RunCalibration.Goal(external_contact_clear=True, activate_zero_force_after=handoff))
        spin(executor, goal_future.done); goal = goal_future.result(); assert goal.accepted
        result = goal.get_result_async()
        spin(executor, lambda: analysis.stage == 'recording')
        manager.trial = analysis.capture.trial_id
        manager.zero_trial = manager.trial+1
        spin(executor, result.done, 25.)
        value = result.result().result
        if failure:
            assert not value.success and value.applied and not value.zero_force_active
            assert value.stop_acknowledged
            assert manager.states['zero_force_controller'] == manager.states['calibration_sequencer_controller'] == 'inactive'
            return
        assert value.success and value.applied, value.message
        assert value.zero_force_active == handoff
        assert manager.states['zero_force_controller'] == ('active' if handoff else 'inactive')
        assert manager.states['calibration_sequencer_controller'] == ('inactive' if handoff else 'active')
        document = yaml.safe_load((Path(value.trial_directory)/'result.yaml').read_text())
        assert document['provenance']['backend'] == 'ethercat'
        assert document['provenance']['model']['known_downstream_mass_kg'] is None
        if handoff:
            observed = commands.call_async(OperatorCommand.Request(command='observe')); spin(executor, observed.done)
            assert observed.result().success
        apply = nodes[-1].create_client(ApplyCalibration, '/calibration_analysis/apply_result')
        spin(executor, apply.service_is_ready)
        applied = apply.call_async(ApplyCalibration.Request(result_file=str(Path(value.trial_directory)/'result.yaml')))
        spin(executor, applied.done)
        assert applied.result().success, applied.result().message
    finally:
        close(nodes, executor)


@pytest.mark.parametrize('failure', ['cancel', 'stale', 'hardware'])
def test_hardware_readiness_and_trial_cleanup(tmp_path, failure):
    analysis, manager, nodes, executor, _ = fixture(tmp_path)
    try:
        commands = nodes[-1].create_client(OperatorCommand, '/calibration_analysis/operator_command')
        spin(executor, commands.service_is_ready)
        prepared = commands.call_async(OperatorCommand.Request(command='prepare')); spin(executor, prepared.done)
        assert prepared.result().success
        if failure == 'hardware':
            manager.lifecycle = 'inactive'
        action = ActionClient(nodes[-1], RunCalibration, '/calibration_analysis/run_calibration')
        spin(executor, action.server_is_ready)
        future = action.send_goal_async(RunCalibration.Goal(external_contact_clear=True)); spin(executor, future.done)
        goal = future.result(); result = goal.get_result_async()
        if failure != 'hardware':
            spin(executor, lambda: analysis.stage == 'recording')
            if failure == 'cancel':
                cancel = goal.cancel_goal_async(); spin(executor, cancel.done)
                assert cancel.result().goals_canceling
            else:
                manager.feedback = False
        spin(executor, result.done)
        value = result.result().result
        assert not value.success and not value.zero_force_active
        assert manager.states['zero_force_controller'] == manager.states['calibration_sequencer_controller'] == 'inactive'
        assert value.stop_acknowledged == (failure == 'cancel')
        if failure != 'cancel':
            assert 'STOP UNVERIFIED' in value.message
    finally:
        close(nodes, executor)


def test_missing_review_contact_and_saved_backend_rejected(tmp_path):
    analysis, manager, nodes, executor, settings = fixture(tmp_path)
    try:
        settings['installation_reviewed'] = False
        with pytest.raises(ValueError, match='review'):
            reviewed_profiles(settings)
        fit = Fit(valid=True, inertial_force_coefficient_kg=.25, r_squared=.999, sample_count=1000,
                  plateau_count=10, positive_slope_kg=.25, negative_slope_kg=.25)
        path = tmp_path/'simulation.yaml'
        path.write_text(yaml.safe_dump(dict(schema_version=1, units={'inertial_force_coefficient_kg':'kg','intercept_n':'N'},
            provenance={'backend':'gazebo','acceleration_source':SOURCE,'model':{}}, fit=asdict(fit))))
        with pytest.raises(ValueError, match='backend'):
            read_result(path, Criteria(), {'backend':'ethercat','model':{}})
        action = ActionClient(nodes[-1], RunCalibration, '/calibration_analysis/run_calibration')
        spin(executor, action.server_is_ready)
        future = action.send_goal_async(RunCalibration.Goal())
        spin(executor, future.done)
        result = future.result().get_result_async(); spin(executor, result.done)
        assert 'Clear external contact' in result.result().result.message
        assert not manager.activations
    finally:
        close(nodes, executor)
