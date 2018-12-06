cmake_minimum_required(VERSION 2.8)

PROJECT(mainVisualizerLibrary)

if (WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
else  ()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()

add_library(VTKReaderLibrary VTKReader.h VTKReader.cpp)

set_target_properties(VTKReaderLibrary PROPERTIES LINKER_LANGUAGE CXX)
