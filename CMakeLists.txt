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

# This project requires C++11.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message (STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

option(CMake_RUN_CLANG_TIDY "Run clang-tidy with the compiler." OFF)

option(ENV "Enable building actor-zeta-environment" ON)

option(ALLOW_EXAMPLES "Enable building examples" OFF)

option(ALLOW_TESTS "Enable building test" OFF)

option(SHARED "" OFF)

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

if (SHARED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    set(BUILD_TYPE SHARED)
else()
    set(BUILD_TYPE STATIC)
endif ()


if(NOT WIN32)
    add_compile_options(-v)
endif()


find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)



include_directories(core)
add_subdirectory(core)
list(APPEND OBJECT_LISTS "$<TARGET_OBJECTS:actor-zeta-core>")


find_package( Threads )

add_library(${PROJECT_NAME} ${BUILD_TYPE} ${OBJECT_LISTS})

target_link_libraries (
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_THREAD_LIBS_INIT}
)


target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/core/actor-zeta
        ${CMAKE_CURRENT_SOURCE_DIR}/environment/actor-zeta
)

if(ALLOW_EXAMPLES)
    add_subdirectory(examples)
endif()