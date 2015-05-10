cmake_minimum_required(VERSION 2.8.4)
project(Project1_Assignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ConcreteCharArrayArray.cpp
    ConcreteCharArrayArray.h
    ConcreteCharArray.cpp
    ConcreteCharArray.h
    CharArray.cpp
    CharArray.h
    CharArrayArray.cpp
    CharArrayArray.h
    main.cpp)

add_executable(Project1_Assignment ${SOURCE_FILES})