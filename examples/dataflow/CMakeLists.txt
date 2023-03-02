project(dataflow)

set( CMAKE_VERBOSE_MAKEFILE on )

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    actor-zeta)
