cmake_minimum_required(VERSION 3.12)
project(project)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)
add_executable(project main.cpp ReadData.cpp ReadData.h Command.cpp Command.h Client.cpp Expression.h ShuntingYard.cpp ShuntingYard.h Expression.cpp ServerSock.cpp ComExp.cpp ComExp.h Calculator.cpp Calculator.h text.cpp text.h newCalc.cpp newCalc.h)