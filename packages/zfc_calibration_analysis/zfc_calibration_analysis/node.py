"""One non-RT coordinator. Single executor thread, reentrant async callbacks.

Every service wait yields an rclpy Future; wall-clock deadlines work when Gazebo
is paused. The executor continues subscriptions/cancellation/status while a
single worker performs fitting, CSV/YAML/plot writes or reusable-result reads.
No spin_until_future_complete, blocking service waits, or nested executor spins.
"""
from concurrent.futures import ThreadPoolExecutor
from dataclasses import asdict
import math
from pathlib import Path
import signal
import time
import yaml

import rclpy
from rclpy.action import ActionServer, GoalResponse, CancelResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.clock import Clock, ClockType
from rclpy.executors import SingleThreadedExecutor
from rclpy.node import Node
from rclpy.parameter import Parameter, parameter_value_to_python
from rclpy.qos import QoSProfile, DurabilityPolicy
from rclpy.task import Future
from controller_manager_msgs.srv import ListControllers, SwitchController, ConfigureController
from rcl_interfaces.srv import GetParameters, ListParameters, SetParametersAtomically
from rcl_interfaces.msg import ParameterDescriptor
from sensor_msgs.msg import JointState
from std_msgs.msg import Bool, Float64, Header
from zfc_interfaces.action import RunCalibration
from zfc_interfaces.msg import TelemetryBatch, TrialStatus, AnalysisState, CalibrationResult
from zfc_interfaces.srv import ApplyCalibration
from .analysis import Capture, Criteria, Fit, reserve_trial, save_trial, save_application, SOURCE


class Interrupted(RuntimeError):
    pass


def fit_message(fit):
    return CalibrationResult(**asdict(fit))


def read_result(path, criteria):
    data = yaml.safe_load(Path(path).read_text())
    if data.get('schema_version') != 1 or data.get('units', {}).get('inertial_force_coefficient_kg') != 'kg':
        raise ValueError('unsupported result schema/units')
    fit = Fit(**data['fit'])
    if not fit.valid or fit.acceleration_source != SOURCE:
        raise ValueError('result is invalid or uses a different acceleration source')
    values = asdict(fit)
    if not all(math.isfinite(v) for v in values.values() if isinstance(v, (int, float))):
        raise ValueError('non-finite result')
    if not 0 < fit.inertial_force_coefficient_kg*criteria.expected_coefficient_sign <= criteria.maximum_coefficient_kg:
        raise ValueError('result coefficient sign/magnitude rejected')
    if fit.r_squared < criteria.minimum_r_squared or fit.residual_rms_n > criteria.maximum_residual_rms_n:
        raise ValueError('result quality rejected')
    if fit.sample_count < 2*criteria.minimum_plateaus_per_branch*criteria.minimum_plateau_samples or fit.plateau_count < 2*criteria.minimum_plateaus_per_branch or fit.uncertainty_kg < 0:
        raise ValueError('result coverage/uncertainty rejected')
    k = fit.inertial_force_coefficient_kg
    if fit.positive_slope_kg*criteria.expected_coefficient_sign <= 0 or fit.negative_slope_kg*criteria.expected_coefficient_sign <= 0 or abs(fit.positive_slope_kg-fit.negative_slope_kg) > abs(k)*criteria.maximum_branch_difference_fraction:
        raise ValueError('result branch polarity/consistency rejected')
    return fit


