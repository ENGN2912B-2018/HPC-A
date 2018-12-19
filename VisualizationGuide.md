# Visualization Set Up Guide
This guide is going to help you build a self-contained command-line tool of visualization. Before you start building, make sure you have already installed the required libraries following the [instructions](https://github.com/ENGN2912B-2018/HPC-A/blob/master/VTKInstallationGuide.md) or sufficed the [system requirements](https://github.com/ENGN2912B-2018/HPC-A#operating-systems-and-software-compilerlibrary-versions-tested).  
## Build instructions
### Linux Systems (Ubuntu 18.04 or RedHat 7/Brown CCV)

#### Fetching the source code
You can clone this repository into your directory in the terminal using ``git clone https://github.com/ENGN2912B-2018/HPC-A.git``.
#### Configuring using CMake
Switch to visualization directory: ``cd HPC-A/visualization``  
Create a build directory:  
```
mkdir build
cd build
```
Configure and generate CMake: ``cmake ..``  
#### Building the project
Simply run:  ``make``

### Windows 10
#### Fetching the source code
You can directly download the source code or clone this repository into your directory in the Git bash using ``git clone https://github.com/ENGN2912B-2018/HPC-A.git``.
#### Configuring using CMake
Under the `HPC-A/visualization` path, you can create a build folder to store the binaries. It is recommended to use CMake to configure the compilation setting in Windows. After specifying the directories for source code and binaries, you should click on the "Configure" button.
In the pop-up window, you should choose "Visual Studio 15 2017 Win64" as the generator for VTK if you are using a 64-bit computer or "Visual Studio 15 2017" if you are using a 32-bit computer.
![Specify the generator](https://upload-images.jianshu.io/upload_images/315072-fb83b67c89f38b44.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
After clicking the "Finish" button, CMake will show all the variables and their values which you can modify and use for compiling the project. An error window may also pop up saying that the project files may be invalid. This is expected since you did not specify the VTK directory that the project requires.  
![Error Window](https://upload-images.jianshu.io/upload_images/315072-5e8ae75857d78a3c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
Now a new variable called `VTK_DIR` may appear in the values and be marked as red. You should set the value of this variable to the path where you build your VTK library, for example: `C:/Users/Angio/Downloads/VTK/VTK-8.1.2/VTK-8.1.2-build`.   
Once you configured all the variables, you can click on the "Configure" button until no variables are marked as red. Then you should click "Generate" button to generate the project files for Visual Studio.
#### Building the project
You can open the solution file in Visual Studio by clicking on the "Open Project" button in CMake.   
Choose `Build->Configuration Manager`, and you can set up the configurations for building the project. It is recommended to change the "Acitve solution configuration" selection to `Release` mode.
![Configuration Manager of Visual Studio](https://upload-images.jianshu.io/upload_images/315072-d8ab4efa18b4ada7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
Then you can choose `Build->Build Solution` or press `Ctrl+Shift+B` shortcut. Then the project should compile.

## Run the Program
### Linux Systems (Ubuntu 18.04 or RedHat 7/Brown CCV)
In the `build/` directory, simply run `./mainVisualizer`.
### Windows 10
#### Executable
You can run the program directly by double-clicking the `mainVisualizer.exe` file under the `build/Release` path.
#### Visual Studio Debugging Tool
It is reported that the `mainVisualizer.exe` program is having some freezing issues if it is being directly run. If this also happens to your system, you can try to avoid it by running the program using the Visual Studio Debug Tool.  
In order to run the program in debug mode, you should first launch Visual Studio and set the  `mainVisualizer` as a startup project. In the Solution Explorer, you need to right click the `mainVisualizer` project, then click "Set as StartUp Project". Then you can run the program in debug mode by choosing `Debug->Start Debugging` or pressing the `F5` shortcut.
