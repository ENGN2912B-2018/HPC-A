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
For now Qt has be installed in a Windows operating system. In order to run the whole program on CCV, GUI will be developed in a Linux environment. The version of Qt installed in Windows now is 5.11.2. We will install Qt 5.10.1 in Ubuntu.

**NOTE: The following steps just the installation instruction from the official website. Please check the version you want to install before the next steps.**

- **Download:**
You can visit Qt officcial website to download Qt in all kinds of operating system, or the Ubuntu installation file can be also downloaded through the command line using wget.
```
wget http://download.qt.io/official_releases/qt/5.7/5.10.1/qt-opensource-linux-x64-5.10.1.run
```
- **Install:**
Adjust permission, run the installer and follow the instruction to complete the installation.
```
chmod +x qt-opensource-linux-x64-5.10.1.run
./qt-opensource-linux-x64-5.10.1.run
```
- **Install g++:**
Open a terminal and execute the following command to install g++:
```
sudo apt-get install build-essential
```
- **Install generic font configuration library - runtime:**
Open a terminal and execute the following command to install the full runtime files for the generic font configuration library:
```
sudo apt-get install libfontconfig1
```
- **Configure a compiler:**
Launch Qt Creator. Go to Tools > Options. Click Build & Run and select tab Kit. Configure a compiler if it is not automatically detected.
- **Install OpenGL libraries:**
Execute the following command to install OpenGL libraries:
```
sudo apt-get install mesa-common-dev
```
**Note:** Just installing the above-mentioned mesa-common-dev kit is not sufficient for more recent Ubuntu versions. Based on a comment in the Qt forum[1] an additional package needs installation. Execute following command:
```
sudo apt-get install libglu1-mesa-dev -y
```
Tested with Qt5.3.1 and Ubuntu 14.04 and it solved the problem with missing -lGL.
- **Set file association with pro files:**
When installing from the on-line source the file association is not done automatically. It also not show up when you try to associate it with file explorer. Create a file named “Qt-Creator.desktop” and fill the file with the following.
```
[Desktop Entry]
Version=1.0
Encoding=UTF-8
Type=Application
Name=QtCreator
Comment=QtCreator
NoDsiplay=true
Exec=(Install folder of QT)/Tools/QtCreator/bin/qtcreator %f
Icon=(Install folder of QT)/5.4/Src/qtdoc/doc/images/landing/icon_QtCreator_78x78px.png
Name[en_US]=Qt-Creator
```
Place this file in home .local/share/applications .
Edit a file named “defaults.list” in the same directory . Add the following line.
```
text/qtcreator=Qt-Creator.desktop;
```
open file mimeapps.list and check if the following line is present.
```
application/vnd.nokia.qt.qmakeprofile=qtcreator.desktop
```
if not add it under [added Associations].
Run the following command.
```
sudo update-mime-database /usr/share/mime
```
now Qt has been added to the list of file associations.

## Troubleshooting
- **Qt Creator needs a compiler set up to build**
Follow the instruction from the previous section to configure compiler for Qt Creator.
1. error: g++: Command not found

**Solution:**
```
sudo apt-get install build-essential
```
2. error: GL/gl.h: No such file or directory

**Solution:**
```
sudo apt-get install mesa-common-dev
```

## Build instructions

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



## Usage documentation
Coming Soon!

## Reference
1. Install Qt 5 on Ubuntu

https://wiki.qt.io/Install_Qt_5_on_Ubuntu

2. How to create your first qt program on Ubuntu Linux.

https://www.wikihow.com/Create-Your-First-Qt-Program-on-Ubuntu-Linux
