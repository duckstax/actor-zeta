cmake_minimum_required(VERSION 3.0)
#
###### cached_queue ################################################################################
#PROJECT(cached_queue CXX)
#
#set(${PROJECT_NAME}_SOURCE_FILES
#    cached_queue.cpp
#)
#
#message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")
#
#add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_FILES})
#
#target_link_libraries(${PROJECT_NAME} actor-zeta CONAN_PKG::catch2)
#
#include(CTest)
#include(Catch)
#catch_discover_tests(${PROJECT_NAME})
#
###### fifo_inbox ##################################################################################
#PROJECT(fifo_inbox CXX)
#
#set(${PROJECT_NAME}_SOURCE_FILES
#    fifo_inbox.cpp
#)
#
#message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")
#
#add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_FILES})
#
#target_link_libraries(${PROJECT_NAME} actor-zeta CONAN_PKG::catch2)
#
#include(CTest)
#include(Catch)
#catch_discover_tests(${PROJECT_NAME})
#
###### fixed_queue #################################################################################
#PROJECT(fixed_queue CXX)
#
#set(${PROJECT_NAME}_SOURCE_FILES
#    fixed_queue.cpp
#)
#
#message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")
#
#add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_FILES})
#
#target_link_libraries(${PROJECT_NAME} actor-zeta CONAN_PKG::catch2)
#
#include(CTest)
#include(Catch)
#catch_discover_tests(${PROJECT_NAME})
#
###### lifo_inbox ##################################################################################
#PROJECT(lifo_inbox CXX)
#
#set(${PROJECT_NAME}_SOURCE_FILES
#    lifo_inbox.cpp
#)
#
#message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")
#
#add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_FILES})
#
#target_link_libraries(${PROJECT_NAME} actor-zeta CONAN_PKG::catch2)
#
#include(CTest)
#include(Catch)
#catch_discover_tests(${PROJECT_NAME})

##### queue #######################################################################################
PROJECT(queue CXX)

set(${PROJECT_NAME}_SOURCE_FILES
    queue.cpp
)

message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} actor-zeta CONAN_PKG::catch2)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})

##### task_queue ##################################################################################
PROJECT(task_queue CXX)

set(${PROJECT_NAME}_SOURCE_FILES
    task_queue.cpp
)

message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} actor-zeta CONAN_PKG::catch2)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})
