# HPC-A
## Numerical Simulation and Visualization of 2D Rayleigh--Bénard Convection
This project is a simulation software for 2D Rayleigh--Bénard Convection. The software takes the input
from user interface, uses numerical solver to compute the temperature and velocity field of fluids,
simulates and visualizes the results of computation, and displays results in a graphical user interface.

## Group Members
Yang Jiao, Yiming Li, Kit Sum Wu  

## Installation
### System requirements
- **Hardware:** For now the project can be built and run in a x86 PC without GPU.
- **Operating System:** For now the visualization module is implemented on a PC with Windows 10 1803, 
but we will soon move to a Linux development environment.
- **Libraries and packages**: This project depends on OpenFOAM 4.1 VTK 8.2.1 and Qt 5.10.1. You need
to install these modules to build the software.
### Build instructions
**NOTE**: The instructions here are just a template and will not compile!  

In your terminal/command prompt:
1. Clone this repository into your directory: ``git clone https://github.com/ENGN2912B-2018/HPC-A.git``
2. Create a build directory: 
```
mkdir build
cd build
```
3. Configure and generate CMake: ``cmake --DCMAKE_CXX_COMPILER=g++ ..``
4. Build the project: ``make``

## How to use the software:
In the `build/` directory, simply run ``./main``.

## Reference
