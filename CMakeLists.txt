cmake_minimum_required(VERSION 2.8.12)

set(PROJECT actor-zeta)

project(${PROJECT} CXX)

include_directories(BEFORE
        ${PROJECT_SOURCE_DIR}/core/header
)

add_compile_options(
        -std=c++11
        -v
        -fno-rtti
        -fno-exceptions
)

IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread ")
    SET(OperatingSystem "Linux")
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

add_subdirectory(core)
add_library(${PROJECT} $<TARGET_OBJECTS:actor-zeta-core>)


