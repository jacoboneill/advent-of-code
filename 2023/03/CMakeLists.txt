cmake_minimum_required(VERSION 3.20)
project(AOC2023_01)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
  main.cpp
  util.hpp
)

add_executable(AOC2023_03 ${SOURCES})
