cmake_minimum_required(VERSION 2.8)

set(PROJECT actor-zeta-libactor_zeta_io)

project(${PROJECT} CXX)

include_directories(.)

list(APPEND HEADER_FILES
        actor-zeta/actor/broker.hpp

        actor-zeta/network/multiplexer.hpp
        actor-zeta/network/connection_identifying.hpp
        actor-zeta/forwards.hpp
)

list(APPEND SOURCE_FILES
        source/network/connection_identifying.cpp
        source/broker.cpp
)

add_library(${PROJECT} OBJECT ${SOURCE_FILES} ${HEADER_FILES} )