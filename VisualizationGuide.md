#Visulization Set Up Guide

## Build instructions

In your terminal/command prompt:
1. Make sure you load the vtk module: ``module load vtk/8.1.0``
1. Clone this repository into your directory: ``git clone https://github.com/ENGN2912B-2018/HPC-A.git``
2. Switch to visualization directory: ``cd visualization``
2. Create a build directory:
```
mkdir build
cd build
```
3. Configure and generate CMake: ``cmake ..``
4. Build the project: ``make``

## Generate the results
In the `build/` directory, simply run `./mainVisualizer`.
