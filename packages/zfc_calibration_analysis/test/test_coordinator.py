"""Standard-service fixtures only; NOT a production controller/backend."""
from pathlib import Path
import sys
import time
import pytest
sys.path.insert(0, str(Path(__file__).parents[1]))
import rclpy
from rclpy.action import ActionClient
from rclpy.executors import SingleThreadedExecutor
from rclpy.node import Node
from rcl_interfaces.msg import SetParametersResult
from controller_manager_msgs.msg import ControllerState
from controller_manager_msgs.srv import ListControllers, SwitchController
from std_msgs.msg import Bool, Float64
from sensor_msgs.msg import JointState
from zfc_interfaces.action import RunCalibration
from zfc_interfaces.msg import TelemetryBatch, TrialStatus, ControllerState as Sample
from rclpy.qos import QoSProfile, DurabilityPolicy
from zfc_calibration_analysis.node import CalibrationAnalysis
from zfc_calibration_analysis.node import read_result
from zfc_calibration_analysis.analysis import Criteria, Fit
from dataclasses import asdict
import yaml


class Services(Node):
    def __init__(self):
        super().__init__('analysis_test_manager')
        self.states = {'calibration_sequencer_controller': 'inactive', 'zero_force_controller': 'inactive'}
        self.create_service(ListControllers, '/controller_manager/list_controllers', self.list)
        self.create_service(SwitchController, '/controller_manager/switch_controller', self.switch)
        self.ack = self.create_publisher(Bool, '/simulation/force_enabled', 10)
        self.force = self.create_publisher(Float64, '/simulation/applied_force', 10)
        self.joint = self.create_publisher(JointState, '/joint_states', 10)
        self.enabled = False
        self.create_subscription(Bool, '/simulation/force_enable', lambda m: setattr(self, 'enabled', m.data), 10)
        self.create_timer(.02, self.publish)

    def list(self, _, response):
        response.controller = [ControllerState(name=k, state=v) for k, v in self.states.items()]
        return response

    def switch(self, request, response):
        for n in request.deactivate_controllers:
            self.states[n] = 'inactive'
        for n in request.activate_controllers:
            self.states[n] = 'active'
        response.ok = True
        return response

    def publish(self):
        self.ack.publish(Bool(data=self.enabled))
        self.force.publish(Float64(data=0.))
        self.joint.publish(JointState(name=['carriage'], position=[0.], velocity=[0.]))


def spin_until(executor, predicate, seconds=6):
    deadline = time.monotonic()+seconds
    while not predicate() and time.monotonic() < deadline:
        executor.spin_once(timeout_sec=.01)
    assert predicate(), 'test fixture deadline'


