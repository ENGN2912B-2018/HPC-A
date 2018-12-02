cmake_minimum_required(VERSION 2.8)
project(HPC-A)

# add compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -p -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

message(STATUS "Running on CCV")

# invoke library CMakeLists.txt
include_directories(src)
add_subdirectory(src)

# create the executable
add_executable(main main.cpp)
