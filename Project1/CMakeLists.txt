cmake_minimum_required(VERSION 3.28)
project(DiningPhilosophers)

set(CMAKE_CXX_STANDARD 17)

add_executable(DiningPhilosophers main.cpp
        Philosopher.h
        Philosopher.cpp
        main.cpp)
