cmake_minimum_required(VERSION 3.16)

project(zero_force_controller LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(IGH_MASTER_ROOT "" CACHE PATH
    "Optional path to an IgH EtherCAT master source/build tree for host-only builds")

find_package(EtherCAT CONFIG QUIET)

if(NOT TARGET EtherLab::ethercat)
    set(_igh_include_hints
        /opt/etherlab/include
        /usr/local/include
        /usr/include
    )
    set(_igh_library_hints
        /opt/etherlab/lib
        /usr/local/lib
        /usr/lib
    )

    if(IGH_MASTER_ROOT)
        list(PREPEND _igh_include_hints "${IGH_MASTER_ROOT}/include")
        list(PREPEND _igh_library_hints "${IGH_MASTER_ROOT}/lib/.libs")
    endif()

    find_path(EtherCAT_INCLUDE_DIR
        NAMES ecrt.h
        PATHS ${_igh_include_hints}
    )

    find_library(EtherCAT_LIBRARY
        NAMES ethercat
        PATHS ${_igh_library_hints}
    )

    if(NOT EtherCAT_INCLUDE_DIR OR NOT EtherCAT_LIBRARY)
        message(FATAL_ERROR
            "Could not find the IgH EtherCAT userspace header/library. "
            "Install IgH under /opt/etherlab or /usr/local, or configure with "
            "-DIGH_MASTER_ROOT=/path/to/igh-master for host-only compilation.")
    endif()

    add_library(EtherLab::ethercat UNKNOWN IMPORTED)
    set_target_properties(EtherLab::ethercat PROPERTIES
        IMPORTED_LOCATION "${EtherCAT_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${EtherCAT_INCLUDE_DIR}"
    )
endif()

add_executable(zero_force_controller
    src/main.cpp
    src/cia402.cpp
    src/clearpath_pdo.cpp
    src/drive_logic.cpp
    src/elm3604_pdo.cpp
)

target_include_directories(zero_force_controller PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(zero_force_controller PRIVATE EtherLab::ethercat)

target_compile_options(zero_force_controller PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
