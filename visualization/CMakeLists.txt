
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ReadUnstructuredGrid)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReadUnstructuredGrid MACOSX_BUNDLE ReadUnstructuredGrid.cxx )
 
target_link_libraries(ReadUnstructuredGrid ${VTK_LIBRARIES})
