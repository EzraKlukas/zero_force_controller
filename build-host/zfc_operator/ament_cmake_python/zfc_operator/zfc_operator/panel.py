"""Qt main thread, ROS worker, asynchronous calls; coordinator owns sequencing."""
import os
import queue
import signal
import sys
import threading
import time
import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node
from rclpy.clock import Clock, ClockType
from rclpy.executors import SingleThreadedExecutor
from rclpy.qos import QoSProfile, DurabilityPolicy
from controller_manager_msgs.srv import ListControllers, ListHardwareComponents
from action_msgs.srv import CancelGoal
from zfc_interfaces.action import RunCalibration
from zfc_interfaces.msg import AnalysisState, MeasuredState
from zfc_interfaces.srv import ApplyCalibration, OperatorCommand
from .plot_clock import PlotClock


class PanelNode(Node):
    def __init__(self, report=lambda _: None):
        super().__init__('operator_panel')
        self.declare_parameter('backend', 'ethercat')
        self.declare_parameter('configure_plotjuggler', True)
        self.report = report
        self.commands = queue.SimpleQueue()
        self.pending = self.remote_busy = self.cancel_requested = False
        self.goal = self.analysis = self.measured = None
        self.cancel_wait = False
        self.received = self.measured_received = 0.
        self.message = 'No automatic activation on launch or reconnect'
        self.controllers = self.hardware = 'unknown'
        self.polls = {}
        self.operations = self.create_client(OperatorCommand, '/calibration_analysis/operator_command')
        self.apply = self.create_client(ApplyCalibration, '/calibration_analysis/apply_result')
        self.action = ActionClient(self, RunCalibration, '/calibration_analysis/run_calibration')
        self.cancel_client = self.create_client(CancelGoal, '/calibration_analysis/run_calibration/_action/cancel_goal')
        self.list_controllers = self.create_client(ListControllers, '/controller_manager/list_controllers')
        self.list_hardware = self.create_client(ListHardwareComponents, '/controller_manager/list_hardware_components')
        self.create_subscription(AnalysisState, '/calibration_analysis/state', self.status, QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL))
        self.create_subscription(MeasuredState, '/plot/measured', self.measurement, 10)
        self.clock_config = PlotClock(self)
        self.wall_clock = Clock(clock_type=ClockType.STEADY_TIME)
        self.create_timer(.05, self.dispatch, clock=self.wall_clock)
        self.create_timer(.5, self.poll, clock=self.wall_clock)

    def status(self, msg):
        self.analysis, self.received, self.remote_busy = msg, time.monotonic(), msg.operation_pending
        if self.cancel_wait and not msg.operation_pending and msg.stage in ('canceled', 'failed', 'complete'):
            self.cancel_wait = self.pending = False
            self.message = 'FINAL coordinator status: '+msg.detail+('' if msg.stop_acknowledged else '; STOP UNVERIFIED')

    def measurement(self, msg):
        self.measured, self.measured_received = msg, time.monotonic()

    def enqueue(self, command, contact=False, handoff=False, path=''):
        self.commands.put((command, contact, handoff, path))

    def dispatch(self):
        while not self.commands.empty():
            command, contact, handoff, path = self.commands.get()
            if command == 'cancel':
                self.cancel_requested = True
                if self.goal:
                    self.goal.cancel_goal_async().add_done_callback(self.cancel_ack)
                elif self.remote_busy and self.cancel_client.service_is_ready():
                    self.cancel_wait = self.pending = True
                    self.cancel_client.call_async(CancelGoal.Request()).add_done_callback(self.cancel_ack)
                self.message = 'Cancel requested; waiting for FINAL cleanup acknowledgment'
                continue
            if self.pending or self.remote_busy:
                self.message = 'Another operation is pending; conflicting request rejected'
                continue
            if time.monotonic()-self.received > 2. or self.analysis is None:
                self.message = 'Coordinator status unavailable; operation refused'
                continue
            self.pending = True
            self.cancel_requested = False
            self.message = 'Request pending: '+command
            if command == 'calibrate':
                if not self.action.server_is_ready():
                    self.pending = False; self.message = 'Calibration action unavailable'
                    continue
                self.action.send_goal_async(RunCalibration.Goal(activate_zero_force_after=handoff, external_contact_clear=contact)).add_done_callback(self.goal_reply)
            else:
                client = self.apply if command == 'apply' else self.operations
                if not client.service_is_ready():
                    self.pending = False; self.message = 'Coordinator service unavailable'
                    continue
                request = ApplyCalibration.Request(result_file=path) if command == 'apply' else OperatorCommand.Request(command=command, external_contact_clear=contact)
                client.call_async(request).add_done_callback(self.service_reply)

    def service_reply(self, future):
        try:
            result = future.result()
            self.message = ('Success: ' if result.success else 'FAILED: ')+result.message
            if hasattr(result, 'stop_acknowledged') and not result.stop_acknowledged:
                self.message += '; STOP UNVERIFIED'
            self.pending = False
        except Exception as error:
            self.message = 'REQUEST OUTCOME UNKNOWN; STOP UNVERIFIED: '+str(error)

    def goal_reply(self, future):
        try:
            self.goal = future.result()
            if not self.goal.accepted:
                self.pending = False; self.goal = None
                self.message = 'Calibration request rejected; inspect coordinator status'
                return
            self.goal.get_result_async().add_done_callback(self.trial_reply)
            if self.cancel_requested:
                self.goal.cancel_goal_async().add_done_callback(self.cancel_ack)
        except Exception as error:
            self.message = 'GOAL OUTCOME UNKNOWN; STOP UNVERIFIED: '+str(error)

    def cancel_ack(self, future):
        try:
            if not future.result().goals_canceling:
                self.message = 'Cancellation not accepted; await FINAL result and inspect states'
        except Exception as error:
            self.message = 'Cancel acknowledgment unavailable: '+str(error)

    def trial_reply(self, future):
        try:
            result = future.result().result
            self.message = result.message+'\nResult directory on acquisition computer: '+result.trial_directory
            if not result.stop_acknowledged:
                self.message += '; STOP UNVERIFIED'
            self.goal = None; self.pending = False
        except Exception as error:
            self.message = 'TRIAL OUTCOME UNKNOWN; STOP UNVERIFIED: '+str(error)

    def poll(self):
        now = time.monotonic()
        for label, client, request in (('controllers', self.list_controllers, ListControllers.Request()), ('hardware', self.list_hardware, ListHardwareComponents.Request())):
            existing = self.polls.get(label)
            if existing and not existing[0].done():
                if now-existing[1] < 2.:
                    continue
                existing[0].cancel()
                setattr(self, label, 'unavailable (network/service timeout)')
            if client.service_is_ready():
                future = client.call_async(request)
                self.polls[label] = future, now
                future.add_done_callback(lambda f, key=label: self.poll_reply(key, f))
            else:
                setattr(self, label, 'unavailable')
        connected = self.analysis is not None and now-self.received < 2. and self.analysis.backend == self.get_parameter('backend').value
        state = self.analysis
        backend = state.backend if connected else self.get_parameter('backend').value+' (unverified)'
        detail = f'Backend: {backend}; domain={os.environ.get("ROS_DOMAIN_ID", "0")}; RMW={os.environ.get("RMW_IMPLEMENTATION", "distro default")}; localhost={os.environ.get("ROS_LOCALHOST_ONLY", "unset")}\n'
        detail += 'StageSystem: '+self.hardware+'\nControllers / command ownership: '+self.controllers+'\n'
        if self.measured and now-self.measured_received < 2.:
            detail += f'Measured: joint fresh={self.measured.joint_fresh}, force fresh={self.measured.force_fresh}; {self.measured.detail}\n'
        else:
            detail += 'Measured data unavailable/stale\n'
        if connected:
            detail += f'{state.stage}: {state.progress:.0%}; {state.detail}\nFit valid={state.fit.valid}, k={state.fit.inertial_force_coefficient_kg:g} kg; {state.fit.reason}\nTrial path: {state.trial_directory}\n'
            if not state.stop_acknowledged:
                detail += 'STOP UNVERIFIED / operation in progress; inspect final acknowledgment\n'
        else:
            detail += 'NETWORK/COORDINATOR STATUS LOST; STOP UNVERIFIED. No automatic restart.\n'
        self.report({'text': detail+self.message, 'busy': self.pending or self.remote_busy, 'connected': connected,
                     'trial': self.goal is not None or self.remote_busy, 'physical': backend == 'ethercat'})

    def poll_reply(self, label, future):
        if self.polls.get(label, (None,))[0] is not future or future.cancelled():
            return
        try:
            response = future.result()
            text = '; '.join(c.name+': '+c.state+' claims='+','.join(c.claimed_interfaces) for c in response.controller) if label == 'controllers' else '; '.join(c.name+': '+c.state.label+' commands='+','.join(i.name+(' [claimed]' if i.is_claimed else ' [unclaimed]') for i in c.command_interfaces) for c in response.component)
            setattr(self, label, text)
        except Exception:
            setattr(self, label, 'unavailable')


