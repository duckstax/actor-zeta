PROJECT(tests_rtt CXX)

file(GLOB ${PROJECT_NAME}_HEADERS
    ./*.hpp
    ./*.h
)

file(GLOB ${PROJECT_NAME}_SOURCES
    ./*.cpp
)

message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")



add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})

target_link_libraries(${PROJECT_NAME}
    PUBLIC actor-zeta
    PUBLIC CONAN_PKG::catch2
)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}../utils")

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})
