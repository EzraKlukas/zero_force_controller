#pragma once
#include "zfc_interfaces/capture.hpp"
#include "zfc_interfaces/msg/telemetry_batch.hpp"
#include "zfc_interfaces/msg/trial_status.hpp"
#include <rclcpp/rclcpp.hpp>
#include <mutex>
namespace zfc {
class TelemetryPublisher {
  struct Pipeline;
public:
  template<class Node> explicit TelemetryPublisher(const std::shared_ptr<Node> &node) {
    pipeline_=std::make_shared<Pipeline>();
    pipeline_->batches_=rclcpp::create_publisher<zfc_interfaces::msg::TelemetryBatch>(node,
      "~/telemetry", rclcpp::QoS(32).reliable());
    pipeline_->status_=rclcpp::create_publisher<zfc_interfaces::msg::TrialStatus>(node,
      "~/trial_status", rclcpp::QoS(1).reliable().transient_local());
    pipeline_->batch_.samples.reserve(256);
    // A queued callback owns the pipeline, so cancellation/destruction cannot
    // leave an executor callback holding a dangling controller pointer.
    timer_=node->create_wall_timer(std::chrono::milliseconds(20),
      [pipeline=pipeline_] { pipeline->drain(); });
  }
  ~TelemetryPublisher() { timer_->cancel(); }
  bool begin(std::uint64_t id) {
    // Never wait for the publisher from a lifecycle callback in the CM loop.
    if (!pipeline_->ready_.exchange(false,std::memory_order_acq_rel)) return false;
    if (pipeline_->capture_.begin(id)) return true;
    pipeline_->ready_.store(true,std::memory_order_release);
    return false;
  }
  void sample(const Snapshot &s) noexcept { pipeline_->capture_.append(s); }
  void finish(bool completed) noexcept { pipeline_->capture_.finish(completed); }
private:
 struct Pipeline {
  void drain() {
    std::lock_guard<std::mutex> lock(consumer_);
    drain_locked();
  }
  void drain_locked() {
    CaptureRecord r;
    // Bounded work per timer: at most the preallocated queue capacity.
    for (std::size_t consumed=0; consumed<8192;) {
      batch_.samples.clear();
      while (batch_.samples.size()<256 && capture_.pop(r)) {
        batch_.samples.emplace_back();
        auto &m=batch_.samples.back();
        m.stamp=rclcpp::Time(r.state.measured.time_ns);
        m.trial_id=r.trial_id; m.sequence=r.sequence;
        m.phase=static_cast<std::uint8_t>(r.state.phase);
        m.fault_code=static_cast<std::uint8_t>(r.state.fault);
        m.valid=r.state.valid;
        m.position_m=r.state.measured.position_m;
        m.velocity_mps=r.state.measured.velocity_mps;
        m.force_n=r.state.measured.force_n;
        m.reference_position_m=r.state.reference_position_m;
        m.reference_velocity_mps=r.state.reference_velocity_mps;
        m.reference_acceleration_mps2=r.state.reference_acceleration_mps2;
        m.baseline_force_n=r.state.baseline_force_n;
        m.noise_rms_n=r.state.noise_rms_n;
        m.residual_force_n=r.state.residual_force_n;
        m.progress=r.state.progress;
        m.excessive_periods=r.state.excessive_periods;
      }
      if (batch_.samples.empty()) break;
      consumed+=batch_.samples.size();
      batch_.stamp=batch_.samples.back().stamp;
      batch_.dropped_samples=capture_.drops();
      if (consumer_trial_!=batch_.samples.front().trial_id) {
        consumer_trial_=batch_.samples.front().trial_id;
        publication_failures_=0;
      }
      batch_.failed_publication_samples=publication_failures_;
      // Sequence gaps provide live loss detection; final exact drop count is
      // authoritative in trial_status (no concurrent read of producer counters).
      try { batches_->publish(batch_); }
      catch (const std::exception &) { publication_failures_+=batch_.samples.size(); }
    }
    Completion done;
    if (capture_.completion(done)) {
      auto &msg=pending_status_;
      msg.stamp=rclcpp::Time(done.final.state.measured.time_ns);
      msg.trial_id=done.final.trial_id;
      msg.final_sequence=done.final.sequence;
      msg.dropped_samples=done.dropped;
      msg.failed_publication_samples=publication_failures_;
      msg.phase=static_cast<std::uint8_t>(done.final.state.phase);
      msg.fault_code=static_cast<std::uint8_t>(done.final.state.fault);
      msg.completed=done.completed;
      msg.successful=done.completed && done.final.state.valid;
      msg.capture_complete=done.dropped==0 && publication_failures_==0;
      status_pending_=true;
    }
    if (status_pending_) {
      try {
        status_->publish(pending_status_);
        status_pending_=false;
        ready_.store(true,std::memory_order_release);
      } catch (const std::exception &) {
        // Retain terminal status and retry outside update() on the next timer.
      }
    }
  }
  Capture<8192> capture_;
  std::atomic<bool> ready_{true};
  std::uint64_t consumer_trial_=0, publication_failures_=0;
  bool status_pending_=false;
  zfc_interfaces::msg::TrialStatus pending_status_;
  std::mutex consumer_; // Consumer/lifecycle only; update never takes this lock.
  zfc_interfaces::msg::TelemetryBatch batch_;
  rclcpp::Publisher<zfc_interfaces::msg::TelemetryBatch>::SharedPtr batches_;
  rclcpp::Publisher<zfc_interfaces::msg::TrialStatus>::SharedPtr status_;
 };
  std::shared_ptr<Pipeline> pipeline_;
  rclcpp::TimerBase::SharedPtr timer_;
};
} // namespace zfc
