cmake_minimum_required(VERSION 3.0)

set(proj_name maze_exec)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE MAZE_EXEC_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "include/*.hpp")
file(GLOB_RECURSE MAZE_EXEC_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "lib/*.cpp")

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/data
    ${CMAKE_CURRENT_BINARY_DIR}/data
    COMMENT "Copying shaders to binary directory"
)

add_executable(${proj_name} ${MAZE_EXEC_HDRS} ${MAZE_EXEC_SRCS})
target_include_directories(${proj_name} PRIVATE "./include" "../maze_lib/include")
target_link_libraries(${proj_name} PRIVATE maze_lib)
set_target_properties(${proj_name} PROPERTIES LINKER_LANGUAGE CXX)
add_dependencies(${proj_name} copy_resources)
