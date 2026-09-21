// Copyright 2020 ROS2-Control Development Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "cycle_timing.hpp"
#include <errno.h>
#include <algorithm>
#include <chrono>
#include <memory>
#include <string>
#include <thread>

#include "controller_manager/controller_manager.hpp"
#include "rclcpp/rclcpp.hpp"
#include "realtime_tools/realtime_helpers.hpp"

using namespace std::chrono_literals;

namespace
{
// Reference: https://man7.org/linux/man-pages/man2/sched_setparam.2.html
// This value is used when configuring the main loop to use SCHED_FIFO scheduling
// We use a midpoint RT priority to allow maximum flexibility to users
int const kSchedPriority = 50;

}  // namespace

int main(int argc, char ** argv)
{
  zfc::timing::initialize();
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Executor> executor =
    std::make_shared<rclcpp::executors::MultiThreadedExecutor>();
  std::string manager_node_name = "controller_manager";

  auto cm = std::make_shared<controller_manager::ControllerManager>(executor, manager_node_name);

  const bool use_sim_time = cm->get_parameter_or("use_sim_time", false);

  const bool has_realtime = realtime_tools::has_realtime_kernel();
  const bool lock_memory = cm->get_parameter_or<bool>("lock_memory", has_realtime);
  if (lock_memory)
  {
    const auto lock_result = realtime_tools::lock_memory();
    if (!lock_result.first)
    {
      RCLCPP_WARN(cm->get_logger(), "Unable to lock the memory: '%s'", lock_result.second.c_str());
    }
  }

  RCLCPP_INFO(cm->get_logger(), "update rate is %d Hz", cm->get_update_rate());
  const int thread_priority = cm->get_parameter_or<int>("thread_priority", kSchedPriority);
  RCLCPP_INFO(
    cm->get_logger(), "Spawning %s RT thread with scheduler priority: %d", cm->get_name(),
    thread_priority);

  std::thread cm_thread(
    [cm, thread_priority, use_sim_time]()
    {
      rclcpp::Parameter cpu_affinity_param;
      if (cm->get_parameter("cpu_affinity", cpu_affinity_param))
      {
        std::vector<int> cpus = {};
        if (cpu_affinity_param.get_type() == rclcpp::ParameterType::PARAMETER_INTEGER)
        {
          cpus = {static_cast<int>(cpu_affinity_param.as_int())};
        }
        else if (cpu_affinity_param.get_type() == rclcpp::ParameterType::PARAMETER_INTEGER_ARRAY)
        {
          const auto cpu_affinity_param_array = cpu_affinity_param.as_integer_array();
          std::for_each(
            cpu_affinity_param_array.begin(), cpu_affinity_param_array.end(),
            [&cpus](int cpu) { cpus.push_back(static_cast<int>(cpu)); });
        }
        const auto affinity_result = realtime_tools::set_current_thread_affinity(cpus);
        if (!affinity_result.first)
        {
          RCLCPP_WARN(
            cm->get_logger(), "Unable to set the CPU affinity : '%s'",
            affinity_result.second.c_str());
        }
      }

      if (!realtime_tools::configure_sched_fifo(thread_priority))
      {
        RCLCPP_WARN(
          cm->get_logger(),
          "Could not enable FIFO RT scheduling policy: with error number <%i>(%s). See "
          "[https://control.ros.org/master/doc/ros2_control/controller_manager/doc/userdoc.html] "
          "for details on how to enable realtime scheduling.",
          errno, strerror(errno));
      }
      else
      {
        RCLCPP_INFO(
          cm->get_logger(), "Successful set up FIFO RT scheduling policy with priority %i.",
          thread_priority);
      }

      // for calculating sleep time
      auto const period = std::chrono::nanoseconds(1'000'000'000 / cm->get_update_rate());
      auto const cm_now = std::chrono::nanoseconds(cm->now().nanoseconds());
      std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>
        next_iteration_time{cm_now};

      // for calculating the measured period of the loop
      rclcpp::Time previous_time = cm->now();

#if ZFC_PROFILE_LEVEL
      zfc::timing::managed_loop = true;
#endif
      while (rclcpp::ok())
      {
        zfc::timing::begin();
#if ZFC_PROFILE_LEVEL
        zfc::timing::map_system_deadline(next_iteration_time.time_since_epoch().count());
#endif
        // calculate measured period
        auto const current_time = cm->now();
        auto const measured_period = current_time - previous_time;
        previous_time = current_time;

        // execute update loop
        ZFC_VALUE(zfc::timing::ros_period_ns, measured_period.nanoseconds());
        zfc::timing::mark(zfc::timing::cm_read_entry);
        cm->read(cm->now(), measured_period);
        zfc::timing::mark(zfc::timing::cm_read_exit);
        zfc::timing::mark(zfc::timing::cm_update_entry);
        cm->update(cm->now(), measured_period);
        zfc::timing::mark(zfc::timing::cm_update_exit);
        zfc::timing::mark(zfc::timing::cm_write_entry);
        cm->write(cm->now(), measured_period);
        zfc::timing::mark(zfc::timing::cm_write_exit);
#if ZFC_PROFILE_LEVEL
        ZFC_VALUE(zfc::timing::write_exit_system_ns, zfc::timing::system_ns());
#endif

        // wait until we hit the end of the period
        next_iteration_time += period;
        zfc::timing::mark(zfc::timing::sleep_entry);
#if ZFC_PROFILE_LEVEL
        ZFC_VALUE(zfc::timing::execution_end_mono_ns, zfc::timing::mono_ns());
#endif
        zfc::timing::finish();
        if (use_sim_time)
        {
          cm->get_clock()->sleep_until(current_time + period);
        }
        else
        {
          std::this_thread::sleep_until(next_iteration_time);
        }
        zfc::timing::after_sleep();
      }
    });

  executor->add_node(cm);
  executor->spin();
  cm_thread.join();
  rclcpp::shutdown();
  zfc::timing::flush();
  return 0;
}
