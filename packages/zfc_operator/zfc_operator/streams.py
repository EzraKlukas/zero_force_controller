"""Input validation and freshness outside the realtime loop."""
import math
import time


def stamp_ns(stamp):
    if stamp.sec < 0 or not 0 <= stamp.nanosec < 1000000000:
        raise ValueError('invalid source timestamp')
    return stamp.sec*1000000000+stamp.nanosec


class Source:
    def __init__(self):
        self.value = None
        self.stamp = None
        self.received = 0.
        self.error = 'no sample'

    def accept(self, stamp, value, now=None):
        now = time.monotonic() if now is None else now
        try:
            ns = stamp_ns(stamp)
            if not all(math.isfinite(v) for v in value):
                raise ValueError('non-finite input')
            if self.stamp is not None and ns <= self.stamp:
                raise ValueError('source timestamp reversed or repeated')
        except ValueError as error:
            # Require a subsequent increasing sample after a reset; do not keep
            # exporting the old value through malformed/new-epoch deliveries.
            self.value = None
            self.error = str(error)
            try:
                self.stamp = stamp_ns(stamp)
            except ValueError:
                self.stamp = None
            return False
        self.stamp, self.value, self.received = ns, value, now
        self.error = ''
        return True

    def fresh(self, ros_ns, timeout, now=None):
        now = time.monotonic() if now is None else now
        return (self.value is not None and now-self.received < timeout and
                0 <= ros_ns-self.stamp < timeout*1e9)


def joint_values(msg, joint='carriage'):
    if msg.name.count(joint) != 1 or len(set(msg.name)) != len(msg.name):
        raise ValueError('missing/duplicate joint name')
    if len(msg.position) != len(msg.name) or len(msg.velocity) != len(msg.name):
        raise ValueError('joint array lengths do not match names')
    index = msg.name.index(joint)
    return msg.position[index], msg.velocity[index]
