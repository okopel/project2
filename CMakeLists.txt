cmake_minimum_required(VERSION 3.12)
project(project)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)
add_executable(project main.cpp ReadData.cpp ReadData.h Command.cpp Command.h Expression.h ShuntingYard.cpp ShuntingYard.h Expression.cpp ComExp.cpp ComExp.h Client.h ServerSock.h OpenServerCommand.cpp OpenServerCommand.h DoubleMap.cpp DoubleMap.h)