cmake_minimum_required(VERSION 3.0)

PROJECT(tooltestsuites LANGUAGES CXX)

set(SOURCE_FILES scheduler_test.cpp)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${project} actor-zeta)
