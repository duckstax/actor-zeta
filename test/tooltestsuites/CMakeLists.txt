PROJECT(tooltestsuites LANGUAGES CXX)

set(SOURCE_FILES scheduler_test.cpp clock_test.cpp)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${project} actor-zeta)
