cmake_minimum_required(VERSION 2.8)

set(PROJECT actor-zeta-io)

project(${PROJECT} CXX)

include_directories(.)

list(APPEND HEADER_FILES
        actor-zeta/actor/broker.hpp

        actor-zeta/environment/network_environment.hpp

        actor-zeta/network/multiplexer.hpp
        actor-zeta/network/connection_identifying.hpp
        actor-zeta/network/fake_multiplexer.hpp
        actor-zeta/forwards.hpp
)

list(APPEND SOURCE_FILES
        source/network/connection_identifying.cpp
        source/network/fake_multiplexer.cpp
        source/broker.cpp
)

add_library(
        ${PROJECT}
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

target_link_libraries(
        ${PROJECT}
        PUBLIC
        actor-zeta-core
)

set_target_properties( ${PROJECT} PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/io)

target_include_directories(
        ${PROJECT}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/header
)