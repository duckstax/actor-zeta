cmake_minimum_required(VERSION 2.8)

project(intrusive_list CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} actor-zeta-core)