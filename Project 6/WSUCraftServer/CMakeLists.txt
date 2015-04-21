cmake_minimum_required(VERSION 3.1)

project(WSUCraftServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lz")

set(SOURCE_FILES
    main.cpp
    WSUCraftService.cpp
    WSUCraftService.h
    WSUMap.cpp
    WSUMap.h)

add_executable(WSUCraftServer ${SOURCE_FILES})