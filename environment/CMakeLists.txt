cmake_minimum_required(VERSION 2.8)

set(project actor-zeta-environment)

if (CMAKE_VERSION VERSION_LESS 3.0)
    PROJECT(${project} CXX)
else()
    cmake_policy(SET CMP0048 NEW)
    PROJECT(${project} VERSION "${CMAKE_PROJECT_VERSION}" LANGUAGES CXX)
endif()

include_directories(SYSTEM .)

set(HEADER_FILES

        actor-zeta/detail/adjacency_list.hpp
        actor-zeta/detail/storage_space.hpp

        actor-zeta/environment.hpp
        actor-zeta/network_environment.hpp
        actor-zeta/supervisor_heavy.hpp

)

set(SOURCE_FILES

        source/abstract_environment.cpp
        source/environment.cpp
        source/supervisor_heavy.cpp
        source/storage_space.cpp
        source/network_environment.cpp)

add_library(
        ${PROJECT_NAME} OBJECT
        ${SOURCE_FILES}
        ${HEADER_FILES}
)


target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/header
)
