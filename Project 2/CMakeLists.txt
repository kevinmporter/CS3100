cmake_minimum_required(VERSION 2.8.4)
project(Project2_Assignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ConcreteMazeLocationArray.cpp
    ConcreteMazeLocationArray.h
    MazeLocationArray.cpp
    MazeLocationArray.h
    main.cpp
    Maze.cpp
    Maze.h)

add_executable(Project2_Assignment ${SOURCE_FILES})