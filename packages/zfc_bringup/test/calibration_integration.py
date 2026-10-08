#!/usr/bin/env python3
"""Prompt-3 opt-in real Fortress/action acceptance; only owns its process group.

Reuses the established Prompt-2 check subscriptions and service helpers. This is
a test consumer, not a new recorder/controller implementation.
"""
import argparse
import json
import math
import os
from pathlib import Path
import signal
import subprocess
import time
import pandas as pd
import rclpy
from rclpy.action import ActionClient
from rcl_interfaces.srv import GetParameters
from std_msgs.msg import Bool
from zfc_interfaces.action import RunCalibration
from zfc_interfaces.srv import ApplyCalibration
from zfc_interfaces.msg import AnalysisState, TelemetryBatch, ControllerState
from headless_integration import Check


class AnalysisCheck(Check):
    def __init__(self, default_goal=False):
        super().__init__()
        self.default_goal = default_goal
        self.analysis_state = None
        self.create_subscription(AnalysisState, '/calibration_analysis/state', lambda m: setattr(self, 'analysis_state', m), 100)
        self.action = ActionClient(self, RunCalibration, '/calibration_analysis/run_calibration')
        self.enable = self.create_publisher(Bool, '/simulation/force_enable', 10)

    def goal(self, activate=True):
        self.wait(self.action.server_is_ready, 10, 'analysis action')
        pending = self.action.send_goal_async(RunCalibration.Goal(activate_zero_force_after=activate))
        self.wait(pending.done, 5, 'action goal acknowledgment')
        return pending.result()

    def inactive(self):
        states = {c.name: c.state for c in self.controllers()}
        assert states['zero_force_controller'] == states['calibration_sequencer_controller'] == 'inactive', states

    def run(self):
        cal, zero = 'calibration_sequencer_controller', 'zero_force_controller'
        self.wait(lambda: self.ready and self.joint is not None, 65, 'simulation startup')
        self.inactive()
        assert sum(name == 'controller_manager' and ns == '/' for name, ns in self.get_node_names_and_namespaces()) == 1
        assert sum(name == 'calibration_analysis' for name, _ in self.get_node_names_and_namespaces()) == 1
        initial = self.q()
        goal = self.goal(activate=not self.default_goal); assert goal.accepted
        result_future = goal.get_result_async()
        self.wait(lambda: self.analysis_state is not None and self.analysis_state.stage == 'recording', 15, 'coordinator recording')
        overlap = self.goal(); assert not overlap.accepted
        # Challenge ONLY the inhibit: the real applied force must stay zero.
        self.force, self.heartbeat = 3., True
        self.advance(.2)
        assert self.applied == 0.
        self.force, self.heartbeat = 0., False
        self.wait(result_future.done, 110, 'fit/apply/baseline handoff')
        result = result_future.result().result
        print('RunCalibration result:', result, flush=True)
        assert result.success and result.applied and result.zero_force_active == (not self.default_goal), result.message
        fit = result.fit
        assert fit.valid and abs(fit.inertial_force_coefficient_kg-.25)/.25 < .05
        states = {c.name: c.state for c in self.controllers()}
        if self.default_goal:
            assert states[cal] == 'active' and states[zero] == 'inactive'
            print('PASS: default-false goal applies fit and leaves sequencer stationary hold, zero-force inactive', flush=True)
            self.parameters(zero, trial_id=result.trial_id+1)
            self.switch([zero], [cal])
            self.wait(lambda: self.records[zero] and self.records[zero][-1].phase == 3, 15, 'manual baseline/noise')
            self.enable.publish(Bool(data=True))
            self.advance(.2)
        else:
            assert states[cal] == 'inactive' and states[zero] == 'active'
        directory = Path(result.trial_directory)
        data = pd.read_csv(directory/'samples.csv')
        metadata = json.loads((directory/'metadata.json').read_text())
        counts = metadata['capture_counts']
        assert metadata['complete'] and counts['dropped'] == 0
        assert list(data.sequence) == list(range(1, counts['final_sequence']+1))
        assert data.iloc[-1].phase == 12 and abs(data.iloc[-1].velocity_mps) < .001
        assert abs(data.iloc[0].position_m-initial) < .001
        assert (directory/'regression.png').is_file() and (directory/'result.yaml').is_file()
        response = self.call(GetParameters, '/'+zero+'/get_parameters', GetParameters.Request(names=['inertial_force_coefficient_kg']))
        assert response.values[0].double_value == fit.inertial_force_coefficient_kg
        zero_records = [s for s in self.records[zero] if s.trial_id == result.trial_id+1]
        baseline = [s for s in zero_records if s.phase in (1, 2)]
        assert len(baseline) >= 1900 and max(s.position_m for s in baseline)-min(s.position_m for s in baseline) < .00003
        assert max(abs(s.reference_position_m-s.position_m) for s in baseline) < 1e-12
        print(f'PASS: {len(data)} early-to-final samples, {fit.plateau_count} plateaus; k={fit.inertial_force_coefficient_kg:.7f} kg, error={abs(fit.inertial_force_coefficient_kg-.25)/.25:.2%}; R²={fit.r_squared:.8f}, RMS={fit.residual_rms_n:.6f} N', flush=True)
        for force, sign in ((1., 1), (-1., -1)):
            start = self.q()
            self.force, self.heartbeat = force, True
            self.advance(.6)
            assert (self.q()-start)*sign > .0001
            self.force = 0.
            self.advance(2.)
            assert self.applied == 0. and abs(self.joint.velocity[0]) < .0001
            released = self.q(); self.advance(.5)
            assert abs(self.q()-released) < .00003
        self.heartbeat = False
        zero_records = [s for s in self.records[zero] if s.trial_id == result.trial_id+1]
        compensation = []
        for previous, current in zip(zero_records, zero_records[1:]):
            if current.phase == previous.phase == 3:
                observed = current.force_n-current.baseline_force_n-current.residual_force_n
                expected = fit.inertial_force_coefficient_kg*previous.reference_acceleration_mps2
                compensation.append(abs(observed-expected))
        assert compensation and max(compensation) < 1e-9, 'next activation must CONSUME fitted coefficient'
        print('PASS: measured-position baseline hold; fitted coefficient consumed; upward/downward/released pushes without stale-force drift', flush=True)
        # Apply while active must reject without switching or changing settings.
        apply = self.call(ApplyCalibration, '/calibration_analysis/apply_result', ApplyCalibration.Request(result_file=str(directory/'result.yaml')))
        assert not apply.success
        # A new action safely deactivates zero-force; cancel while sequencer moves.
        canceled = self.goal(); assert canceled.accepted
        pending = canceled.get_result_async()
        old_trial = result.trial_id
        self.wait(lambda: self.analysis_state and self.analysis_state.trial_id > old_trial and self.analysis_state.recorded_samples > 50, 15, 'new trial early samples')
        request = canceled.cancel_goal_async(); self.wait(request.done, 5, 'cancel accepted')
        assert request.result().goals_canceling
        self.wait(pending.done, 20, 'controlled cancellation result')
        canceled_result = pending.result().result
        assert not canceled_result.success and not canceled_result.applied and canceled_result.stop_acknowledged
        self.inactive()
        incomplete = json.loads((Path(canceled_result.trial_directory)/'metadata.json').read_text())
        assert not incomplete['complete'] and incomplete['fit']['reason']
        print('PASS: overlap rejection, active apply rejection, cancellation acknowledged; incomplete trial saved and both controllers inactive', flush=True)
        # Explicit reusable-result application, without activation.
        apply = self.call(ApplyCalibration, '/calibration_analysis/apply_result', ApplyCalibration.Request(result_file=str(directory/'result.yaml')))
        assert apply.success, apply.message
        self.inactive()
        # Invalid envelope fails checked STRICT activation, never applies/activates zero.
        self.parameters(cal, excursion_limit_m=.0001)
        failed = self.goal(); assert failed.accepted
        pending = failed.get_result_async(); self.wait(pending.done, 20, 'invalid trajectory activation failure')
        value = pending.result().result
        print('Invalid activation result:', value.message, value.stop_acknowledged, flush=True)
        assert not value.success and not value.applied and value.stop_acknowledged
        self.inactive()
        self.parameters(cal, excursion_limit_m=.06)
        # Malformed synchronized data injected into the EXISTING telemetry channel
        # tests the coordinator failure path (test-only, no alternate recorder).
        bad = self.goal(); assert bad.accepted
        pending = bad.get_result_async()
        self.wait(lambda: self.analysis_state and self.analysis_state.stage == 'recording' and self.analysis_state.recorded_samples > 20, 15, 'bad-data trial active')
        publisher = self.create_publisher(TelemetryBatch, '/'+cal+'/telemetry', 10)
        self.advance(.1)
        publisher.publish(TelemetryBatch(samples=[ControllerState(trial_id=self.analysis_state.trial_id+500, sequence=1, valid=True)]))
        self.wait(pending.done, 20, 'bad-data controlled stop')
        value = pending.result().result
        assert not value.success and not value.applied and value.stop_acknowledged and 'identity' in value.message
        self.inactive()
        print('PASS: reusable apply leaves inactive; invalid activation and mismatched-trial data fail closed', flush=True)
        # Deliberately unsupported GUI-style time reset: detect it and fail safe.
        # Normal reset remains a FULL launch/session restart, never a silent re-zero.
        jumping = self.goal(); assert jumping.accepted
        pending = jumping.get_result_async()
        self.wait(lambda: self.analysis_state and self.analysis_state.stage == 'recording' and self.analysis_state.recorded_samples > 20, 15, 'time-jump trial active')
        reset = subprocess.run(['ign', 'service', '-s', '/world/zfc/control',
            '--reqtype', 'ignition.msgs.WorldControl', '--reptype', 'ignition.msgs.Boolean',
            '--timeout', '3000', '--req', 'reset: {time_only: true}'], capture_output=True, text=True, timeout=5)
        assert reset.returncode == 0 and 'data: true' in reset.stdout
        self.wait(pending.done, 20, 'backward simulation time failure cleanup')
        value = pending.result().result
        assert not value.success and not value.applied and not value.zero_force_active
        states = {c.name: c.state for c in self.controllers()}
        assert states[zero] == 'inactive'
        if value.stop_acknowledged:
            self.inactive()
        else:
            assert 'STOP UNVERIFIED' in value.message
            blocked = self.goal(); assert not blocked.accepted
            print('LIMITATION: Fortress backward reset stalls stock control; deactivation unacknowledged. Force inhibited, zero-force inactive, further actions blocked; FULL restart required.', flush=True)
        assert self.applied == 0. and all(math.isfinite(x) for x in self.joint.position+self.joint.velocity)
        print('PASS: actual time reset fails explicitly without applying/activating zero-force', flush=True)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--log', default='/tmp/zfc-calibration-acceptance.log')
    parser.add_argument('--default-goal', action='store_true', help='exercise default false, then explicit manual handoff')
    parser.add_argument('--startup-only', action='store_true', help='fresh-session inactive startup and no implicit result loading')
    args = parser.parse_args()
    os.environ.update(ROS_LOCALHOST_ONLY='1', ROS_DOMAIN_ID='83', IGN_PARTITION='zfc_calibration_'+str(os.getpid()), ROS_LOG_DIR='/tmp/zfc-calibration-acceptance-ros')
    signal.signal(signal.SIGALRM, lambda *_: (_ for _ in ()).throw(TimeoutError('240 s acceptance watchdog')))
    signal.alarm(240)
    with Path(args.log).open('w') as log:
        process = subprocess.Popen(['ros2', 'launch', 'zfc_bringup', 'local.launch.py', 'backend:=gazebo', 'gui:=false', 'plot:=false'], stdout=log, stderr=subprocess.STDOUT, start_new_session=True)
        node = None
        try:
            rclpy.init(); node = AnalysisCheck(args.default_goal)
            if args.startup_only:
                node.wait(lambda: node.ready and node.joint is not None, 65, 'fresh startup')
                node.inactive()
                parameter = node.call(GetParameters, '/zero_force_controller/get_parameters', GetParameters.Request(names=['inertial_force_coefficient_kg']))
                assert parameter.values[0].double_value == 0.
                node.wait(lambda: node.analysis_state is not None and node.analysis_state.stage == 'idle', 5, 'analysis idle')
                print('PASS: full session restart restores inactive controllers, idle analysis, no implicit fit loading', flush=True)
            else:
                node.run()
        finally:
            if node:
                node.force = 0.; node.send_force(); node.destroy_node()
            if rclpy.ok():
                rclpy.shutdown()
            os.killpg(process.pid, signal.SIGINT)
            try:
                process.wait(timeout=10)
            except subprocess.TimeoutExpired:
                os.killpg(process.pid, signal.SIGTERM)
                try:
                    process.wait(timeout=5)
                except subprocess.TimeoutExpired:
                    os.killpg(process.pid, signal.SIGKILL); process.wait(timeout=5)
            signal.alarm(0)
            print('Owned launch group cleaned up; log: '+args.log, flush=True)


if __name__ == '__main__':
    main()
