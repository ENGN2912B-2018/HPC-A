# Simulation Set Up Instructions

## Getting started with openFOAM
This section provides instructions for running openFOAM simulations on the Brown CCV Linux Redhat environment. First, the following commands should be entered into the terminal to load modules which are necessary for the project:

`module load mpi/openmpi_2.0.3_intel`

`module load openfoam/4.1`

Then, the following command should be run.

`source $FOAM_INST_DIR/OpenFOAM-4.1/etc/bashrc`

Please note that the previous three commands need to be run each time a new CCV session is started.

If this is the first time you are using openFOAM, you must make a copy of the openFOAM tutorial files which you have permission to edit. To do this, we use the following command to create a destination directory to which we will copy the tutorial files:

`mkdir -p $FOAM_RUN`

We then copy the files from the tutorials directory in the openFOAM file set to this newly created directory:

`cp -r $FOAM_TUTORIALS $FOAM_RUN`

If you have already created the run directory and copied the tutorial files, there is no need to repeat it.

## Simulation: Setting up the simulation

### 1. Create case directory
In OpenFOAM, the details of a simulation are included in what is called a case directory. The version of openFOAM available on the Brown CCV, openFOAM 4.1, does not have a case directory for Rayleigh Benard convection, so we will create our own. First, navigate to the solver directory:

`cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/`

You can download the case directory from this Github repository, which is based off of the guide on [CuriosityFluids](https://curiosityfluids.com/2017/06/12/rayleigh-benard-convection-using-buoyantboussinesqpimplefoam/). This case directory models a 2D flow in a rectangular region. Alternatively, you can download and modify the case directory for Rayleigh-Benard Convection [here](https://github.com/OpenFOAM/OpenFOAM-6/tree/master/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/BernardCells), which is set up to model 3D convection. The files included in this directory and their purpose are described here. To begin with, the case directory contains subdirectories titled '0', 'constant', and 'system' directories. The '0' directory contains files describing the initial conditions. The 'constant' directory contains information on physical constants and properties of the fluid. The 'system' directory contains directions for setting up the simulation. The case directory will also contain time directories corresponding to time steps in the simulation once the solver has been run. These directories contain the results of the simulation at each time step. A file tree of the case directory is shown below.

```bash
├── 0
│   ├── alphat
│   ├── epsilon
│   ├── k
│   ├── nut
│   ├── p
│   ├── p_rgh
│   ├── T
│   ├── U
├── constant
│   ├── g
│   ├── transportProperties
│   ├── turbulenceProperties
├── system
│   ├── blockMeshDict
│   ├── controlDict
│   ├── setFieldsDict
│   ├── decomposeParDict
│   ├── fvSolution
│   ├── fvSchemes
├── Time Directories
│   ├── alphat
│   ├── p
│   ├── phi
│   ├── p_rgh
│   ├── T
│   ├── U
│   ├── mag(U)
│   ├── uniform
```

### 2. Enable file editing

While in the `simulation` directory, create a build folder:

`mkdir build`

Then, run the following commands to compile the code:

`cmake -D CMAkE_CXX_COMPILER=g++ ..`

`make`

This should create the executable `set` in the `build` folder. Run the following commands from the `build` directory to copy this file into the `0` and `constant` directories:

`cp set $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection/0`

`cp set $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection/constant`

With this, the preparations to interface with OpenFOAM from C++ are finished. If you include the `RBConvSim.h` file in your C++ code, you can instantiate a simulation class, modify parameters, and run simulations from within C++.

### 3. Creating data sets

The controlDict file in the case directory included in this repository has already been modified to create vtk-compatible data files. In order to generate data sets, first designate a location to save the vtk data sets in line 196 of the main.cpp file. You can then perform simulations for various cases using the `main` executable created by running the `make` command in the build folder.

To make it easier to transfer the data files to a different location, we recommend zipping them first. A sample zip command is shown below.

`zip -r example.zip example`

## Parallelization

It is possible to use openmpi to parallelize the OpenFOAM simulation. To enable this, we must first decompose the simulation problem to smaller parts to assign to each processor. We do this by running the following command in the case directory.

`decomposePar`

This creates a number of directories called `processor[n]` in the case directory, for n = 0 to n = np - 1, where  np is the number of processors specified in the `decomposeParDict` file in the `system` directory. Then, the following command is run to perform the parallelized computing task. The `> log` part of the command sends the output to a text file `log`, and the `&` has the task run in the background.

`mpirun -np 16 buoyantBoussinesqPimpleFoam -parallel > log &`

Once the simulation has finished, the data from all of the processors mmust be reunited. This is done using the following command:

`reconstructPar`

Note: The simulation data must be reconstructed at each time step, and the reconstruction for each time step requires several seconds. This may be useful if only few time steps (e.g. only the final time) were of interest. However, since we are visualizing the entire process with 1000 time steps, we would not see any improvements in total computation time. Therefore, we did not implement the parallelization in our project.
