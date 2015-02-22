cmake_minimum_required(VERSION 2.8.4)
project(Lab1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES main.c)
add_executable(Lab1 ${SOURCE_FILES})