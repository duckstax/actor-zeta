cmake_minimum_required(VERSION 2.8)

include_directories(.)

set(PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")

set(HEADERS "${HEADERS}"
        ${PREFIX}/actor-zeta/actor/broker.hpp

        ${PREFIX}/actor-zeta/environment/network_environment.hpp

        ${PREFIX}/actor-zeta/network/multiplexer.hpp
        ${PREFIX}/actor-zeta/network/connection_identifying.hpp
        ${PREFIX}/actor-zeta/network/fake_multiplexer.hpp
        ${PREFIX}/actor-zeta/forwards.hpp

        PARENT_SCOPE
)

set(SOURCES "${SOURCES}"
        ${PREFIX}/source/network/connection_identifying.cpp
        ${PREFIX}/source/network/fake_multiplexer.cpp
        ${PREFIX}/source/broker.cpp

        PARENT_SCOPE
)

set(IMPORT_LOCATIONS "${IMPORT_LOCATIONS}" ${CMAKE_CURRENT_SOURCE_DIR}/io PARENT_SCOPE)
