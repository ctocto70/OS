cmake_minimum_required(VERSION 3.22)
project(Vector)

set(CMAKE_CXX_STANDARD 14)

include_directories(../Number)

add_library(Vector SHARED Vector.cpp Vector.h)

find_library(NUMBER Number ../Number/cmake-build-debug)

target_link_libraries(Vector LINK_PUBLIC ${NUMBER})
