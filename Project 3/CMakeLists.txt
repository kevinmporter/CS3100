cmake_minimum_required(VERSION 2.8.4)
project(Project3Assignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Array.h
    ConcreteArray.h
    main.cpp
    Tester.h)

add_executable(Project3Assignment ${SOURCE_FILES})