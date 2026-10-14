# generated from rosidl_generator_py/resource/_idl.py.em
# with input from zfc_interfaces:msg/TrialStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_TrialStatus(type):
    """Metaclass of message 'TrialStatus'."""

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
                'zfc_interfaces.msg.TrialStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__trial_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__trial_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__trial_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__trial_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__trial_status

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


class TrialStatus(metaclass=Metaclass_TrialStatus):
    """Message class 'TrialStatus'."""

    __slots__ = [
        '_stamp',
        '_trial_id',
        '_final_sequence',
        '_dropped_samples',
        '_failed_publication_samples',
        '_phase',
        '_fault_code',
        '_completed',
        '_successful',
        '_capture_complete',
    ]

    _fields_and_field_types = {
        'stamp': 'builtin_interfaces/Time',
        'trial_id': 'uint64',
        'final_sequence': 'uint64',
        'dropped_samples': 'uint64',
        'failed_publication_samples': 'uint64',
        'phase': 'uint8',
        'fault_code': 'uint8',
        'completed': 'boolean',
        'successful': 'boolean',
        'capture_complete': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from builtin_interfaces.msg import Time
        self.stamp = kwargs.get('stamp', Time())
        self.trial_id = kwargs.get('trial_id', int())
        self.final_sequence = kwargs.get('final_sequence', int())
        self.dropped_samples = kwargs.get('dropped_samples', int())
        self.failed_publication_samples = kwargs.get('failed_publication_samples', int())
        self.phase = kwargs.get('phase', int())
        self.fault_code = kwargs.get('fault_code', int())
        self.completed = kwargs.get('completed', bool())
        self.successful = kwargs.get('successful', bool())
        self.capture_complete = kwargs.get('capture_complete', bool())

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
        if self.final_sequence != other.final_sequence:
            return False
        if self.dropped_samples != other.dropped_samples:
            return False
        if self.failed_publication_samples != other.failed_publication_samples:
            return False
        if self.phase != other.phase:
            return False
        if self.fault_code != other.fault_code:
            return False
        if self.completed != other.completed:
            return False
        if self.successful != other.successful:
            return False
        if self.capture_complete != other.capture_complete:
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
    def final_sequence(self):
        """Message field 'final_sequence'."""
        return self._final_sequence

    @final_sequence.setter
    def final_sequence(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'final_sequence' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'final_sequence' field must be an unsigned integer in [0, 18446744073709551615]"
        self._final_sequence = value

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
    def completed(self):
        """Message field 'completed'."""
        return self._completed

    @completed.setter
    def completed(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'completed' field must be of type 'bool'"
        self._completed = value

    @builtins.property
    def successful(self):
        """Message field 'successful'."""
        return self._successful

    @successful.setter
    def successful(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'successful' field must be of type 'bool'"
        self._successful = value

    @builtins.property
    def capture_complete(self):
        """Message field 'capture_complete'."""
        return self._capture_complete

    @capture_complete.setter
    def capture_complete(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'capture_complete' field must be of type 'bool'"
        self._capture_complete = value
