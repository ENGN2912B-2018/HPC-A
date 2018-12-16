
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

## Design Philosophy
Our project is divided as three parts: numerical calculation and simulation of Rayleigh-Bénard Convection in 2D space, data visualization of simulation and GUI design. In our project, we need to solve a constitute equations for Rayleigh--B\'enard Convection and  build a 2D mesh simulation with parameters, including fluid properties, fluid volume geometry, time step,mesh spacing and simulation duration. The simulation will produce fluid velocity and temperature for each mesh node for data visualization. However, problems like converge failure, low simulation speed and are needed to be pay attention to.
 
The input of data visualization is the result of Rayleigh-Bénard Convection simulation and the resulting graphics should be exported to GUI section. It gives users a direct view of their calculation and help them to better understand Rayleigh--B\'enard Convection or the errors occurred in their calculation. The configurations should include output map layer, dimensions of output, color schemes and result export format. The main challenges can be the data format of the integration and the computational efficiency.
 
Graphical User Interface is like a conductor of the project. It control the progress of both simulation and visualization. There should be four main functions in GUI: data loading and saving, parameter setting, progress control like start or pause and result display. However, we may encounter challenges like processing large data set, dealing the data concurrency and the warning of invalid input or errors in the simulation and visualization.

## Build instructions

Please refer to the separate readme files for installation instructions.

[Simulation Set Up Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/master/simulation/README.md)

### Visulization: Build instructions

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

### Visualization: Generate the results
In the `build/` directory, simply run `./mainVisualizer`.

### GUI: Build a Qt project with Qt Creator: 
We need to install Qt and VTK. The detailed installation guides are here: 
[Qt Installation Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/gui/Qt%20installation%20guide.md)
[VTK Installation GUide](https://github.com/ENGN2912B-2018/HPC-A/blob/gui/VTK%20installation%20guide.md)

### GUI: Build a Qt project with CMake: 
I use a simple "hello world" example to show the basic build instruction.

- **Create a directory for a Qt program and change into the directory:**
```
mkdir QtHelloWorld
cd QtHelloWorld
```

- **Create a source code file:**

```
gedit main.cpp
```
- **Add your code, save the file and exit.**
```
#include <QApplication>
#include <QLabel>
#include <QWidget>
int main(int argc, char *argv[ ])
{
QApplication app(argc, argv);
QLabel hello("<center>Welcome to my first WikiHow Qt program</center>");
hello.setWindowTitle("My First WikiHow Qt Program");
hello.resize(400, 400);
hello.show();
return app.exec();
}
```


- **Build and compile the file:**

**NOTE: you should in the QtHelloWorld directory to build and conpile the file.**

```
qmake -project
qmake
make
```
The first line will create the Qt project file.
The second line will create the Qt make file.
The last line will compile the Qt make file on your system into an executable program. At this point, providing that there are no errors the file should compile into an executable program.

- **Run executable file:**

 ./QtHelloWorld

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
