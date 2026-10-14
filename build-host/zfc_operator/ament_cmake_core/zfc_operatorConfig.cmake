# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_zfc_operator_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED zfc_operator_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(zfc_operator_FOUND FALSE)
  elseif(NOT zfc_operator_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(zfc_operator_FOUND FALSE)
  endif()
  return()
endif()
set(_zfc_operator_CONFIG_INCLUDED TRUE)

# output package information
if(NOT zfc_operator_FIND_QUIETLY)
  message(STATUS "Found zfc_operator: 0.1.0 (${zfc_operator_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'zfc_operator' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${zfc_operator_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(zfc_operator_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${zfc_operator_DIR}/${_extra}")
endforeach()
