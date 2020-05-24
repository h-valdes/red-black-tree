# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c17 -fsanitize=address -fsanitize=leak -lm -g -ggdb --gdb-index")

set(CMAKE_BUILD_TYPE Debug)

# Project's name

project(benchmark C)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ../red-black-tree/include/
    ../red-black-tree/src/
)
file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "../red-black-tree/include/rbtree.h"
    "../red-black-tree/src/rbtree.c"
)

set (PROJECT_SOURCES main.c)

add_executable(benchmark ${all_SRCS})

target_link_libraries(benchmark m)