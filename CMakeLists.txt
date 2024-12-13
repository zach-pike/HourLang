cmake_minimum_required(VERSION 3.30.0)

project(MyLanguage)

include_directories(src/)
include_directories(include/)

file(GLOB_RECURSE INTERP_SRC src/*.cpp)
list(FILTER INTERP_SRC EXCLUDE REGEX "${CMAKE_SOURCE_DIR}/src/Utility/.*")

file(GLOB_RECURSE UTILITY_SRC src/Utility/*.cpp)
add_library(Utility STATIC ${UTILITY_SRC})

add_library(Math SHARED BuiltinModules/Math/Math.cpp)
target_link_libraries(Math Utility)

set_target_properties(Math PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/libraries"
    PREFIX ""
)

add_library(Raylib SHARED BuiltinModules/Raylib/Raylib.cpp)
target_link_directories(Raylib PUBLIC BuiltinModules/Raylib)
target_link_libraries(Raylib Utility raylib winmm)


set_target_properties(Raylib PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/libraries"
    PREFIX ""
)

add_executable(Interpreter ${INTERP_SRC})
target_link_libraries(Interpreter Utility)
