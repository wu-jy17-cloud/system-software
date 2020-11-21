cmake_minimum_required(VERSION 3.16)
project(system_software)

set(CMAKE_CXX_STANDARD 14)

add_executable(system_software main.cpp proc.h sched.h proc.cpp)