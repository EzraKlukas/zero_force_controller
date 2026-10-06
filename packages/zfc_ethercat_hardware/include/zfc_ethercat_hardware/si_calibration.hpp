#pragma once
#include <array>
#include <cmath>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>
namespace zfc_ethercat_hardware {
// Installation calibration only. No PDO units or switch interpretation change.
struct SiCalibration {
  double metres_per_count = NAN, encoder_zero_counts = NAN;
  double velocity_mps_per_raw_unit = NAN;
  std::array<double, 3> force_scale{NAN, NAN, NAN};
  std::array<double, 3> force_zero{NAN, NAN, NAN};
  double lower = NAN, upper = NAN;
  static bool parameter(std::string_view key) noexcept {
    return key == "metres_per_count" || key == "encoder_zero_counts" ||
           key == "velocity_mps_per_raw_unit" ||
           key == "conventions_confirmed" || key == "force_frame" ||
           key == "force_channel_mapping" ||
           key == "force_x_newtons_per_count" || key == "force_y_newtons_per_count" ||
           key == "force_z_newtons_per_count" || key == "force_x_zero_counts" ||
           key == "force_y_zero_counts" || key == "force_z_zero_counts";
  }
  template<class Parameters>
  static SiCalibration load(const Parameters &params, double min, double max) {
    auto text = [&](const std::string &key) -> std::string {
      const auto it = params.find(key);
      if (it == params.end())
        throw std::runtime_error("Missing installation calibration: " + key);
      return it->second;
    };
    auto number = [&](const std::string &key, bool nonzero) {
      const auto value = text(key);
      std::size_t used = 0;
      double result = NAN;
      try { result = std::stod(value, &used); }
      catch (...) { throw std::runtime_error("Invalid installation calibration: " + key); }
      if (used != value.size() || !std::isfinite(result) || (nonzero && result == 0))
        throw std::runtime_error("Installation calibration " + key +
                                 " must be finite" + (nonzero ? " and nonzero" : ""));
      return result;
    };
    SiCalibration c;
    c.metres_per_count = number("metres_per_count", true);
    c.encoder_zero_counts = number("encoder_zero_counts", false);
    c.velocity_mps_per_raw_unit = number("velocity_mps_per_raw_unit", true);
    const std::array<std::string, 3> axes{"x", "y", "z"};
    for (unsigned i = 0; i < 3; ++i) {
      c.force_scale[i] = number("force_" + axes[i] + "_newtons_per_count", true);
      c.force_zero[i] = number("force_" + axes[i] + "_zero_counts", false);
    }
    if (text("conventions_confirmed") != "true" ||
        text("force_frame") != "load_cell_link" ||
        text("force_channel_mapping") != "x,y,z")
      throw std::runtime_error(
          "Confirm lower datum, independently measured raw velocity units/sign, and "
          "ELM X/Y/Z channel signs in load_cell_link (+X upward); "
          "require conventions_confirmed=true, force_frame=load_cell_link, "
          "force_channel_mapping=x,y,z. Other mappings/coupling require review.");
    if (!std::isfinite(min) || !std::isfinite(max) || min != 0 || max <= min)
      throw std::runtime_error("Require finite carriage travel bounds with lower datum=0");
    c.lower = min;
    c.upper = max;
    for (const auto raw : {std::numeric_limits<std::int32_t>::min(),
                           std::numeric_limits<std::int32_t>::max()}) {
      if (!std::isfinite(c.position(raw)) || !std::isfinite(c.velocity(raw)))
        throw std::runtime_error("Position/velocity installation calibration overflows native int32 feedback");
      for (unsigned i = 0; i < 3; ++i)
        if (!std::isfinite(c.force(i, raw)))
          throw std::runtime_error("Force installation calibration overflows native int32 feedback: " + axes[i]);
    }
    // Both travel endpoints must be representable by the native drive command.
    std::int32_t unused;
    if (!c.to_counts(min, unused) || !c.to_counts(max, unused))
      throw std::runtime_error("Calibrated travel endpoints exceed int32 encoder range or round outside travel");
    return c;
  }
  double position(std::int32_t counts) const noexcept {
    return metres_per_count * (double(counts) - encoder_zero_counts);
  }
  double velocity(std::int32_t raw) const noexcept {
    return velocity_mps_per_raw_unit * double(raw);
  }
  double force(unsigned axis, std::int32_t raw) const noexcept {
    return force_scale[axis] * (double(raw) - force_zero[axis]);
  }
  bool to_counts(double q, std::int32_t &out) const noexcept {
    if (!std::isfinite(q) || !std::isfinite(metres_per_count) ||
        metres_per_count == 0 || !std::isfinite(encoder_zero_counts) ||
        q < lower || q > upper)
      return false;
    const double raw = encoder_zero_counts + q / metres_per_count;
    if (!std::isfinite(raw) || raw < std::numeric_limits<std::int32_t>::min() ||
        raw > std::numeric_limits<std::int32_t>::max())
      return false;
    const double rounded = std::round(raw);
    if (rounded < std::numeric_limits<std::int32_t>::min() ||
        rounded > std::numeric_limits<std::int32_t>::max())
      return false;
    const auto counts = static_cast<std::int32_t>(rounded);
    const double actual = position(counts);
    if (!std::isfinite(actual) || actual < lower || actual > upper)
      return false;
    out = counts;
    return true;
  }
};
} // namespace zfc_ethercat_hardware
