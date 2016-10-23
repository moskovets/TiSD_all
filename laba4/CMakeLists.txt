cmake_minimum_required(VERSION 3.6)
project(laba4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CQueue_array.cpp CQueue_array.h CQueue_list.cpp CQueue_list.h library.h)
add_executable(laba4 ${SOURCE_FILES})