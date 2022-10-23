# install mingw
echo "Installing Mingw"
Invoke-WebRequest "https://github.com/brechtsanders/winlibs_mingw/releases/download/12.1.0-14.0.4-10.0.0-ucrt-r2/winlibs-x86_64-posix-seh-gcc-12.1.0-llvm-14.0.4-mingw-w64ucrt-10.0.0-r2.zip" -OutFile mingw.zip
Expand-Archive mingw.zip -DestinationPath .
rm mingw.zip
mv mingw* mingw
mv mingw "C:/Program Files/mingw"

# install cmake
echo "Installing CMake"
Invoke-WebRequest "https://github.com/Kitware/CMake/releases/download/v3.24.0-rc2/cmake-3.24.0-rc2-windows-x86_64.zip" -OutFile cmake.zip
Expand-Archive cmake.zip -DestinationPath .
rm cmake.zip
mv cmake* cmake
mv cmake "C:/Program Files/cmake"

# install boost
echo "Installing Boost"
Invoke-WebRequest "https://boostorg.jfrog.io/artifactory/main/release/1.79.0/source/boost_1_79_0.zip" -OutFile boost.zip
Expand-Archive boost.zip -DestinationPath .
rm boost.zip
mv boost* boost
mv boost "C:/Program Files/boost"

# setting path
[Environment]::SetEnvironmentVariable("Path", $env:Path + ";C:\Program Files\cmake\bin;C:\Program Files\mingw\bin", "Machine")
$env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine")