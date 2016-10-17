cmake_minimum_required(VERSION 3.6)
project(laba3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp MyRecord.cpp MyRecord.h Table_key.cpp Table_key.h)
add_executable(laba3 ${SOURCE_FILES})