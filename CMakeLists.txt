cmake_minimum_required(VERSION 3.12)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main.cpp ReadData.cpp ReadData.h Command.cpp Command.h Client.cpp)