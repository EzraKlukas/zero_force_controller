"""Harmless bidirectional topic AND service preflight, no hardware dependencies."""
import argparse
import math
import time
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from std_srvs.srv import Trigger


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--name', choices=('host', 'jetson'), required=True)
    parser.add_argument('--peer', choices=('host', 'jetson'), required=True)
    parser.add_argument('--timeout', type=float, default=30.)
    args, ros_args = parser.parse_known_args()
    if args.name == args.peer or not math.isfinite(args.timeout) or args.timeout <= 0:
        parser.error('use reciprocal distinct names and positive timeout')
    rclpy.init(args=ros_args)
    node = Node('zfc_network_preflight_'+args.name)
    topic_received, service_received = [False], [False]
    publisher = node.create_publisher(String, '/zfc_preflight/'+args.name, 10)
    node.create_timer(.1, lambda: publisher.publish(String(data=args.name)))
    node.create_subscription(String, '/zfc_preflight/'+args.peer, lambda m: topic_received.__setitem__(0, m.data == args.peer), 10)
    def ping(_, response):
        response.success, response.message = True, args.name
        return response
    node.create_service(Trigger, '/zfc_preflight/'+args.name+'/ping', ping)
    client = node.create_client(Trigger, '/zfc_preflight/'+args.peer+'/ping')
    future = [None]
    def request_ping():
        if client.service_is_ready() and future[0] is None:
            future[0] = client.call_async(Trigger.Request())
    node.create_timer(.5, request_ping)
    deadline = time.monotonic()+args.timeout
    try:
        while time.monotonic() < deadline:
            rclpy.spin_once(node, timeout_sec=.1)
            if future[0] is not None and future[0].done():
                response = future[0].result()
                service_received[0] = response is not None and response.success and response.message == args.peer
                future[0] = None
        passed = topic_received[0] and service_received[0]
        print(f'{args.name}: peer topic={topic_received[0]}, peer service reply={service_received[0]}; '+('PASS' if passed else 'FAIL'))
    finally:
        node.destroy_node(); rclpy.shutdown()
    raise SystemExit(0 if passed else 1)
