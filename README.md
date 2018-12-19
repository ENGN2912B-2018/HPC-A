
# Numerical Simulation and Visualization of 2D Rayleigh-Bénard Convection

ENGN2912B : Scientific Computing in C++

Final Project

High Performance Computing, Group A

Submitted December 2018



## Group Members
Yang Jiao   (yang_jiao@brown.edu)

Yiming Li   (yiming_li1@brown.edu)

Kit Sum Wu  (kitsum_wu@brown.edu)

## Contents
[Introduction](#introduction)  
[Software Architectural Design](#software-architectural-design)  
[Interface Descriptions](#interface-descriptions)  
[Testing and Evaluation](#testing-and-evaluation)  
[Conclusions](#conclusions)  
[Future Work](#future-work)    
[Author Contributions](#author-contributions)   
[References](#references)  

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

The input of data visualization is the result of Rayleigh-Bénard Convection simulation and the resulting graphics should be exported to GUI section. It gives users a direct view of their calculation and help them to better understand Rayleigh--B\'enard Convection or the errors occurred in their calculation. The visualization options include output map layer and color scheme.

The graphical user interface (GUI) is like the conductor of the project. The GUI will receive simulation and visualization parameters from the user and show the the visualization of the corresponding simulation case.

A block diagram representation of our program is below:

![software architecture](https://github.com/ENGN2912B-2018/HPC-A/blob/master/images/softwarearchitecture.png)

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

![msgbox](https://github.com/ENGN2912B-2018/HPC-A/blob/master/images/msg%20box.png)

Our project cannot run fast enough under all conditions to be considered real time. After the user presses "visualization", they have to wait for a while because the project has to read vtk data first. When the time step is 2 seconds, the program takes the longest time to produce a visualization because the finer time resolution means that there is more data to read and process. Therefore, if users want to see progress in much shorter time, they need to choose 20 seconds to be the time step, which will decrease to volume of data which needs to be processed to create the time lapse video of the convection.
![result](https://github.com/ENGN2912B-2018/HPC-A/blob/master/images/result.png)

## Data Visualization
The data visualization module reads the data from `.vtk` files generated by OpenFOAM in VTK's `vtkUnstructuredGrid` format, maps it into a 2D plane object with different colors, and renders the results in an OpenGL window. Windows `AVI` video can also be generated and saved during the visualization process.  

The module is mainly implemented as `VTKReaderLibrary` in the `VTKReader.h` and `VTKReader.cpp` files under both `\visualization\src` and `gui\RBCGUI` folders, providing both support for graphical and command-line interfaces. The `mainVisualizer.cxx` file itself is the source code of self-contained command-line based app that directly uses the library and generated the desired results.

## Communications Protocols
### Simulation and Visualization
The simulation and visualization components are connected using OpenFOAM's `writeVTK` function method. `writeVTK` automatically generates `vtkUnstructuredGrid` files that can be read by VTK's reader methods during the simulation process.

### Qt, Simulation and Visualization
Since for different values of simulation parameter Pr and Ra, the data generated by OpenFOAM are stored in different folders. The name of every folder is consist of the name and value of these two parameter. Therefore, the control of simulation is just as easy as open an assigned folder.

In order to call the visualization in Qt, we wrap the main function of the VTK program in the callback function of "visualization" button. Also, other source code and header file of VTK program should be added into Qt program.

## Threading and Concurrency
The OpenMP API is applied by our data visualization library to parallelize and accelerate the data processing and visualization pipeline. With parallelizaton, the files are processed by multiple threads in the same time, and the total run time is decreased to 13% (from 60 seconds to 8 seconds when 8 threads are used) of that of the original system under certain multithreading schedule and operating system conditions.

## Exception Handling
Exception handling techniques are implemented in our system. Three types of exceptions are defined in the program:
1. The program fails to locate the folder of the simulation results;

2. The simulation results do not exist or are corrupted;

3. All other unexpected exceptions, such as the computational resources are exhausted by the program.  

In all of those situations, the program will terminate, and pop up different messages. For the file I/O issues, we will prompt the user to check the file path and parameter settings; and for the unexpected exceptions, we will prompt the user to contact us in the [Github Issues page](https://github.com/ENGN2912B-2018/HPC-A/issues).

In addition, in the helper program we used behind the scenes to automatically generate data sets, if the user provides an invalid input, they are prompted to try again until an acceptable value is received.

# Testing and Evaluation

## Operating system(s) and software compiler/library version(s) tested
### Main Application:
#### Windows 10
MSVC2017 64bit , Qt 5.10.1, VTK 8.1.2

### Visualization Module:
**Windows 10:** CMake 3.13.2, Visual Studio 2017, VTK 8.1.2  
**Ubuntu 18.04:** CMake 3.10.2, gcc 7.3.0, VTK 8.1.2    
**RedHat 7 (CCV, Should be run under a GPU node):**  CMake 3.8.0, gcc 7.2, VTK 8.1.0  

**Note:** The multithreading utilities are not supported on the CCV environment, and the video saving utilities are not supported on any Linux systems.

### Simulation Automation Tool:
**RedHat 7:** CMake 3.8.0, gcc 7.2, OpenFOAM 4.1, openMPI 2.0.3


## Description of functional testing to date
### Simulation
#### Automation via C++
To provide a versatile method for running several OpenFOAM simulations in sequence, we wrote a wrapper for the OpenFOAM convection simulation which can read and modify an OpenFOAM test case. Upon verifying that the simulation parameters could be successfully changed from within a C++ file, we then implemented a program to automate the generation of data sets for cases Rayleigh-Bénard Convection with varying Rayleigh and Prandtl numbers for use by the visualization and graphical interface parts of the project. The person creating these data sets has the ability to determine the number of Ra and Pr values to draw combinations from, and to set them via command line. This way, a collection of data sets can be generated incrementally if they do not have access to the CCV for an extended time, and new data sets can be added easily if needed.
### Visualization
#### Identification of functions, expected inputs and outputs
For conducting functional tests for visualization components, we implemented a driver program named `mainVisualizer`.
The inputs of `mainVisualizer` are commands from user input which specify visualization parameters, and `.vtk` files that generated from the simulation components. The `.vtk` files can also be downloaded from [this Google Drive page](https://drive.google.com/open?id=1uOd3skYjSeGgKKKBibIzqVxK3MpL1rfd).
The expected output of `mainVisualizer` should be a OpenGL render window showing the visualization results in an animation. In Windows 10, an optional Windows AVI video can also be saved in the same directory as the `.vtk` files.
#### Execution, actual outputs and evaluation
**Linux:**   
Under the terminal, we ran the `./mainVisualizer` file and enter the parameters as the instructions.

![Linux Command-line tool](https://upload-images.jianshu.io/upload_images/315072-8ab196915da0c1cc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
Then the results were generated in an Open GL render window.
![Execution results](https://upload-images.jianshu.io/upload_images/315072-864cbb3d6d7e6356.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)  

**Windows:**   
We directly double clicked the `mainVisualizer` executable and enter the parameters as the instructions.
![Windows Command-line tool](https://upload-images.jianshu.io/upload_images/315072-a6dd5569c8ec2a20.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
Then the results were generated in an OpenGL render window.  
![Execution results](https://upload-images.jianshu.io/upload_images/315072-f191266d7938752d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
A video was also generated in the same path as the `.vtk` files, and the results are the same as shown in the OpenGL render window.  
![Saved video file](https://upload-images.jianshu.io/upload_images/315072-31016b8b59ccc209.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

We can say that the visualization module passed the functional tests according to the results.

## Build instructions

Please refer to the following files for installation instructions.

[Simulation Set Up Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/master/SimulationGuide.md)

[Visualization Set Up Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/master/VisualizationGuide.md)

[GUI Set Up Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/master/GUIGuide.md)

# Conclusions
## Major Accomplishments
In our project, we implemented and developed:
- an appropriate wrapper class to simulate the 2D Rayleigh-Bénard Convection numerically using OpenFOAM application
- a visualization library to read the simulation results and generate an animation for the results
- a graphical user interface that allow user to choose from some different fixed parameter sets and provide visualizations from pre-generated simulations
- a command-line tool that provides multi-platform supports and error handling  

## Completeness and Challenges
Compared to our objectives, we did not implement:
- a seamless program from simulation to visualization
- a integrated widget in graphical user interface that shows the visualization results  

We attribute these drawbacks to various different reasons. During the time of this project, we encountered several compatibility issues which prevented us from unifying the three parts of our program on one system and which required a significant amount of time to resolve. When we try to have the visualization window embedded in the GUI, the GUI window does not respond after the user presses the visualization button. As a result, we believe that the QVTKOpenGLWidget only displays the last frame of the visualization instead of the whole video. Therefore, abandoned the idea of using QVTKOpenGLWidget to display visualization in Qt main window. We now show the visualizations in an OpenGL window rather than inside the user interface because of the complexity of `QVTKOpenGLWidget` and Qt multithreading libraries.

In addition, we also discovered that Qt and VTK can not be built jointly in the CCV environment due to a OpenGL version issue. Thus, if we wanted to integrate the GUI and visualization, we were left with the option of using a Windows system, which cannot support OpenFOAM. Since we were able to mimic the automated simulation of data with user-selected parameters by saving some data sets beforehand, we chose to design our project for a Windows system to maximize the number of functions we could demonstrate at the end of the project period.

In our current version, there remain some areas where small improvements could be made. For example, our GUI hasn't implemented the selecting of the data reading path, so users have to change the vtk data path in the code before the program is built. Additionally, the person running the simulation automation tool must also manually change the location to save the generated data sets in the code before the program is built. There may also be possibilities for errors which we have not already considered and accounted for.  

# Future Work
### Multi-Platform Support
Our main application can only work on Windows 10 operating system. Linux-based operating systems(including the Brown CCV environment) are not supported due to an incompatible OpenGL version. For the users who want to simulate the Rayleigh-Bénard Convection on Linux systems, we offer a [command-line based solution](https://github.com/ENGN2912B-2018/HPC-A/blob/master/VisualizationGuide.md) that can work on both Windows and Linux. One possible future work for our project is to provide support for multi-platform development.

### Real-time Simulation and Visualization
There is a gap between our simulation and visualization components: our visualization module can only be run after the simulation is completed since we are directly using the pre-compiled OpenFOAM application to generate the simulation results. In the future, we can delve into the OpenFOAM C++ source code, develop OpenFOAM based libraries, and implement a seamlessly connected application that could provide real-time visualization during simulation.

### Modification of More Simulation Parameters
Once we are able to integrate the simulation with the visualization and the GUI on the same system, then the next step would be to enable the user to change more simulation parameters from the GUI. For example, the simulation time step, the domain width and height, and the mesh resolution are parameters which were kept constant in this version due to limited time and resources. Additionally, future versions of this project could allow the user to change physical properties of the fluid to change the non-dimensional parameters. This would illustrate the idea that the same fluid behavior can be observed even in different physical conditions.

### More Visualization Options
For this iteration of the project, we focused on visualizing two scalar fields, temperature and velocity magnitude. In the future, we could add the ability to visualize the velocity vector field using scaled arrows indicating flow direction and magnitude originating at each node. In addition, the ability to view isotherms in the temperature field may also be a useful function of the program to be added in future iterations.

### 3D Simulation and Visualization
Another possible future direction for this project is to give the user the option visualizing a 3D simulation. In this case, we would give the user the option of taking cross sections of the domain from the three directions and then allow them to play a movie of the phenomenon. We could also give the user the option of viewing the outside surface of the region from different angles.

# Author Contributions

Yang Jiao focused on converting the simulation files into VTK format, visualizing the data and developing the command-line tool. He is responsible for all the source code under the `visualization` directory and the `writeVTK` function object in the `RBConvection\system\controlDict` file.

Yiming Li focused on creating the GUI to control simulation setting, visualization setting and the start of visualization. She is responsible for all the source code under `gui` directory.

Katie Wu focused on the numerical simulation. She is responsible for setting up the OpenFOAM case directory to simulate Rayleigh-Bénard Convection and automating the use of OpenFOAM to generate data sets.

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

[VTK Qt examples](https://www.vtk.org/Wiki/VTK/Examples/Cxx/Qt)
