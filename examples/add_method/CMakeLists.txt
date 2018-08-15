cmake_minimum_required(VERSION 2.8)

set(project add_method)

project(${project} CXX)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)

add_executable(${project} ${SOURCE_FILES})

target_link_libraries(${project} actor-zeta)