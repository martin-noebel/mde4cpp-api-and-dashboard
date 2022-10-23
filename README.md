# Mde4cpp-API and -Dashboard

This is an REST-API inclusive Dashboard for the MDE4CPP-Project. It uses an library example for a prototype implementation. All necessary files and dlls are included in the project.

## Preparations
Install all needed tools (CMake, Mingw) and necessary libraries (Boost).

1.) open a powershell as admin and type in:
```powershell
set-executionpolicy remotesigned
```

2.) execute the script with:
```powershell
./init.ps1
```

3.) check cmake and mingw version:
```powershell
gcc --version
cmake --version
```

## Building
Build and execute the project and access it at [localhost:8080](http://localhost:8080).

1.) configure the build system:
```powershell
cmake -G "MinGW Makefiles" -B build -S .
```

2.) build the project:
```powershell
cmake --build build
```

3.) run the project:
```powershell
./build/Mde4cppApi.exe
```