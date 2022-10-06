cmake_minimum_required(VERSION 3.22)
project(TestLab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(TestLab2 main.cpp)


include_directories(../Number)

find_library(NUMBER Number ../Number/cmake-build-debug)

target_link_libraries(TestLab2 LINK_PUBLIC ${NUMBER})


include_directories(../Vector)

find_library(VECTOR Vector ../Vector/cmake-build-debug)

target_link_libraries(TestLab2 LINK_PUBLIC ${VECTOR})
