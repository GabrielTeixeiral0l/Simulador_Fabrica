cmake_minimum_required(VERSION 4.3)
project(simulador)

set(CMAKE_CXX_STANDARD 20)

add_executable(simulador main.cpp
        Ecra.cpp
        Ecra.h)
