# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target zfc_interfaces::zfc_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${zfc_interfaces_TARGETS}.
if(zfc_interfaces_TARGETS AND NOT TARGET zfc_interfaces::zfc_interfaces)
  add_library(zfc_interfaces::zfc_interfaces INTERFACE IMPORTED)
  set_target_properties(zfc_interfaces::zfc_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${zfc_interfaces_TARGETS}")
endif()
