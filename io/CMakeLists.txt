cmake_minimum_required(VERSION 2.8)

set(project actor-zeta-io)

if (CMAKE_VERSION VERSION_LESS 3.0)
    PROJECT(${project} CXX)
else()
    cmake_policy(SET CMP0048 NEW)
    PROJECT(${project} VERSION "${CMAKE_PROJECT_VERSION}" LANGUAGES CXX)
endif()

include_directories(.)

set(HEADER_FILES
        actor-zeta/actor/broker.hpp

        actor-zeta/environment/network_environment.hpp

        actor-zeta/network/multiplexer.hpp
        actor-zeta/network/connection_identifying.hpp
        actor-zeta/network/fake_multiplexer.hpp
        actor-zeta/forwards.hpp
)

set(SOURCE_FILES
        source/network/connection_identifying.cpp
        source/network/fake_multiplexer.cpp
        source/broker.cpp
)

add_library(
        ${PROJECT_NAME} ${BUILD_TYPE}
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

target_link_libraries(
        ${PROJECT_NAME}
        PUBLIC
        actor-zeta-core
)

set_target_properties( ${PROJECT_NAME} PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/io)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/header
)