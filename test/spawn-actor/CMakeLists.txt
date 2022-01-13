cmake_minimum_required(VERSION 3.0)


cmake_policy(SET CMP0048 NEW)
PROJECT(spawn-actor VERSION "${CMAKE_PROJECT_VERSION}" LANGUAGES CXX)
message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")

set(SOURCE_FILES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} actor-zeta tooltestsuites CONAN_PKG::catch2)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})