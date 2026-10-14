# Install script for directory: /home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/packages/zfc_operator

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/install-host/zfc_operator")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zfc_operator/environment" TYPE FILE FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_environment_hooks/pythonpath.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zfc_operator/environment" TYPE FILE FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_environment_hooks/pythonpath.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/local/lib/python3.10/dist-packages/zfc_operator-0.1.0-py3.10.egg-info" TYPE DIRECTORY FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_python/zfc_operator/zfc_operator.egg-info/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/local/lib/python3.10/dist-packages/zfc_operator" TYPE DIRECTORY FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/packages/zfc_operator/zfc_operator/" REGEX "/[^/]*\\.pyc$" EXCLUDE REGEX "/\\_\\_pycache\\_\\_$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(
        COMMAND
        "/usr/bin/python3" "-m" "compileall"
        "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/install-host/zfc_operator/local/lib/python3.10/dist-packages/zfc_operator"
      )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/zfc_operator" TYPE PROGRAM FILES
    "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/packages/zfc_operator/scripts/plot_relay"
    "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/packages/zfc_operator/scripts/operator_panel"
    "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/packages/zfc_operator/scripts/network_probe"
    "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/packages/zfc_operator/scripts/cyclone_profile"
    "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/packages/zfc_operator/scripts/fastdds_profile"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zfc_operator" TYPE DIRECTORY FILES
    "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/packages/zfc_operator/launch"
    "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/packages/zfc_operator/plot"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/zfc_operator")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/zfc_operator")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zfc_operator/environment" TYPE FILE FILES "/opt/ros/humble/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zfc_operator/environment" TYPE FILE FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zfc_operator/environment" TYPE FILE FILES "/opt/ros/humble/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zfc_operator/environment" TYPE FILE FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_environment_hooks/path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zfc_operator" TYPE FILE FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_environment_hooks/local_setup.bash")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zfc_operator" TYPE FILE FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_environment_hooks/local_setup.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zfc_operator" TYPE FILE FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zfc_operator" TYPE FILE FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zfc_operator" TYPE FILE FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_environment_hooks/package.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_index/share/ament_index/resource_index/packages/zfc_operator")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zfc_operator/cmake" TYPE FILE FILES
    "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_core/zfc_operatorConfig.cmake"
    "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/ament_cmake_core/zfc_operatorConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zfc_operator" TYPE FILE FILES "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/packages/zfc_operator/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/ezraklukas/Documents/arbeit/ubckin/notes/ezra/resources/ros2_framework/zfc_impl/build-host/zfc_operator/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
