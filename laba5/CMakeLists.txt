cmake_minimum_required(VERSION 3.6)
project(laba5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CList.cpp CList.h library.h CSparse_matrix.cpp CSparse_matrix.h)
add_executable(laba5 ${SOURCE_FILES})