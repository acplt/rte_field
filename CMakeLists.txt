cmake_minimum_required(VERSION 3.12)

project(rte_field)

# Include ov core (if it isn't already included)
find_package(RTE)

# Include ov helper functions and definitions
get_target_property(RTE_CMAKE_DIR ov RTE_CMAKE_DIR)
include(${RTE_CMAKE_DIR}/ov_functions.cmake)
include(${RTE_CMAKE_DIR}/ov_definitions.cmake)


# The field libraries
add_subdirectory(IOdriverlib)
add_subdirectory(kbuslib)
add_subdirectory(wagoFBKlib)
add_subdirectory(wagoIPClib)
add_subdirectory(modbusTcpLib)
add_subdirectory(raspi)


# Export all targets to make build tree importable via find_package(RTEMisc)
 export(EXPORT ${PROJECT_NAME}
     FILE RTEFieldConfig.cmake)
