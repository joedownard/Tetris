cmake_minimum_required(VERSION 3.17)
project(Tetris)

set(CMAKE_CXX_STANDARD 14)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_library(glad "include/glad/glad.h" "glad/glad.c")

include_directories(include)

add_subdirectory(glfw-3.3.2)

add_executable(Tetris main.cpp Shader.h)

target_link_libraries(Tetris glfw glad)