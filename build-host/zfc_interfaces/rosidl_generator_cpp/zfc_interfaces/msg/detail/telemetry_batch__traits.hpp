// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from zfc_interfaces:msg/TelemetryBatch.idl
// generated code does not contain a copyright notice

#ifndef ZFC_INTERFACES__MSG__DETAIL__TELEMETRY_BATCH__TRAITS_HPP_
#define ZFC_INTERFACES__MSG__DETAIL__TELEMETRY_BATCH__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "zfc_interfaces/msg/detail/telemetry_batch__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"
// Member 'samples'
#include "zfc_interfaces/msg/detail/controller_state__traits.hpp"

namespace zfc_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const TelemetryBatch & msg,
  std::ostream & out)
{
  out << "{";
  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: samples
  {
    if (msg.samples.size() == 0) {
      out << "samples: []";
    } else {
      out << "samples: [";
      size_t pending_items = msg.samples.size();
      for (auto item : msg.samples) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: dropped_samples
  {
    out << "dropped_samples: ";
    rosidl_generator_traits::value_to_yaml(msg.dropped_samples, out);
    out << ", ";
  }

  // member: failed_publication_samples
  {
    out << "failed_publication_samples: ";
    rosidl_generator_traits::value_to_yaml(msg.failed_publication_samples, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TelemetryBatch & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }

  // member: samples
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.samples.size() == 0) {
      out << "samples: []\n";
    } else {
      out << "samples:\n";
      for (auto item : msg.samples) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: dropped_samples
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dropped_samples: ";
    rosidl_generator_traits::value_to_yaml(msg.dropped_samples, out);
    out << "\n";
  }

  // member: failed_publication_samples
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "failed_publication_samples: ";
    rosidl_generator_traits::value_to_yaml(msg.failed_publication_samples, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TelemetryBatch & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace zfc_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use zfc_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const zfc_interfaces::msg::TelemetryBatch & msg,
  std::ostream & out, size_t indentation = 0)
{
  zfc_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use zfc_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const zfc_interfaces::msg::TelemetryBatch & msg)
{
  return zfc_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<zfc_interfaces::msg::TelemetryBatch>()
{
  return "zfc_interfaces::msg::TelemetryBatch";
}

template<>
inline const char * name<zfc_interfaces::msg::TelemetryBatch>()
{
  return "zfc_interfaces/msg/TelemetryBatch";
}

template<>
struct has_fixed_size<zfc_interfaces::msg::TelemetryBatch>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<zfc_interfaces::msg::TelemetryBatch>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value && has_bounded_size<zfc_interfaces::msg::ControllerState>::value> {};

template<>
struct is_message<zfc_interfaces::msg::TelemetryBatch>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ZFC_INTERFACES__MSG__DETAIL__TELEMETRY_BATCH__TRAITS_HPP_
