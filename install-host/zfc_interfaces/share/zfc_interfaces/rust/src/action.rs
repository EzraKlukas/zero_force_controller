
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to zfc_interfaces__action__RunCalibration_Goal

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunCalibration_Goal::default())
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_Goal {
  type RmwMsg = super::action::rmw::RunCalibration_Goal;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        activate_zero_force_after: msg.activate_zero_force_after,
        external_contact_clear: msg.external_contact_clear,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      activate_zero_force_after: msg.activate_zero_force_after,
      external_contact_clear: msg.external_contact_clear,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      activate_zero_force_after: msg.activate_zero_force_after,
      external_contact_clear: msg.external_contact_clear,
    }
  }
}


// Corresponds to zfc_interfaces__action__RunCalibration_Result

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub trial_directory: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,


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
    pub fit: super::msg::CalibrationResult,

}



impl Default for RunCalibration_Result {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunCalibration_Result::default())
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_Result {
  type RmwMsg = super::action::rmw::RunCalibration_Result;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        trial_id: msg.trial_id,
        trial_directory: msg.trial_directory.as_str().into(),
        message: msg.message.as_str().into(),
        applied: msg.applied,
        zero_force_active: msg.zero_force_active,
        stop_acknowledged: msg.stop_acknowledged,
        fit: super::msg::CalibrationResult::into_rmw_message(std::borrow::Cow::Owned(msg.fit)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      trial_id: msg.trial_id,
        trial_directory: msg.trial_directory.as_str().into(),
        message: msg.message.as_str().into(),
      applied: msg.applied,
      zero_force_active: msg.zero_force_active,
      stop_acknowledged: msg.stop_acknowledged,
        fit: super::msg::CalibrationResult::into_rmw_message(std::borrow::Cow::Borrowed(&msg.fit)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      trial_id: msg.trial_id,
      trial_directory: msg.trial_directory.to_string(),
      message: msg.message.to_string(),
      applied: msg.applied,
      zero_force_active: msg.zero_force_active,
      stop_acknowledged: msg.stop_acknowledged,
      fit: super::msg::CalibrationResult::from_rmw_message(msg.fit),
    }
  }
}


// Corresponds to zfc_interfaces__action__RunCalibration_Feedback

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunCalibration_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: super::msg::AnalysisState,

}



impl Default for RunCalibration_Feedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunCalibration_Feedback::default())
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_Feedback {
  type RmwMsg = super::action::rmw::RunCalibration_Feedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        state: super::msg::AnalysisState::into_rmw_message(std::borrow::Cow::Owned(msg.state)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        state: super::msg::AnalysisState::into_rmw_message(std::borrow::Cow::Borrowed(&msg.state)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      state: super::msg::AnalysisState::from_rmw_message(msg.state),
    }
  }
}


// Corresponds to zfc_interfaces__action__RunCalibration_FeedbackMessage

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunCalibration_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::action::RunCalibration_Feedback,

}



impl Default for RunCalibration_FeedbackMessage {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunCalibration_FeedbackMessage::default())
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_FeedbackMessage {
  type RmwMsg = super::action::rmw::RunCalibration_FeedbackMessage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        feedback: super::action::RunCalibration_Feedback::into_rmw_message(std::borrow::Cow::Owned(msg.feedback)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        feedback: super::action::RunCalibration_Feedback::into_rmw_message(std::borrow::Cow::Borrowed(&msg.feedback)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      feedback: super::action::RunCalibration_Feedback::from_rmw_message(msg.feedback),
    }
  }
}






// Corresponds to zfc_interfaces__action__RunCalibration_SendGoal_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunCalibration_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::action::RunCalibration_Goal,

}



impl Default for RunCalibration_SendGoal_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunCalibration_SendGoal_Request::default())
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_SendGoal_Request {
  type RmwMsg = super::action::rmw::RunCalibration_SendGoal_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        goal: super::action::RunCalibration_Goal::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        goal: super::action::RunCalibration_Goal::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      goal: super::action::RunCalibration_Goal::from_rmw_message(msg.goal),
    }
  }
}


// Corresponds to zfc_interfaces__action__RunCalibration_SendGoal_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunCalibration_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,

}



impl Default for RunCalibration_SendGoal_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunCalibration_SendGoal_Response::default())
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_SendGoal_Response {
  type RmwMsg = super::action::rmw::RunCalibration_SendGoal_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
    }
  }
}


// Corresponds to zfc_interfaces__action__RunCalibration_GetResult_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunCalibration_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,

}



impl Default for RunCalibration_GetResult_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunCalibration_GetResult_Request::default())
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_GetResult_Request {
  type RmwMsg = super::action::rmw::RunCalibration_GetResult_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
    }
  }
}


// Corresponds to zfc_interfaces__action__RunCalibration_GetResult_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunCalibration_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::action::RunCalibration_Result,

}



