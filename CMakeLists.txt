cmake_minimum_required(VERSION 2.8)

set(project actor-zeta)

set (CMAKE_PROJECT_VERSION_MAJOR 1)
set (CMAKE_PROJECT_VERSION_MINOR 0)
set (CMAKE_PROJECT_VERSION_PATCH 0)
set (CMAKE_PROJECT_VERSION "${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}.${CMAKE_PROJECT_VERSION_PATCH}")

if (CMAKE_VERSION VERSION_LESS 3.0)
    PROJECT(${project} CXX)
else()
    cmake_policy(SET CMP0048 NEW)
    PROJECT(${project} VERSION "${CMAKE_PROJECT_VERSION}" LANGUAGES CXX)
endif()

set(CMAKE_CXX_STANDARD 11 CACHE STRING "The C++ standard whose features are requested." )
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message (STATUS "STANDARD CPP = ${CMAKE_CXX_STANDARD}")

message (STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

option(CMake_RUN_CLANG_TIDY "Run clang-tidy with the compiler." OFF)

option(ALLOW_EXAMPLES "Enable building examples" OFF)

option(ALLOW_TESTS "Enable building test" OFF)

option(DEV_MODE "developer mode" OFF)

option(RTTI_DISABLE "RTTI DISABLE" ON)

option(EXCEPTIONS_DISABLE "EXCEPTIONS DISABLE" ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

    if (EXCEPTIONS_DISABLE)
        message("Disable C++ exceptions.")
        string(REGEX REPLACE "/EH[a-z]+" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
    endif()

    if (RTTI_DISABLE)
        message("Disable RTTI.")
        string(REGEX REPLACE "/GR" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR-")
    endif()

else(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

    if (EXCEPTIONS_DISABLE)
        message("Disable C++ exceptions.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
    endif()

    if (RTTI_DISABLE)
        message("Disable RTTI.")
        string(REGEX REPLACE "-frtti" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
    endif()

endif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

if (DEV_MODE)
    set(ALLOW_TESTS ON CACHE BOOL "" FORCE)
    set(ALLOW_EXAMPLES ON CACHE BOOL "" FORCE)
    include(cmake/clang_tools.cmake)
endif ()

if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(
            -Wall
            -Wextra
            -Wpedantic

            -Wcast-align
            -Wcast-qual
            -Wconversion
            -Wctor-dtor-privacy
            -Wenum-compare
            -Wfloat-equal
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Woverloaded-virtual
            -Wredundant-decls
            -Wsign-conversion
            -Wsign-promo
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX)
endif()


find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

set(HEADER_FILES
        header/actor-zeta/abstract_actor.hpp
        header/actor-zeta/abstract_supervisor.hpp
        header/actor-zeta/actor.hpp
        header/actor-zeta/address_t.hpp
        header/actor-zeta/basic_actor.hpp
        header/actor-zeta/communication_module.hpp
        header/actor-zeta/cooperative_actor.hpp
        header/actor-zeta/dispatcher.hpp
        header/actor-zeta/handler.hpp

        header/actor-zeta/detail/any.hpp
        header/actor-zeta/detail/callable_trait.hpp
        header/actor-zeta/detail/string_view.hpp
        header/actor-zeta/detail/type_list.hpp
        header/actor-zeta/detail/type_traits.hpp

        header/actor-zeta/executor/policy/profiled.hpp
        header/actor-zeta/executor/policy/unprofiled.hpp
        header/actor-zeta/executor/policy/work_sharing.hpp
        header/actor-zeta/executor/abstract_executor.hpp
        header/actor-zeta/executor/executor.hpp
        header/actor-zeta/executor/executable.hpp
        header/actor-zeta/executor/profiled_executor.hpp
        header/actor-zeta/executor/execution_device.hpp
        header/actor-zeta/executor/worker.hpp

        header/actor-zeta/blocking_mail_queue.hpp
        header/actor-zeta/message.hpp

        header/actor-zeta/forwards.hpp
        header/actor-zeta.hpp
)

set(SOURCE_FILES

        source/abstract_actor.cpp
        source/abstract_supervisor.cpp
        source/actor.cpp
        source/address_t.cpp
        source/communication_module.cpp
        source/cooperative_actor.cpp
        source/dispatcher.cpp

        source/detail/string_view.cpp

        source/executor/abstract_executor.cpp
        source/executor/executable.cpp
        source/executor/execution_device.cpp

        source/message.cpp
        source/blocking_mail_queue.cpp
)

include_directories(SYSTEM header)

find_package( Threads )

add_library(
        ${PROJECT_NAME}
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

target_link_libraries (
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_THREAD_LIBS_INIT}
)


target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/header/actor-zeta
)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/header
)

if (ALLOW_TESTS)
    add_subdirectory(test)
endif ()


if(ALLOW_EXAMPLES)
    add_subdirectory(examples)
endif()