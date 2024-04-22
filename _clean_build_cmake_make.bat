echo off

echo Cleaning "build" directory...
rmdir /S /Q build
echo Making "build" directory...
mkdir build

echo Changing directory to "build"
cd build
echo Running CMake
cmake -G "MSYS Makefiles" ..
echo Running Make
make

set /p DUMMY=Done. Press ENTER to exit...