def main():
    headless = '--headless' in sys.argv
    args = [a for a in sys.argv if a != '--headless']
    rclpy.init(args=args)
    if headless:
        node = PanelNode()
        try:
            rclpy.spin(node)
        except KeyboardInterrupt:
            pass
        finally:
            node.destroy_node()
            if rclpy.ok():
                rclpy.shutdown()
        return
    from PyQt5 import QtCore, QtWidgets

    class Reports(QtCore.QObject):
        changed = QtCore.pyqtSignal(object)

    app = QtWidgets.QApplication(args[:1]); reports = Reports()
    node = PanelNode(reports.changed.emit)
    executor = SingleThreadedExecutor(); executor.add_node(node)
    worker = threading.Thread(target=executor.spin, name='operator-ros', daemon=True)
    widget = QtWidgets.QWidget(); widget.setWindowTitle('ZFC operator — observation keeps drive holding')
    layout = QtWidgets.QVBoxLayout(widget)
    status = QtWidgets.QLabel('Waiting for coordinator'); status.setWordWrap(True)
    status.setTextFormat(QtCore.Qt.PlainText)
    status.setTextInteractionFlags(QtCore.Qt.TextSelectableByMouse); layout.addWidget(status)
    instruction = QtWidgets.QLabel('Clear external contact for calibration and fresh baseline/noise capture. Sensors cannot prove no human contact.\nUI/network loss does not stop Jetson control or recording. Cancel and await FINAL cleanup before shutdown. This panel is not an emergency stop.')
    instruction.setWordWrap(True); layout.addWidget(instruction)
    contact = QtWidgets.QCheckBox('External contact is clear for this request and will remain clear during capture')
    handoff = QtWidgets.QCheckBox('Activate zero-force after calibration (default off)')
    layout.addWidget(contact); layout.addWidget(handoff)
    path = QtWidgets.QLineEdit(); path.setPlaceholderText('Absolute result.yaml path on acquisition computer'); layout.addWidget(path)
    buttons = {}
    for title, command in (('Prepare hardware (sensor broadcasters only)', 'prepare'), ('Calibrate and analyze', 'calibrate'),
                           ('Apply saved result', 'apply'), ('Start zero-force with fresh baseline', 'start_zero_force'),
                           ('Return to observation — drive holding', 'observe'), ('Cancel trial; await final cleanup', 'cancel')):
        button = QtWidgets.QPushButton(title); layout.addWidget(button); buttons[command] = button
        def submit(_, cmd=command):
            node.enqueue(cmd, contact.isChecked(), handoff.isChecked(), path.text())
            if cmd in ('calibrate', 'start_zero_force'):
                contact.setChecked(False)
        button.clicked.connect(submit)

    def update(data):
        status.setText(data['text'])
        for command, button in buttons.items():
            button.setEnabled(data['trial'] if command == 'cancel' else data['connected'] and not data['busy'])
        if not data['physical']:
            buttons['prepare'].setEnabled(False)
        handoff.setEnabled(not data['busy']); contact.setEnabled(not data['busy']); path.setEnabled(not data['busy'])
    reports.changed.connect(update)
    widget.resize(860, 640); widget.show(); worker.start()
    signal.signal(signal.SIGINT, lambda *_: app.quit())
    timer = QtCore.QTimer(); timer.timeout.connect(lambda: None); timer.start(100)
    try:
        app.exec_()
    finally:
        executor.shutdown(timeout_sec=2.); worker.join(timeout=2.)
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()
