cmake_minimum_required(VERSION 3.0)

PROJECT(polymorphic_allocator CXX)

set(CMAKE_CXX_STANDARD 14 )

set(SOURCE_FILES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} actor-zeta)