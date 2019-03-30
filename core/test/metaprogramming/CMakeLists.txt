cmake_minimum_required(VERSION 2.8)

set(project metaprogramming)

project(${project} CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(${project}  main.cpp)

target_link_libraries(${project} actor-zeta-core)