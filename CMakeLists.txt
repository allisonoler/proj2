cmake_minimum_required(VERSION 3.30)
project(proj2)

set(CMAKE_CXX_STANDARD 20)

add_executable(proj2 main.cpp
        DatalogProgram.h
        Predicate.h
        Rule.h
        Parameter.h)
