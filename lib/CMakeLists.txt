cmake_minimum_required(VERSION 3.24)
project(task2Lib)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE main.cpp main.h)

set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(task2Lib SHARED ${SOURCE})
