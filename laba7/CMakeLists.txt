cmake_minimum_required(VERSION 3.6)
project(laba7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CAVL.cpp CAVL.h library.h CBST.cpp CBST.h CHashTableOpen.cpp CHashTableOpen.h CHashTableClose.cpp CHashTableClose.h)
add_executable(laba7 ${SOURCE_FILES})