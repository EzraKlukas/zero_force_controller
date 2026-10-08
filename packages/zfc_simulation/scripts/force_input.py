#!/usr/bin/env python3
"""Simulation-only COM force, +Z upward. One writer at a time; no joint claims.

GUI defaults to zero; CLI pulse duration follows simulation time. Heartbeats
refresh a bounded replacement command, NOT a persistent additive wrench.
"""
import argparse
import math
import signal
import time
import rclpy
from rclpy.node import Node
from ros_gz_interfaces.msg import Entity, EntityWrench
from std_msgs.msg import Bool
from rclpy.qos import QoSProfile, DurabilityPolicy


class ForceInput(Node):
    def __init__(self):
        super().__init__("simulation_force_input")
        self.force = 0.
        self.ready = False
        self.enabled = False
        self.create_subscription(Bool, "/simulation/force_enabled", self.interlock, 10)
        self.pub = self.create_publisher(EntityWrench, "/simulation/force_input", 10)
        self.create_subscription(Bool, "/simulation/ready", lambda m: setattr(self, "ready", m.data),
            QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL))
        # ROS time: a paused experiment does not consume a scripted pulse.
        self.create_timer(.05, self.send)

    def send(self):
        m = EntityWrench()
        m.entity.name, m.entity.type = "stage::tool_link", Entity.LINK
        m.wrench.force.z = self.force if self.ready and self.enabled else 0.
        self.pub.publish(m)

    def interlock(self, msg):
        if msg.data != self.enabled:
            self.force = 0. # Re-enable cannot resurrect a disabled GUI/CLI request.
        self.enabled = msg.data
        if not self.enabled:
            self.force = 0.


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--gui", action="store_true")
    parser.add_argument("--force", type=float, default=0., help="signed world-Z force, N")
    parser.add_argument("--duration", type=float, default=1., help="pulse duration, simulation seconds")
    parser.add_argument("--timeout", type=float, default=60., help="CLI wall-time watchdog, seconds")
    args, ros_args = parser.parse_known_args()
    if not all(math.isfinite(x) for x in (args.force, args.duration, args.timeout)) or abs(args.force) > 10 or args.duration <= 0 or args.timeout <= 0:
        parser.error("finite force within +/-10 N, positive duration and timeout required")
    rclpy.init(args=ros_args)
    node = ForceInput()
    try:
        if args.gui:
            from PyQt5.QtCore import Qt, QTimer
            from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QSlider, QLabel, QPushButton
            app = QApplication([])
            signal.signal(signal.SIGINT, lambda *_: app.quit())
            signal.signal(signal.SIGTERM, lambda *_: app.quit())
            window = QWidget()
            window.setWindowTitle("Simulation tool force (+Z upward); one input writer")
            layout = QVBoxLayout(window)
            label = QLabel("0.00 N — release before calibration")
            slider = QSlider(Qt.Horizontal)
            slider.setRange(-1000, 1000)
            def change(value):
                node.force = value/100.
                label.setText(f"{node.force:+.2f} N (+Z upward)")
                node.send()  # Release/changes are immediate even while paused.
            slider.valueChanged.connect(change)
            layout.addWidget(label)
            layout.addWidget(slider)
            for title, value in (("Push up (+1 N)", 100), ("Push down (-1 N)", -100), ("Release", 0)):
                button = QPushButton(title)
                button.clicked.connect(lambda checked=False, v=value: slider.setValue(v))
                layout.addWidget(button)
            timer = QTimer()
            def poll():
                rclpy.spin_once(node, timeout_sec=0)
                slider.setEnabled(node.enabled)
                if not node.enabled:
                    slider.setValue(0)
                    label.setText("Calibration interlock — force disabled")
            timer.timeout.connect(poll)
            timer.start(10)
            window.show()
            app.exec()
        else:
            deadline = time.monotonic()+args.timeout
            while (not node.ready or not node.enabled or node.get_clock().now().nanoseconds == 0) and time.monotonic() < deadline:
                rclpy.spin_once(node, timeout_sec=.05)
            if not node.ready or not node.enabled or node.get_clock().now().nanoseconds == 0:
                raise RuntimeError("Simulation readiness timeout")
            start = node.get_clock().now().nanoseconds
            node.force = args.force
            node.send()
            while (node.get_clock().now().nanoseconds-start)*1e-9 < args.duration:
                if time.monotonic() >= deadline:
                    raise RuntimeError("Pulse wall-time watchdog expired (is simulation paused?)")
                rclpy.spin_once(node, timeout_sec=.02)
    except KeyboardInterrupt:
        pass
    finally:
        signal.signal(signal.SIGINT, signal.SIG_IGN)
        node.force = 0.
        node.send()
        # Best-effort final release is backed by the independent 0.5 s watchdog.
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
