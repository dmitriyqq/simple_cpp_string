cmake_minimum_required(VERSION 3.9)
project(string_class_cpp)

include_directories(include)

set(CMAKE_CXX_STANDARD 14)

add_executable(string_class_cpp main.cpp src/String.cpp include/String.h)