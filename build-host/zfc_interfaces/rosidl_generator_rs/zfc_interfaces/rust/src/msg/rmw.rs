#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__msg__ControllerState() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__msg__ControllerState__init(msg: *mut ControllerState) -> bool;
    fn zfc_interfaces__msg__ControllerState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ControllerState>, size: usize) -> bool;
    fn zfc_interfaces__msg__ControllerState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ControllerState>);
    fn zfc_interfaces__msg__ControllerState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ControllerState>, out_seq: *mut rosidl_runtime_rs::Sequence<ControllerState>) -> bool;
}

// Corresponds to zfc_interfaces__msg__ControllerState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ControllerState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub trial_id: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub sequence: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub phase: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub fault_code: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub position_m: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub velocity_mps: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub force_n: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reference_position_m: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reference_velocity_mps: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reference_acceleration_mps2: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub baseline_force_n: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub noise_rms_n: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub residual_force_n: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub progress: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub excessive_periods: u64,

}



impl Default for ControllerState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__msg__ControllerState__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__msg__ControllerState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ControllerState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__ControllerState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__ControllerState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__ControllerState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ControllerState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ControllerState where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/msg/ControllerState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__msg__ControllerState() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__msg__TelemetryBatch() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__msg__TelemetryBatch__init(msg: *mut TelemetryBatch) -> bool;
    fn zfc_interfaces__msg__TelemetryBatch__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<TelemetryBatch>, size: usize) -> bool;
    fn zfc_interfaces__msg__TelemetryBatch__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<TelemetryBatch>);
    fn zfc_interfaces__msg__TelemetryBatch__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<TelemetryBatch>, out_seq: *mut rosidl_runtime_rs::Sequence<TelemetryBatch>) -> bool;
}

// Corresponds to zfc_interfaces__msg__TelemetryBatch
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Reliable capture stream; consumers must verify sequence continuity.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TelemetryBatch {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub samples: rosidl_runtime_rs::BoundedSequence<super::super::msg::rmw::ControllerState, 256>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub dropped_samples: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub failed_publication_samples: u64,

}



impl Default for TelemetryBatch {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__msg__TelemetryBatch__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__msg__TelemetryBatch__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for TelemetryBatch {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__TelemetryBatch__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__TelemetryBatch__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__TelemetryBatch__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for TelemetryBatch {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for TelemetryBatch where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/msg/TelemetryBatch";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__msg__TelemetryBatch() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__msg__TrialStatus() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__msg__TrialStatus__init(msg: *mut TrialStatus) -> bool;
    fn zfc_interfaces__msg__TrialStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<TrialStatus>, size: usize) -> bool;
    fn zfc_interfaces__msg__TrialStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<TrialStatus>);
    fn zfc_interfaces__msg__TrialStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<TrialStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<TrialStatus>) -> bool;
}

// Corresponds to zfc_interfaces__msg__TrialStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Transient-local terminal status; independent of plotting delivery.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TrialStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub trial_id: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub final_sequence: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub dropped_samples: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub failed_publication_samples: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub phase: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub fault_code: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub completed: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub successful: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub capture_complete: bool,

}



impl Default for TrialStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__msg__TrialStatus__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__msg__TrialStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for TrialStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__TrialStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__TrialStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__TrialStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for TrialStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for TrialStatus where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/msg/TrialStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__msg__TrialStatus() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__msg__PlotState() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__msg__PlotState__init(msg: *mut PlotState) -> bool;
    fn zfc_interfaces__msg__PlotState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PlotState>, size: usize) -> bool;
    fn zfc_interfaces__msg__PlotState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PlotState>);
    fn zfc_interfaces__msg__PlotState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PlotState>, out_seq: *mut rosidl_runtime_rs::Sequence<PlotState>) -> bool;
}

// Corresponds to zfc_interfaces__msg__PlotState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Decimated visualization only. Original full-rate batches remain authoritative.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlotState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: super::super::msg::rmw::ControllerState,

    /// Reconstructed outside update from force - frozen baseline - residual.
    /// Meaningful only in compliant phase; zero in capture/calibration phases.
    pub inertial_compensation_n: f64,

}



