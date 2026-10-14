"""Late/restarted PlotJuggler streamers: bounded asynchronous configuration."""
import time
from rcl_interfaces.srv import SetParameters
from rclpy.parameter import Parameter
from rclpy.clock import Clock, ClockType


class PlotClock:
    def __init__(self, node):
        self.node = node
        self.client = node.create_client(SetParameters, '/plotjuggler/set_parameters')
        self.future = None
        self.started = 0.
        self.timer = node.create_timer(1., self.tick, clock=Clock(clock_type=ClockType.STEADY_TIME))

    def tick(self):
        if self.future is not None:
            if time.monotonic()-self.started < 2.:
                return
            self.future.cancel()
            self.future = None
            self.node.get_logger().warning('PlotJuggler clock request timed out; retrying asynchronously')
        if self.node.get_parameter('configure_plotjuggler').value and self.client.service_is_ready():
            request = SetParameters.Request(parameters=[Parameter('use_sim_time', value=bool(
                self.node.get_parameter('use_sim_time').value)).to_parameter_msg()])
            self.started = time.monotonic()
            self.future = self.client.call_async(request)
            self.future.add_done_callback(self.done)

    def done(self, future):
        if future is not self.future:
            return
        self.future = None
        try:
            result = future.result()
            if result is None or len(result.results) != 1 or not result.results[0].successful:
                raise RuntimeError('streamer rejected use_sim_time')
        except Exception as error:
            self.node.get_logger().error('PlotJuggler clock configuration failed: '+str(error))
        # Repeat idempotently: restarting the streamer recreates its ROS node.
