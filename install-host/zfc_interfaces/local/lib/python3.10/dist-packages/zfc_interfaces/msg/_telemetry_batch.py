# generated from rosidl_generator_py/resource/_idl.py.em
# with input from zfc_interfaces:msg/TelemetryBatch.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_TelemetryBatch(type):
    """Metaclass of message 'TelemetryBatch'."""

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
                'zfc_interfaces.msg.TelemetryBatch')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__telemetry_batch
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__telemetry_batch
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__telemetry_batch
            cls._TYPE_SUPPORT = module.type_support_msg__msg__telemetry_batch
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__telemetry_batch

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

            from zfc_interfaces.msg import ControllerState
            if ControllerState.__class__._TYPE_SUPPORT is None:
                ControllerState.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class TelemetryBatch(metaclass=Metaclass_TelemetryBatch):
    """Message class 'TelemetryBatch'."""

    __slots__ = [
        '_stamp',
        '_samples',
        '_dropped_samples',
        '_failed_publication_samples',
    ]

    _fields_and_field_types = {
        'stamp': 'builtin_interfaces/Time',
        'samples': 'sequence<zfc_interfaces/ControllerState, 256>',
        'dropped_samples': 'uint64',
        'failed_publication_samples': 'uint64',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BoundedSequence(rosidl_parser.definition.NamespacedType(['zfc_interfaces', 'msg'], 'ControllerState'), 256),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from builtin_interfaces.msg import Time
        self.stamp = kwargs.get('stamp', Time())
        self.samples = kwargs.get('samples', [])
        self.dropped_samples = kwargs.get('dropped_samples', int())
        self.failed_publication_samples = kwargs.get('failed_publication_samples', int())

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
        if self.samples != other.samples:
            return False
        if self.dropped_samples != other.dropped_samples:
            return False
        if self.failed_publication_samples != other.failed_publication_samples:
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
    def samples(self):
        """Message field 'samples'."""
        return self._samples

    @samples.setter
    def samples(self, value):
        if __debug__:
            from zfc_interfaces.msg import ControllerState
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) <= 256 and
                 all(isinstance(v, ControllerState) for v in value) and
                 True), \
                "The 'samples' field must be a set or sequence with length <= 256 and each value of type 'ControllerState'"
        self._samples = value

    @builtins.property
    def dropped_samples(self):
        """Message field 'dropped_samples'."""
        return self._dropped_samples

    @dropped_samples.setter
    def dropped_samples(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'dropped_samples' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'dropped_samples' field must be an unsigned integer in [0, 18446744073709551615]"
        self._dropped_samples = value

    @builtins.property
    def failed_publication_samples(self):
        """Message field 'failed_publication_samples'."""
        return self._failed_publication_samples

    @failed_publication_samples.setter
    def failed_publication_samples(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'failed_publication_samples' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'failed_publication_samples' field must be an unsigned integer in [0, 18446744073709551615]"
        self._failed_publication_samples = value
