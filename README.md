## Table of contents
* [Introduction](#general-info)
* [Technologies](#technologies)
* [Prerequisites](#Prerequisites)
* [Setup](#setup)
* [Deployment](#Deployment)

## Introduction
The Library-Management-System is a software system with a Graphical User Interface to provide the libraries with a helpfull software system that has features like: registration system, publishing books system, borrowing system and searching and payment methods.

## Technologies
Project is created with:
*	C++
*	QT Framework
*	CSS3
*	SQLite

## Prerequisites
*	Windows 7 (32-bit or 64-bit) or higher ,Linux Ubuntu 16.04 LTS or higher.
*	256 MB of RAM
*	500 MHz CPU
*	OpenGL ES 2.0 support 
*	Qt C++ Framework Installed
*	MinGW Compiler

## Setup
*	Download and install Qt C++ Framework with MinGW Compiler https://www.qt.io/download.
*	git clone https://github.com/AmrElsersy/Library-Management-System.git .
*	configure the project from the .pro file included.
*	Run the code

## Deployment
*	To get the all the dll files and the dependencies of the project use windeployqt tool for windows or linuxdeployqt for Ubuntu.
*	Open the QTDIR/bin path and run qtenv2.bat to initialize the windeployqt environment.
* Run the Project in Release Mode to get the executable from PROJECT_DIR/build/release/PROJECT.exe
* Run $ windeployqt path_to_project/PROJECT.exe
* Copy the icon folder included in the project in the "/../../path_to_project" path
* Run the executable deployed application
```
$ cd QTDIR/bin
$ qtenv2.bat
$ windeployqt PROJECT_DIR/build/release/PROJECT.exe
$ cd PROJECT_DIR/build/release
$ ./PROJECT.exe
```