impl Default for RunCalibration_GetResult_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunCalibration_GetResult_Response::default())
  }
}

impl rosidl_runtime_rs::Message for RunCalibration_GetResult_Response {
  type RmwMsg = super::action::rmw::RunCalibration_GetResult_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: msg.status,
        result: super::action::RunCalibration_Result::into_rmw_message(std::borrow::Cow::Owned(msg.result)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      status: msg.status,
        result: super::action::RunCalibration_Result::into_rmw_message(std::borrow::Cow::Borrowed(&msg.result)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      status: msg.status,
      result: super::action::RunCalibration_Result::from_rmw_message(msg.result),
    }
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






#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_action_type_support_handle__zfc_interfaces__action__RunCalibration() -> *const std::ffi::c_void;
}

// Corresponds to zfc_interfaces__action__RunCalibration
#[allow(missing_docs, non_camel_case_types)]
pub struct RunCalibration;

impl rosidl_runtime_rs::Action for RunCalibration {
  // --- Associated types for client library users ---
  /// The goal message defined in the action definition.
  type Goal = RunCalibration_Goal;

  /// The result message defined in the action definition.
  type Result = RunCalibration_Result;

  /// The feedback message defined in the action definition.
  type Feedback = RunCalibration_Feedback;

  // --- Associated types for client library implementation ---
  /// The feedback message with generic fields which wraps the feedback message.
  type FeedbackMessage = super::action::RunCalibration_FeedbackMessage;

  /// The send_goal service using a wrapped version of the goal message as a request.
  type SendGoalService = super::action::RunCalibration_SendGoal;

  /// The generic service to cancel a goal.
  type CancelGoalService = action_msgs::srv::rmw::CancelGoal;

  /// The get_result service using a wrapped version of the result message as a response.
  type GetResultService = super::action::RunCalibration_GetResult;

  // --- Methods for client library implementation ---
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_action_type_support_handle__zfc_interfaces__action__RunCalibration() }
  }

  fn create_goal_request(
    goal_id: &[u8; 16],
    goal: super::action::rmw::RunCalibration_Goal,
  ) -> super::action::rmw::RunCalibration_SendGoal_Request {
   super::action::rmw::RunCalibration_SendGoal_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
      goal,
    }
  }

  fn split_goal_request(
    request: super::action::rmw::RunCalibration_SendGoal_Request,
  ) -> (
    [u8; 16],
   super::action::rmw::RunCalibration_Goal,
  ) {
    (request.goal_id.uuid, request.goal)
  }

  fn create_goal_response(
    accepted: bool,
    stamp: (i32, u32),
  ) -> super::action::rmw::RunCalibration_SendGoal_Response {
   super::action::rmw::RunCalibration_SendGoal_Response {
      accepted,
      stamp: builtin_interfaces::msg::rmw::Time {
        sec: stamp.0,
        nanosec: stamp.1,
      },
    }
  }

  fn get_goal_response_accepted(
    response: &super::action::rmw::RunCalibration_SendGoal_Response,
  ) -> bool {
    response.accepted
  }

  fn get_goal_response_stamp(
    response: &super::action::rmw::RunCalibration_SendGoal_Response,
  ) -> (i32, u32) {
    (response.stamp.sec, response.stamp.nanosec)
  }

  fn create_feedback_message(
    goal_id: &[u8; 16],
    feedback: super::action::rmw::RunCalibration_Feedback,
  ) -> super::action::rmw::RunCalibration_FeedbackMessage {
    let mut message = super::action::rmw::RunCalibration_FeedbackMessage::default();
    message.goal_id.uuid = *goal_id;
    message.feedback = feedback;
    message
  }

  fn split_feedback_message(
    feedback: super::action::rmw::RunCalibration_FeedbackMessage,
  ) -> (
    [u8; 16],
   super::action::rmw::RunCalibration_Feedback,
  ) {
    (feedback.goal_id.uuid, feedback.feedback)
  }

  fn create_result_request(
    goal_id: &[u8; 16],
  ) -> super::action::rmw::RunCalibration_GetResult_Request {
   super::action::rmw::RunCalibration_GetResult_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
    }
  }

  fn get_result_request_uuid(
    request: &super::action::rmw::RunCalibration_GetResult_Request,
  ) -> &[u8; 16] {
    &request.goal_id.uuid
  }

  fn create_result_response(
    status: i8,
    result: super::action::rmw::RunCalibration_Result,
  ) -> super::action::rmw::RunCalibration_GetResult_Response {
   super::action::rmw::RunCalibration_GetResult_Response {
      status,
      result,
    }
  }

  fn split_result_response(
    response: super::action::rmw::RunCalibration_GetResult_Response
  ) -> (
    i8,
   super::action::rmw::RunCalibration_Result,
  ) {
    (response.status, response.result)
  }
}


