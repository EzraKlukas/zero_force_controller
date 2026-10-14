# generated from rosidl_generator_py/resource/_idl.py.em
# with input from zfc_interfaces:action/RunCalibration.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RunCalibration_Goal(type):
    """Metaclass of message 'RunCalibration_Goal'."""

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
                'zfc_interfaces.action.RunCalibration_Goal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__run_calibration__goal
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__run_calibration__goal
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__run_calibration__goal
            cls._TYPE_SUPPORT = module.type_support_msg__action__run_calibration__goal
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__run_calibration__goal

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RunCalibration_Goal(metaclass=Metaclass_RunCalibration_Goal):
    """Message class 'RunCalibration_Goal'."""

    __slots__ = [
        '_activate_zero_force_after',
        '_external_contact_clear',
    ]

    _fields_and_field_types = {
        'activate_zero_force_after': 'boolean',
        'external_contact_clear': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.activate_zero_force_after = kwargs.get('activate_zero_force_after', bool())
        self.external_contact_clear = kwargs.get('external_contact_clear', bool())

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
        if self.activate_zero_force_after != other.activate_zero_force_after:
            return False
        if self.external_contact_clear != other.external_contact_clear:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def activate_zero_force_after(self):
        """Message field 'activate_zero_force_after'."""
        return self._activate_zero_force_after

    @activate_zero_force_after.setter
    def activate_zero_force_after(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'activate_zero_force_after' field must be of type 'bool'"
        self._activate_zero_force_after = value

    @builtins.property
    def external_contact_clear(self):
        """Message field 'external_contact_clear'."""
        return self._external_contact_clear

    @external_contact_clear.setter
    def external_contact_clear(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'external_contact_clear' field must be of type 'bool'"
        self._external_contact_clear = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_RunCalibration_Result(type):
    """Metaclass of message 'RunCalibration_Result'."""

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
                'zfc_interfaces.action.RunCalibration_Result')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__run_calibration__result
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__run_calibration__result
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__run_calibration__result
            cls._TYPE_SUPPORT = module.type_support_msg__action__run_calibration__result
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__run_calibration__result

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


class RunCalibration_Result(metaclass=Metaclass_RunCalibration_Result):
    """Message class 'RunCalibration_Result'."""

    __slots__ = [
        '_success',
        '_trial_id',
        '_trial_directory',
        '_message',
        '_applied',
        '_zero_force_active',
        '_stop_acknowledged',
        '_fit',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'trial_id': 'uint64',
        'trial_directory': 'string',
        'message': 'string',
        'applied': 'boolean',
        'zero_force_active': 'boolean',
        'stop_acknowledged': 'boolean',
        'fit': 'zfc_interfaces/CalibrationResult',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['zfc_interfaces', 'msg'], 'CalibrationResult'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.trial_id = kwargs.get('trial_id', int())
        self.trial_directory = kwargs.get('trial_directory', str())
        self.message = kwargs.get('message', str())
        self.applied = kwargs.get('applied', bool())
        self.zero_force_active = kwargs.get('zero_force_active', bool())
        self.stop_acknowledged = kwargs.get('stop_acknowledged', bool())
        from zfc_interfaces.msg import CalibrationResult
        self.fit = kwargs.get('fit', CalibrationResult())

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
        if self.success != other.success:
            return False
        if self.trial_id != other.trial_id:
            return False
        if self.trial_directory != other.trial_directory:
            return False
        if self.message != other.message:
            return False
        if self.applied != other.applied:
            return False
        if self.zero_force_active != other.zero_force_active:
            return False
        if self.stop_acknowledged != other.stop_acknowledged:
            return False
        if self.fit != other.fit:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value

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

    @builtins.property
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value

    @builtins.property
    def applied(self):
        """Message field 'applied'."""
        return self._applied

    @applied.setter
    def applied(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'applied' field must be of type 'bool'"
        self._applied = value

    @builtins.property
    def zero_force_active(self):
        """Message field 'zero_force_active'."""
        return self._zero_force_active

    @zero_force_active.setter
    def zero_force_active(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'zero_force_active' field must be of type 'bool'"
        self._zero_force_active = value

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


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_RunCalibration_Feedback(type):
    """Metaclass of message 'RunCalibration_Feedback'."""

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
                'zfc_interfaces.action.RunCalibration_Feedback')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__run_calibration__feedback
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__run_calibration__feedback
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__run_calibration__feedback
            cls._TYPE_SUPPORT = module.type_support_msg__action__run_calibration__feedback
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__run_calibration__feedback

            from zfc_interfaces.msg import AnalysisState
            if AnalysisState.__class__._TYPE_SUPPORT is None:
                AnalysisState.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RunCalibration_Feedback(metaclass=Metaclass_RunCalibration_Feedback):
    """Message class 'RunCalibration_Feedback'."""

    __slots__ = [
        '_state',
    ]

    _fields_and_field_types = {
        'state': 'zfc_interfaces/AnalysisState',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['zfc_interfaces', 'msg'], 'AnalysisState'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from zfc_interfaces.msg import AnalysisState
        self.state = kwargs.get('state', AnalysisState())

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
        if self.state != other.state:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def state(self):
        """Message field 'state'."""
        return self._state

    @state.setter
    def state(self, value):
        if __debug__:
            from zfc_interfaces.msg import AnalysisState
            assert \
                isinstance(value, AnalysisState), \
                "The 'state' field must be a sub message of type 'AnalysisState'"
        self._state = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_RunCalibration_SendGoal_Request(type):
    """Metaclass of message 'RunCalibration_SendGoal_Request'."""

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
                'zfc_interfaces.action.RunCalibration_SendGoal_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__run_calibration__send_goal__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__run_calibration__send_goal__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__run_calibration__send_goal__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__run_calibration__send_goal__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__run_calibration__send_goal__request

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

            from zfc_interfaces.action import RunCalibration
            if RunCalibration.Goal.__class__._TYPE_SUPPORT is None:
                RunCalibration.Goal.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RunCalibration_SendGoal_Request(metaclass=Metaclass_RunCalibration_SendGoal_Request):
    """Message class 'RunCalibration_SendGoal_Request'."""

    __slots__ = [
        '_goal_id',
        '_goal',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'goal': 'zfc_interfaces/RunCalibration_Goal',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['zfc_interfaces', 'action'], 'RunCalibration_Goal'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from zfc_interfaces.action._run_calibration import RunCalibration_Goal
        self.goal = kwargs.get('goal', RunCalibration_Goal())

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
        if self.goal_id != other.goal_id:
            return False
        if self.goal != other.goal:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value

    @builtins.property
    def goal(self):
        """Message field 'goal'."""
        return self._goal

    @goal.setter
    def goal(self, value):
        if __debug__:
            from zfc_interfaces.action._run_calibration import RunCalibration_Goal
            assert \
                isinstance(value, RunCalibration_Goal), \
                "The 'goal' field must be a sub message of type 'RunCalibration_Goal'"
        self._goal = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_RunCalibration_SendGoal_Response(type):
    """Metaclass of message 'RunCalibration_SendGoal_Response'."""

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
                'zfc_interfaces.action.RunCalibration_SendGoal_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__run_calibration__send_goal__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__run_calibration__send_goal__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__run_calibration__send_goal__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__run_calibration__send_goal__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__run_calibration__send_goal__response

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


class RunCalibration_SendGoal_Response(metaclass=Metaclass_RunCalibration_SendGoal_Response):
    """Message class 'RunCalibration_SendGoal_Response'."""

    __slots__ = [
        '_accepted',
        '_stamp',
    ]

    _fields_and_field_types = {
        'accepted': 'boolean',
        'stamp': 'builtin_interfaces/Time',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.accepted = kwargs.get('accepted', bool())
        from builtin_interfaces.msg import Time
        self.stamp = kwargs.get('stamp', Time())

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
        if self.accepted != other.accepted:
            return False
        if self.stamp != other.stamp:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def accepted(self):
        """Message field 'accepted'."""
        return self._accepted

    @accepted.setter
    def accepted(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'accepted' field must be of type 'bool'"
        self._accepted = value

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


class Metaclass_RunCalibration_SendGoal(type):
    """Metaclass of service 'RunCalibration_SendGoal'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('zfc_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'zfc_interfaces.action.RunCalibration_SendGoal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__run_calibration__send_goal

            from zfc_interfaces.action import _run_calibration
            if _run_calibration.Metaclass_RunCalibration_SendGoal_Request._TYPE_SUPPORT is None:
                _run_calibration.Metaclass_RunCalibration_SendGoal_Request.__import_type_support__()
            if _run_calibration.Metaclass_RunCalibration_SendGoal_Response._TYPE_SUPPORT is None:
                _run_calibration.Metaclass_RunCalibration_SendGoal_Response.__import_type_support__()


class RunCalibration_SendGoal(metaclass=Metaclass_RunCalibration_SendGoal):
    from zfc_interfaces.action._run_calibration import RunCalibration_SendGoal_Request as Request
    from zfc_interfaces.action._run_calibration import RunCalibration_SendGoal_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_RunCalibration_GetResult_Request(type):
    """Metaclass of message 'RunCalibration_GetResult_Request'."""

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
                'zfc_interfaces.action.RunCalibration_GetResult_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__run_calibration__get_result__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__run_calibration__get_result__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__run_calibration__get_result__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__run_calibration__get_result__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__run_calibration__get_result__request

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RunCalibration_GetResult_Request(metaclass=Metaclass_RunCalibration_GetResult_Request):
    """Message class 'RunCalibration_GetResult_Request'."""

    __slots__ = [
        '_goal_id',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())

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
        if self.goal_id != other.goal_id:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_RunCalibration_GetResult_Response(type):
    """Metaclass of message 'RunCalibration_GetResult_Response'."""

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
                'zfc_interfaces.action.RunCalibration_GetResult_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__run_calibration__get_result__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__run_calibration__get_result__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__run_calibration__get_result__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__run_calibration__get_result__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__run_calibration__get_result__response

            from zfc_interfaces.action import RunCalibration
            if RunCalibration.Result.__class__._TYPE_SUPPORT is None:
                RunCalibration.Result.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RunCalibration_GetResult_Response(metaclass=Metaclass_RunCalibration_GetResult_Response):
    """Message class 'RunCalibration_GetResult_Response'."""

    __slots__ = [
        '_status',
        '_result',
    ]

    _fields_and_field_types = {
        'status': 'int8',
        'result': 'zfc_interfaces/RunCalibration_Result',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['zfc_interfaces', 'action'], 'RunCalibration_Result'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status = kwargs.get('status', int())
        from zfc_interfaces.action._run_calibration import RunCalibration_Result
        self.result = kwargs.get('result', RunCalibration_Result())

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
        if self.status != other.status:
            return False
        if self.result != other.result:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def status(self):
        """Message field 'status'."""
        return self._status

    @status.setter
    def status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'status' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'status' field must be an integer in [-128, 127]"
        self._status = value

    @builtins.property
    def result(self):
        """Message field 'result'."""
        return self._result

    @result.setter
    def result(self, value):
        if __debug__:
            from zfc_interfaces.action._run_calibration import RunCalibration_Result
            assert \
                isinstance(value, RunCalibration_Result), \
                "The 'result' field must be a sub message of type 'RunCalibration_Result'"
        self._result = value


class Metaclass_RunCalibration_GetResult(type):
    """Metaclass of service 'RunCalibration_GetResult'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('zfc_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'zfc_interfaces.action.RunCalibration_GetResult')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__run_calibration__get_result

            from zfc_interfaces.action import _run_calibration
            if _run_calibration.Metaclass_RunCalibration_GetResult_Request._TYPE_SUPPORT is None:
                _run_calibration.Metaclass_RunCalibration_GetResult_Request.__import_type_support__()
            if _run_calibration.Metaclass_RunCalibration_GetResult_Response._TYPE_SUPPORT is None:
                _run_calibration.Metaclass_RunCalibration_GetResult_Response.__import_type_support__()


class RunCalibration_GetResult(metaclass=Metaclass_RunCalibration_GetResult):
    from zfc_interfaces.action._run_calibration import RunCalibration_GetResult_Request as Request
    from zfc_interfaces.action._run_calibration import RunCalibration_GetResult_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_RunCalibration_FeedbackMessage(type):
    """Metaclass of message 'RunCalibration_FeedbackMessage'."""

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
                'zfc_interfaces.action.RunCalibration_FeedbackMessage')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__run_calibration__feedback_message
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__run_calibration__feedback_message
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__run_calibration__feedback_message
            cls._TYPE_SUPPORT = module.type_support_msg__action__run_calibration__feedback_message
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__run_calibration__feedback_message

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

            from zfc_interfaces.action import RunCalibration
            if RunCalibration.Feedback.__class__._TYPE_SUPPORT is None:
                RunCalibration.Feedback.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RunCalibration_FeedbackMessage(metaclass=Metaclass_RunCalibration_FeedbackMessage):
    """Message class 'RunCalibration_FeedbackMessage'."""

    __slots__ = [
        '_goal_id',
        '_feedback',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'feedback': 'zfc_interfaces/RunCalibration_Feedback',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['zfc_interfaces', 'action'], 'RunCalibration_Feedback'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from zfc_interfaces.action._run_calibration import RunCalibration_Feedback
        self.feedback = kwargs.get('feedback', RunCalibration_Feedback())

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
        if self.goal_id != other.goal_id:
            return False
        if self.feedback != other.feedback:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value

    @builtins.property
    def feedback(self):
        """Message field 'feedback'."""
        return self._feedback

    @feedback.setter
    def feedback(self, value):
        if __debug__:
            from zfc_interfaces.action._run_calibration import RunCalibration_Feedback
            assert \
                isinstance(value, RunCalibration_Feedback), \
                "The 'feedback' field must be a sub message of type 'RunCalibration_Feedback'"
        self._feedback = value


class Metaclass_RunCalibration(type):
    """Metaclass of action 'RunCalibration'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('zfc_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'zfc_interfaces.action.RunCalibration')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_action__action__run_calibration

            from action_msgs.msg import _goal_status_array
            if _goal_status_array.Metaclass_GoalStatusArray._TYPE_SUPPORT is None:
                _goal_status_array.Metaclass_GoalStatusArray.__import_type_support__()
            from action_msgs.srv import _cancel_goal
            if _cancel_goal.Metaclass_CancelGoal._TYPE_SUPPORT is None:
                _cancel_goal.Metaclass_CancelGoal.__import_type_support__()

            from zfc_interfaces.action import _run_calibration
            if _run_calibration.Metaclass_RunCalibration_SendGoal._TYPE_SUPPORT is None:
                _run_calibration.Metaclass_RunCalibration_SendGoal.__import_type_support__()
            if _run_calibration.Metaclass_RunCalibration_GetResult._TYPE_SUPPORT is None:
                _run_calibration.Metaclass_RunCalibration_GetResult.__import_type_support__()
            if _run_calibration.Metaclass_RunCalibration_FeedbackMessage._TYPE_SUPPORT is None:
                _run_calibration.Metaclass_RunCalibration_FeedbackMessage.__import_type_support__()


class RunCalibration(metaclass=Metaclass_RunCalibration):

    # The goal message defined in the action definition.
    from zfc_interfaces.action._run_calibration import RunCalibration_Goal as Goal
    # The result message defined in the action definition.
    from zfc_interfaces.action._run_calibration import RunCalibration_Result as Result
    # The feedback message defined in the action definition.
    from zfc_interfaces.action._run_calibration import RunCalibration_Feedback as Feedback

    class Impl:

        # The send_goal service using a wrapped version of the goal message as a request.
        from zfc_interfaces.action._run_calibration import RunCalibration_SendGoal as SendGoalService
        # The get_result service using a wrapped version of the result message as a response.
        from zfc_interfaces.action._run_calibration import RunCalibration_GetResult as GetResultService
        # The feedback message with generic fields which wraps the feedback message.
        from zfc_interfaces.action._run_calibration import RunCalibration_FeedbackMessage as FeedbackMessage

        # The generic service to cancel a goal.
        from action_msgs.srv._cancel_goal import CancelGoal as CancelGoalService
        # The generic message for get the status of a goal.
        from action_msgs.msg._goal_status_array import GoalStatusArray as GoalStatusMessage

    def __init__(self):
        raise NotImplementedError('Action classes can not be instantiated')
