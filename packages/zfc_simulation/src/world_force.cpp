#include "zfc_simulation/force_command.hpp"
#include <algorithm>
#include <chrono>
#include <mutex>
#include <ignition/gazebo/System.hh>
#include <ignition/gazebo/Link.hh>
#include <ignition/gazebo/components/Link.hh>
#include <ignition/gazebo/components/Model.hh>
#include <ignition/gazebo/components/Name.hh>
#include <ignition/gazebo/components/ParentEntity.hh>
#include <ignition/plugin/Register.hh>
#include <ignition/transport/Node.hh>
#include <ignition/msgs/entity_wrench.pb.h>
#include <ignition/msgs/double.pb.h>
#include <ignition/msgs/boolean.pb.h>
namespace zfc_simulation {
namespace sim=ignition::gazebo;
std::int64_t wall_ns() {
  return std::chrono::duration_cast<std::chrono::nanoseconds>(
    std::chrono::steady_clock::now().time_since_epoch()).count();
}
class WorldForce : public sim::System, public sim::ISystemConfigure,
                   public sim::ISystemPreUpdate {
public:
  void Configure(const sim::Entity &,const std::shared_ptr<const sdf::Element> &,
                 sim::EntityComponentManager &,sim::EventManager &) override {
    node_.Subscribe("/world/zfc/force_input",&WorldForce::receive,this);
    applied_=node_.Advertise<ignition::msgs::Double>("/world/zfc/applied_force");
    node_.Subscribe("/world/zfc/force_enable",&WorldForce::enable,this);
    enabled_=node_.Advertise<ignition::msgs::Boolean>("/world/zfc/force_enabled");
  }
  void PreUpdate(const sim::UpdateInfo &info,sim::EntityComponentManager &ecm) override {
    if (info.paused) return;
    if (link_==sim::kNullEntity) {
      const auto model=ecm.EntityByComponents(sim::components::Model(),
                                             sim::components::Name("stage"));
      if (model!=sim::kNullEntity)
        link_=ecm.EntityByComponents(sim::components::Link(),
          sim::components::Name("tool_link"),sim::components::ParentEntity(model));
    }
    double force;
    bool enabled;
    {
      // Non-RT simulation callback only; no ROS/control-thread dependency.
      std::lock_guard<std::mutex> lock(mutex_);
      force=command_.value(wall_ns());
      enabled=command_.enabled;
    }
    if (link_!=sim::kNullEntity) {
      // The reviewed tool COM is at its link origin. AddWorldForce silently
      // does nothing without WorldPose; AddWorldWrench needs no pose component.
      sim::Link(link_).AddWorldWrench(ecm,{0,0,force},{0,0,0});
      ignition::msgs::Double msg;
      msg.set_data(force);
      applied_.Publish(msg);
      ignition::msgs::Boolean ack;
      ack.set_data(enabled);
      enabled_.Publish(ack); // Physics-step acknowledgment, not transport receipt.
    }
  }
private:
  void enable(const ignition::msgs::Boolean &msg) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (command_.enabled!=msg.data()) command_.enable(msg.data());
  }
  void receive(const ignition::msgs::EntityWrench &msg) {
    const auto &w=msg.wrench();
    const bool valid=msg.entity().name()=="stage::tool_link" &&
      msg.entity().type()==ignition::msgs::Entity::LINK && msg.entity().id()==0 &&
      w.force().x()==0 && w.force().y()==0 && w.torque().x()==0 &&
      w.torque().y()==0 && w.torque().z()==0;
    std::lock_guard<std::mutex> lock(mutex_);
    command_.receive(w.force().z(),wall_ns(),valid);
  }
  ignition::transport::Node node_;
  ignition::transport::Node::Publisher applied_;
  ignition::transport::Node::Publisher enabled_;
  sim::Entity link_=sim::kNullEntity;
  std::mutex mutex_;
  ForceCommand command_;
};
} // namespace zfc_simulation
IGNITION_ADD_PLUGIN(zfc_simulation::WorldForce,ignition::gazebo::System,
                    ignition::gazebo::ISystemConfigure,ignition::gazebo::ISystemPreUpdate)
