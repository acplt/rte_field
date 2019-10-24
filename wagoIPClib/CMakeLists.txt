
if(UNIX AND !CYGWIN AND OV_ARCH_i386)
    add_ov_library(wagoIPClib FALSE)
    ov_library_includes(wagoIPClib fb kbuslib)

    target_link_libraries(wagoIPClib
        -lpthread
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libkbus.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libmisc.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libuio.a)
endif()