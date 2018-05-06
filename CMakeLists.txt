cmake_minimum_required(VERSION 2.8)

set(PROJECT actor-zeta)

project(${PROJECT} CXX)

include_directories(
        libactor_zeta_core
        libactor_zeta_io
)

add_compile_options(
        -std=c++11
        -v
        -fno-rtti
        -fno-exceptions
)

IF(NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread ")
ENDIF()

add_subdirectory(libactor_zeta_core)
add_subdirectory(libactor_zeta_io)
add_library(${PROJECT} $<TARGET_OBJECTS:actor-zeta-libactor_zeta_core> $<TARGET_OBJECTS:actor-zeta-libactor_zeta_io>)

add_subdirectory(examples)

