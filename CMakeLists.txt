cmake_minimum_required(VERSION 3.28)
project(Sosyal_Ag)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sosyal_Ag main.cpp
        utils.cpp
        Person.cpp
        Graph.cpp)