class CalibrationAnalysis(Node):
    def __init__(self):
        super().__init__('calibration_analysis')
        self.group = ReentrantCallbackGroup()
        self.wall_clock = Clock(clock_type=ClockType.STEADY_TIME)
        defaults = dict(backend='gazebo', controller_manager='/controller_manager',
                        calibration_controller='calibration_sequencer_controller',
                        zero_force_controller='zero_force_controller', output_directory='/tmp/zfc-calibration-trials',
                        service_timeout_s=8., capture_timeout_s=120., drain_timeout_s=8.,
                        baseline_timeout_s=15., maximum_samples=120000, known_downstream_mass_kg=.25)
        defaults.update(asdict(Criteria()))
        for name, value in defaults.items():
            self.declare_parameter(name, value, ParameterDescriptor(read_only=True))
        self.settings = {name: self.get_parameter(name).value for name in defaults}
        self.criteria = Criteria(**{name: self.settings[name] for name in asdict(Criteria())})
        self.criteria.validate()
        if self.settings['backend'] not in ('gazebo', 'ethercat'):
            raise ValueError('backend must be gazebo or ethercat')
        if self.settings['maximum_samples'] < 2 or any(not math.isfinite(self.settings[k]) or self.settings[k] <= 0 for k in ('service_timeout_s', 'capture_timeout_s', 'drain_timeout_s', 'baseline_timeout_s')):
            raise ValueError('positive finite deadlines and bounded capacity required')
        if not Path(self.settings['output_directory']).is_absolute():
            raise ValueError('output_directory must be absolute')
        if not math.isfinite(self.settings['known_downstream_mass_kg']) or not 0 < self.settings['known_downstream_mass_kg'] <= 10.05:
            raise ValueError('known simulation downstream mass must be finite and positive')
        self.cal, self.zero = self.settings['calibration_controller'], self.settings['zero_force_controller']
        manager = self.settings['controller_manager'].rstrip('/')
        self.list_client = self.create_client(ListControllers, manager+'/list_controllers', callback_group=self.group)
        self.switch_client = self.create_client(SwitchController, manager+'/switch_controller', callback_group=self.group)
        self.configure_client = self.create_client(ConfigureController, manager+'/configure_controller', callback_group=self.group)
        self.parameter_clients = {}
        for controller in (self.cal, self.zero):
            self.parameter_clients[controller] = {
                'get': self.create_client(GetParameters, '/'+controller+'/get_parameters', callback_group=self.group),
                'list': self.create_client(ListParameters, '/'+controller+'/list_parameters', callback_group=self.group),
                'set': self.create_client(SetParametersAtomically, '/'+controller+'/set_parameters_atomically', callback_group=self.group)}
        self.worker = ThreadPoolExecutor(max_workers=1, thread_name_prefix='calibration-files-fit')
        self.file_job = self.worker.submit(lambda: True) # Worker readiness before any claim.
        self.busy = False
        self.unresolved_stop = False
        self.capture = None
        self.capture_armed = False
        self.known_old_trials = set()
        self.last_trial = 0
        self.stage = 'idle'
        self.detail = 'idle; motion is never started by node startup'
        self.progress = 0.
        self.fit = Fit()
        self.stop_acknowledged = True
        self.ready = False
        self.force_enabled = None
        self.force_enabled_received = 0.
        self.applied_force = None
        self.force_received = 0.
        self.force_desired = None
        self.joint = None
        self.zero_sample = None
        self.last_clock_ns = 0
        self.time_error = ''
        self.status_publisher = self.create_publisher(AnalysisState, '~/state', QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL))
        self.force_publisher = self.create_publisher(Bool, '/simulation/force_enable', 10)
        self.create_subscription(Bool, '/simulation/ready', lambda m: setattr(self, 'ready', m.data), QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL), callback_group=self.group)
        self.create_subscription(Bool, '/simulation/force_enabled', self.force_ack, 10, callback_group=self.group)
        self.create_subscription(Float64, '/simulation/applied_force', self.force_value, 10, callback_group=self.group)
        self.create_subscription(JointState, '/joint_states', self.joints, 10, callback_group=self.group)
        self.create_subscription(TelemetryBatch, '/'+self.cal+'/telemetry', self.batch, 200, callback_group=self.group)
        self.create_subscription(TelemetryBatch, '/'+self.zero+'/telemetry', self.zero_batch, 200, callback_group=self.group)
        self.create_subscription(TrialStatus, '/'+self.cal+'/trial_status', self.terminal, QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL), callback_group=self.group)
        self.action = ActionServer(self, RunCalibration, '~/run_calibration', self.execute,
                                   goal_callback=self.goal, cancel_callback=lambda _: CancelResponse.ACCEPT,
                                   callback_group=self.group)
        self.create_service(ApplyCalibration, '~/apply_result', self.apply_service, callback_group=self.group)
        self.create_timer(.1, self.tick, clock=self.wall_clock, callback_group=self.group)
        self.goal_handle = None

    def force_ack(self, m):
        self.force_enabled, self.force_enabled_received = m.data, time.monotonic()

    def force_value(self, m):
        self.applied_force, self.force_received = m.data, time.monotonic()

    def joints(self, m):
        if 'carriage' in m.name:
            index = m.name.index('carriage')
            if len(m.position) > index and len(m.velocity) > index:
                self.joint = (m.position[index], m.velocity[index], time.monotonic())

    def batch(self, m):
        if not self.capture_armed:
            for sample in m.samples:
                self.known_old_trials.add(sample.trial_id)
                self.last_trial = max(self.last_trial, sample.trial_id)
            return
        # Only explicitly known previous trials may be late DDS deliveries.
        filtered = [s for s in m.samples if s.trial_id not in self.known_old_trials]
        if filtered:
            copy = TelemetryBatch(samples=filtered, dropped_samples=m.dropped_samples,
                                  failed_publication_samples=m.failed_publication_samples)
            self.capture.batch(copy)

    def zero_batch(self, m):
        if m.samples:
            self.zero_sample = m.samples[-1]
            self.last_trial = max(self.last_trial, self.zero_sample.trial_id)

    def terminal(self, m):
        self.last_trial = max(self.last_trial, m.trial_id)
        if self.capture_armed and m.trial_id == self.capture.trial_id:
            self.capture.finish(m)
        else:
            self.known_old_trials.add(m.trial_id)

    def tick(self):
        now = self.get_clock().now().nanoseconds
        if self.busy and self.last_clock_ns and now < self.last_clock_ns:
            self.time_error = 'ROS/simulation clock moved backwards; restart full session'
        self.last_clock_ns = now
        if self.force_desired is not None:
            self.force_publisher.publish(Bool(data=self.force_desired))
        stages = ['idle', 'preparing', 'stopping', 'recording', 'draining', 'analyzing', 'applying', 'baseline', 'complete', 'canceled', 'failed']
        state = AnalysisState(header=Header(stamp=self.get_clock().now().to_msg()), trial_id=self.capture.trial_id if self.capture else 0,
                              stage=self.stage, stage_code=stages.index(self.stage), progress=self.progress, detail=self.detail,
                              recorded_samples=len(self.capture.rows) if self.capture else 0,
                              dropped_samples=self.capture.dropped if self.capture else 0,
                              final_sequence=self.capture.final_sequence if self.capture else 0,
                              stop_acknowledged=self.stop_acknowledged, fit=fit_message(self.fit))
        self.status_publisher.publish(state)
        if self.goal_handle and self.goal_handle.is_active:
            self.goal_handle.publish_feedback(RunCalibration.Feedback(state=state))

    async def sleep(self, seconds=.02):
        future = Future()
        timer = self.create_timer(seconds, lambda: future.set_result(True) if not future.done() else None,
                                  clock=self.wall_clock, callback_group=self.group)
        try:
            await future
        finally:
            self.destroy_timer(timer)

    def check(self, cancellable=True):
        if cancellable and self.goal_handle and self.goal_handle.is_cancel_requested:
            raise Interrupted('calibration canceled')
        if self.time_error:
            raise Interrupted(self.time_error)
        if self.capture_armed and self.capture.error:
            raise Interrupted(self.capture.error)
        if self.stage in ('recording', 'draining', 'analyzing', 'applying', 'baseline') and self.force_desired is False and not self.force_is(False):
            raise Interrupted('force interlock or applied-force freshness lost')
        if self.stage in ('analyzing', 'applying') and not self.stationary():
            raise Interrupted('finished sequencer is no longer stationary')

    async def wait(self, predicate, seconds, reason, checked=True):
        deadline = time.monotonic()+seconds
        while not predicate():
            if checked:
                self.check()
            if time.monotonic() >= deadline:
                raise Interrupted('timeout: '+reason)
            await self.sleep()
        if checked:
            self.check()

    async def call(self, client, request, checked=True):
        await self.wait(client.service_is_ready, self.settings['service_timeout_s'], client.srv_name+' unavailable', checked)
        future = client.call_async(request)
        # Do not abandon an in-flight switch/parameter write on cancellation.
        # Its checked result/timeout is followed by explicit stop verification.
        await self.wait(future.done, self.settings['service_timeout_s'], client.srv_name+' response', False)
        result = future.result()
        if result is None:
            raise Interrupted(client.srv_name+' returned no response')
        if checked:
            self.check()
        return result

    async def states(self, checked=True):
        response = await self.call(self.list_client, ListControllers.Request(), checked)
        states = {c.name: c.state for c in response.controller}
        if self.cal not in states or self.zero not in states:
            raise Interrupted('both configured motion controllers are required')
        return states

    async def switch(self, activate=(), deactivate=(), checked=True):
        request = SwitchController.Request(activate_controllers=list(activate), deactivate_controllers=list(deactivate),
                                           strictness=SwitchController.Request.STRICT)
        request.timeout.sec = max(1, int(self.settings['service_timeout_s'])-2)
        response = await self.call(self.switch_client, request, checked)
        if not response.ok:
            raise Interrupted('STRICT controller switch rejected')
        states = await self.states(checked)
        if any(states[name] != 'active' for name in activate) or any(states[name] != 'inactive' for name in deactivate):
            raise Interrupted('STRICT switch acknowledgment does not match controller states')

    async def stop(self):
        self.stage = 'stopping'
        self.force_desired = False
        self.stop_acknowledged = False
        # Even after cancellation/bad data, services and subscriptions stay live.
        states = await self.states(False)
        active = [n for n in (self.cal, self.zero) if states[n] == 'active']
        if active:
            await self.switch(deactivate=active, checked=False)
        states = await self.states(False)
        # Humble transitions an activation-ERROR controller to unconfigured and
        # releases its interfaces. Configure it back to INACTIVE only; never retry
        # activation. If settings/configuration remain invalid, report unverified
        # cleanup instead of pretending the requested inactive state was reached.
        for name in (self.cal, self.zero):
            if states[name] == 'unconfigured':
                response = await self.call(self.configure_client, ConfigureController.Request(name=name), False)
                if not response.ok:
                    raise Interrupted('could not restore '+name+' to configured inactive state')
        states = await self.states(False)
        if any(states[n] != 'inactive' for n in (self.cal, self.zero)):
            raise Interrupted('motion inactive state could not be verified')
        await self.wait(lambda: self.stationary() and self.force_is(False), self.settings['service_timeout_s'], 'stationary inactive/force-disabled acknowledgment', False)
        # A second checked list guards against a delayed preceding service reply.
        await self.sleep(.1)
        states = await self.states(False)
        if any(states[n] != 'inactive' for n in (self.cal, self.zero)):
            raise Interrupted('late controller activation detected during cleanup')
        self.stop_acknowledged = True

    def stationary(self):
        return self.joint is not None and time.monotonic()-self.joint[2] < .5 and all(math.isfinite(v) for v in self.joint[:2]) and abs(self.joint[1]) < .001

    def force_is(self, enabled):
        now = time.monotonic()
        return self.force_enabled == enabled and now-self.force_enabled_received < .5 and now-self.force_received < .5 and self.applied_force is not None and math.isfinite(self.applied_force) and abs(self.applied_force) < 1e-9

    async def parameter_snapshot(self, controller):
        listing = await self.call(self.parameter_clients[controller]['list'], ListParameters.Request())
        names = listing.result.names
        response = await self.call(self.parameter_clients[controller]['get'], GetParameters.Request(names=names))
        return {name: parameter_value_to_python(value) for name, value in zip(names, response.values)}

    async def set_parameters(self, controller, **values):
        states = await self.states()
        if states[controller] != 'inactive':
            raise Interrupted(controller+' must be inactive before parameter application')
        request = SetParametersAtomically.Request(parameters=[Parameter(k, value=v).to_parameter_msg() for k, v in values.items()])
        response = await self.call(self.parameter_clients[controller]['set'], request)
        if not response.result.successful:
            raise Interrupted('atomic parameter application rejected: '+response.result.reason)

    def goal(self, _):
        if self.busy or self.unresolved_stop or not self.file_job.done() or self.settings['backend'] != 'gazebo':
            return GoalResponse.REJECT
        self.busy = True
        return GoalResponse.ACCEPT

    async def worker_result(self, future, checked=True):
        # Poll worker future, never wait on it synchronously in executor callbacks.
        await self.wait(future.done, 30., 'fit/file worker', checked)
        return future.result()

    def submit_worker(self, function, *args):
        if not self.file_job.done():
            raise Interrupted('previous fit/file worker has not drained; restart after inspection')
        self.file_job = self.worker.submit(function, *args)
        return self.file_job

    async def execute(self, goal):
        self.goal_handle = goal
        self.capture = None
        self.capture_armed = False
        self.time_error = ''
        self.fit = Fit()
        self.progress = 0.
        self.stop_acknowledged = False
        directory = ''
        metadata = {}
        fit_job = None
        result = RunCalibration.Result()
        try:
            self.stage, self.detail = 'preparing', 'release/inhibit force; configure inactive sequencer; subscribe before claim'
            self.force_desired = False
            await self.wait(lambda: self.ready and self.force_is(False), self.settings['service_timeout_s'], 'simulation ready and force interlock')
            await self.stop()
            self.check()
            parameters = await self.parameter_snapshot(self.cal)
            zero_parameters = await self.parameter_snapshot(self.zero)
            trial = max(time.time_ns(), self.last_trial+1, int(parameters['trial_id'])+1, int(zero_parameters['trial_id'])+1)
            if trial >= 2**63-2:
                raise Interrupted('positive int64 trial-ID space exhausted')
            self.last_trial = trial
            directory = str(Path(self.settings['output_directory'])/str(trial))
            await self.worker_result(self.submit_worker(reserve_trial, directory))
            self.capture = Capture(trial, self.settings['maximum_samples'], self.criteria.maximum_gap_s)
            # Armed BEFORE parameter/switch requests; all early sequence records retained.
            self.capture_armed = True
            parameters['trial_id'] = trial
            await self.set_parameters(self.cal, trial_id=trial)
            metadata = {'trial_id': trial, 'backend': self.settings['backend'], 'controller': self.cal,
                        'use_sim_time': self.get_parameter('use_sim_time').value,
                        'parameters': parameters, 'zero_force_parameters_before': zero_parameters,
                        'model': {'sensor_frame': 'load_cell_link +X upward', 'force_path': 'parent_to_child, child frame',
                                  'known_downstream_mass_kg': self.settings['known_downstream_mass_kg'],
                                  'session_coordinate': 'known simulated mid-travel startup; not hardware lower stop'},
                        'acceleration_source': SOURCE, 'capture_counts': {}}
            self.stage, self.detail = 'recording', 'STRICT activation; synchronized full-rate batches'
            self.stop_acknowledged = False
            await self.switch(activate=[self.cal])
            deadline = time.monotonic()+self.settings['capture_timeout_s']
            while not self.capture.terminal:
                self.check()
                if not self.force_is(False):
                    raise Interrupted('force interlock/applied force lost during trial')
                if time.monotonic() >= deadline:
                    raise Interrupted('bounded capture timeout (pause or missing completion)')
                if self.capture.rows:
                    self.progress = min(.8, len(self.capture.rows)/40000*.8)
                await self.sleep()
            self.stage, self.detail = 'draining', 'terminal received; waiting for exact final source sequence'
            await self.wait(lambda: self.capture.drained, self.settings['drain_timeout_s'], 'final batch drain')
            self.capture_armed = False
            self.known_old_trials.add(trial)
            self.progress = .85
            await self.wait(self.stationary, self.settings['service_timeout_s'], 'stationary finished sequencer')
            self.stop_acknowledged = True
            metadata['capture_counts'] = {'recorded': len(self.capture.rows), 'final_sequence': self.capture.final_sequence,
                                          'dropped': self.capture.dropped, 'first_sequence': self.capture.rows[0][0]}
            self.stage, self.detail = 'analyzing', 'sequencer holds; worker fits and saves CSV/result/regression'
            fit_job = self.submit_worker(save_trial, directory, tuple(self.capture.rows), metadata, self.criteria)
            self.fit = await self.worker_result(fit_job)
            if not self.fit.valid:
                raise Interrupted('fit rejected: '+self.fit.reason)
            self.stage, self.detail = 'applying', 'checked atomic update while zero-force inactive'
            await self.set_parameters(self.zero, inertial_force_coefficient_kg=self.fit.inertial_force_coefficient_kg)
            result.applied = True
            # Confirm the parameter service value. Activation separately refreshes logic settings.
            applied = await self.parameter_snapshot(self.zero)
            if applied['inertial_force_coefficient_kg'] != self.fit.inertial_force_coefficient_kg:
                raise Interrupted('applied coefficient readback mismatch')
            if goal.request.activate_zero_force_after:
                self.stage, self.detail = 'baseline', 'STRICT handoff; measured-position hold and fresh baseline/noise'
                await self.set_parameters(self.zero, trial_id=trial+1)
                self.zero_sample = None
                await self.switch(activate=[self.zero], deactivate=[self.cal])
                await self.wait(lambda: self.zero_sample is not None and self.zero_sample.trial_id == trial+1 and self.zero_sample.phase in (3, 5),
                                self.settings['baseline_timeout_s'], 'zero-force baseline/noise completion')
                if not self.zero_sample.valid or self.zero_sample.phase != 3:
                    raise Interrupted('zero-force activation/baseline fault')
                if not self.force_is(False):
                    raise Interrupted('force interlock lost during baseline capture')
                self.force_desired = True
                await self.wait(lambda: self.force_is(True), self.settings['service_timeout_s'], 'released force re-enable acknowledgment')
                self.force_desired = None
                result.zero_force_active = True
            else:
                # Successful, stationary sequencer remains holding during/manual after analysis.
                self.force_desired = None # Remains inhibited until explicitly enabled by operator.
            await self.worker_result(self.submit_worker(save_application, directory, result.applied,
                                                       result.zero_force_active, self.fit.inertial_force_coefficient_kg))
            self.progress = 1.
            self.stage, self.detail = 'complete', 'validated result applied; '+('zero-force compliant after new baseline' if result.zero_force_active else 'sequencer stationary hold; zero-force inactive')
            result.success, result.message = True, self.detail
            goal.succeed()
        except Exception as error:
            self.detail = str(error)
            self.capture_armed = False
            if self.capture:
                self.known_old_trials.add(self.capture.trial_id)
            try:
                await self.stop()
                result.zero_force_active = False
            except Exception as stop_error:
                self.unresolved_stop = True
                self.detail += '; STOP UNVERIFIED: '+str(stop_error)
            if self.time_error:
                self.unresolved_stop = True # Full session restart required after a time reset.
            try:
                if fit_job:
                    await self.worker_result(fit_job, False)
                if self.capture and directory:
                    metadata.update(trial_id=self.capture.trial_id, backend=self.settings['backend'],
                                    capture_counts={'recorded': len(self.capture.rows), 'final_sequence': self.capture.final_sequence, 'dropped': self.capture.dropped})
                    await self.worker_result(self.submit_worker(save_trial, directory, tuple(self.capture.rows), metadata, self.criteria, self.detail), False)
            except Exception as file_error:
                self.detail += '; incomplete-trial persistence failed: '+str(file_error)
            self.stage = 'canceled' if goal.is_cancel_requested else 'failed'
            result.message = self.detail
            # A successfully applied VALID fit is not rolled back, but cancellation
            # never activates zero-force and the trial is saved incomplete.
            if goal.is_cancel_requested:
                goal.canceled()
            else:
                goal.abort()
        finally:
            result.trial_id = self.capture.trial_id if self.capture else 0
            result.trial_directory = directory
            result.fit = fit_message(self.fit)
            result.stop_acknowledged = self.stop_acknowledged
            self.goal_handle = None
            self.busy = False
            self.tick()
        return result

    async def apply_service(self, request, response):
        if self.busy or self.unresolved_stop or not self.file_job.done():
            response.message = 'another operation or unresolved stop is pending'
            return response
        if self.settings['backend'] != 'gazebo':
            response.message = 'physical commissioning is not enabled by this simulated workflow'
            return response
        self.busy = True
        try:
            fit = await self.worker_result(self.submit_worker(read_result, request.result_file, self.criteria))
            states = await self.states()
            if states[self.zero] != 'inactive':
                raise Interrupted('zero-force must be inactive; apply service never switches motion')
            await self.set_parameters(self.zero, inertial_force_coefficient_kg=fit.inertial_force_coefficient_kg)
            self.fit = fit
            response.success, response.message, response.fit = True, 'validated reusable result applied; activate explicitly', fit_message(fit)
        except Exception as error:
            response.message = str(error)
        finally:
            self.busy = False
        return response

    def close(self):
        self.action.destroy()
        self.worker.shutdown(wait=True, cancel_futures=True)


def main():
    rclpy.init()
    node = CalibrationAnalysis()
    executor = SingleThreadedExecutor()
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        signal.signal(signal.SIGINT, signal.SIG_IGN)
        # Shutdown is not a controller stop acknowledgment. Cancel the action and
        # await its result BEFORE terminating this node/launch in normal operation.
        executor.shutdown()
        node.close()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()
