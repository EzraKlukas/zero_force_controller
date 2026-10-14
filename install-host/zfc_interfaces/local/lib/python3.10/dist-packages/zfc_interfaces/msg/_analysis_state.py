# generated from rosidl_generator_py/resource/_idl.py.em
# with input from zfc_interfaces:msg/AnalysisState.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_AnalysisState(type):
    """Metaclass of message 'AnalysisState'."""

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
                'zfc_interfaces.msg.AnalysisState')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__analysis_state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__analysis_state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__analysis_state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__analysis_state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__analysis_state

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

            from zfc_interfaces.msg import CalibrationResult
            if CalibrationResult.__class__._TYPE_SUPPORT is None:
                CalibrationResult.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class AnalysisState(metaclass=Metaclass_AnalysisState):
    """Message class 'AnalysisState'."""

    __slots__ = [
        '_header',
        '_trial_id',
        '_stage',
        '_stage_code',
        '_progress',
        '_recorded_samples',
        '_dropped_samples',
        '_final_sequence',
        '_stop_acknowledged',
        '_detail',
        '_fit',
        '_backend',
        '_operation_pending',
        '_trial_directory',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'trial_id': 'uint64',
        'stage': 'string',
        'stage_code': 'uint8',
        'progress': 'double',
        'recorded_samples': 'uint64',
        'dropped_samples': 'uint64',
        'final_sequence': 'uint64',
        'stop_acknowledged': 'boolean',
        'detail': 'string',
        'fit': 'zfc_interfaces/CalibrationResult',
        'backend': 'string',
        'operation_pending': 'boolean',
        'trial_directory': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['zfc_interfaces', 'msg'], 'CalibrationResult'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.trial_id = kwargs.get('trial_id', int())
        self.stage = kwargs.get('stage', str())
        self.stage_code = kwargs.get('stage_code', int())
        self.progress = kwargs.get('progress', float())
        self.recorded_samples = kwargs.get('recorded_samples', int())
        self.dropped_samples = kwargs.get('dropped_samples', int())
        self.final_sequence = kwargs.get('final_sequence', int())
        self.stop_acknowledged = kwargs.get('stop_acknowledged', bool())
        self.detail = kwargs.get('detail', str())
        from zfc_interfaces.msg import CalibrationResult
        self.fit = kwargs.get('fit', CalibrationResult())
        self.backend = kwargs.get('backend', str())
        self.operation_pending = kwargs.get('operation_pending', bool())
        self.trial_directory = kwargs.get('trial_directory', str())

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
        if self.trial_id != other.trial_id:
            return False
        if self.stage != other.stage:
            return False
        if self.stage_code != other.stage_code:
            return False
        if self.progress != other.progress:
            return False
        if self.recorded_samples != other.recorded_samples:
            return False
        if self.dropped_samples != other.dropped_samples:
            return False
        if self.final_sequence != other.final_sequence:
            return False
        if self.stop_acknowledged != other.stop_acknowledged:
            return False
        if self.detail != other.detail:
            return False
        if self.fit != other.fit:
            return False
        if self.backend != other.backend:
            return False
        if self.operation_pending != other.operation_pending:
            return False
        if self.trial_directory != other.trial_directory:
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
    def stage(self):
        """Message field 'stage'."""
        return self._stage

    @stage.setter
    def stage(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'stage' field must be of type 'str'"
        self._stage = value

    @builtins.property
    def stage_code(self):
        """Message field 'stage_code'."""
        return self._stage_code

    @stage_code.setter
    def stage_code(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'stage_code' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'stage_code' field must be an unsigned integer in [0, 255]"
        self._stage_code = value

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
    def recorded_samples(self):
        """Message field 'recorded_samples'."""
        return self._recorded_samples

    @recorded_samples.setter
    def recorded_samples(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'recorded_samples' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'recorded_samples' field must be an unsigned integer in [0, 18446744073709551615]"
        self._recorded_samples = value

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
    def stop_acknowledged(self):
        """Message field 'stop_acknowledged'."""
        return self._stop_acknowledged

    @stop_acknowledged.setter
    def stop_acknowledged(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'stop_acknowledged' field must be of type 'bool'"
        self._stop_acknowledged = value

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

    @builtins.property
    def fit(self):
        """Message field 'fit'."""
        return self._fit

    @fit.setter
    def fit(self, value):
        if __debug__:
            from zfc_interfaces.msg import CalibrationResult
            assert \
                isinstance(value, CalibrationResult), \
                "The 'fit' field must be a sub message of type 'CalibrationResult'"
        self._fit = value

    @builtins.property
    def backend(self):
        """Message field 'backend'."""
        return self._backend

    @backend.setter
    def backend(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'backend' field must be of type 'str'"
        self._backend = value

    @builtins.property
    def operation_pending(self):
        """Message field 'operation_pending'."""
        return self._operation_pending

    @operation_pending.setter
    def operation_pending(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'operation_pending' field must be of type 'bool'"
        self._operation_pending = value

    @builtins.property
    def trial_directory(self):
        """Message field 'trial_directory'."""
        return self._trial_directory

    @trial_directory.setter
    def trial_directory(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'trial_directory' field must be of type 'str'"
        self._trial_directory = value
