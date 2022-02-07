cmake_minimum_required(VERSION 3.0)

set(project benchmark_message)

if (CMAKE_VERSION VERSION_LESS 3.0)
    PROJECT(${project} CXX)
else ()
    cmake_policy(SET CMP0048 NEW)
    PROJECT(${project} VERSION "${CMAKE_PROJECT_VERSION}" LANGUAGES CXX)
endif ()

set(SOURCE_FILES main.cpp)
set(HEADER_FILES
    fixtures.hpp
    register_benchmark.hpp)

message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} actor-zeta CONAN_PKG::benchmark)
