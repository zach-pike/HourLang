cmake_minimum_required(VERSION 3.30.0)

project(MyLanguage)

include_directories(src/)
include_directories(include/)

file(GLOB_RECURSE INTERP_SRC src/*.cpp)
add_executable(Interpreter ${INTERP_SRC})