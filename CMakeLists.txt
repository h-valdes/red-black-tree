# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c17 -fsanitize=address -fsanitize=leak -lm -g -ggdb --gdb-index")

set(CMAKE_BUILD_TYPE Debug)

# Project's name

project(rbtree C)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/benchmarking
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/benchmarking
)
file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/include/benchmarking/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/benchmarking/*.c"
)

set (PROJECT_SOURCES main.c)

add_executable(rbtree ${all_SRCS})

target_link_libraries(rbtree m)