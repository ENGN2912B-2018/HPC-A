## VTK Installation Guide

Before we install VTK, we need to install CMake first. We followed the CMake installation provided by [here](https://www.vtk.org/Wiki/VTK/Configure_and_Build)

### Download and install CMake

- **Download CMake binaries:**

You can go [here](https://cmake.org/files/) to choose a CMake version. 
**Download and create a folder for CMake, then extract CMake in that folder: **

```
cd $HOME
wget http://www.cmake.org/files/v2.8/cmake-2.8.12.2-Linux-i386.tar.gz
mkdir software
cd software
tar xvfz ../cmake-2.8.12.2-Linux-i386.tar.gz
```

- **Build and install CMake:**

```
cd $HOME
wget http://www.cmake.org/files/v2.8/cmake-2.8.12.2.tar.gz
tar xzf cmake-2.8.12.2.tar.gz
cd cmake-2.8.12.2
./configure --prefix=$HOME/software
make
make install
```

### Download and install VTK

We followed rest of the steps provided by [here](https://kezunlin.me/post/b901735e/).
- **Download VTK source:**

[Available VTK version](https://www.vtk.org/download/)
```
wget https://www.vtk.org/files/release/8.1/VTK-8.1.0.tar.gz

wget https://www.vtk.org/files/release/8.1/VTKData-8.1.0.tar.gz
```

integrate VTK with Qt for a pretty graphical user interface, we need to turn on some options.

- **configure VTK with Qt**

Make a new VTK folder where we want to install VKT and a VTK-build folder. Then move to VTK-build folder and configure VTK.
Firstly, we should run ```cmake-gui ..```. 
Secondly, we add the VTK source file to the path, and assign the build path to VTK-build. 
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
**CMAKE_INSTALL_PREFIX is the path where the VTK libraries and head files finally be created after the installation.**

Then continue pressing configure without any modification until no file in red. When congifurstion is done, press "generate" button.

- **download MD5 VTKData and install VTK**
Extract VTKData-8.1.0.tar.gz and copy MD5 to VTK-build/ExternalData/Objects/MD5
Finally, we go to build folder and run following command to finish the VTK installation:
```
make -j8
sudo make -j8 install
```
The VTK installation is done. 
