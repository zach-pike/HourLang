cmake_minimum_required(VERSION 3.30.0)

include_directories(${CMAKE_SOURCE_DIR}/src)

# Raylib module
add_library(Raylib SHARED Raylib.cpp WrappedRaylib.cpp)
target_link_directories(Raylib PUBLIC .)
target_link_libraries(Raylib Interpreter raylib winmm)

set_target_properties(Raylib PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/libraries"
    PREFIX ""
)