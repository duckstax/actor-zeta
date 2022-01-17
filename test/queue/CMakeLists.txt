cmake_minimum_required(VERSION 3.0)

PROJECT(queue CXX)

set(SOURCE_FILES
    main.cpp
    cached_queue.cpp
    fifo_inbox.cpp
    fixed_queue.cpp
    lifo_inbox.cpp
    queue.cpp
    task_queue.cpp
)

message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} actor-zeta CONAN_PKG::catch2)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})
