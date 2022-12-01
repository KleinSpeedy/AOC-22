cmake_minimum_required(VERSION 3.16)

project(AoC22 C)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_SYSTEM Linux)

# Miscelaneous
include_directories(misc)

# Puzzles
add_subdirectory(1)