cmake_minimum_required(VERSION 3.0)

PROJECT(communication CXX)

set(SOURCE_FILES main.cpp)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS_} -O0 -g -fno-omit-frame-pointer -fsanitize=thread")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} actor-zeta)