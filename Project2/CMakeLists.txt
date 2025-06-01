cmake_minimum_required(VERSION 3.28)
project(Project2)

set(CMAKE_CXX_STANDARD 17)


add_executable(Project2 main.cpp
        Server.cpp
        Server.h
        ClientHandler.cpp
        ClientHandler.h
        Client.cpp
        Client.h)

if (WIN32)
    target_link_libraries(Project2 ws2_32)
endif()

