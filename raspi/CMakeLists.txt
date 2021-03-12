
if(UNIX)
    # If libwiringPi cannot be found, disable default build of the raspi library unless explicitly enabled by user
    find_library(LIB_WIRING_PI wiringPi)
    if(NOT LIB_WIRING_PI)
        SET(BUILD_OV_LIBRARY_raspi OFF CACHE BOOL "")
    endif()

    add_ov_library(raspi)
    ov_library_includes(raspi ov fb)

    target_link_libraries(raspi PRIVATE -lwiringPi)
endif()