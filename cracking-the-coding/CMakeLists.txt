cmake_minimum_required(VERSION 3.0.0)

set(GCC_COVERAGE_COMPILE_FLAGS 
    "-fsanitize=address,leak,undefined -Wall -Wextra -Wunused -Wformat -std=c++1z")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# Choose a chapter to run
add_subdirectory(chapter_1)