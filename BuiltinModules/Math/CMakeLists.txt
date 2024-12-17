cmake_minimum_required(VERSION 3.30.0)

include_directories(${CMAKE_SOURCE_DIR}/src)

# Math module
add_library(Math SHARED Math.cpp)
target_link_libraries(Math Interpreter)

set_target_properties(Math PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/libraries"
    PREFIX ""
)
