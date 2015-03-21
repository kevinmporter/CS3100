cmake_minimum_required(VERSION 3.1)
project(Project4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
AlphaBeta.cpp
AlphaBeta.h
Connect4Game.cpp
Connect4Game.h
ConnectBoard.cpp
ConnectBoard.h
TicTacToeBoard.h
TicTacToeGame.h)
add_executable(Project4 ${SOURCE_FILES})