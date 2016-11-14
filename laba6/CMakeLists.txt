cmake_minimum_required(VERSION 3.6)
project(laba6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BST.cpp BST.h library.h)
add_executable(laba6 ${SOURCE_FILES})