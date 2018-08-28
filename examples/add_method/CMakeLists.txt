cmake_minimum_required(VERSION 2.8)
project(add_method CXX)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} actor-zeta)
