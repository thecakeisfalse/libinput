cmake_minimum_required(VERSION 3.0.0)
project(libinput VERSION 1.0.0)

include_directories(include)

file(GLOB SRCS src/*.c)
add_library(libinput STATIC ${SRCS})

set_property(TARGET libinput PROPERTY C_STANDART 99)
set_property(TARGET libinput PROPERTY POSITION_INDEPENDENT_CODE ON)

set_target_properties(libinput PROPERTIES OUTPUT_NAME input)

install(TARGETS libinput)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})