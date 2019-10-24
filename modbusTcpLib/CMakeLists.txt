
add_ov_library(modbusTcpLib FALSE)
ov_library_includes(modbusTcpLib ov fb ksbase TCPbind)

target_compile_definitions(modbusTcpLib PRIVATE -DPLT_USE_WINSOCK2=1)

if (CYGWIN)
    target_compile_definitions(modbusTcpLib PRIVATE -D_GNU_SOURCE=1)
endif()