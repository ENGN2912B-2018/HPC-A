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

## Installation
We need to install Qt and VTK. The detailed installation guides are here: 

[Qt Installation Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/gui/Qt%20installation%20guide.md)

[VTK Installation GUide](https://github.com/ENGN2912B-2018/HPC-A/blob/gui/VTK%20installation%20guide.md)


## Build Instruction
### Build a Qt project with Qt Creator: 

### Build a Qt project with CMake: 
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


- **Build and conpile the file:**

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


## Reference
1. Install Qt 5 on Ubuntu

https://wiki.qt.io/Install_Qt_5_on_Ubuntu

2. How to create your first qt program on Ubuntu Linux.

https://www.wikihow.com/Create-Your-First-Qt-Program-on-Ubuntu-Linux
