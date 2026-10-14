#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__srv__ApplyCalibration_Request() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__srv__ApplyCalibration_Request__init(msg: *mut ApplyCalibration_Request) -> bool;
    fn zfc_interfaces__srv__ApplyCalibration_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ApplyCalibration_Request>, size: usize) -> bool;
    fn zfc_interfaces__srv__ApplyCalibration_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ApplyCalibration_Request>);
    fn zfc_interfaces__srv__ApplyCalibration_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ApplyCalibration_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ApplyCalibration_Request>) -> bool;
}

// Corresponds to zfc_interfaces__srv__ApplyCalibration_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ApplyCalibration_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub result_file: rosidl_runtime_rs::String,

}



impl Default for ApplyCalibration_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__srv__ApplyCalibration_Request__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__srv__ApplyCalibration_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ApplyCalibration_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__srv__ApplyCalibration_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__srv__ApplyCalibration_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__srv__ApplyCalibration_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ApplyCalibration_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ApplyCalibration_Request where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/srv/ApplyCalibration_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__srv__ApplyCalibration_Request() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__srv__ApplyCalibration_Response() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__srv__ApplyCalibration_Response__init(msg: *mut ApplyCalibration_Response) -> bool;
    fn zfc_interfaces__srv__ApplyCalibration_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ApplyCalibration_Response>, size: usize) -> bool;
    fn zfc_interfaces__srv__ApplyCalibration_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ApplyCalibration_Response>);
    fn zfc_interfaces__srv__ApplyCalibration_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ApplyCalibration_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ApplyCalibration_Response>) -> bool;
}

// Corresponds to zfc_interfaces__srv__ApplyCalibration_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ApplyCalibration_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub fit: super::super::msg::rmw::CalibrationResult,

}



impl Default for ApplyCalibration_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__srv__ApplyCalibration_Response__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__srv__ApplyCalibration_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ApplyCalibration_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__srv__ApplyCalibration_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__srv__ApplyCalibration_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__srv__ApplyCalibration_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ApplyCalibration_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ApplyCalibration_Response where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/srv/ApplyCalibration_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__srv__ApplyCalibration_Response() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__srv__OperatorCommand_Request() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__srv__OperatorCommand_Request__init(msg: *mut OperatorCommand_Request) -> bool;
    fn zfc_interfaces__srv__OperatorCommand_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<OperatorCommand_Request>, size: usize) -> bool;
    fn zfc_interfaces__srv__OperatorCommand_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<OperatorCommand_Request>);
    fn zfc_interfaces__srv__OperatorCommand_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<OperatorCommand_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<OperatorCommand_Request>) -> bool;
}

// Corresponds to zfc_interfaces__srv__OperatorCommand_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OperatorCommand_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub command: rosidl_runtime_rs::String,

    /// Physical operator affirmation for THIS request; sensors cannot prove no contact.
    pub external_contact_clear: bool,

}



impl Default for OperatorCommand_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__srv__OperatorCommand_Request__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__srv__OperatorCommand_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for OperatorCommand_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__srv__OperatorCommand_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__srv__OperatorCommand_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__srv__OperatorCommand_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for OperatorCommand_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for OperatorCommand_Request where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/srv/OperatorCommand_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__srv__OperatorCommand_Request() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__srv__OperatorCommand_Response() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__srv__OperatorCommand_Response__init(msg: *mut OperatorCommand_Response) -> bool;
    fn zfc_interfaces__srv__OperatorCommand_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<OperatorCommand_Response>, size: usize) -> bool;
    fn zfc_interfaces__srv__OperatorCommand_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<OperatorCommand_Response>);
    fn zfc_interfaces__srv__OperatorCommand_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<OperatorCommand_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<OperatorCommand_Response>) -> bool;
}

// Corresponds to zfc_interfaces__srv__OperatorCommand_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
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
    pub message: rosidl_runtime_rs::String,

}



impl Default for OperatorCommand_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__srv__OperatorCommand_Response__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__srv__OperatorCommand_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for OperatorCommand_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__srv__OperatorCommand_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__srv__OperatorCommand_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__srv__OperatorCommand_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for OperatorCommand_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for OperatorCommand_Response where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/srv/OperatorCommand_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__srv__OperatorCommand_Response() }
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


