cmake_minimum_required(VERSION 2.8.12)

set(PROJECT actor-zeta-libactor_zeta_io)

project(${PROJECT} CXX)

include_directories(.)

set(HEADER_FILES
        actor-zeta/standard_handlers/reg_write.hpp
        actor-zeta/standard_handlers/write.hpp
        actor-zeta/broker.hpp
        actor-zeta/connection_handler.hpp
        actor-zeta/forwards.hpp
        actor-zeta/multiplexer.hpp
)

set(SOURCE_FILES
        source/broker.cpp
)

add_library(${PROJECT} OBJECT ${SOURCE_FILES} ${HEADER_FILES} )