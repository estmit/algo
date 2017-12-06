cmake_minimum_required(VERSION 3.8)
project(codebase)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
set(CMAKE_CXX_COMPILER "/usr/local/Cellar/gcc@5/5.5.0/bin/g++-5")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -std=c++11")

add_library(timer timer.c)

add_executable(main lcs.cpp)
target_link_libraries(main timer)
