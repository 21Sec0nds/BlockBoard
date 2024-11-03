cmake_minimum_required(VERSION 3.20)
project(BlockBoard)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(BlockBoard BlockBoard/BlockB.cpp)

if(WIN32)
    message(STATUS "Building on Windows")
elseif(UNIX AND NOT APPLE)
    message(STATUS "Building on Linux")
elseif(APPLE)
    message(STATUS "Building on macOS")
endif()
