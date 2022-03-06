cmake_minimum_required(VERSION 3.21)
project(myGrep)

set(CMAKE_CXX_STANDARD 17)

add_executable(myGrep src/main.cpp include/searchFromFile.h src/searchFromFile.cpp include/searchFromString.h
        src/searchFromString.cpp)
