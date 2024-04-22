echo off
echo Changing directory to "build"
cd build
echo Running CMake
cmake -G "MSYS Makefiles" ..
echo Running Make
make
set /p DUMMY=Done. Press ENTER to exit...