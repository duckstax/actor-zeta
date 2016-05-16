cmake_minimum_required(VERSION 2.8.12)

set(PROJECT actor-zeta-libactor_zeta_io)

project(${PROJECT} CXX)

include_directories(.
        ../libactor_zeta_core/actor-zeta
)

set(HEADER_FILES
        actor-zeta/broker.hpp
        actor-zeta/connection.hpp
        actor-zeta/forwards.hpp
        actor-zeta/multiplexer.hpp
)

set(SOURCE_FILES
        source/broker.сpp
)

add_library(${PROJECT} OBJECT ${SOURCE_FILES} ${HEADER_FILES})