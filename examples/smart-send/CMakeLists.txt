cmake_minimum_required(VERSION 3.0)

project(smart-send)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} actor-zeta)
