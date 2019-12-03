
if(UNIX AND NOT CYGWIN)

    add_ov_library(wagoFBKlib)
    ov_library_includes(wagoFBKlib fb kbuslib)

    target_compile_options(wagoFBKlib PRIVATE -fomit-frame-pointer -pipe -msoft-float -fno-builtin -DEMBED -fno-strict-aliasing)
endif()
