cmake_minimum_required(VERSION 3.30.0)

project(MyLanguage)

add_subdirectory(BuiltinModules/)

include_directories(src/)
include_directories(include/)

file(GLOB_RECURSE INTERPRETER_SRC src/*/*.cpp)
add_library(Interpreter STATIC ${INTERPRETER_SRC})

# Frontend
add_executable(Hour src/Main.cpp)
target_link_libraries(Hour Interpreter)
