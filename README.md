
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

A block diagram representation of our program is below:

![alt text](https://github.com/ENGN2912B-2018/HPC-A/blob/master/images/softwarearchitecture.png)

# Interface Descriptions
## Graphical Interface
Our GUI has two windows. The main window contains three buttons for users to control the project and a parameter display table, which cannot be edited by users. The first time user start our project, all the parameters are of default values. 

![main window](https://github.com/ENGN2912B-2018/HPC-A/blob/master/images/GUI-MainWindow.png)

After pressing "parameter setting" button, a new parameter window will jump out. The parameter window contains two part: the simulation parameter setting part and the visualization parameter setting part.
For the simulation setting part, user can choose the value of Pr and Ra. When they click "apply simulation changes", GUI will set the parameters with the new value. It will also generate a file path to read the pre-stored simulation data, which is accociated with the chosen Pr value and Ra value.

   ![simulation](https://github.com/ENGN2912B-2018/HPC-A/blob/master/images/simParameter.png)

For the visualization part, users can choose different color scheme and time steps. They can choose to visualize convection temperature T or fluid velocity mag(U). Then click "apply visualization changes" to assign new values to the visualization parameters.

   ![visualization](https://github.com/ENGN2912B-2018/HPC-A/blob/master/images/visParameter.png)
   
When users have made changes to parameters of interest, they can press "apply changes" to display the latest parameter value in the main window. Then press "visualization" button to start visualization. If some parameters remain unchanged, a message box will jump out to tell users whether they want to continue visualization with default values. 

Our project cannot be real time, so after users press "visualization", they have to wait for a while because the project has to read vtk data first. When the time step is 2, it takes the longest time to read data and visualize them. Therefore, if users want to see the whole progress in much shorter time, they need to choose 20 to be the time step.

## Data Visualization
The data visualization module reads the data from `.vtk` files generated by OpenFOAM in VTK's `vtkUnstructuredGrid` format, maps it into a 2D plane object with different colors, and renders the results in an OpenGL window. Windows `AVI` video can also be generated and saved during the visualization process.  

The module is mainly implemented as `VTKReaderLibrary` in the `VTKReader.h` and `VTKReader.cpp` files under both `\visualization\src` and `gui\RBCGUI` folders, providing both support for graphical and command-line interfaces. The `mainVisualizer.cxx` file itself is the source code of self-contained command-line based app that directly uses the library and generated the desired results.
## Communications Protocols
### Simulation and Visualization
The simulation and visualization components are connected using OpenFOAM's `writeVTK` function method. `writeVTK` automatically generates `vtkUnstructuredGrid` files that can be read by VTK's reader methods during the simulation process.

## Threading and Concurrency
The OpenMP API is applied by our data visualization library to parallelize and accelerate the data processing and visualization pipeline. With parrallelizaton, the files are processed by multiple threads in the same time, and the total run time is decreased to 13% (from 60 seconds to 8 seconds when 8 threads are used) of the original system under certain multithreading schedule and operating system.

## Exception Handling
Exception handling techniques are implemented in our system. Three types of exceptions are defined in the program:
1. The program fails to locate the folder of the simulation results;

2. The simulation results do not exist or are corrupted;

3. All other unexpected exceptions, such as the computational resources are exhausted by the program.  

In all of those situations, the program will terminate, and pop up different messages. For the file I/O issues, we will prompt the user to check the file path and parameter settings; and for the unexpected exceptions, we will prompt the user to contact us in the [Github Issues Page](https://github.com/ENGN2912B-2018/HPC-A/issues).
# Testing and Evaluation

## Operating system(s) and software compiler/library version(s) tested
### Main Application:
#### Windows 10
MSVC2017 64bit , Qt 5.10.1, VTK 8.1.2

### Command-line tools:
### Visualization Module:
**Windows 10:** CMake 3.13.2, Visual Studio 2017, VTK 8.1.2  
**Ubuntu 18.04:** CMake 3.10.2, gcc 7.3.0, VTK 8.1.2    
**RedHat 7 (CCV, Should be run under a GPU node):**  CMake 3.8.0, gcc 7.2, VTK 8.1.0  

**Note:** The multithreading utilities are not supported on the CCV environment, and the video saving utilities are not supported on any Linux systems.  

## Description of functional testing to date
### Simulation
### Visualization
#### Identification of functions, expected inputs and outputs
For conducting functional tests for visualization components, we implemented a driver program named `mainVisualizer`.
The inputs of `mainVisualizer` are commands from user input which specify visualization parameters, and `.vtk` files that generated from the simulation components. The `.vtk` files can also be downloaded from [this Google Drive Page](https://drive.google.com/open?id=1uOd3skYjSeGgKKKBibIzqVxK3MpL1rfd).
The expected output of `mainVisualizer` should be a OpenGL render window showing the visualization results in an animation. In Windows 10, an optional Windows AVI video can also be saved in the same directory as the `.vtk` files.
#### Execution, actual outputs and evaluation
**Linux:** 
Under the terminal, we rAn `./mainVisualizer` file and enter the parameters as instruction.

![Linux Command-line tool](https://upload-images.jianshu.io/upload_images/315072-8ab196915da0c1cc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
Then the results were generated in an Open GL render window.
![Execution results](https://upload-images.jianshu.io/upload_images/315072-864cbb3d6d7e6356.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### Graphical User Interface (Main Application)

## Build instructions

Please refer to the following files for installation instructions.

[Simulation Set Up Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/master/SimulationGuide.md)

[Visualization Set Up Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/master/VisualizationGuide.md)

[GUI Set Up Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/master/GUIGuide.md)

# Conclusions

# Future Work
### Supports for Multi-Platform
Our main application can only work on Windows 10 operating system. Linux-based operating systems(including the Brown CCV environment) are not supported due to an incompatible OpenGL version. For the users who want to simulate the -Bénard Convection on Linux systems, we offer a [command-lind based solution](https://github.com/ENGN2912B-2018/HPC-A/blob/master/VisualizationGuide.md) that can work on both Windows and Linux. One possible future work for our project is to provide supports for multi-platform development.

# Author Contributions

Yang Jiao focused on visualizing the data and developing the command-line tool.

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
