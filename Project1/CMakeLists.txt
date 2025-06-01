cmake_minimum_required(VERSION 3.28)
project(Project1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project1 main.cpp
        Philosopher.h
        Philosopher.cpp
        main.cpp
        Dijkstra.cpp
        Dijkstra.h)
