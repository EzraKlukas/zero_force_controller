#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to zfc_interfaces__msg__ControllerState

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ControllerState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::ControllerState::default())
  }
}

impl rosidl_runtime_rs::Message for ControllerState {
  type RmwMsg = super::msg::rmw::ControllerState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
        trial_id: msg.trial_id,
        sequence: msg.sequence,
        phase: msg.phase,
        fault_code: msg.fault_code,
        valid: msg.valid,
        position_m: msg.position_m,
        velocity_mps: msg.velocity_mps,
        force_n: msg.force_n,
        reference_position_m: msg.reference_position_m,
        reference_velocity_mps: msg.reference_velocity_mps,
        reference_acceleration_mps2: msg.reference_acceleration_mps2,
        baseline_force_n: msg.baseline_force_n,
        noise_rms_n: msg.noise_rms_n,
        residual_force_n: msg.residual_force_n,
        progress: msg.progress,
        excessive_periods: msg.excessive_periods,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      trial_id: msg.trial_id,
      sequence: msg.sequence,
      phase: msg.phase,
      fault_code: msg.fault_code,
      valid: msg.valid,
      position_m: msg.position_m,
      velocity_mps: msg.velocity_mps,
      force_n: msg.force_n,
      reference_position_m: msg.reference_position_m,
      reference_velocity_mps: msg.reference_velocity_mps,
      reference_acceleration_mps2: msg.reference_acceleration_mps2,
      baseline_force_n: msg.baseline_force_n,
      noise_rms_n: msg.noise_rms_n,
      residual_force_n: msg.residual_force_n,
      progress: msg.progress,
      excessive_periods: msg.excessive_periods,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
      trial_id: msg.trial_id,
      sequence: msg.sequence,
      phase: msg.phase,
      fault_code: msg.fault_code,
      valid: msg.valid,
      position_m: msg.position_m,
      velocity_mps: msg.velocity_mps,
      force_n: msg.force_n,
      reference_position_m: msg.reference_position_m,
      reference_velocity_mps: msg.reference_velocity_mps,
      reference_acceleration_mps2: msg.reference_acceleration_mps2,
      baseline_force_n: msg.baseline_force_n,
      noise_rms_n: msg.noise_rms_n,
      residual_force_n: msg.residual_force_n,
      progress: msg.progress,
      excessive_periods: msg.excessive_periods,
    }
  }
}


// Corresponds to zfc_interfaces__msg__TelemetryBatch
/// Reliable capture stream; consumers must verify sequence continuity.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TelemetryBatch {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub samples: rosidl_runtime_rs::BoundedSequence<super::msg::rmw::ControllerState, 256>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub dropped_samples: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub failed_publication_samples: u64,

}



impl Default for TelemetryBatch {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::TelemetryBatch::default())
  }
}

impl rosidl_runtime_rs::Message for TelemetryBatch {
  type RmwMsg = super::msg::rmw::TelemetryBatch;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
        samples: msg.samples,
        dropped_samples: msg.dropped_samples,
        failed_publication_samples: msg.failed_publication_samples,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
        samples: msg.samples.clone(),
      dropped_samples: msg.dropped_samples,
      failed_publication_samples: msg.failed_publication_samples,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
      samples: msg.samples,
      dropped_samples: msg.dropped_samples,
      failed_publication_samples: msg.failed_publication_samples,
    }
  }
}


// Corresponds to zfc_interfaces__msg__TrialStatus
/// Transient-local terminal status; independent of plotting delivery.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TrialStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::TrialStatus::default())
  }
}

