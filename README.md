# HPC-A
## Numerical Simulation and Visualization of 2D Rayleigh--Bénard Convection
This project is a simulation software for 2D Rayleigh--Bénard Convection. The software takes the input
from user interface, uses numerical solver to compute the temperature and velocity field of fluids,
simulates and visualizes the results of computation, and displays results in a graphical user interface.

## Group Members
Yang Jiao, Yiming Li, Kit Sum Wu  

## Installation
### System requirements
- **Hardware:** For now the project can be built and run in a Linux PC without GPU. It is fully compatible with the Brown CCV environment.
- **Operating System:** For now the visualization module is implemented on a PC with Ubuntu 18.04 LTS, 
and it can also be run on Brown CCV, which uses RedHat7 operation system.
- **Libraries and packages**: This project depends on OpenFOAM 4.1, VTK 8.1.0 and Qt 5.10.1. You need
to install these modules to build the software. Instructions for Brown CCV users to load these modules will be provided.
### Build instructions

In your terminal/command prompt:
1. Make sure you load the vtk module: ``module load vtk/8.1.0``
1. Clone this repository into your directory: ``git clone https://github.com/ENGN2912B-2018/HPC-A.git``
2. Switch to visualization directory: ``cd visualization``
2. Create a build directory: 
```
mkdir build
cd build
```
3. Configure and generate CMake: ``cmake --DCMAKE_CXX_COMPILER=g++ ..``
4. Build the project: ``make``

## How to use the software:
To use the software, for now you should first use OpenFOAM to generate the simulation results, then execute the visualization program for getting the visualization.
### Simulation
1. Make sure you load the OpenFOAM modules: `module load mpi/openmpi_2.0.3_intel` `module load openfoam/4.1`
2. Run the command for each CCV session created: `source $FOAM_INST_DIR/OpenFOAM-4.1/etc/bashrc`
3. Create mesh, set up the boundaries conditions and physical properties: you can follow the instructions in the simulation branch.
4. Under the case directory `RBConvection`, run the solver: `buoyantBoussinesqPimpleFoam`

Now you will have a directory called `VTK/` under your case directory. Copy one of the `.vtk` file into the `visualization/build/` directory.

### Visualization
In the `build/` directory, simply run `./ReadUnstructuredGrid <VTK>`. `<VTK>` is your ``.vtk`` file copied.

## Reference
Coming soon!
