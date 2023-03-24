cmake_minimum_required(VERSION 3.0)

set(proj_name maze_lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE MAZE_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "include/*.hpp")
file(GLOB_RECURSE MAZE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "lib/*.cpp")

add_library(${proj_name} STATIC ${MAZE_HDRS} ${MAZE_SRCS})
target_include_directories(${proj_name} PRIVATE "./include")
set_target_properties(${proj_name} PROPERTIES LINKER_LANGUAGE CXX)