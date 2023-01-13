cmake_minimum_required(VERSION 3.23)
project(LinuxMultithreading)

set(CMAKE_CXX_STANDARD 14)

add_executable(LinuxMultithreading main.cpp Vector.cpp Vector.h MatrixMultiply.cpp MatrixMultiply.h)
