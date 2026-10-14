# generated from rosidl_generator_py/resource/_idl.py.em
# with input from zfc_interfaces:msg/CalibrationResult.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_CalibrationResult(type):
    """Metaclass of message 'CalibrationResult'."""

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
                'zfc_interfaces.msg.CalibrationResult')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__calibration_result
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__calibration_result
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__calibration_result
            cls._TYPE_SUPPORT = module.type_support_msg__msg__calibration_result
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__calibration_result

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class CalibrationResult(metaclass=Metaclass_CalibrationResult):
    """Message class 'CalibrationResult'."""

    __slots__ = [
        '_valid',
        '_reason',
        '_inertial_force_coefficient_kg',
        '_intercept_n',
        '_r_squared',
        '_residual_rms_n',
        '_uncertainty_kg',
        '_sample_count',
        '_plateau_count',
        '_positive_slope_kg',
        '_negative_slope_kg',
        '_tracking_rms_m',
        '_acceleration_source',
    ]

    _fields_and_field_types = {
        'valid': 'boolean',
        'reason': 'string',
        'inertial_force_coefficient_kg': 'double',
        'intercept_n': 'double',
        'r_squared': 'double',
        'residual_rms_n': 'double',
        'uncertainty_kg': 'double',
        'sample_count': 'uint64',
        'plateau_count': 'uint64',
        'positive_slope_kg': 'double',
        'negative_slope_kg': 'double',
        'tracking_rms_m': 'double',
        'acceleration_source': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.valid = kwargs.get('valid', bool())
        self.reason = kwargs.get('reason', str())
        self.inertial_force_coefficient_kg = kwargs.get('inertial_force_coefficient_kg', float())
        self.intercept_n = kwargs.get('intercept_n', float())
        self.r_squared = kwargs.get('r_squared', float())
        self.residual_rms_n = kwargs.get('residual_rms_n', float())
        self.uncertainty_kg = kwargs.get('uncertainty_kg', float())
        self.sample_count = kwargs.get('sample_count', int())
        self.plateau_count = kwargs.get('plateau_count', int())
        self.positive_slope_kg = kwargs.get('positive_slope_kg', float())
        self.negative_slope_kg = kwargs.get('negative_slope_kg', float())
        self.tracking_rms_m = kwargs.get('tracking_rms_m', float())
        self.acceleration_source = kwargs.get('acceleration_source', str())

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
        if self.valid != other.valid:
            return False
        if self.reason != other.reason:
            return False
        if self.inertial_force_coefficient_kg != other.inertial_force_coefficient_kg:
            return False
        if self.intercept_n != other.intercept_n:
            return False
        if self.r_squared != other.r_squared:
            return False
        if self.residual_rms_n != other.residual_rms_n:
            return False
        if self.uncertainty_kg != other.uncertainty_kg:
            return False
        if self.sample_count != other.sample_count:
            return False
        if self.plateau_count != other.plateau_count:
            return False
        if self.positive_slope_kg != other.positive_slope_kg:
            return False
        if self.negative_slope_kg != other.negative_slope_kg:
            return False
        if self.tracking_rms_m != other.tracking_rms_m:
            return False
        if self.acceleration_source != other.acceleration_source:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

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
    def reason(self):
        """Message field 'reason'."""
        return self._reason

    @reason.setter
    def reason(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'reason' field must be of type 'str'"
        self._reason = value

    @builtins.property
    def inertial_force_coefficient_kg(self):
        """Message field 'inertial_force_coefficient_kg'."""
        return self._inertial_force_coefficient_kg

    @inertial_force_coefficient_kg.setter
    def inertial_force_coefficient_kg(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'inertial_force_coefficient_kg' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'inertial_force_coefficient_kg' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._inertial_force_coefficient_kg = value

    @builtins.property
    def intercept_n(self):
        """Message field 'intercept_n'."""
        return self._intercept_n

    @intercept_n.setter
    def intercept_n(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'intercept_n' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'intercept_n' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._intercept_n = value

    @builtins.property
    def r_squared(self):
        """Message field 'r_squared'."""
        return self._r_squared

    @r_squared.setter
    def r_squared(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'r_squared' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'r_squared' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._r_squared = value

    @builtins.property
    def residual_rms_n(self):
        """Message field 'residual_rms_n'."""
        return self._residual_rms_n

    @residual_rms_n.setter
    def residual_rms_n(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'residual_rms_n' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'residual_rms_n' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._residual_rms_n = value

    @builtins.property
    def uncertainty_kg(self):
        """Message field 'uncertainty_kg'."""
        return self._uncertainty_kg

    @uncertainty_kg.setter
    def uncertainty_kg(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'uncertainty_kg' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'uncertainty_kg' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._uncertainty_kg = value

    @builtins.property
    def sample_count(self):
        """Message field 'sample_count'."""
        return self._sample_count

    @sample_count.setter
    def sample_count(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'sample_count' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'sample_count' field must be an unsigned integer in [0, 18446744073709551615]"
        self._sample_count = value

    @builtins.property
    def plateau_count(self):
        """Message field 'plateau_count'."""
        return self._plateau_count

    @plateau_count.setter
    def plateau_count(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'plateau_count' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'plateau_count' field must be an unsigned integer in [0, 18446744073709551615]"
        self._plateau_count = value

    @builtins.property
    def positive_slope_kg(self):
        """Message field 'positive_slope_kg'."""
        return self._positive_slope_kg

    @positive_slope_kg.setter
    def positive_slope_kg(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'positive_slope_kg' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'positive_slope_kg' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._positive_slope_kg = value

    @builtins.property
    def negative_slope_kg(self):
        """Message field 'negative_slope_kg'."""
        return self._negative_slope_kg

    @negative_slope_kg.setter
    def negative_slope_kg(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'negative_slope_kg' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'negative_slope_kg' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._negative_slope_kg = value

    @builtins.property
    def tracking_rms_m(self):
        """Message field 'tracking_rms_m'."""
        return self._tracking_rms_m

    @tracking_rms_m.setter
    def tracking_rms_m(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'tracking_rms_m' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'tracking_rms_m' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._tracking_rms_m = value

    @builtins.property
    def acceleration_source(self):
        """Message field 'acceleration_source'."""
        return self._acceleration_source

    @acceleration_source.setter
    def acceleration_source(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'acceleration_source' field must be of type 'str'"
        self._acceleration_source = value
