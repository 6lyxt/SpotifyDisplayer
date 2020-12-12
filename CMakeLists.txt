# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.9)
project(SpotifyDisplayer)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

set(SOURCE_FILES main.cpp)
add_executable(SpotifyDisplayer ${SOURCE_FILES})