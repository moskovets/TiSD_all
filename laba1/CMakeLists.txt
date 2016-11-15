cmake_minimum_required(VERSION 3.6)
project(TiSD_laba1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BigDouble.cpp BigDouble.h BigInt.cpp BigInt.h)
add_executable(TiSD_laba1 ${SOURCE_FILES})