# Mde4cpp-API and -Dashboard

This is an REST-API inclusive Dashboard for the MDE4CPP-Project.

## Preparations
Download [Boost](https://www.boost.org/users/download/) and make sure to install it in :
``C:/Program Files/``

## Building
1.) configure the build system: ``cmake -B build -S .``

2.) build the project: ``cmake --build build``

3.) run the project: ``./build/Mde4cppApi.exe``

## Bugs??
Add the following flags to the ecore CmakeList: ``-std=c++0x -Wno-narrowing``