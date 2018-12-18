# GUI Set Up Guide

## Build a Qt project with Qt Creator
We need to install Qt and VTK. The detailed installation guides are here: 
**For Linux users**

[Linux (Ubuntu) Qt Installation Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/gui/Qt%20installation%20guide.md)
[Linux (Ubuntu) VTK Installation Guide](https://github.com/ENGN2912B-2018/HPC-A/blob/gui/VTK%20installation%20guide.md)

**For Windows users**

## Build a Qt project in Linux
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
