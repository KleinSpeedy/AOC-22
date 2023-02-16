cmake_minimum_required(VERSION 3.16)

project(AoC22 C)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_SYSTEM Linux)

# Miscelaneous
include_directories(puzzle-inputs/)

# Puzzles
add_subdirectory(days/1)
add_subdirectory(days/2)
add_subdirectory(days/3)
add_subdirectory(days/4) # doesnt work yet