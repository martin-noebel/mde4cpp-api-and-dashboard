# MDE4CPP-API

This is an REST-API inclusive Dashboard for the MDE4CPP-Project.

## Building
1.) create the build directory: ``mkdir build``

2.) change into the build directory: ``cd build``

3.) make the project: ``cmake ..``

4.) build the project: ``cmake --build .``

5.) run the project: ``./Mde4cppApi.exe``

## Bugs??
Add the following flags to the ecore CmakeList: ``-std=c++0x -Wno-narrowing``