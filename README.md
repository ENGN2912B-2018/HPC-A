# HPC-A
## Numerical Simulation and Visualization of 2D Rayleigh--Bénard Convection
This project is a simulation software for 2D Rayleigh--Bénard Convection. The software takes the input
from user interface, uses numerical solver to compute the temperature and velocity field of fluids,
simulates and visualizes the results of computation, and displays results in a graphical user interface.

## Group Members
Yang Jiao, Yiming Li, Kit Sum Wu  

## Design Philosophy
Our project is divided as three parts: numerical calculation and simulation of Rayleigh--B\'enard Convection in 2D space, data visualization of simulation and GUI design. In our project, we need to solve a constitute equations for Rayleigh--B\'enard Convection and  build a 2D mesh simulation with parameters, including fluid properties, fluid volume geometry, time step,mesh spacing and simulation duration. The simulation will produce fluid velocity and temperature for each mesh node for data visualization. However, problems like converge failure, low simulation speed and are needed to be pay attention to.
 
The input of data visualization is the result of Rayleigh--B\'enard Convection simulation and the resulting graphics should be exported to GUI section. It gives users a direct view of their calculation and help them to better understand Rayleigh--B\'enard Convection or the errors occurred in their calculation. The configurations should include output map layer, dimensions of output, color schemes and result export format. The main challenges can be the data format of the integration and the computational efficiency.
 
Graphical User Interface is like a conductor of the project. It control the progress of both simulation and visualization. There should be four main functions in GUI: data loading and saving, parameter setting, progress control like start or pause and result display. However, we may encounter challenges like processing large data set, dealing the data concurrency and the warning of invalid input or errors in the simulation and visualization.

## Build instructions
### Simulation: Getting started with openFOAM
This section provides instructions for running openFOAM simulations on the Brown CCV Linux Redhat environment. First, the following commands should be entered into the terminal to load modules which are necessary for the project:

`module load mpi/openmpi_2.0.3_intel`
`module load openfoam/4.1`

Then, the following commands should be run:

`source $FOAM_INST_DIR/OpenFOAM-4.1/etc/bashrc`

Now, we must make a copy of the openFOAM tutorial files to edit. They will be used as a template for constructing the simulations for this project. To do this, we use the following command to create a destination directory to which we will copy the tutorial files:

`mkdir -p $FOAM_RUN`

We then copy the files from the tutorials directory in the openFOAM file set to this newly created directory:

`cp -r $FOAM_TUTORIALS $FOAM_RUN`

We can move to this directory with the following command:

`cd $FOAM_RUN/tutorials`

### Simulation: Setting up the simulation

### Simulation: Saving data and loading data

## Usage documentation
Coming Soon!

## References
https://openfoamwiki.net/index.php/FAQ/Installation_and_Running
file:///G:/My%20Drive/Fall%202018/ENGN2912B/Final/4-OpenFOAM%20Structure.pdf
https://www.openfoam.com/documentation/tutorial-guide/tutorialse2.php#x6-60002.1
https://cfd.direct/openfoam/user-guide/v6-tutorials/

