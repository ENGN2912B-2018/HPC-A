cmake_minimum_required(VERSION 2.8)

project(HPC-ALibrary)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(HPC-ALibrary RBConvSim.h)

set_target_properties(HPC-ALibrary PROPERTIES LINKER_LANGUAGE CXX)
