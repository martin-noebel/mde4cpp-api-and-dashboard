# open a powershell as admin and type in: "set-executionpolicy remotesigned"
# then run the script with: ".\script.ps1"
# install chocolatey
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
# install java 17
choco install openjdk17
# install mingw-64
choco install mingw
# install gradle
choco install gradle
# install cmake
choco install cmake
# install git
choco install git
# install eclipse (TODO: Modelling Framework)
choco install eclipse --version=4.21
# install Acceleo
eclipse.exe -application org.eclipse.equinox.p2.director -repository https://download.eclipse.org/acceleo/updates/releases/3.7/R202102190929/ -destination C:/Eclipse
# install amalgamation
eclipse.exe -application org.eclipse.equinox.p2.director -repository https://download.eclipse.org/modeling/amalgam/updates/releases/1.12.1/capella/ -destination C:/Eclipse
# install sirius
eclipse.exe -application org.eclipse.equinox.p2.director -repository https://download.eclipse.org/sirius/updates/releases/6.6.0/2020-09/ -destination C:/Eclipse
# install uml designer
eclipse.exe -application org.eclipse.equinox.p2.director -repository https://sse.tu-ilmenau.de/umldesigner-update/ -destination C:/Eclipse
# install mde4cpp
md 'C:\MDE4CPP\'
cd 'C:\MDE4CPP\'
git clone https://github.com/MDE4CPP/MDE4CPP.git
# setting environment variables (TODO: Gradle)
[Environment]::SetEnvironmentVariable("CLASSPATH", "C:\Eclipse\plugins", "Machine")
[Environment]::SetEnvironmentVariable("COMPILER_DELIVERY_NAME", "x86_64-w64-mingw32", "Machine")
[Environment]::SetEnvironmentVariable("MDE4CPP_HOME", "C:\MDE4CPP", "Machine")
[Environment]::SetEnvironmentVariable("MDE4CPP_ECLIPSE_HOME", "C:\Eclipse", "Machine")<
[Environment]::SetEnvironmentVariable("CMAKE_HOME", "C:\CMake", "Machine")
[Environment]::SetEnvironmentVariable("COMPILER_HOME", "C:\MinGW-w64", "Machine")
[Environment]::SetEnvironmentVariable("JAVA_HOME", "C:\Program Files\OpenJDK\jdk-17.0.2", "Machine")
[Environment]::SetEnvironmentVariable("COMPILER_VERSION", "8.1.0", "Machine")
[Environment]::SetEnvironmentVariable("Path", $env:Path + ";C:\MDE4CPP\application\tools;C:\CMake\bin;C:\MinGW-w64\bin;C:\Program Files\OpenJDK\jdk-17.0.2\bin", "Machine")
# build the project
gradlew
gradlew buildAll


