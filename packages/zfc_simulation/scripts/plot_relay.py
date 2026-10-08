#!/usr/bin/env python3
"""Non-RT, timestamp-decimated plotting; never modifies calibration capture."""
import rclpy
import math
import signal
from rclpy.node import Node
from zfc_interfaces.msg import TelemetryBatch, PlotState
from sensor_msgs.msg import JointState
from geometry_msgs.msg import WrenchStamped
from rcl_interfaces.srv import SetParameters
from rclpy.parameter import Parameter


class PlotRelay(Node):
    def __init__(self):
        super().__init__("plot_relay")
        self.last = {}
        self.joint = self.force = None
        self.publishers_by_controller = {}
        for name, short in (("zero_force_controller", "zero_force"),
                            ("calibration_sequencer_controller", "calibration")):
            self.publishers_by_controller[name] = self.create_publisher(PlotState, "/plot/"+short, 10)
            self.create_subscription(TelemetryBatch, "/"+name+"/telemetry",
                lambda m, n=name: self.receive(n, m), 100)
        self.create_subscription(JointState, "/joint_states", lambda m: setattr(self, "joint", m), 10)
        self.create_subscription(WrenchStamped, "/load_cell_broadcaster/wrench", lambda m: setattr(self, "force", m), 10)
        self.create_timer(.01, self.seed_inactive)
        self.declare_parameter("configure_plotjuggler", False)
        self.plot_client = self.create_client(SetParameters, "/plotjuggler/set_parameters")
        self.plot_future = None
        self.create_timer(1., self.configure_plot_clock)

    def configure_plot_clock(self):
        # The stock ROS2 streamer creates its node only when Start is clicked.
        # Its CLI does not accept ROS launch parameter files. Configure it here,
        # asynchronously outside all controller updates; headers remain primary.
        if not self.get_parameter("configure_plotjuggler").value or self.plot_future is not None:
            return
        if self.plot_client.service_is_ready():
            request = SetParameters.Request()
            request.parameters = [Parameter("use_sim_time", value=True).to_parameter_msg()]
            self.plot_future = self.plot_client.call_async(request)
            self.plot_future.add_done_callback(self.plot_clock_result)

    def plot_clock_result(self, future):
        result = future.result()
        if result is None or not all(r.successful for r in result.results):
            self.get_logger().error("Could not set PlotJuggler use_sim_time; use header timestamps and check its parameters")

    def seed_inactive(self):
        # Make the live measured channels available before manual activation.
        # This is explicitly phase=idle, valid=false, trial=0; no reference exists.
        if self.joint is None or self.force is None:
            return
        index = self.joint.name.index("carriage")
        for name, publisher in self.publishers_by_controller.items():
            if name in self.last:
                continue
            msg = PlotState()
            msg.header.stamp = msg.state.stamp = self.joint.header.stamp
            msg.state.valid = False
            msg.state.position_m = self.joint.position[index]
            msg.state.velocity_mps = self.joint.velocity[index]
            msg.state.force_n = self.force.wrench.force.x
            msg.state.reference_position_m = math.nan
            msg.state.reference_velocity_mps = math.nan
            msg.state.reference_acceleration_mps2 = math.nan
            publisher.publish(msg)

    def receive(self, name, batch):
        for state in batch.samples:
            stamp = state.stamp.sec*1000000000+state.stamp.nanosec
            trial, previous = self.last.get(name, (None, -10000000))
            if trial != state.trial_id or stamp < previous or stamp-previous >= 10000000:
                msg = PlotState()
                msg.header.stamp, msg.state = state.stamp, state
                if state.phase == 3 and state.valid:
                    msg.inertial_compensation_n = state.force_n-state.baseline_force_n-state.residual_force_n
                self.publishers_by_controller[name].publish(msg)
                self.last[name] = (state.trial_id, stamp)


def main():
    rclpy.init()
    node = PlotRelay()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        signal.signal(signal.SIGINT, signal.SIG_IGN)  # launch may forward a second SIGINT
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
