
if(UNIX AND NOT CYGWIN)

    set(BUILD_OV_LIBRARY_wagoFBKlib OFF CACHE BOOL "")

    add_ov_library(wagoFBKlib)
    ov_library_includes(wagoFBKlib fb kbuslib)

    target_compile_options(wagoFBKlib PRIVATE -fomit-frame-pointer -pipe -msoft-float -fno-builtin -DEMBED -fno-strict-aliasing)
endif()
