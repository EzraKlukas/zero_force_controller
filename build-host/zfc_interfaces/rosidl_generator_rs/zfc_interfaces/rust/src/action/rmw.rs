
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_Goal() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__action__RunCalibration_Goal__init(msg: *mut RunCalibration_Goal) -> bool;
    fn zfc_interfaces__action__RunCalibration_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_Goal>, size: usize) -> bool;
    fn zfc_interfaces__action__RunCalibration_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_Goal>);
    fn zfc_interfaces__action__RunCalibration_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunCalibration_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_Goal>) -> bool;
}

// Corresponds to zfc_interfaces__action__RunCalibration_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunCalibration_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub activate_zero_force_after: bool,

    /// Physical operator affirmation for this trial and baseline/noise capture.
    pub external_contact_clear: bool,

}



impl Default for RunCalibration_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__action__RunCalibration_Goal__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__action__RunCalibration_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunCalibration_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunCalibration_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/action/RunCalibration_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_Goal() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_Result() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__action__RunCalibration_Result__init(msg: *mut RunCalibration_Result) -> bool;
    fn zfc_interfaces__action__RunCalibration_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_Result>, size: usize) -> bool;
    fn zfc_interfaces__action__RunCalibration_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_Result>);
    fn zfc_interfaces__action__RunCalibration_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunCalibration_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_Result>) -> bool;
}

// Corresponds to zfc_interfaces__action__RunCalibration_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunCalibration_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub trial_id: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub trial_directory: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub applied: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub zero_force_active: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stop_acknowledged: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub fit: super::super::msg::rmw::CalibrationResult,

}



impl Default for RunCalibration_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__action__RunCalibration_Result__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__action__RunCalibration_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunCalibration_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunCalibration_Result where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/action/RunCalibration_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_Result() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__action__RunCalibration_Feedback__init(msg: *mut RunCalibration_Feedback) -> bool;
    fn zfc_interfaces__action__RunCalibration_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_Feedback>, size: usize) -> bool;
    fn zfc_interfaces__action__RunCalibration_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_Feedback>);
    fn zfc_interfaces__action__RunCalibration_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunCalibration_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_Feedback>) -> bool;
}

// Corresponds to zfc_interfaces__action__RunCalibration_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunCalibration_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: super::super::msg::rmw::AnalysisState,

}



impl Default for RunCalibration_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__action__RunCalibration_Feedback__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__action__RunCalibration_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunCalibration_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunCalibration_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/action/RunCalibration_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_Feedback() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__action__RunCalibration_FeedbackMessage__init(msg: *mut RunCalibration_FeedbackMessage) -> bool;
    fn zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_FeedbackMessage>, size: usize) -> bool;
    fn zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_FeedbackMessage>);
    fn zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunCalibration_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_FeedbackMessage>) -> bool;
}

// Corresponds to zfc_interfaces__action__RunCalibration_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunCalibration_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::RunCalibration_Feedback,

}



impl Default for RunCalibration_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__action__RunCalibration_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__action__RunCalibration_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunCalibration_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunCalibration_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/action/RunCalibration_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_FeedbackMessage() }
  }
}




#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__action__RunCalibration_SendGoal_Request__init(msg: *mut RunCalibration_SendGoal_Request) -> bool;
    fn zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_SendGoal_Request>, size: usize) -> bool;
    fn zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_SendGoal_Request>);
    fn zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunCalibration_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_SendGoal_Request>) -> bool;
}

// Corresponds to zfc_interfaces__action__RunCalibration_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunCalibration_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::RunCalibration_Goal,

}



impl Default for RunCalibration_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__action__RunCalibration_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__action__RunCalibration_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunCalibration_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunCalibration_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/action/RunCalibration_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_SendGoal_Request() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__action__RunCalibration_SendGoal_Response__init(msg: *mut RunCalibration_SendGoal_Response) -> bool;
    fn zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_SendGoal_Response>, size: usize) -> bool;
    fn zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_SendGoal_Response>);
    fn zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunCalibration_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_SendGoal_Response>) -> bool;
}

// Corresponds to zfc_interfaces__action__RunCalibration_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunCalibration_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for RunCalibration_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__action__RunCalibration_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__action__RunCalibration_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunCalibration_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunCalibration_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/action/RunCalibration_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_SendGoal_Response() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__action__RunCalibration_GetResult_Request__init(msg: *mut RunCalibration_GetResult_Request) -> bool;
    fn zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_GetResult_Request>, size: usize) -> bool;
    fn zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_GetResult_Request>);
    fn zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunCalibration_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_GetResult_Request>) -> bool;
}

// Corresponds to zfc_interfaces__action__RunCalibration_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunCalibration_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for RunCalibration_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__action__RunCalibration_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__action__RunCalibration_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunCalibration_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunCalibration_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/action/RunCalibration_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_GetResult_Request() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__action__RunCalibration_GetResult_Response__init(msg: *mut RunCalibration_GetResult_Response) -> bool;
    fn zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_GetResult_Response>, size: usize) -> bool;
    fn zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_GetResult_Response>);
    fn zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunCalibration_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<RunCalibration_GetResult_Response>) -> bool;
}

// Corresponds to zfc_interfaces__action__RunCalibration_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunCalibration_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::RunCalibration_Result,

}



impl Default for RunCalibration_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__action__RunCalibration_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__action__RunCalibration_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunCalibration_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__action__RunCalibration_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunCalibration_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/action/RunCalibration_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__action__RunCalibration_GetResult_Response() }
  }
}






#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__zfc_interfaces__action__RunCalibration_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to zfc_interfaces__action__RunCalibration_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct RunCalibration_SendGoal;

impl rosidl_runtime_rs::Service for RunCalibration_SendGoal {
    type Request = RunCalibration_SendGoal_Request;
    type Response = RunCalibration_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__zfc_interfaces__action__RunCalibration_SendGoal() }
    }
}




#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__zfc_interfaces__action__RunCalibration_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to zfc_interfaces__action__RunCalibration_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct RunCalibration_GetResult;

impl rosidl_runtime_rs::Service for RunCalibration_GetResult {
    type Request = RunCalibration_GetResult_Request;
    type Response = RunCalibration_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__zfc_interfaces__action__RunCalibration_GetResult() }
    }
}


