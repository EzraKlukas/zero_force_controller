#!/usr/bin/env python3
"""Finite startup gate. No command-interface claims and no experiment activation."""
import math
import time
import signal
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, DurabilityPolicy
from controller_manager_msgs.srv import ListControllers, ListHardwareInterfaces, SwitchController
from geometry_msgs.msg import WrenchStamped
from sensor_msgs.msg import JointState
from rosgraph_msgs.msg import Clock
from std_msgs.msg import Bool


class Startup(Node):
    def __init__(self):
        super().__init__("simulation_ready")
        self.declare_parameter("tool_mass_kg", .2)
        self.raw = self.wrench = self.joint = None
        self.clock = 0
        self.raw_count = 0
        self.deadline = None
        self.create_subscription(WrenchStamped, "/simulation/raw_load_cell", self.raw_cb, 10)
        self.create_subscription(WrenchStamped, "/load_cell_broadcaster/wrench",
                                 lambda m: setattr(self, "wrench", m), 10)
        self.create_subscription(JointState, "/joint_states",
                                 lambda m: setattr(self, "joint", m), 10)
        self.create_subscription(Clock, "/clock", self.clock_cb, 10)
        self.ready = self.create_publisher(Bool, "/simulation/ready",
            QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL))

    def raw_cb(self, msg):
        if all(math.isfinite(v) for v in
               (msg.wrench.force.x, msg.wrench.force.y, msg.wrench.force.z)):
            self.raw = msg
            self.raw_count += 1

    def clock_cb(self, msg):
        self.clock = msg.clock.sec * 1000000000 + msg.clock.nanosec

    def call(self, typ, service, request):
        client = self.create_client(typ, "/controller_manager/" + service)
        try:
            remaining = lambda: min(5., max(0., self.deadline-time.monotonic()))
            if not client.wait_for_service(timeout_sec=remaining()):
                return None
            future = client.call_async(request)
            rclpy.spin_until_future_complete(self, future, timeout_sec=remaining())
            return future.result() if future.done() else None
        finally:
            self.destroy_client(client)

    def start(self):
        deadline = time.monotonic() + 60
        self.deadline = deadline
        names = {"zero_force_controller", "calibration_sequencer_controller",
                 "joint_state_broadcaster", "load_cell_broadcaster"}
        expected = (.05 + self.get_parameter("tool_mass_kg").value) * 9.81
        while time.monotonic() < deadline and rclpy.ok():
            rclpy.spin_once(self, timeout_sec=.1)
            response = self.call(ListControllers, "list_controllers", ListControllers.Request())
            if response is None or not names.issubset({c.name for c in response.controller}):
                continue
            if any(c.state == "active" for c in response.controller if c.name in names):
                raise RuntimeError("Simulation startup requires all four controllers inactive")
            if any(c.state != "inactive" for c in response.controller if c.name in names):
                continue  # Loaded is not yet configured; wait for the spawner.
            interfaces = self.call(ListHardwareInterfaces, "list_hardware_interfaces",
                                   ListHardwareInterfaces.Request())
            if interfaces is None:
                continue
            command = [i for i in interfaces.command_interfaces if i.name == "carriage/position"]
            if not command or not command[0].is_available or command[0].is_claimed:
                continue
            if len([i for i in interfaces.state_interfaces if i.is_available]) != 5:
                continue
            if self.clock <= 0 or self.raw_count < 3 or abs(self.raw.wrench.force.x - expected) > .1:
                continue
            request = SwitchController.Request()
            request.activate_controllers = ["joint_state_broadcaster", "load_cell_broadcaster"]
            request.strictness = SwitchController.Request.STRICT
            request.timeout.sec = 5
            result = self.call(SwitchController, "switch_controller", request)
            if result is None or not result.ok:
                raise RuntimeError("Broadcaster activation failed")
            break
        else:
            raise RuntimeError("60 s startup timeout: manager/interfaces/clock/valid force not ready")
        while time.monotonic() < deadline and rclpy.ok():
            rclpy.spin_once(self, timeout_sec=.1)
            if self.joint is None or self.wrench is None:
                continue
            q = self.joint.position[self.joint.name.index("carriage")]
            v = self.joint.velocity[self.joint.name.index("carriage")]
            f = self.wrench.wrench.force.x
            if all(math.isfinite(x) for x in (q, v, f)) and abs(q) < .001 and abs(v) < .001 and abs(f-expected) < .1:
                self.ready.publish(Bool(data=True))
                self.get_logger().info(f"SIMULATION_READY: q={q:.6f} m F.x={f:.6f} N; motion INACTIVE")
                return
        raise RuntimeError("Broadcasters did not expose finite stationary SI/gravity data")


def main():
    rclpy.init()
    node = Startup()
    try:
        node.start()
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        signal.signal(signal.SIGINT, signal.SIG_IGN)
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
