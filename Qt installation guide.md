## Qt Installation Guide

For now Qt has be installed in a Windows operating system. In order to run the whole program on CCV, GUI will be developed in a Linux environment. The version of Qt installed in Windows now is 5.11.2. We will install Qt 5.10.1 in Ubuntu.

**NOTE: The following steps just the installation instruction from the [official website](https://wiki.qt.io/Install_Qt_5_on_Ubuntu). Please check the version of Qt you want to install before the next steps.**

- **Download:**

You can visit Qt officcial website to download Qt in all kinds of operating system, or the Ubuntu installation file can be also downloaded through the command line using wget.
```
wget http://download.qt.io/official_releases/qt/5.10/5.10.1/qt-opensource-linux-x64-5.10.1.run
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
