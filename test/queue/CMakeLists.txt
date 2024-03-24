PROJECT(tests_lifo_inbox CXX)

message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")

add_executable(${PROJECT_NAME} lifo_inbox.cpp)

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