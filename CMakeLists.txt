cmake_minimum_required(VERSION 3.21)
project(myGrep)

set(CMAKE_CXX_STANDARD 17)

add_executable(myGrep main.cpp searchFromFile.h searchFromFile.cpp searchFromString.h searchFromString.cpp)
