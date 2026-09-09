#pragma once
#include "count_command.hpp"
#include "hardware_interface/system_interface.hpp"
#include <array>
namespace zfc_ethercat_hardware {
class EthercatHardware : public hardware_interface::SystemInterface {
public:
  using Callback = hardware_interface::CallbackReturn;
  using Result = hardware_interface::return_type;
  ~EthercatHardware() override;
  Callback on_init(const hardware_interface::HardwareInfo &) override;
  Callback on_configure(const rclcpp_lifecycle::State &) override;
  Callback on_activate(const rclcpp_lifecycle::State &) override;
  Callback on_deactivate(const rclcpp_lifecycle::State &) override;
  Callback on_cleanup(const rclcpp_lifecycle::State &) override;
  Callback on_shutdown(const rclcpp_lifecycle::State &) override;
  Callback on_error(const rclcpp_lifecycle::State &) override;
  std::vector<hardware_interface::StateInterface>
  export_state_interfaces() override;
  std::vector<hardware_interface::CommandInterface>
  export_command_interfaces() override;
  Result perform_command_mode_switch(const std::vector<std::string> &,
                                     const std::vector<std::string> &) override;
  Result read(const rclcpp::Time &, const rclcpp::Duration &) override;
  Result write(const rclcpp::Time &, const rclcpp::Duration &) override;

private:
  void copy_state() noexcept;
  void fault(bool communication) noexcept;
  bool stop() noexcept;
  void reset() noexcept;
  zfc::EthercatSystem core_;
  zfc::StopSequence stop_sequence_;
  std::array<double, 25> state_{};
  double command_ = 0, startup_timeout_ = 20;
  std::int32_t previous_ = 0;
  bool active_ = false, claimed_ = false, fault_ = false, stop_complete_ = true;
  bool read_pending_ = false, prefaulted_ = false;
  std::uint64_t last_read_ns_ = 0;
};
} // namespace zfc_ethercat_hardware