impl rosidl_runtime_rs::Message for TrialStatus {
  type RmwMsg = super::msg::rmw::TrialStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
        trial_id: msg.trial_id,
        final_sequence: msg.final_sequence,
        dropped_samples: msg.dropped_samples,
        failed_publication_samples: msg.failed_publication_samples,
        phase: msg.phase,
        fault_code: msg.fault_code,
        completed: msg.completed,
        successful: msg.successful,
        capture_complete: msg.capture_complete,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      trial_id: msg.trial_id,
      final_sequence: msg.final_sequence,
      dropped_samples: msg.dropped_samples,
      failed_publication_samples: msg.failed_publication_samples,
      phase: msg.phase,
      fault_code: msg.fault_code,
      completed: msg.completed,
      successful: msg.successful,
      capture_complete: msg.capture_complete,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
      trial_id: msg.trial_id,
      final_sequence: msg.final_sequence,
      dropped_samples: msg.dropped_samples,
      failed_publication_samples: msg.failed_publication_samples,
      phase: msg.phase,
      fault_code: msg.fault_code,
      completed: msg.completed,
      successful: msg.successful,
      capture_complete: msg.capture_complete,
    }
  }
}


// Corresponds to zfc_interfaces__msg__PlotState
/// Decimated visualization only. Original full-rate batches remain authoritative.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlotState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: super::msg::ControllerState,

    /// Reconstructed outside update from force - frozen baseline - residual.
    /// Meaningful only in compliant phase; zero in capture/calibration phases.
    pub inertial_compensation_n: f64,

}



impl Default for PlotState {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::PlotState::default())
  }
}

impl rosidl_runtime_rs::Message for PlotState {
  type RmwMsg = super::msg::rmw::PlotState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        state: super::msg::ControllerState::into_rmw_message(std::borrow::Cow::Owned(msg.state)).into_owned(),
        inertial_compensation_n: msg.inertial_compensation_n,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        state: super::msg::ControllerState::into_rmw_message(std::borrow::Cow::Borrowed(&msg.state)).into_owned(),
      inertial_compensation_n: msg.inertial_compensation_n,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      state: super::msg::ControllerState::from_rmw_message(msg.state),
      inertial_compensation_n: msg.inertial_compensation_n,
    }
  }
}


// Corresponds to zfc_interfaces__msg__CalibrationResult
/// Signed slope of force.x against effective commanded acceleration; NOT total mass.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CalibrationResult {

    // This member is not documented.
    #[allow(missing_docs)]
    pub valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reason: std::string::String,


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
    pub acceleration_source: std::string::String,

}



impl Default for CalibrationResult {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::CalibrationResult::default())
  }
}

impl rosidl_runtime_rs::Message for CalibrationResult {
  type RmwMsg = super::msg::rmw::CalibrationResult;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        valid: msg.valid,
        reason: msg.reason.as_str().into(),
        inertial_force_coefficient_kg: msg.inertial_force_coefficient_kg,
        intercept_n: msg.intercept_n,
        r_squared: msg.r_squared,
        residual_rms_n: msg.residual_rms_n,
        uncertainty_kg: msg.uncertainty_kg,
        sample_count: msg.sample_count,
        plateau_count: msg.plateau_count,
        positive_slope_kg: msg.positive_slope_kg,
        negative_slope_kg: msg.negative_slope_kg,
        tracking_rms_m: msg.tracking_rms_m,
        acceleration_source: msg.acceleration_source.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      valid: msg.valid,
        reason: msg.reason.as_str().into(),
      inertial_force_coefficient_kg: msg.inertial_force_coefficient_kg,
      intercept_n: msg.intercept_n,
      r_squared: msg.r_squared,
      residual_rms_n: msg.residual_rms_n,
      uncertainty_kg: msg.uncertainty_kg,
      sample_count: msg.sample_count,
      plateau_count: msg.plateau_count,
      positive_slope_kg: msg.positive_slope_kg,
      negative_slope_kg: msg.negative_slope_kg,
      tracking_rms_m: msg.tracking_rms_m,
        acceleration_source: msg.acceleration_source.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      valid: msg.valid,
      reason: msg.reason.to_string(),
      inertial_force_coefficient_kg: msg.inertial_force_coefficient_kg,
      intercept_n: msg.intercept_n,
      r_squared: msg.r_squared,
      residual_rms_n: msg.residual_rms_n,
      uncertainty_kg: msg.uncertainty_kg,
      sample_count: msg.sample_count,
      plateau_count: msg.plateau_count,
      positive_slope_kg: msg.positive_slope_kg,
      negative_slope_kg: msg.negative_slope_kg,
      tracking_rms_m: msg.tracking_rms_m,
      acceleration_source: msg.acceleration_source.to_string(),
    }
  }
}


