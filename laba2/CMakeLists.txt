cmake_minimum_required(VERSION 3.6)
project(laba2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Stack_array.cpp Stack_array.h)
add_executable(laba2 ${SOURCE_FILES})