cmake_minimum_required(VERSION 3.24)
project(.)

# Use modern C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(..)

# Source files (only .cpp, no .h files)
add_executable(Empringham_KimmyRPG
        main.cpp
        Story.cpp)