// Corresponds to zfc_interfaces__msg__AnalysisState

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AnalysisState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub trial_id: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stage: std::string::String,


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
    pub detail: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub fit: super::msg::CalibrationResult,


    // This member is not documented.
    #[allow(missing_docs)]
    pub backend: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operation_pending: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub trial_directory: std::string::String,

}



impl Default for AnalysisState {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::AnalysisState::default())
  }
}

impl rosidl_runtime_rs::Message for AnalysisState {
  type RmwMsg = super::msg::rmw::AnalysisState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        trial_id: msg.trial_id,
        stage: msg.stage.as_str().into(),
        stage_code: msg.stage_code,
        progress: msg.progress,
        recorded_samples: msg.recorded_samples,
        dropped_samples: msg.dropped_samples,
        final_sequence: msg.final_sequence,
        stop_acknowledged: msg.stop_acknowledged,
        detail: msg.detail.as_str().into(),
        fit: super::msg::CalibrationResult::into_rmw_message(std::borrow::Cow::Owned(msg.fit)).into_owned(),
        backend: msg.backend.as_str().into(),
        operation_pending: msg.operation_pending,
        trial_directory: msg.trial_directory.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      trial_id: msg.trial_id,
        stage: msg.stage.as_str().into(),
      stage_code: msg.stage_code,
      progress: msg.progress,
      recorded_samples: msg.recorded_samples,
      dropped_samples: msg.dropped_samples,
      final_sequence: msg.final_sequence,
      stop_acknowledged: msg.stop_acknowledged,
        detail: msg.detail.as_str().into(),
        fit: super::msg::CalibrationResult::into_rmw_message(std::borrow::Cow::Borrowed(&msg.fit)).into_owned(),
        backend: msg.backend.as_str().into(),
      operation_pending: msg.operation_pending,
        trial_directory: msg.trial_directory.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      trial_id: msg.trial_id,
      stage: msg.stage.to_string(),
      stage_code: msg.stage_code,
      progress: msg.progress,
      recorded_samples: msg.recorded_samples,
      dropped_samples: msg.dropped_samples,
      final_sequence: msg.final_sequence,
      stop_acknowledged: msg.stop_acknowledged,
      detail: msg.detail.to_string(),
      fit: super::msg::CalibrationResult::from_rmw_message(msg.fit),
      backend: msg.backend.to_string(),
      operation_pending: msg.operation_pending,
      trial_directory: msg.trial_directory.to_string(),
    }
  }
}


// Corresponds to zfc_interfaces__msg__MeasuredState
/// Visualization only: independent broadcaster samples, NOT synchronized capture.
/// Header is the joint source time. Force retains its own source time.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MeasuredState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub force_stamp: builtin_interfaces::msg::Time,


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
    pub detail: std::string::String,

}



impl Default for MeasuredState {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::MeasuredState::default())
  }
}

impl rosidl_runtime_rs::Message for MeasuredState {
  type RmwMsg = super::msg::rmw::MeasuredState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        force_stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.force_stamp)).into_owned(),
        position_m: msg.position_m,
        velocity_mps: msg.velocity_mps,
        force_n: msg.force_n,
        joint_fresh: msg.joint_fresh,
        force_fresh: msg.force_fresh,
        valid: msg.valid,
        detail: msg.detail.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        force_stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.force_stamp)).into_owned(),
      position_m: msg.position_m,
      velocity_mps: msg.velocity_mps,
      force_n: msg.force_n,
      joint_fresh: msg.joint_fresh,
      force_fresh: msg.force_fresh,
      valid: msg.valid,
        detail: msg.detail.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      force_stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.force_stamp),
      position_m: msg.position_m,
      velocity_mps: msg.velocity_mps,
      force_n: msg.force_n,
      joint_fresh: msg.joint_fresh,
      force_fresh: msg.force_fresh,
      valid: msg.valid,
      detail: msg.detail.to_string(),
    }
  }
}


