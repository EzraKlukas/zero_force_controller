"""Wall-timer decimation on acquisition computer; never validates trial capture."""
import copy
from collections import deque
import math
import signal
import time
import rclpy
from rclpy.node import Node
from rclpy.clock import Clock, ClockType
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import JointState
from geometry_msgs.msg import WrenchStamped
from controller_manager_msgs.srv import ListHardwareComponents
from zfc_interfaces.msg import TelemetryBatch, PlotState, MeasuredState
from .streams import Source, joint_values, stamp_ns
from .plot_clock import PlotClock


class PlotRelay(Node):
    def __init__(self):
        super().__init__('plot_relay')
        self.declare_parameter('rate_hz', 100.)
        self.declare_parameter('freshness_s', .5)
        self.declare_parameter('configure_plotjuggler', False)
        self.declare_parameter('require_active_hardware', False)
        self.declare_parameter('hardware_component', 'StageSystem')
        rate = self.get_parameter('rate_hz').value
        self.timeout = self.get_parameter('freshness_s').value
        if not math.isfinite(rate) or not 1 <= rate <= 1000 or not math.isfinite(self.timeout) or self.timeout <= 0:
            raise ValueError('require rate_hz in [1,1000] and positive finite freshness_s')
        self.joint, self.force = Source(), Source()
        self.last_measured = None
        self.controllers = {}
        self.plot_publishers = {}
        self.sent = {}
        self.trials = {}
        self.queues = {}
        self.selected = {}
        self.decimated = {}
        self.period_ns = round(1e9/rate)
        self.hardware_future = None
        self.hardware_started = self.hardware_received = 0.
        self.hardware_ready = False
        self.hardware_detail = 'hardware state unavailable'
        self.hardware_client = self.create_client(ListHardwareComponents, '/controller_manager/list_hardware_components')
        self.measured = self.create_publisher(MeasuredState, '/plot/measured', 10)
        for name, short in (('zero_force_controller', 'zero_force'), ('calibration_sequencer_controller', 'calibration')):
            self.queues[name] = deque(maxlen=32) # Visualization loss is allowed; capture is separate.
            self.plot_publishers[name] = self.create_publisher(PlotState, '/plot/'+short, 10)
            self.create_subscription(TelemetryBatch, '/'+name+'/telemetry', lambda m, n=name: self.receive(n, m), 100)
        # BEST_EFFORT readers match both sensor-data and reliable broadcasters.
        self.create_subscription(JointState, '/joint_states', self.joints, qos_profile_sensor_data)
        self.create_subscription(WrenchStamped, '/load_cell_broadcaster/wrench', self.forces, qos_profile_sensor_data)
        self.create_timer(1./rate, self.publish, clock=Clock(clock_type=ClockType.STEADY_TIME))
        self.clock_config = PlotClock(self)
        if self.get_parameter('require_active_hardware').value:
            self.create_timer(.25, self.check_hardware, clock=Clock(clock_type=ClockType.STEADY_TIME))

    def check_hardware(self):
        # Observation only. No lifecycle changes and no command claims.
        if self.hardware_future is not None:
            if time.monotonic()-self.hardware_started < 1.:
                return
            old = self.hardware_future
            self.hardware_future = None
            old.cancel()
            self.hardware_ready = False
            self.hardware_detail = 'hardware-state query timed out'
        if self.hardware_client.service_is_ready():
            self.hardware_started = time.monotonic()
            self.hardware_future = self.hardware_client.call_async(ListHardwareComponents.Request())
            self.hardware_future.add_done_callback(self.hardware_result)
        else:
            self.hardware_ready = False
            self.hardware_detail = 'hardware-state service unavailable'

    def hardware_result(self, future):
        if future is not self.hardware_future:
            return
        self.hardware_future = None
        self.hardware_ready = False
        try:
            response = future.result()
            component = self.get_parameter('hardware_component').value
            stages = [c for c in response.component if c.name == component]
            required = {'carriage/position', 'carriage/velocity', 'load_cell/force.x', 'load_cell/force.y', 'load_cell/force.z'}
            self.hardware_ready = len(stages) == 1 and stages[0].state.label == 'active' and required <= {
                i.name for i in stages[0].state_interfaces if i.is_available}
            self.hardware_detail = '' if self.hardware_ready else component+' is not active with available SI state interfaces'
            self.hardware_received = time.monotonic()
        except Exception as error:
            self.hardware_detail = 'hardware-state query failed: '+str(error)

    def joints(self, msg):
        try:
            self.joint.accept(msg.header.stamp, joint_values(msg))
        except ValueError as error:
            self.joint.value, self.joint.error = None, str(error)

    def forces(self, msg):
        self.force.accept(msg.header.stamp, (msg.wrench.force.x, msg.wrench.force.y, msg.wrench.force.z))

    def receive(self, name, batch):
        for state in batch.samples:
            if state.trial_id <= 0 or state.sequence <= 0:
                self.controllers.pop(name, None)
                continue
            try:
                stamp = stamp_ns(state.stamp)
            except ValueError:
                self.controllers.pop(name, None)
                continue
            old = self.controllers.get(name)
            trial, sequence = self.trials.get(name, (0, 0))
            if state.trial_id < trial or (state.trial_id == trial and state.sequence <= sequence):
                continue # Late previous activation deliveries never mix trials.
            if old and state.trial_id == old[0].trial_id and stamp < stamp_ns(old[0].stamp):
                self.controllers.pop(name, None)
                self.queues[name].clear()
                self.selected.pop(name, None)
                continue
            self.trials[name] = state.trial_id, state.sequence
            self.controllers[name] = (copy.deepcopy(state), time.monotonic())
            previous_trial, previous_stamp = self.decimated.get(name, (None, 0))
            if previous_trial != state.trial_id:
                self.queues[name].clear()
                self.selected.pop(name, None)
            if previous_trial != state.trial_id or stamp-previous_stamp >= self.period_ns:
                self.queues[name].append(self.controllers[name])
                self.decimated[name] = state.trial_id, stamp

    def publish(self):
        now = time.monotonic()
        ros_ns = self.get_clock().now().nanoseconds
        jf, ff = self.joint.fresh(ros_ns, self.timeout, now), self.force.fresh(ros_ns, self.timeout, now)
        hardware_ok = not self.get_parameter('require_active_hardware').value or (
            self.hardware_ready and now-self.hardware_received < 1.)
        jf, ff = jf and hardware_ok, ff and hardware_ok
        key = self.joint.stamp, self.force.stamp, jf, ff
        if key != self.last_measured:
            msg = MeasuredState(joint_fresh=jf, force_fresh=ff, valid=jf and ff)
            if self.joint.stamp is not None:
                msg.header.stamp.sec, msg.header.stamp.nanosec = divmod(self.joint.stamp, 1000000000)
            if self.force.stamp is not None:
                msg.force_stamp.sec, msg.force_stamp.nanosec = divmod(self.force.stamp, 1000000000)
            msg.position_m, msg.velocity_mps = self.joint.value if jf else (math.nan, math.nan)
            msg.force_n = self.force.value[0] if ff else math.nan
            msg.detail = 'independent broadcaster source times; pairing is not synchronous' if msg.valid else (
                'joint: '+(self.joint.error or 'stale')+'; force: '+(self.force.error or 'stale'))
            if not hardware_ok:
                msg.detail += '; '+(self.hardware_detail or 'hardware-state report stale')
            self.measured.publish(msg)
            self.last_measured = key
        for name, publisher in self.plot_publishers.items():
            entry = self.controllers.get(name)
            active = hardware_ok and entry and now-entry[1] < self.timeout and 0 <= ros_ns-stamp_ns(entry[0].stamp) < self.timeout*1e9
            if active:
                while self.queues[name] and (now-self.queues[name][0][1] >= self.timeout or
                        not 0 <= ros_ns-stamp_ns(self.queues[name][0][0].stamp) < self.timeout*1e9):
                    self.queues[name].popleft()
                if self.queues[name]:
                    self.selected[name] = self.queues[name].popleft()
                selected = self.selected.get(name)
                if selected is None:
                    continue
                state = copy.deepcopy(selected[0])
                token = state.trial_id, state.sequence
                fields = ('position_m', 'velocity_mps', 'force_n', 'reference_position_m', 'reference_velocity_mps',
                          'reference_acceleration_mps2', 'baseline_force_n', 'noise_rms_n', 'residual_force_n')
                if not all(math.isfinite(getattr(state, f)) for f in fields):
                    state.valid = False
                    for field in fields:
                        setattr(state, field, math.nan)
            else:
                self.queues[name].clear()
                self.selected.pop(name, None)
                # Compatibility channels recover broadcaster fallback after EVERY
                # deactivation. MeasuredState is the authoritative plot measurement.
                state = PlotState().state
                token = ('idle', key)
                if self.joint.stamp is not None:
                    state.stamp.sec, state.stamp.nanosec = divmod(self.joint.stamp, 1000000000)
                state.position_m, state.velocity_mps = self.joint.value if jf else (math.nan, math.nan)
                state.force_n = self.force.value[0] if ff else math.nan
                for field in ('reference_position_m', 'reference_velocity_mps', 'reference_acceleration_mps2',
                              'baseline_force_n', 'noise_rms_n', 'residual_force_n'):
                    setattr(state, field, math.nan)
                state.valid = False # No controller reference; does not invalidate measured stream.
            if self.sent.get(name) == token:
                continue
            msg = PlotState(header=MeasuredState().header, state=state, inertial_compensation_n=math.nan)
            msg.header.stamp = state.stamp
            if state.phase == 3 and state.valid:
                msg.inertial_compensation_n = state.force_n-state.baseline_force_n-state.residual_force_n
            publisher.publish(msg)
            self.sent[name] = token


def main():
    rclpy.init()
    node = PlotRelay()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        signal.signal(signal.SIGINT, signal.SIG_IGN)
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()
