
# Numerical Simulation and Visualization of 2D Rayleigh-Bénard Convection

ENGN2912B : Scientific Computing in C++

Final Project

High Performance Computing, Group A

Submitted December 2018

## Group Members
Yang Jiao   (yang_jiao@brown.edu)

Yiming Li   (yiming_li1@brown.edu)

Kit Sum Wu  (kitsum_wu@brown.edu)

# Introduction

This project is a visualization tool for 2D Rayleigh-Bénard Convection. The software receives input from user interface then displays a corresponding data set generated using numerical simulation.

## Goals and Objectives
The goal of this project is to create a user interface to interactively set simulation parameters and view the results of the simulation. The example we use for the project is Rayleigh-Benard convection, although this idea could easily be extended to other numerical simulations of other phenomena. 

Our objectives are as follows:
- accept simulation and visualization parameters from the user via a graphical user interface, and display the results
- numerically simulate Rayleigh--Bénard convection based on input parameters
- visualize the data from the simulation, and pass the results to the gui for display

# Software Architectural Design
Our project is divided as three parts: numerical simulation of 2D Rayleigh-Bénard Convection, data visualization of simulation and GUI design. The simulation will produce data for fluid velocity and temperature for each mesh node for data visualization.
 
The input of data visualization is the result of Rayleigh-Bénard Convection simulation and the resulting graphics should be exported to GUI section. It gives users a direct view of their calculation and help them to better understand Rayleigh--B\'enard Convection or the errors occurred in their calculation. The configurations should include output map layer, dimensions of output, color schemes and result export format.
 
The graphical user interface (GUI) is like the conductor of the project. The GUI will receive simulation and visualization parameters from the user and show the the visualization of the corresponding simulation case.

# Build instructions

Please refer to the following files for installation instructions.

[Simulation Set Up Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/master/SimulationGuide.md)

[Visualization Set Up Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/master/VisualizationGuide.md)

[GUI Set Up Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/master/GUIGuide.md)

# Testing and Evaluation

# Conclusions

# Future Work

# Author Contributions

Yang Jiao focused on visualizing the data.

Yiming Li focused on creating the GUI.

Kit Sum Wu focused on the numerical simulation.

# References
[Installing and Running OpenFOAM](https://openfoamwiki.net/index.php/FAQ/Installation_and_Running)

[OpenFOAM Structure](https://canvas.vt.edu/files/4773672/download?download_frd=1)

[Lid-driven Cavity Flow](https://www.openfoam.com/documentation/tutorial-guide/tutorialse2.php#x6-60002.1)

[OpenFOAM User Guide](https://cfd.direct/openfoam/user-guide-v4/)

[CFD on HPC](http://www.hpc.lsu.edu/training/weekly-materials/2014-Fall/intro_of_20141105.pdf)

[OpenFOAM Programming Tutorials](https://github.com/UnnamedMoose/BasicOpenFOAMProgrammingTutorials)

[writeVTK, an OpenFOAM function object](https://github.com/OpenFOAM/OpenFOAM-4.x/blob/master/applications/utilities/postProcessing/dataConversion/foamToVTK/foamToVTK/writeVTK/controlDict)

[VTK Examples: ColorCells](https://lorensen.github.io/VTKExamples/site/Cxx/PolyData/ColorCells/)

[VTK Examples: ReadLegacyUnstructuredGrid](https://lorensen.github.io/VTKExamples/site/Cxx/IO/ReadLegacyUnstructuredGrid/)

[VTK Examples: Hawaii](https://lorensen.github.io/VTKExamples/site/Cxx/Visualization/Hawaii/)

[(PDF) VTK file formats](https://www.vtk.org/wp-content/uploads/2015/04/file-formats.pdf)

[(PDF) Simple Visualization of unstructured grids with VTK](https://hal.inria.fr/inria-00107738/document)

[Install Qt 5 on Ubuntu](https://wiki.qt.io/Install_Qt_5_on_Ubuntu)

[How to create your first qt program on Ubuntu Linux.](https://www.wikihow.com/Create-Your-First-Qt-Program-on-Ubuntu-Linux)
