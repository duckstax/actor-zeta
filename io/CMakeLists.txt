cmake_minimum_required(VERSION 2.8)
project(actor-zeta-io CXX)

set(HEADERS
  include/actor-zeta-io/actor/broker.hpp
  include/actor-zeta-io/environment/network_environment.hpp
  include/actor-zeta-io/network/multiplexer.hpp
  include/actor-zeta-io/network/connection_identifying.hpp
  include/actor-zeta-io/network/fake_multiplexer.hpp
  include/actor-zeta-io/forwards.hpp)

set(SOURCES
  source/network/connection_identifying.cpp
  source/network/fake_multiplexer.cpp
  source/broker.cpp)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ./include)
set_target_properties(${PROJECT_NAME} PROPERTIES IMPORTED_LOCATION ./)
target_link_libraries(${PROJECT_NAME} actor-zeta)
