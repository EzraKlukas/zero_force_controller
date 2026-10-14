#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to zfc_interfaces__srv__ApplyCalibration_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ApplyCalibration_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub result_file: std::string::String,

}



impl Default for ApplyCalibration_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ApplyCalibration_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ApplyCalibration_Request {
  type RmwMsg = super::srv::rmw::ApplyCalibration_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        result_file: msg.result_file.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        result_file: msg.result_file.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      result_file: msg.result_file.to_string(),
    }
  }
}


// Corresponds to zfc_interfaces__srv__ApplyCalibration_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ApplyCalibration_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub fit: super::msg::CalibrationResult,

}



impl Default for ApplyCalibration_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ApplyCalibration_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ApplyCalibration_Response {
  type RmwMsg = super::srv::rmw::ApplyCalibration_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        message: msg.message.as_str().into(),
        fit: super::msg::CalibrationResult::into_rmw_message(std::borrow::Cow::Owned(msg.fit)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        message: msg.message.as_str().into(),
        fit: super::msg::CalibrationResult::into_rmw_message(std::borrow::Cow::Borrowed(&msg.fit)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      message: msg.message.to_string(),
      fit: super::msg::CalibrationResult::from_rmw_message(msg.fit),
    }
  }
}


// Corresponds to zfc_interfaces__srv__OperatorCommand_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OperatorCommand_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub command: std::string::String,

    /// Physical operator affirmation for THIS request; sensors cannot prove no contact.
    pub external_contact_clear: bool,

}



impl Default for OperatorCommand_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::OperatorCommand_Request::default())
  }
}

impl rosidl_runtime_rs::Message for OperatorCommand_Request {
  type RmwMsg = super::srv::rmw::OperatorCommand_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        command: msg.command.as_str().into(),
        external_contact_clear: msg.external_contact_clear,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        command: msg.command.as_str().into(),
      external_contact_clear: msg.external_contact_clear,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      command: msg.command.to_string(),
      external_contact_clear: msg.external_contact_clear,
    }
  }
}


// Corresponds to zfc_interfaces__srv__OperatorCommand_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OperatorCommand_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stop_acknowledged: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for OperatorCommand_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::OperatorCommand_Response::default())
  }
}

impl rosidl_runtime_rs::Message for OperatorCommand_Response {
  type RmwMsg = super::srv::rmw::OperatorCommand_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        stop_acknowledged: msg.stop_acknowledged,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      stop_acknowledged: msg.stop_acknowledged,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      stop_acknowledged: msg.stop_acknowledged,
      message: msg.message.to_string(),
    }
  }
}






#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__zfc_interfaces__srv__ApplyCalibration() -> *const std::ffi::c_void;
}

// Corresponds to zfc_interfaces__srv__ApplyCalibration
#[allow(missing_docs, non_camel_case_types)]
pub struct ApplyCalibration;

impl rosidl_runtime_rs::Service for ApplyCalibration {
    type Request = ApplyCalibration_Request;
    type Response = ApplyCalibration_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__zfc_interfaces__srv__ApplyCalibration() }
    }
}




#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__zfc_interfaces__srv__OperatorCommand() -> *const std::ffi::c_void;
}

// Corresponds to zfc_interfaces__srv__OperatorCommand
#[allow(missing_docs, non_camel_case_types)]
pub struct OperatorCommand;

impl rosidl_runtime_rs::Service for OperatorCommand {
    type Request = OperatorCommand_Request;
    type Response = OperatorCommand_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__zfc_interfaces__srv__OperatorCommand() }
    }
}


