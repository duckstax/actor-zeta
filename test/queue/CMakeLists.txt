##### cached_queue ################################################################################
PROJECT(tests_cached_queue CXX)

file(GLOB ${PROJECT_NAME}_HEADERS
    ./*.hpp
    ./*.h
)

file(GLOB ${PROJECT_NAME}_SOURCES
    ./cached_queue.cpp
)

message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})

if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang"  AND UNIX AND NOT APPLE ) #------------------------------------- Clang
    target_link_libraries(${PROJECT_NAME}
        PUBLIC ${REQ_LLVM_LIBRARIES}
    )
endif() #--------------------------------------------------------------------------- Clang

target_link_libraries(${PROJECT_NAME}
    PUBLIC actor-zeta
    PUBLIC CONAN_PKG::catch2
)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})

##### fifo_inbox ##################################################################################
PROJECT(tests_fifo_inbox CXX)

file(GLOB ${PROJECT_NAME}_HEADERS
    ./*.hpp
    ./*.h
)

file(GLOB ${PROJECT_NAME}_SOURCES
    ./fifo_inbox.cpp
)

message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})

if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang"  AND UNIX AND NOT APPLE ) #------------------------------------- Clang
    target_link_libraries(${PROJECT_NAME}
        PUBLIC ${REQ_LLVM_LIBRARIES}
    )
endif() #--------------------------------------------------------------------------- Clang

target_link_libraries(${PROJECT_NAME}
    PUBLIC actor-zeta
    PUBLIC CONAN_PKG::catch2
)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})

##### fixed_queue #################################################################################
PROJECT(tests_fixed_queue CXX)

file(GLOB ${PROJECT_NAME}_HEADERS
    ./*.hpp
    ./*.h
)

file(GLOB ${PROJECT_NAME}_SOURCES
    ./fixed_queue.cpp
)

message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})

if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang"  AND UNIX AND NOT APPLE ) #------------------------------------- Clang
    target_link_libraries(${PROJECT_NAME}
        PUBLIC ${REQ_LLVM_LIBRARIES}
    )
endif() #--------------------------------------------------------------------------- Clang

target_link_libraries(${PROJECT_NAME}
    PUBLIC actor-zeta
    PUBLIC CONAN_PKG::catch2
)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})

##### lifo_inbox ##################################################################################
PROJECT(tests_lifo_inbox CXX)

file(GLOB ${PROJECT_NAME}_HEADERS
    ./*.hpp
    ./*.h
)

file(GLOB ${PROJECT_NAME}_SOURCES
    ./lifo_inbox.cpp
)

message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})

if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang"  AND UNIX AND NOT APPLE ) #------------------------------------- Clang
    target_link_libraries(${PROJECT_NAME}
        PUBLIC ${REQ_LLVM_LIBRARIES}
    )
endif() #--------------------------------------------------------------------------- Clang

target_link_libraries(${PROJECT_NAME}
    PUBLIC actor-zeta
    PUBLIC CONAN_PKG::catch2
)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})

##### queue #######################################################################################
PROJECT(tests_queue CXX)

file(GLOB ${PROJECT_NAME}_HEADERS
    ./*.hpp
    ./*.h
)

file(GLOB ${PROJECT_NAME}_SOURCES
    ./queue.cpp
)

message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})

if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang"  AND UNIX AND NOT APPLE ) #------------------------------------- Clang
    target_link_libraries(${PROJECT_NAME}
        PUBLIC ${REQ_LLVM_LIBRARIES}
    )
endif() #--------------------------------------------------------------------------- Clang

target_link_libraries(${PROJECT_NAME}
    PUBLIC actor-zeta
    PUBLIC CONAN_PKG::catch2
)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})

##### task_queue ##################################################################################
PROJECT(tests_task_queue CXX)

file(GLOB ${PROJECT_NAME}_HEADERS
    ./*.hpp
    ./*.h
)

file(GLOB ${PROJECT_NAME}_SOURCES
    ./task_queue.cpp
)

message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})

if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang"  AND UNIX AND NOT APPLE ) #------------------------------------- Clang
    target_link_libraries(${PROJECT_NAME}
        PUBLIC ${REQ_LLVM_LIBRARIES}
    )
endif() #--------------------------------------------------------------------------- Clang

target_link_libraries(${PROJECT_NAME}
    PUBLIC actor-zeta
    PUBLIC CONAN_PKG::catch2
)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})
