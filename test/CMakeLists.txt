cmake_minimum_required(VERSION 3.24)
project(task2Test)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE main.cpp)

link_directories(${CMAKE_BINARY_DIR}/lib)

add_executable(task2Test ${SOURCE})

target_link_libraries(task2Test task2Lib)