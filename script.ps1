# open a powershell as admin and type in: "set-executionpolicy remotesigned"
# then run the script with: "./script.ps1"
# install chocolatey
echo "Installing Chocolatey"
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
# create a directory under the user folder
echo "Init MDE4CPP directory"
mkdir $env:USERPROFILE\MDE4CPP
cd $env:USERPROFILE\MDE4CPP
# install java
echo "Installing Java"
Invoke-WebRequest "https://download.oracle.com/java/17/latest/jdk-17_windows-x64_bin.zip" -OutFile java.zip
Expand-Archive java.zip -DestinationPath .
rm java.zip
mv jdk* java
# install mingw
echo "Installing Mingw"
Invoke-WebRequest "https://github.com/brechtsanders/winlibs_mingw/releases/download/12.1.0-14.0.4-10.0.0-ucrt-r2/winlibs-x86_64-posix-seh-gcc-12.1.0-llvm-14.0.4-mingw-w64ucrt-10.0.0-r2.zip" -OutFile mingw.zip
Expand-Archive mingw.zip -DestinationPath .
rm mingw.zip
mv mingw* mingw
# install gradle
echo "Installing Gradle"
Invoke-WebRequest "https://services.gradle.org/distributions/gradle-7.4.2-bin.zip" -OutFile gradle.zip
Expand-Archive gradle.zip -DestinationPath .
rm gradle.zip
mv gradle* gradle
# install cmake
echo "Installing CMake"
Invoke-WebRequest "https://github.com/Kitware/CMake/releases/download/v3.24.0-rc2/cmake-3.24.0-rc2-windows-x86_64.zip" -OutFile cmake.zip
Expand-Archive cmake.zip -DestinationPath .
rm cmake.zip
mv cmake* cmake
# set path variable and refresh it
echo "Setting path variable"
[Environment]::SetEnvironmentVariable("Path", $env:Path + "$env:USERPROFILE\MDE4CPP\cmake\bin;$env:USERPROFILE\MDE4CPP\gradle\bin;$env:USERPROFILE\MDE4CPP\mingw\bin;$env:USERPROFILE\MDE4CPP\java\bin;", "Machine")
$env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine")
# install eclipse modeling
echo "Installing Eclipse Modeling"
Invoke-WebRequest "https://www.eclipse.org/downloads/download.php?file=/technology/epp/downloads/release/2021-12/R/eclipse-modeling-2021-12-R-win32-x86_64.zip&r=1" -OutFile eclipse.zip
Expand-Archive eclipse.zip -DestinationPath .
rm eclipse.zip
# wait for the user to install all eclipse repositories
echo "Please install all repositories from: https://github.com/MDE4CPP/UML-Designer"
./eclipse/eclipse.exe
Write-Host -NoNewLine 'Press any key to continue if you installed all repositories ...';
$null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown');
# install git
echo "Installing Git"
choco install git
# clone MDE4CPP
echo "Cloning MDE4CPP repository"
git clone https://github.com/MDE4CPP/MDE4CPP.git
mv MDE4CPP src
# set environment variables and refresh them
echo "Setting environment variables"
$env:ChocolateyInstall = Convert-Path "$((Get-Command choco).Path)\..\.."
Import-Module "$env:ChocolateyInstall\helpers\chocolateyProfile.psm1"
[Environment]::SetEnvironmentVariable("JAVA_HOME", "$env:USERPROFILE\MDE4CPP\java", "Machine")
[Environment]::SetEnvironmentVariable("COMPILER_HOME", "$env:USERPROFILE\MDE4CPP\mingw", "Machine")
[Environment]::SetEnvironmentVariable("GRADLE_HOME", "$env:USERPROFILE\MDE4CPP\gradle", "Machine")
[Environment]::SetEnvironmentVariable("MDE4CPP_HOME", "$env:USERPROFILE\MDE4CPP\src", "Machine")
[Environment]::SetEnvironmentVariable("MDE4CPP_ECLIPSE_HOME", "$env:USERPROFILE\MDE4CPP\eclipse", "Machine")
[Environment]::SetEnvironmentVariable("CMAKE_HOME", "$env:USERPROFILE\MDE4CPP\cmake", "Machine")
[Environment]::SetEnvironmentVariable("GRADLE_OPTS", "-Dorg.gradle.parallel=true", "Machine")
[Environment]::SetEnvironmentVariable("ORG_GRADLE_PROJECT_WORKER", "1", "Machine")
[Environment]::SetEnvironmentVariable("ORG_GRADLE_PROJECT_RELEASE", "1", "Machine")
[Environment]::SetEnvironmentVariable("ORG_GRADLE_PROJECT_DEBUG", "1", "Machine")
[Environment]::SetEnvironmentVariable("ORG_GRADLE_PROJECT_DEBUG_MESSAGE_FUML", "0", "Machine")
[Environment]::SetEnvironmentVariable("CLASSPATH", "$env:USERPROFILE\MDE4CPP\eclipse\plugins", "Machine")
[Environment]::SetEnvironmentVariable("COMPILER_DELIVERY_NAME", "x86_64-w64-mingw32", "Machine")
[Environment]::SetEnvironmentVariable("COMPILER_VERSION", "8.1.0", "Machine")
refreshenv
# build the project
echo "Building the project"
cd src
gradle
gradle buildAll
exit