impl Default for PlotState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__msg__PlotState__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__msg__PlotState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PlotState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__PlotState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__PlotState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__PlotState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PlotState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PlotState where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/msg/PlotState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__msg__PlotState() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__msg__CalibrationResult() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__msg__CalibrationResult__init(msg: *mut CalibrationResult) -> bool;
    fn zfc_interfaces__msg__CalibrationResult__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CalibrationResult>, size: usize) -> bool;
    fn zfc_interfaces__msg__CalibrationResult__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CalibrationResult>);
    fn zfc_interfaces__msg__CalibrationResult__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CalibrationResult>, out_seq: *mut rosidl_runtime_rs::Sequence<CalibrationResult>) -> bool;
}

// Corresponds to zfc_interfaces__msg__CalibrationResult
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Signed slope of force.x against effective commanded acceleration; NOT total mass.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CalibrationResult {

    // This member is not documented.
    #[allow(missing_docs)]
    pub valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reason: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub inertial_force_coefficient_kg: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub intercept_n: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub r_squared: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub residual_rms_n: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub uncertainty_kg: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub sample_count: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub plateau_count: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub positive_slope_kg: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub negative_slope_kg: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tracking_rms_m: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub acceleration_source: rosidl_runtime_rs::String,

}



impl Default for CalibrationResult {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__msg__CalibrationResult__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__msg__CalibrationResult__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CalibrationResult {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__CalibrationResult__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__CalibrationResult__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__CalibrationResult__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CalibrationResult {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CalibrationResult where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/msg/CalibrationResult";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__msg__CalibrationResult() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__msg__AnalysisState() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__msg__AnalysisState__init(msg: *mut AnalysisState) -> bool;
    fn zfc_interfaces__msg__AnalysisState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<AnalysisState>, size: usize) -> bool;
    fn zfc_interfaces__msg__AnalysisState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<AnalysisState>);
    fn zfc_interfaces__msg__AnalysisState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<AnalysisState>, out_seq: *mut rosidl_runtime_rs::Sequence<AnalysisState>) -> bool;
}

// Corresponds to zfc_interfaces__msg__AnalysisState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AnalysisState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub trial_id: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stage: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stage_code: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub progress: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub recorded_samples: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub dropped_samples: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub final_sequence: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stop_acknowledged: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub detail: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub fit: super::super::msg::rmw::CalibrationResult,


    // This member is not documented.
    #[allow(missing_docs)]
    pub backend: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operation_pending: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub trial_directory: rosidl_runtime_rs::String,

}



impl Default for AnalysisState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__msg__AnalysisState__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__msg__AnalysisState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for AnalysisState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__AnalysisState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__AnalysisState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__AnalysisState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for AnalysisState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for AnalysisState where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/msg/AnalysisState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__msg__AnalysisState() }
  }
}


#[link(name = "zfc_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__msg__MeasuredState() -> *const std::ffi::c_void;
}

#[link(name = "zfc_interfaces__rosidl_generator_c")]
extern "C" {
    fn zfc_interfaces__msg__MeasuredState__init(msg: *mut MeasuredState) -> bool;
    fn zfc_interfaces__msg__MeasuredState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<MeasuredState>, size: usize) -> bool;
    fn zfc_interfaces__msg__MeasuredState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<MeasuredState>);
    fn zfc_interfaces__msg__MeasuredState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<MeasuredState>, out_seq: *mut rosidl_runtime_rs::Sequence<MeasuredState>) -> bool;
}

// Corresponds to zfc_interfaces__msg__MeasuredState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Visualization only: independent broadcaster samples, NOT synchronized capture.
/// Header is the joint source time. Force retains its own source time.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MeasuredState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub force_stamp: builtin_interfaces::msg::rmw::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub position_m: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub velocity_mps: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub force_n: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub joint_fresh: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub force_fresh: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub detail: rosidl_runtime_rs::String,

}



impl Default for MeasuredState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !zfc_interfaces__msg__MeasuredState__init(&mut msg as *mut _) {
        panic!("Call to zfc_interfaces__msg__MeasuredState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for MeasuredState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__MeasuredState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__MeasuredState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { zfc_interfaces__msg__MeasuredState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for MeasuredState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for MeasuredState where Self: Sized {
  const TYPE_NAME: &'static str = "zfc_interfaces/msg/MeasuredState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__zfc_interfaces__msg__MeasuredState() }
  }
}


