cmake_minimum_required(VERSION 2.8)

set(project flat_map)

project(${project} CXX)

add_executable(${project} main.cpp)

target_link_libraries(${project} actor-zeta-core)