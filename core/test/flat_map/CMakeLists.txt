cmake_minimum_required(VERSION 2.8)

set(project flat_map)

project(${project} CXX)

set(SOURCE_FILES main.cpp)

add_executable(${project} ${SOURCE_FILES})
target_link_libraries(${project} actor-zeta-core)