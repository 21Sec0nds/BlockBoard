cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

# X11 libraries
find_package(X11 REQUIRED)

add_executable(untitled main.cpp)

# X11 library
target_link_libraries(untitled PRIVATE X11)
