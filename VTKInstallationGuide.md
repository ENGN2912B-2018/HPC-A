# VTK Installation Guide with CMake
**(Note: Start an issue on our [Issues page](https://github.com/ENGN2912B-2018/HPC-A/issues) if you are having troubles in building the VTK library!)**  

VTK provides two types of installation: binary installation which allow users to build simple applications directly using Tcl scripts and pre-compiled VTK executables, and source codes installation which enables users to build classes and applications using C++, Java, Python and Tcl. In this page we will introduce the source codes installation of VTK using CMake in multiple platforms.  
## Contents
[Installing VTK on CCV](#installing-vtk-on-ccv)  
[Installing VTK on Ubuntu 18.04 LTS](#installing-vtk-on-ubuntu-1804-lts)  
[Installing VTK on Windows 10](#installing-vtk-on-windows-10)
## Installing VTK on Brown CCV(RedHat 7)

VTK and CMake is already installed on CCV. All we need to do is to activate the modules by running the following commands:

```
module load vtk/8.1.0
module load cmake/3.8.0
```
Then the CMake and VTK are both good to use.  

**Note:**  Sometimes the version of those libraries may change due to CCV's package update, and you can use ``module avail <package>`` to check the available versions of a certain package.

## Installing VTK on Ubuntu 18.04 LTS
### Installing CMake
In Ubuntu 18.04 you can use the `apt-get` utilities to achieve and install CMake. The command should be run under root account:
```
sudo apt-get install cmake
sudo apt-get install cmake-qt-gui
```
Following the instructions of `apt-get`, you can install the CMake software in your system.

### Configuring VTK Installation
#### Download the Source Code
You can download the VTK source code files directly in the [VTK Download Page](https://www.vtk.org/download/), or use the following commands:
```
wget https://www.vtk.org/files/release/8.1/VTK-8.1.2.tar.gz
```
Extract the `.tar.gz` files directly in the graphical user interface or in the terminal:
```
tar xvzf VTK-8.1.2.tar.gz -C <Your directory>
```
#### Configuring VTK using CMake
For simplicity it is recommended to use the `cmake-qt-gui` tools to configure the VTK compilation.  
In CMake, you can specify the directories for source code and binaries. Then you should click on the "Configure" button.
![CMake Configuration](https://upload-images.jianshu.io/upload_images/315072-42e2d7d3b5a1e7f8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
In the pop-up window, you should choose "Unix Makefiles" as the generator for VTK.
![Specify the generator](https://upload-images.jianshu.io/upload_images/315072-b0d47257023eccc3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
After clicking the "Finish" button, CMake will show all the variables and their values which you can modify and use for compiling VTK. You should click on the "Advanced" checkbox to see a full list of these variables. The variables that are marked as red indicate that the variables are generated during the previous configuration.  
Some important variables values to build VTK for this project are listed as follow:
- `BUILD_DOCUMENTATION`: Under some systems this value may be set to true at default. This indicates that a built-in documentation will be generated when building VTK. Building the documentation requires some extra external libraries that might have not been installed in your system, so it is recommended to set this value to false.
- `BUILD_EXAMPLES` and `BUILD_TESTING`: These two values are set to true at default. This determines that some example and testing executables will be built. This might be useful for VTK learners, but you can set it to false for saving storage space if you only need to compile and run a VTK application.
- `BUILD_SHARED_LIBS`: Shared libraries will be built if you set this value to true. In order cases, static libraries will be built, and the VTK applications will be self-contained.
- `VTK_Group_Qt`: This value should be set as false since the graphical user interface based on Qt is not supported by our project in Linux.

Once you configured all the variables, you can click on the "Configure" button until no variables are marked as red. Then you should click "Generate" button to generate the Unix makefiles.
![Generate the makefiles](https://upload-images.jianshu.io/upload_images/315072-a0253d071f854aa9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
#### Compile and Install VTK  
Under the directory you specify for the binaries, simply run:
```
make
```
And the VTK should compile. You should run ``make install`` to copy all the files you need to compile and run VTK in to a directory that other users can share.


## Installing VTK on Windows 10
For configuring VTK on Windows 10, please make sure you have already followed the [GUI Set Up Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/master/GUIGuide.md) and installed Qt in your computer. [Visual Studio 2017](https://visualstudio.microsoft.com/vs/) is also required as the generator to build the VTK library.
### Installing CMake
A recommended method to obtain CMake in Windows 10 is downloading the `.msi` installer file from the [CMake Download Page](https://cmake.org/download/). You can choose a preferred version of CMake for your system in the website. The CMake version we used to compile our project on Windows is 3.12.4.
![CMake installer on Windows](https://upload-images.jianshu.io/upload_images/315072-e485de92624ae2e0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
You can follow the instructions of CMake installer to install CMake in your Windows machine.
### Download the Source Code
It is recommended that VTK source code files should be downloaded directly in the [VTK Download Page](https://www.vtk.org/download/). You can unzip the `.zip` file and obtain the source code.
### Configuring a Qt-integrated VTK
You can launch the CMake(cmake-gui) application and configure the VTK compilation.
In CMake, you can specify the directories for source code and binaries. Then you should click on the "Configure" button.
![CMake Configuration](https://upload-images.jianshu.io/upload_images/315072-8f7f0c49d54fd62d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
In the pop-up window, you should choose "Visual Studio 15 2017 Win64" as the generator for VTK if you are using a 64-bit computer or "Visual Studio 15 2017" if you are using a 32-bit computer.
![Specify the generator](https://upload-images.jianshu.io/upload_images/315072-fb83b67c89f38b44.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
After clicking the "Finish" button, CMake will show all the variables and their values which you can modify and use for compiling VTK. You should click on the "Advanced" checkbox to see a full list of these variables. The variables that are marked as red indicate that the variables are generated during the previous configuration.  
Some important variables values to build VTK for this project are listed as follow:
- `BUILD_DOCUMENTATION`: Under some systems this value may be set to true at default. This indicates that a built-in documentation will be generated when building VTK. Building the documentation requires some extra external libraries that might have not been installed in your system, so it is recommended to set this value to false.
- `BUILD_EXAMPLES` and `BUILD_TESTING`: These two values are set to true at default. This determines that some example and testing executables will be built. This might be useful for VTK learners, but you can set it to false for saving storage space if you only need to compile and run a VTK application.
- `BUILD_SHARED_LIBS`: Shared libraries will be built if you set this value to true. In order cases, static libraries will be built, and the VTK applications will be self-contained.
- `VTK_Group_Qt`: This value should be set as true since we need to provide Qt-support for the program.

![Error Window](https://upload-images.jianshu.io/upload_images/315072-8ea28bb9dc23bad4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
After setting up those value, you can click on the "Configure" button. Then an error window may pop up saying that the project files may be invalid. This is expected if you set some Qt-relate configurations without indicating the directory of Qt.  
Now a new variable called `Qt5_DIR` may appear in the values and be marked as red. You should set the value of this variable to the `cmake` path under your Qt directory, for example: `C:\Qt\5.11.2\msvc2017_64\lib\cmake`. Note that the `msvc2017_64` path, this directory should be compatible to your current generator of CMake.   
Once you configured all the variables, you can click on the "Configure" button until no variables are marked as red. Then you should click "Generate" button to generate the project files for Visual Studio.
### Building VTK
You can open the solution file in Visual Studio by clicking on the "Open Project" button in CMake.   
Choose `Build->Configuration Manager`, and you can set up the configurations for building VTK. It is recommended to change the "Acitve solution configuration" selection to `Release` mode.
![Configuration Manager of Visual Studio](https://upload-images.jianshu.io/upload_images/315072-b84d78a1a25ce53b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)  
Then you can choose `Build->Build Solution` or press `Ctrl+Shift+B` shortcut. The VTK should compile. It may take a long time(nearly an hour on a Core i7-8550U laptop with 16 GiB memory) to compile.  
## References
VTK provides a comprehensive [User Guide](https://www.kitware.com/products/books/VTKUsersGuide.pdf), which includes a step-by-step instruction on installing VTK. We actually followed this user guide to set up the environment for our project development.  
