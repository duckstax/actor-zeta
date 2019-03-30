cmake_minimum_required(VERSION 2.8)

project(spinlock CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}_test_1 spinlick_test_1.cpp)

target_link_libraries(${PROJECT_NAME}_test_1 actor-zeta-core)

add_executable(${PROJECT_NAME}_test_2 spinlick_test_2.cpp)

target_link_libraries(${PROJECT_NAME}_test_2 actor-zeta-core)