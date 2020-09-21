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

    # Use the highest warning level for Visual Studio.
    set(CMAKE_CXX_WARNING_LEVEL 4)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")

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

    # Use -Wall for clang and gcc.
    if(NOT CMAKE_CXX_FLAGS MATCHES "-Wall")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    endif(NOT CMAKE_CXX_FLAGS MATCHES "-Wall")

    # Use -Wextra for clang and gcc.
    if(NOT CMAKE_CXX_FLAGS MATCHES "-Wextra")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
    endif(NOT CMAKE_CXX_FLAGS MATCHES "-Wextra")

    # Use -Werror for clang and gcc.
    if(NOT CMAKE_CXX_FLAGS MATCHES "-Werror")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
    endif(NOT CMAKE_CXX_FLAGS MATCHES "-Werror")

    if (EXCEPTIONS_DISABLE)
        message("Disable C++ exceptions.")
        string(REGEX REPLACE "-fexceptions" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
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
        header/actor-zeta/base/abstract_actor.hpp
        header/actor-zeta/base/actor.hpp
        header/actor-zeta/base/actor_address.hpp
        header/actor-zeta/base/cooperative_actor.hpp
        header/actor-zeta/base/basic_actor.hpp
        header/actor-zeta/base/blocking_actor.hpp
        header/actor-zeta/base/communication_module.hpp
        header/actor-zeta/base/context.hpp
        header/actor-zeta/base/dispatcher.hpp
        header/actor-zeta/base/handler.hpp
        header/actor-zeta/base/metadata.hpp
        header/actor-zeta/base/abstract_supervisor.hpp

        header/actor-zeta/detail/any.hpp
        header/actor-zeta/detail/callable_trait.hpp
        header/actor-zeta/detail/intrusive_ptr.hpp
        header/actor-zeta/detail/ref_counted.hpp
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

        header/actor-zeta/messaging/blocking_mail_queue.hpp
        header/actor-zeta/messaging/mail_box.hpp
        header/actor-zeta/messaging/message.hpp
        header/actor-zeta/messaging/message_header.hpp

        header/actor-zeta/forwards.hpp
)

set(SOURCE_FILES

        source/actor/abstract_actor.cpp
        source/actor/actor.cpp
        source/actor/actor_address.cpp
        source/actor/cooperative_actor.cpp
        source/actor/blocking_actor.cpp
        source/actor/dispatcher.cpp
        source/actor/abstract_supervisor.cpp
        source/actor/communication_module.cpp

        source/detail/string_view.cpp
        source/detail/ref_counted.cpp

        source/executor/abstract_executor.cpp
        source/executor/executable.cpp
        source/executor/execution_device.cpp

        source/messaging/message.cpp
        source/messaging/message_header.cpp
        source/messaging/blocking_mail_queue.cpp
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