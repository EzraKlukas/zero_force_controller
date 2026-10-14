# generated from rosidl_generator_py/resource/_idl.py.em
# with input from zfc_interfaces:msg/MeasuredState.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MeasuredState(type):
    """Metaclass of message 'MeasuredState'."""

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
                'zfc_interfaces.msg.MeasuredState')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__measured_state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__measured_state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__measured_state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__measured_state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__measured_state

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class MeasuredState(metaclass=Metaclass_MeasuredState):
    """Message class 'MeasuredState'."""

    __slots__ = [
        '_header',
        '_force_stamp',
        '_position_m',
        '_velocity_mps',
        '_force_n',
        '_joint_fresh',
        '_force_fresh',
        '_valid',
        '_detail',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'force_stamp': 'builtin_interfaces/Time',
        'position_m': 'double',
        'velocity_mps': 'double',
        'force_n': 'double',
        'joint_fresh': 'boolean',
        'force_fresh': 'boolean',
        'valid': 'boolean',
        'detail': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        from builtin_interfaces.msg import Time
        self.force_stamp = kwargs.get('force_stamp', Time())
        self.position_m = kwargs.get('position_m', float())
        self.velocity_mps = kwargs.get('velocity_mps', float())
        self.force_n = kwargs.get('force_n', float())
        self.joint_fresh = kwargs.get('joint_fresh', bool())
        self.force_fresh = kwargs.get('force_fresh', bool())
        self.valid = kwargs.get('valid', bool())
        self.detail = kwargs.get('detail', str())

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
        if self.header != other.header:
            return False
        if self.force_stamp != other.force_stamp:
            return False
        if self.position_m != other.position_m:
            return False
        if self.velocity_mps != other.velocity_mps:
            return False
        if self.force_n != other.force_n:
            return False
        if self.joint_fresh != other.joint_fresh:
            return False
        if self.force_fresh != other.force_fresh:
            return False
        if self.valid != other.valid:
            return False
        if self.detail != other.detail:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def force_stamp(self):
        """Message field 'force_stamp'."""
        return self._force_stamp

    @force_stamp.setter
    def force_stamp(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'force_stamp' field must be a sub message of type 'Time'"
        self._force_stamp = value

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
    def joint_fresh(self):
        """Message field 'joint_fresh'."""
        return self._joint_fresh

    @joint_fresh.setter
    def joint_fresh(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'joint_fresh' field must be of type 'bool'"
        self._joint_fresh = value

    @builtins.property
    def force_fresh(self):
        """Message field 'force_fresh'."""
        return self._force_fresh

    @force_fresh.setter
    def force_fresh(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'force_fresh' field must be of type 'bool'"
        self._force_fresh = value

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
    def detail(self):
        """Message field 'detail'."""
        return self._detail

    @detail.setter
    def detail(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'detail' field must be of type 'str'"
        self._detail = value
