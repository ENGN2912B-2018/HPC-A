
cmake_minimum_required(VERSION 2.8)

## PROJECT(ReadUnstructuredGrid)

PROJECT(mainVisualizer)

if (WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
else  ()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

include_directories(src)
add_subdirectory(src)

## add_executable(ReadUnstructuredGrid MACOSX_BUNDLE ReadUnstructuredGrid.cxx )

add_executable(mainVisualizer MACOSX_BUNDLE mainVisualizer.cxx)
target_link_libraries(mainVisualizer VTKReaderLibrary ${VTK_LIBRARIES})

## target_link_libraries(ReadUnstructuredGrid ${VTK_LIBRARIES})
