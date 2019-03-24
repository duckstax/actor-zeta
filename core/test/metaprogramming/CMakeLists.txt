cmake_minimum_required(VERSION 2.8)

set(project metaprogramming)

if (CMAKE_VERSION VERSION_LESS 3.0)
    PROJECT(${project} CXX)
else()
    cmake_policy(SET CMP0048 NEW)
    PROJECT(${project} VERSION "${CMAKE_PROJECT_VERSION}" LANGUAGES CXX)
endif()

set(SOURCE_FILES main.cpp)

add_executable(${project} ${SOURCE_FILES})
target_link_libraries(${project} actor-zeta-core)