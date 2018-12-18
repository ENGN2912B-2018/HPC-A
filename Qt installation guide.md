# Qt Installation Guide
##  Contents:
[Linux Qt Installation Guide](#linux-qt-installation-guide)

[Windows 10 Qt Installation Guide](#windows-10-qt-installation-guide)

[Associate VTK libraries with Qt](#associate-vtk-libraries-with-qt)

## Linux Qt Installation Guide

Part 1 is a Qt installation guide for Linux machines (Ubuntu 18.04 LTS). The following steps are the installation of Qt 5.10.1. It is a detailed installation guide based on [Qt official tutorial website](https://wiki.qt.io/Install_Qt_5_on_Ubuntu). You can choose any version available on [Qt official release website](http://download.qt.io/official_releases/qt/). The installation steps for different versions of Qt are the same. **However, if you want to install a different version to ours, you should CHECK and CHANGE the number of version in the command in every step.**

- **Download:**

You can visit [Qt official release website](http://download.qt.io/official_releases/qt/) to download Qt package, or just simply download it through command line by executing the following command in your terminal:
```
wget http://download.qt.io/official_releases/qt/5.10/5.10.1/qt-opensource-linux-x64-5.10.1.run
```
When it's done, keep your terminal open and you can move to the installation step.

- **Install:**

In this step, you need to adjust permission first by executing this command: 
```
chmod +x qt-opensource-linux-x64-5.10.1.run
```

Then run the installer:
```
./qt-opensource-linux-x64-5.10.1.run
```
Now you can see a Qt installation window. Sign in or sign up first, and **MAKE SURE your installation directory is where you can read and write files freely**. Then you can continue to install Qt with default settings.

- **Install necessary tools and libraries:**

Make sure that you have essential build tools and libraries in your machine. Execute the following command to install **g++**:
```
sudo apt-get install build-essential
```

Execute the following command to install the **full runtime files** for the generic font configuration library:
```
sudo apt-get install libfontconfig1
```

Execute the following command to install **OpenGL libraries**:
```
sudo apt-get install mesa-common-dev
```

**Note:** Just installing the above-mentioned mesa-common-dev kit is not sufficient for more recent Ubuntu versions. Based on a comment in the Qt forum, an additional package needs installation. Execute following command:
```
sudo apt-get install libglu1-mesa-dev -y
```
Tested with Qt5.3.1 and Ubuntu 14.04 and it solved the problem with missing -lGL.

Now you have completed the installation steps.

- **Check your compiler:**

Check whether g++ has been successfully intalled and can be detected by Qt. Launch Qt Creator, go to Tools > Options and select Kits. You will see a computer icon in front of gcc, showing that gcc now works in your machine and in Qt.


## Windows 10 Qt Installation Guide

Part 2 is a Qt installation guide for Windows 10.

Go to the [Qt official release website](http://download.qt.io/official_releases/qt/), choose a version you want to install and download it. The Qt installation in Win 10 is pretty easy. It just like install any other softwares.

After finishing the installation, you should go to **check whether your compiler will work.** Go to Tools >Options >and select Kits. 

![Qt kit](https://github.com/ENGN2912B-2018/HPC-A/blob/master/images/Qt.png)

At first, in my computer, all these compilers have warning icons in front of them, except the MinGW.nHowever, MinGW cannot compile in my operating system. If you have the same problem, go to [Microsoft website](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk) to download and install Windows 10 SDK. Run **winsdksetup.exe** and install it in the default directory.

![sdk](https://github.com/ENGN2912B-2018/HPC-A/blob/master/images/SDK.png)

After the installation is done, go to the **Installers** folder in the previous install directory, and run all these exe files:

![exe](https://github.com/ENGN2912B-2018/HPC-A/blob/master/images/SDK_exe.png)

Then go back to kits, you will see some of the compilers can work now. You can start to build and compile your own projects now.

## Associate VTK libraries with Qt

If you want to use the third party libraries in Qt, you need to add the include path and the lib path of the thrid party in Qt pro file. For example, in our project we want to use VTK in Qt, so in the pro file, we add these following lines:
```
INCLUDEPATH += \
    /usr/local/include/vtk-8.1 \
    /usr/local
    
LIBS+= -L/usr/local/lib \
-lvtkalglib-8.1 \ru
-lvtkChartsCore-8.1 \
-lvtkCommonColor-8.1 \
-lvtkCommonComputationalGeometry-8.1 \
-lvtkCommonCore-8.1 \
-lvtkCommonDataModel-8.1 \
-lvtkCommonExecutionModel-8.1 \
-lvtkCommonMath-8.1 \
-lvtkCommonMisc-8.1 \
-lvtkCommonSystem-8.1 \
-lvtkCommonTransforms-8.1 \
-lvtkDICOMParser-8.1 \
-lvtkDomainsChemistry-8.1 \
-lvtkDomainsChemistryOpenGL2-8.1 \
-lvtkexoIIc-8.1 \
-lvtkexpat-8.1 \
-lvtkFiltersAMR-8.1 \
-lvtkFiltersCore-8.1 \
-lvtkFiltersExtraction-8.1 \
-lvtkFiltersFlowPaths-8.1 \
-lvtkFiltersGeneral-8.1 \
-lvtkFiltersGeneric-8.1 \
-lvtkFiltersGeometry-8.1 \
-lvtkFiltersHybrid-8.1 \
-lvtkFiltersHyperTree-8.1 \
-lvtkFiltersImaging-8.1 \
-lvtkFiltersModeling-8.1 \
-lvtkFiltersParallel-8.1 \
-lvtkFiltersParallelImaging-8.1 \
-lvtkFiltersPoints-8.1 \
-lvtkFiltersProgrammable-8.1 \
-lvtkFiltersSelection-8.1 \
-lvtkFiltersSMP-8.1 \
-lvtkFiltersSources-8.1 \
-lvtkFiltersStatistics-8.1 \
-lvtkFiltersTexture-8.1 \
-lvtkFiltersTopology-8.1 \
-lvtkFiltersVerdict-8.1 \
-lvtkfreetype-8.1 \
-lvtkGeovisCore-8.1 \
-lvtkgl2ps-8.1 \
-lvtkglew-8.1 \
-lvtkGUISupportQt-8.1 \
-lvtkGUISupportQtSQL-8.1 \
-lvtkhdf5-8.1 \
-lvtkhdf5_hl-8.1 \
-lvtkImagingColor-8.1 \
-lvtkImagingCore-8.1 \
-lvtkImagingFourier-8.1 \
-lvtkImagingGeneral-8.1 \
-lvtkImagingHybrid-8.1 \
-lvtkImagingMath-8.1 \
-lvtkImagingMorphological-8.1 \
-lvtkImagingSources-8.1 \
-lvtkImagingStatistics-8.1 \
-lvtkImagingStencil-8.1 \
-lvtkInfovisCore-8.1 \
-lvtkInfovisLayout-8.1 \
-lvtkInteractionImage-8.1 \
-lvtkInteractionStyle-8.1 \
-lvtkInteractionWidgets-8.1 \
-lvtkIOAMR-8.1 \
-lvtkIOCore-8.1 \
-lvtkIOEnSight-8.1 \
-lvtkIOExodus-8.1 \
-lvtkIOExport-8.1 \
-lvtkIOExportOpenGL2-8.1 \
-lvtkIOGeometry-8.1 \
-lvtkIOImage-8.1 \
-lvtkIOImport-8.1 \
-lvtkIOInfovis-8.1 \
-lvtkIOLegacy-8.1 \
-lvtkIOLSDyna-8.1 \
-lvtkIOMINC-8.1 \
-lvtkIOMovie-8.1 \
-lvtkIONetCDF-8.1 \
-lvtkIOParallel-8.1 \
-lvtkIOParallelXML-8.1 \
-lvtkIOPLY-8.1 \
-lvtkIOSQL-8.1 \
-lvtkIOTecplotTable-8.1 \
-lvtkIOVideo-8.1 \
-lvtkIOXML-8.1 \
-lvtkIOXMLParser-8.1 \
-lvtkjpeg-8.1 \
-lvtkjsoncpp-8.1 \
-lvtklibharu-8.1 \
-lvtklibxml2-8.1 \
-lvtklz4-8.1 \
-lvtkmetaio-8.1 \
-lvtkNetCDF-8.1 \
-lvtknetcdfcpp-8.1 \
-lvtkoggtheora-8.1 \
-lvtkParallelCore-8.1 \
-lvtkpng-8.1 \
-lvtkproj4-8.1 \
-lvtkRenderingAnnotation-8.1 \
-lvtkRenderingContext2D-8.1 \
-lvtkRenderingContextOpenGL2-8.1 \
-lvtkRenderingCore-8.1 \
-lvtkRenderingFreeType-8.1 \
-lvtkRenderingGL2PSOpenGL2-8.1 \
-lvtkRenderingImage-8.1 \
-lvtkRenderingLabel-8.1 \
-lvtkRenderingLOD-8.1 \
-lvtkRenderingOpenGL2-8.1 \
-lvtkRenderingQt-8.1 \
-lvtkRenderingVolume-8.1 \
-lvtkRenderingVolumeOpenGL2-8.1 \
-lvtksqlite-8.1 \
-lvtksys-8.1 \
-lvtkTestingGenericBridge-8.1 \
-lvtkTestingIOSQL-8.1 \
-lvtkTestingRendering-8.1 \
-lvtktiff-8.1 \
-lvtkverdict-8.1 \
-lvtkViewsContext2D-8.1 \
-lvtkViewsCore-8.1 \
-lvtkViewsInfovis-8.1 \
-lvtkViewsQt-8.1 \
-lvtkzlib-8.1     
```

Now, all the VTK classes and libraries can work in Qt.


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
