
cmake_minimum_required(VERSION 2.8)

## PROJECT(ReadUnstructuredGrid)

PROJECT(mainVisualizer)

## if (WIN32)
##   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
## else  ()
##   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
## endif ()

find_package(VTK REQUIRED)
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

  
include(${VTK_USE_FILE})

include_directories(src)
add_subdirectory(src)

## add_executable(ReadUnstructuredGrid MACOSX_BUNDLE ReadUnstructuredGrid.cxx )

add_executable(mainVisualizer MACOSX_BUNDLE mainVisualizer.cxx)
target_link_libraries(mainVisualizer VTKReaderLibrary ${VTK_LIBRARIES})

## target_link_libraries(ReadUnstructuredGrid ${VTK_LIBRARIES})
