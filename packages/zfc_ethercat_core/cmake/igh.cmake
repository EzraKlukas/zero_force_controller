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