@pytest.mark.parametrize('failure', ['cancel', 'reject', 'timeout', 'time_jump', 'fit'])
def test_async_responsiveness_and_inactive_failure(failure):
    rclpy.init(args=['--ros-args', '-p', 'service_timeout_s:=0.5', '-p', 'capture_timeout_s:=1.0'])
    executor = SingleThreadedExecutor()
    nodes = []
    try:
        analysis = CalibrationAnalysis(); analysis.ready = True
        manager = Services()
        cal, zero = Node('calibration_sequencer_controller'), Node('zero_force_controller')
        for node in (cal, zero):
            node.declare_parameter('trial_id', 0)
        if failure == 'reject':
            cal.add_on_set_parameters_callback(lambda _: SetParametersResult(successful=False, reason='test rejected trial parameter'))
        if failure == 'timeout':
            analysis.list_client = analysis.create_client(ListControllers, '/missing/list_controllers')
        nodes = [analysis, manager, cal, zero]
        for node in nodes:
            executor.add_node(node)
        client = ActionClient(zero, RunCalibration, '/calibration_analysis/run_calibration')
        spin_until(executor, client.server_is_ready)
        future = client.send_goal_async(RunCalibration.Goal(activate_zero_force_after=True))
        spin_until(executor, future.done)
        goal = future.result(); assert goal.accepted
        result = goal.get_result_async()
        if failure in ('cancel', 'time_jump', 'fit'):
            spin_until(executor, lambda: analysis.stage == 'recording')
            overlap = client.send_goal_async(RunCalibration.Goal())
            spin_until(executor, overlap.done)
            assert not overlap.result().accepted
            if failure == 'cancel':
                cancellation = goal.cancel_goal_async()
                spin_until(executor, cancellation.done)
                assert cancellation.result().goals_canceling
            elif failure == 'time_jump':
                analysis.time_error = 'simulator restarted/backward clock'
            else:
                samples = cal.create_publisher(TelemetryBatch, '/calibration_sequencer_controller/telemetry', 100)
                terminal = cal.create_publisher(TrialStatus, '/calibration_sequencer_controller/trial_status', QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL))
                spin_until(executor, lambda: samples.get_subscription_count() > 0)
                trial = analysis.capture.trial_id
                rows = []
                for i in range(1600):
                    a = [.2, -.2, .4, -.4, .8, -.8, 1.2, -1.2][i//200]
                    sample = Sample(trial_id=trial, sequence=i+1, valid=True, phase=10,
                                    force_n=2.4525-.25*a, velocity_mps=.05, reference_velocity_mps=.05,
                                    reference_acceleration_mps2=a)
                    sample.stamp.sec, sample.stamp.nanosec = divmod(i*1000000, 1000000000)
                    rows.append(sample)
                for start in range(0, len(rows), 256):
                    samples.publish(TelemetryBatch(samples=rows[start:start+256]))
                terminal.publish(TrialStatus(trial_id=trial, final_sequence=len(rows), completed=True,
                                            successful=True, capture_complete=True, phase=12))
        # A rejected fit persists both its regression and incomplete metadata.
        # Do not assume matplotlib/disk latency is below six seconds under load.
        spin_until(executor, result.done, seconds=20)
        value = result.result().result
        assert not value.success and not value.applied and not value.zero_force_active
        assert manager.states['zero_force_controller'] == 'inactive'
        assert manager.states['calibration_sequencer_controller'] == 'inactive'
        assert value.stop_acknowledged == (failure != 'timeout')
        if failure == 'fit':
            assert 'fit rejected' in value.message, value.message
        assert analysis.force_enabled_received > 0, 'subscriptions stayed responsive while awaiting services/action'
        if failure == 'timeout':
            assert analysis.unresolved_stop
    finally:
        executor.shutdown()
        for node in nodes:
            if isinstance(node, CalibrationAnalysis):
                node.close()
            node.destroy_node()
        rclpy.shutdown()


@pytest.mark.parametrize('invalid', ['sign', 'units', 'source', 'quality', 'nonfinite', 'coverage'])
def test_reusable_result_validation(tmp_path, invalid):
    fit = Fit(valid=True, inertial_force_coefficient_kg=.25, r_squared=.999,
              sample_count=1000, plateau_count=10, positive_slope_kg=.25, negative_slope_kg=.25)
    data = dict(schema_version=1, units={'inertial_force_coefficient_kg': 'kg'}, fit=asdict(fit))
    if invalid == 'sign':
        data['fit']['inertial_force_coefficient_kg'] = -.25
    elif invalid == 'units':
        data['units']['inertial_force_coefficient_kg'] = 'counts'
    elif invalid == 'source':
        data['fit']['acceleration_source'] = 'measured velocity difference'
    elif invalid == 'quality':
        data['fit']['r_squared'] = .5
    elif invalid == 'coverage':
        data['fit']['plateau_count'] = 1
    else:
        data['fit']['intercept_n'] = float('nan')
    path = tmp_path/'result.yaml'; path.write_text(yaml.safe_dump(data))
    with pytest.raises(ValueError):
        read_result(path, Criteria())
