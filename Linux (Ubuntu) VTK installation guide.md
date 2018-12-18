## Linux (Ubuntu) VTK Installation Guide

Before you install VTK, you need to install CMake first. Our guide is based on [VTK wiki](https://www.vtk.org/Wiki/VTK/Configure_and_Build).

### Download and install CMake

- **Download CMake binaries:**

You can go to [CMake official website](https://cmake.org/files/) to choose a CMake version. 

**Download and create a folder for CMake, then extract CMake in that folder: **

Open your terminal and change to your HOMR directory:

```
cd $HOME
```
Download CMake source code by executing the following command, but you need to **change the version if you are installing a different version from ours:**

```
wget http://www.cmake.org/files/v2.8/cmake-2.8.12.2-Linux-i386.tar.gz
```

make a new directory, which name is "software", to unzip the CMake package,and enter that directory:

```
mkdir software
cd software
```
Now you are in software folder, unzip the package:

```
tar xvfz ../cmake-2.8.12.2-Linux-i386.tar.gz
```

- **Build and install CMake:**

Execute these commands in your terminal line by line, and wait for the installation.
```
cd $HOME
wget http://www.cmake.org/files/v2.8/cmake-2.8.12.2.tar.gz
tar xzf cmake-2.8.12.2.tar.gz
cd cmake-2.8.12.2
./configure --prefix=$HOME/software
make
make install
```

When it's done, you have finished the installation of CMake. You can step to install VTK.

### Download and install VTK

Our VTK installation is based on [this tutorial](https://kezunlin.me/post/b901735e/).

- **Download VTK source:**

You can choose one of these [Available VTK versions](https://www.vtk.org/download/) to install. Here we install VTK 8.1.0. The installation steps are the same for different version. **CHECK and CHANGE your VTK version** in every command if your VTK version is different from ours.

Open your terminal. Download VTK source code and data by executing these two commands:

```
wget https://www.vtk.org/files/release/8.1/VTK-8.1.0.tar.gz

wget https://www.vtk.org/files/release/8.1/VTKData-8.1.0.tar.gz
```


- **configure VTK with Qt**
Because in our program, we need to use VTK in Qt, so during the VTK installation, you should turn on some settings to let VTK support Qt.
Make a new VTK folder where we want to install VKT and a VTK-build folder. **The loaction of the folder should be where you can read and write files freely.** Then move to VTK-build folder and configure VTK.
Firstly, you should run ```cmake-gui ..``` to open CMake GUI. 

Secondly, you need to add the path of VTK source file to "where is the source code", and assign the path of "where to build the library" to VTK-build folder. 

![alt text](https://github.com/ENGN2912B-2018/HPC-A/blob/master/images/CMake.png)

At this time, the cmake gui should be blank. After we press the "configure" button, many files will come out in red. 
Then configure VTK with the following option:

```
VTK_Group_Qt       ON
VTK_QT_VERSION     5 # default

VTK_RENDERING_BACKEND OpenGL2 # default
BUILD_SHARED_LIBS  ON
CMAKE_BUILD_TYPE   build
CMAKE_INSTALL_PREFIX /usr/local
```

**CMAKE_INSTALL_PREFIX is the path where the VTK libraries and header files finally be created after the installation. This path should also be read and written freely.**

Then continue pressing configure button without any modification until no file in red. When congifurstion is done, press "generate" button.

- **download MD5 VTKData and install VTK**
Extract VTKData-8.1.0.tar.gz and copy MD5 to VTK-build/ExternalData/Objects/MD5
Finally, you should go to VTK-build folder and run following command to finish the VTK installation:
```
make -j8
sudo make -j8 install
```
When all the things are done, the VTK installation is done. 
