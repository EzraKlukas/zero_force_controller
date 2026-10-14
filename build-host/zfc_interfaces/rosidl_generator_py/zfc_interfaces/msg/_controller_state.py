# generated from rosidl_generator_py/resource/_idl.py.em
# with input from zfc_interfaces:msg/ControllerState.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ControllerState(type):
    """Metaclass of message 'ControllerState'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('zfc_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'zfc_interfaces.msg.ControllerState')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__controller_state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__controller_state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__controller_state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__controller_state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__controller_state

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ControllerState(metaclass=Metaclass_ControllerState):
    """Message class 'ControllerState'."""

    __slots__ = [
        '_stamp',
        '_trial_id',
        '_sequence',
        '_phase',
        '_fault_code',
        '_valid',
        '_position_m',
        '_velocity_mps',
        '_force_n',
        '_reference_position_m',
        '_reference_velocity_mps',
        '_reference_acceleration_mps2',
        '_baseline_force_n',
        '_noise_rms_n',
        '_residual_force_n',
        '_progress',
        '_excessive_periods',
    ]

    _fields_and_field_types = {
        'stamp': 'builtin_interfaces/Time',
        'trial_id': 'uint64',
        'sequence': 'uint64',
        'phase': 'uint8',
        'fault_code': 'uint8',
        'valid': 'boolean',
        'position_m': 'double',
        'velocity_mps': 'double',
        'force_n': 'double',
        'reference_position_m': 'double',
        'reference_velocity_mps': 'double',
        'reference_acceleration_mps2': 'double',
        'baseline_force_n': 'double',
        'noise_rms_n': 'double',
        'residual_force_n': 'double',
        'progress': 'double',
        'excessive_periods': 'uint64',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from builtin_interfaces.msg import Time
        self.stamp = kwargs.get('stamp', Time())
        self.trial_id = kwargs.get('trial_id', int())
        self.sequence = kwargs.get('sequence', int())
        self.phase = kwargs.get('phase', int())
        self.fault_code = kwargs.get('fault_code', int())
        self.valid = kwargs.get('valid', bool())
        self.position_m = kwargs.get('position_m', float())
        self.velocity_mps = kwargs.get('velocity_mps', float())
        self.force_n = kwargs.get('force_n', float())
        self.reference_position_m = kwargs.get('reference_position_m', float())
        self.reference_velocity_mps = kwargs.get('reference_velocity_mps', float())
        self.reference_acceleration_mps2 = kwargs.get('reference_acceleration_mps2', float())
        self.baseline_force_n = kwargs.get('baseline_force_n', float())
        self.noise_rms_n = kwargs.get('noise_rms_n', float())
        self.residual_force_n = kwargs.get('residual_force_n', float())
        self.progress = kwargs.get('progress', float())
        self.excessive_periods = kwargs.get('excessive_periods', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.stamp != other.stamp:
            return False
        if self.trial_id != other.trial_id:
            return False
        if self.sequence != other.sequence:
            return False
        if self.phase != other.phase:
            return False
        if self.fault_code != other.fault_code:
            return False
        if self.valid != other.valid:
            return False
        if self.position_m != other.position_m:
            return False
        if self.velocity_mps != other.velocity_mps:
            return False
        if self.force_n != other.force_n:
            return False
        if self.reference_position_m != other.reference_position_m:
            return False
        if self.reference_velocity_mps != other.reference_velocity_mps:
            return False
        if self.reference_acceleration_mps2 != other.reference_acceleration_mps2:
            return False
        if self.baseline_force_n != other.baseline_force_n:
            return False
        if self.noise_rms_n != other.noise_rms_n:
            return False
        if self.residual_force_n != other.residual_force_n:
            return False
        if self.progress != other.progress:
            return False
        if self.excessive_periods != other.excessive_periods:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def stamp(self):
        """Message field 'stamp'."""
        return self._stamp

    @stamp.setter
    def stamp(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'stamp' field must be a sub message of type 'Time'"
        self._stamp = value

    @builtins.property
    def trial_id(self):
        """Message field 'trial_id'."""
        return self._trial_id

    @trial_id.setter
    def trial_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'trial_id' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'trial_id' field must be an unsigned integer in [0, 18446744073709551615]"
        self._trial_id = value

    @builtins.property
    def sequence(self):
        """Message field 'sequence'."""
        return self._sequence

    @sequence.setter
    def sequence(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'sequence' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'sequence' field must be an unsigned integer in [0, 18446744073709551615]"
        self._sequence = value

    @builtins.property
    def phase(self):
        """Message field 'phase'."""
        return self._phase

    @phase.setter
    def phase(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'phase' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'phase' field must be an unsigned integer in [0, 255]"
        self._phase = value

    @builtins.property
    def fault_code(self):
        """Message field 'fault_code'."""
        return self._fault_code

    @fault_code.setter
    def fault_code(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'fault_code' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'fault_code' field must be an unsigned integer in [0, 255]"
        self._fault_code = value

    @builtins.property
    def valid(self):
        """Message field 'valid'."""
        return self._valid

    @valid.setter
    def valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'valid' field must be of type 'bool'"
        self._valid = value

    @builtins.property
    def position_m(self):
        """Message field 'position_m'."""
        return self._position_m

    @position_m.setter
    def position_m(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'position_m' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'position_m' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._position_m = value

    @builtins.property
    def velocity_mps(self):
        """Message field 'velocity_mps'."""
        return self._velocity_mps

    @velocity_mps.setter
    def velocity_mps(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'velocity_mps' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'velocity_mps' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._velocity_mps = value

    @builtins.property
    def force_n(self):
        """Message field 'force_n'."""
        return self._force_n

    @force_n.setter
    def force_n(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'force_n' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'force_n' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._force_n = value

    @builtins.property
    def reference_position_m(self):
        """Message field 'reference_position_m'."""
        return self._reference_position_m

    @reference_position_m.setter
    def reference_position_m(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'reference_position_m' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'reference_position_m' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._reference_position_m = value

    @builtins.property
    def reference_velocity_mps(self):
        """Message field 'reference_velocity_mps'."""
        return self._reference_velocity_mps

    @reference_velocity_mps.setter
    def reference_velocity_mps(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'reference_velocity_mps' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'reference_velocity_mps' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._reference_velocity_mps = value

    @builtins.property
    def reference_acceleration_mps2(self):
        """Message field 'reference_acceleration_mps2'."""
        return self._reference_acceleration_mps2

    @reference_acceleration_mps2.setter
    def reference_acceleration_mps2(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'reference_acceleration_mps2' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'reference_acceleration_mps2' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._reference_acceleration_mps2 = value

    @builtins.property
    def baseline_force_n(self):
        """Message field 'baseline_force_n'."""
        return self._baseline_force_n

    @baseline_force_n.setter
    def baseline_force_n(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'baseline_force_n' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'baseline_force_n' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._baseline_force_n = value

    @builtins.property
    def noise_rms_n(self):
        """Message field 'noise_rms_n'."""
        return self._noise_rms_n

    @noise_rms_n.setter
    def noise_rms_n(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'noise_rms_n' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'noise_rms_n' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._noise_rms_n = value

    @builtins.property
    def residual_force_n(self):
        """Message field 'residual_force_n'."""
        return self._residual_force_n

    @residual_force_n.setter
    def residual_force_n(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'residual_force_n' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'residual_force_n' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._residual_force_n = value

    @builtins.property
    def progress(self):
        """Message field 'progress'."""
        return self._progress

    @progress.setter
    def progress(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'progress' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'progress' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._progress = value

    @builtins.property
    def excessive_periods(self):
        """Message field 'excessive_periods'."""
        return self._excessive_periods

    @excessive_periods.setter
    def excessive_periods(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'excessive_periods' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'excessive_periods' field must be an unsigned integer in [0, 18446744073709551615]"
        self._excessive_periods = value
