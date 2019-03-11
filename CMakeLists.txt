cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

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

option(CMake_RUN_CLANG_TIDY "Run clang-tidy with the compiler." OFF)

option(IO "Enable building actor-zeta-io" ON)

option(EXAMPLES "Enable building examples" OFF)

message (STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

option(SHARED "" OFF)

option(RTTI "" OFF)

option(ALLOW_TESTS "" OFF)

option(DEV_MODE "" OFF)

if (SHARED)
    set(BUILD_TYPE SHARED)
else()
    set(BUILD_TYPE STATIC)
endif ()


if(NOT WIN32)
    add_compile_options(
            -v
            -fno-rtti
            -fno-exceptions
    )
endif()


find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)


if(CMAKE_GENERATOR STREQUAL Xcode)
    if(CMake_RUN_CLANG_TIDY)
        if(CMake_SOURCE_DIR STREQUAL CMake_BINARY_DIR)
            message(FATAL_ERROR "CMake_RUN_CLANG_TIDY requires an out-of-source build!")
        endif()
        find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)
        if(NOT CLANG_TIDY_COMMAND)
            message(FATAL_ERROR "CMake_RUN_CLANG_TIDY is ON but clang-tidy is not found!")
        endif()
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

        # Create a preprocessor definition that depends on .clang-tidy content so
        # the compile command will change when .clang-tidy changes.  This ensures
        # that a subsequent build re-runs clang-tidy on all sources even if they
        # do not otherwise need to be recompiled.  Nothing actually uses this
        # definition.  We add it to targets on which we run clang-tidy just to
        # get the build dependency on the .clang-tidy file.
        file(SHA1 ${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy clang_tidy_sha1)
        set(CLANG_TIDY_DEFINITIONS "CLANG_TIDY_SHA1=${clang_tidy_sha1}")
        unset(clang_tidy_sha1)

    endif()
    configure_file(.clang-tidy .clang-tidy COPYONLY)
endif()


include_directories(core)


if(IO)
    include_directories(io)
endif()


add_subdirectory(core)

if(IO)
    add_subdirectory(io)
endif()

if(EXAMPLES)
    add_subdirectory(examples)
endif()

add_custom_target(${PROJECT_NAME} ALL COMMAND ${CMAKE_CXX_ARCHIVE_CREATE} lib${PROJECT_NAME}.a $<TARGET_FILE:actor-zeta-core> $<TARGET_FILE:actor-zeta-io>)