#!/usr/bin/env python3
"""Opt-in Fortress acceptance check; isolated domain/partition, bounded lifetime.

Run from a sourced build overlay. Never selects or starts physical hardware.
"""
import argparse
import math
import os
from pathlib import Path
import signal
import subprocess
import time

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, DurabilityPolicy
from rcl_interfaces.srv import SetParameters
from rclpy.parameter import Parameter
from controller_manager_msgs.srv import ListControllers, ListHardwareInterfaces, SwitchController
from rosgraph_msgs.msg import Clock
from sensor_msgs.msg import JointState
from std_msgs.msg import Bool, Float64
from ros_gz_interfaces.msg import EntityWrench, Entity
from zfc_interfaces.msg import TelemetryBatch, TrialStatus, PlotState


class Check(Node):
    def __init__(self):
        super().__init__("gazebo_acceptance")
        self.ready = False
        self.clock = 0.
        self.joint = None
        self.applied = None
        self.records = {"calibration_sequencer_controller": [], "zero_force_controller": []}
        self.status = {}
        self.plots = {"zero_force": [], "calibration": []}
        self.force = 0.
        self.heartbeat = False  # No force-input publication during calibration.
        self.create_subscription(Bool, "/simulation/ready", lambda m: setattr(self, "ready", m.data),
            QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL))
        self.create_subscription(Clock, "/clock", lambda m: setattr(self, "clock", m.clock.sec+m.clock.nanosec*1e-9), 10)
        self.create_subscription(JointState, "/joint_states", lambda m: setattr(self, "joint", m), 100)
        self.create_subscription(Float64, "/simulation/applied_force", lambda m: setattr(self, "applied", m.data), 100)
        for name in self.records:
            self.create_subscription(TelemetryBatch, "/"+name+"/telemetry",
                lambda m, n=name: self.records[n].extend(m.samples), 200)
            self.create_subscription(TrialStatus, "/"+name+"/trial_status",
                lambda m, n=name: self.status.__setitem__(n, m),
                QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL))
        self.publisher = self.create_publisher(EntityWrench, "/simulation/force_input", 10)
        self.create_timer(.05, self.send_force)
        for short in self.plots:
            self.create_subscription(PlotState, "/plot/"+short,
                lambda m, n=short: self.plots[n].append(m), 100)

    def send_force(self):
        if self.heartbeat:
            m = EntityWrench()
            m.entity.name, m.entity.type = "stage::tool_link", Entity.LINK
            m.wrench.force.z = self.force
            self.publisher.publish(m)

    def wait(self, predicate, seconds, reason):
        deadline = time.monotonic()+seconds
        while time.monotonic() < deadline:
            rclpy.spin_once(self, timeout_sec=.02)
            if predicate():
                return
        raise AssertionError("Timeout: "+reason)

    def call(self, typ, path, request):
        client = self.create_client(typ, path)
        try:
            assert client.wait_for_service(timeout_sec=5), path
            future = client.call_async(request)
            self.wait(future.done, 5, path)
            return future.result()
        finally:
            self.destroy_client(client)

    def controllers(self):
        return self.call(ListControllers, "/controller_manager/list_controllers", ListControllers.Request()).controller

    def switch(self, activate=(), deactivate=(), ok=True):
        request = SwitchController.Request()
        request.activate_controllers, request.deactivate_controllers = list(activate), list(deactivate)
        request.strictness, request.timeout.sec = SwitchController.Request.STRICT, 3
        result = self.call(SwitchController, "/controller_manager/switch_controller", request)
        assert result.ok == ok, (activate, deactivate, result.ok)

    def parameters(self, name, **values):
        request = SetParameters.Request()
        request.parameters = [Parameter(k, value=v).to_parameter_msg() for k, v in values.items()]
        result = self.call(SetParameters, "/"+name+"/set_parameters", request)
        assert all(r.successful for r in result.results), result.results

    def advance(self, seconds):
        start = self.clock
        self.wait(lambda: self.clock >= start+seconds, max(10, seconds*5), "advancing simulation time")

    def q(self):
        return self.joint.position[self.joint.name.index("carriage")]

    def pause(self, paused):
        result = subprocess.run(["ign", "service", "-s", "/world/zfc/control",
            "--reqtype", "ignition.msgs.WorldControl", "--reptype", "ignition.msgs.Boolean",
            "--timeout", "3000", "--req", "pause: "+str(paused).lower()],
            capture_output=True, text=True, timeout=5)
        assert result.returncode == 0 and "data: true" in result.stdout, result

    def run(self):
        cal, zero = "calibration_sequencer_controller", "zero_force_controller"
        self.wait(lambda: self.ready and self.joint is not None, 65, "valid simulated startup")
        self.wait(lambda: self.applied is not None, 5, "resolved downstream force target")
        managers = [n for n, ns in self.get_node_names_and_namespaces() if n == "controller_manager" and ns == "/"]
        assert len(managers) == 1, managers
        states = {c.name: c.state for c in self.controllers()}
        assert states[zero] == states[cal] == "inactive", states
        assert states["joint_state_broadcaster"] == states["load_cell_broadcaster"] == "active", states
        interfaces = self.call(ListHardwareInterfaces, "/controller_manager/list_hardware_interfaces", ListHardwareInterfaces.Request())
        assert [(i.name, i.is_available, i.is_claimed) for i in interfaces.command_interfaces] == [("carriage/position", True, False)]
        assert {i.name for i in interfaces.state_interfaces} == {"carriage/position", "carriage/velocity", "load_cell/force.x", "load_cell/force.y", "load_cell/force.z"}
        self.advance(.1)
        print("PASS: sole manager, advancing clock, force-only interfaces, inactive motion startup", flush=True)
        self.parameters(cal, trial_id=41)
        initial = self.q()
        self.switch([cal])
        interfaces = self.call(ListHardwareInterfaces, "/controller_manager/list_hardware_interfaces", ListHardwareInterfaces.Request())
        assert [(i.name, i.is_available, i.is_claimed) for i in interfaces.command_interfaces] == [("carriage/position", True, True)]
        self.switch([zero], ok=False)
        self.wait(lambda: cal in self.status, 100, "terminal calibration status")
        terminal = self.status[cal]
        print("Calibration terminal:", terminal, "last sample:", self.records[cal][-1], flush=True)
        if not terminal.successful:
            for r in self.records[cal][::100]:
                print(r.sequence, r.position_m, r.reference_position_m, r.velocity_mps, r.force_n, flush=True)
        assert terminal.successful and terminal.capture_complete, terminal
        self.wait(lambda: len(self.records[cal]) >= terminal.final_sequence, 5, "full-rate final batch")
        records = [r for r in self.records[cal] if r.trial_id == 41]
        assert [r.sequence for r in records] == list(range(1, terminal.final_sequence+1))
        assert terminal.dropped_samples == terminal.failed_publication_samples == 0
        assert all(r.valid and all(math.isfinite(x) for x in (r.position_m, r.velocity_mps, r.force_n, r.reference_position_m)) for r in records)
        assert max(abs(r.reference_position_m-initial) for r in records) < .06
        assert abs(records[0].reference_position_m-initial) < .001
        assert abs(records[-1].reference_velocity_mps) < 1e-12
        assert abs(records[-1].velocity_mps) < .001
        forces = [r.force_n for r in records]
        errors = [r.position_m-r.reference_position_m for r in records]
        assert max(forces)-min(forces) > .05, "sensor force must respond to actual acceleration"
        # Describe async FT transport delay against acceleration computed from
        # MEASURED velocity, not against the idealized reference step.
        acceleration = [(b.velocity_mps-a.velocity_mps)/.001 for a, b in zip(records, records[1:])]
        lag_errors = []
        for lag in range(11):
            differences = [records[i+1+lag].force_n-(2.4525+.25*a)
                           for i, a in enumerate(acceleration[:-11]) if abs(a) < 20]
            lag_errors.append(math.sqrt(sum(e*e for e in differences)/len(differences)))
        best_lag = min(range(11), key=lag_errors.__getitem__)
        rms = math.sqrt(sum(e*e for e in errors)/len(errors))
        assert max(map(abs, errors)) < .002
        plots = [m for m in self.plots["calibration"] if m.state.trial_id == 41]
        assert len(plots) > len(records)/15 and len(plots) < len(records)/8
        stamps = [m.header.stamp.sec*1000000000+m.header.stamp.nanosec for m in plots]
        assert all(b-a >= 10000000 for a, b in zip(stamps, stamps[1:]))
        print(f"PASS: calibration {len(records)} contiguous samples; F=[{min(forces):.4f},{max(forces):.4f}] N; tracking RMS={rms:.6f}, max={max(map(abs,errors)):.6f} m", flush=True)
        print(f"Sensor observation: best sampled lag {best_lag} ms, RMS versus known-mass measured-velocity acceleration {lag_errors[best_lag]:.6f} N (not a calibration fit)", flush=True)
        self.parameters(zero, inertial_force_coefficient_kg=.25, trial_id=42)
        self.switch([zero], [cal])
        self.wait(lambda: self.records[zero] and self.records[zero][-1].phase == 3, 15, "baseline/noise capture")
        self.pause(True)
        # Observe stability after already queued sensor/capture messages drain.
        start = time.monotonic()
        while time.monotonic()-start < .2:
            rclpy.spin_once(self, timeout_sec=.02)
        clock, sequence = self.clock, self.records[zero][-1].sequence
        start = time.monotonic()
        while time.monotonic()-start < .3:
            rclpy.spin_once(self, timeout_sec=.02)
        assert self.clock == clock and self.records[zero][-1].sequence == sequence
        self.pause(False)
        self.advance(.1)
        print("PASS: pause freezes clock and controller experiment sequence", flush=True)
        self.switch([cal], ok=False)
        self.heartbeat = False  # One force-input writer, including CLI checks.
        pulse = subprocess.Popen(["ros2", "run", "zfc_simulation", "force_input",
            "--force", "1", "--duration", ".3", "--timeout", "10",
            "--ros-args", "-p", "use_sim_time:=true"], start_new_session=True)
        try:
            self.wait(lambda: self.applied == 1., 8, "installed CLI pulse applies force")
            self.wait(lambda: pulse.poll() is not None, 10, "CLI pulse completion")
            assert pulse.returncode == 0
        finally:
            if pulse.poll() is None:
                os.killpg(pulse.pid, signal.SIGINT)
                try:
                    pulse.wait(timeout=3)
                except subprocess.TimeoutExpired:
                    os.killpg(pulse.pid, signal.SIGKILL)
                    pulse.wait(timeout=3)
        self.heartbeat = True
        self.advance(2.)
        assert abs(self.applied) < 1e-12
        print("PASS: installed CLI simulation-time pulse and release", flush=True)
        for force in (1., -1.):
            self.force = force
            q0 = self.q()
            self.advance(.6)
            state = self.records[zero][-1]
            print("Push diagnostics:", self.applied, state, flush=True)
            assert state.valid, state
            assert (self.q()-q0)*force > .0001, (force, self.q()-q0)
            assert state.reference_velocity_mps*force > .001
            assert state.residual_force_n*force < -.2
            print(f"PASS: {force:+.1f} N world-Z push; q change={self.q()-q0:+.6f} m; residual={state.residual_force_n:+.4f} N", flush=True)
            self.force = 0.
            self.advance(2.)
            assert abs(self.applied) < 1e-12
            assert abs(self.records[zero][-1].reference_velocity_mps) < .0001
        self.force = 1.
        self.advance(.2)
        self.heartbeat = False
        self.wait(lambda: self.applied == 0., 2, "real-time heartbeat timeout clears force")
        self.force, self.heartbeat = 0., True
        self.advance(2.)
        q0 = self.q()
        self.advance(.5)
        assert abs(self.q()-q0) < .0001
        print("PASS: release, force replacement, heartbeat clearing and no stale-force drift", flush=True)
        self.switch([], [zero])
        self.advance(.2)
        q0 = self.q()
        self.advance(.2)
        assert abs(self.q()-q0) < .0001
        self.parameters(zero, excursion_limit_m=.0005, trial_id=43)
        self.switch([zero])
        self.wait(lambda: self.records[zero][-1].trial_id == 43 and self.records[zero][-1].phase == 3, 15, "fault-test baseline")
        self.force = 2.
        self.wait(lambda: self.status.get(zero) is not None and self.status[zero].trial_id == 43, 10, "bounded excursion fault")
        assert not self.status[zero].successful
        self.force = 0.
        self.advance(.5)
        assert all(math.isfinite(x) for x in self.joint.position+self.joint.velocity)
        q0 = self.q()
        self.advance(.3)
        assert abs(self.q()-q0) < .0001
        # Humble logs update(ERROR) but does not automatically unclaim it.
        self.switch([], [zero])
        print("PASS: controller fault finite stationary hold, then explicit deactivation", flush=True)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--log", default="/tmp/zfc-gazebo-acceptance.log")
    args = parser.parse_args()
    os.environ["ROS_LOCALHOST_ONLY"] = "1"
    os.environ["ROS_DOMAIN_ID"] = "73"
    os.environ["IGN_PARTITION"] = "zfc_acceptance_"+str(os.getpid())
    os.environ["ROS_LOG_DIR"] = "/tmp/zfc-gazebo-acceptance-ros-log"
    # Overall watchdog includes launch startup, test assertions and teardown.
    signal.signal(signal.SIGALRM, lambda *_: (_ for _ in ()).throw(TimeoutError("240 s overall watchdog")))
    signal.alarm(240)
    with Path(args.log).open("w") as log:
        process = subprocess.Popen(["ros2", "launch", "zfc_bringup", "local.launch.py",
            "backend:=gazebo", "gui:=false", "plot:=false"], stdout=log, stderr=subprocess.STDOUT, start_new_session=True)
        node = None
        try:
            rclpy.init()
            node = Check()
            node.run()
        finally:
            if node is not None:
                node.force = 0.
                node.send_force()
                node.destroy_node()
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
                    os.killpg(process.pid, signal.SIGKILL)
                    process.wait(timeout=5)
            signal.alarm(0)
            print("Launch teardown complete; log: "+args.log, flush=True)


if __name__ == "__main__":
    main()
