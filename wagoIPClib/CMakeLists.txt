
if(UNIX AND (NOT CYGWIN) AND OV_ARCH_i386)

    set(BUILD_OV_LIBRARY_wagoIPClib OFF CACHE BOOL "")

    add_ov_library(wagoIPClib)
    ov_library_includes(wagoIPClib fb kbuslib)

    target_link_libraries(wagoIPClib
        -lpthread
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libkbus.so.0.0.0
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libmisc.so.0.0.0
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libuio.so.0.0.0)
endif()
