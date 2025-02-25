cmake_minimum_required(VERSION 3.10)
project(networking)

set(CMAKE_CXX_STANDARD 14) # Or 14, 20, etc.

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(networking ${SOURCES})