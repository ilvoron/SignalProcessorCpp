echo off

echo Cleaning "build" directory...
rmdir /S /Q build
echo Making "build" directory...
mkdir build

echo Changing directory to "build"
cd build
echo Running CMake
cmake -G "MinGW Makefiles" ..
echo Running Make
mingw32-make

set /p DUMMY=Done. Press ENTER to exit...