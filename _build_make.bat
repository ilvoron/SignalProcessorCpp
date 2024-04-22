echo off
echo Changing directory to "build"
cd build
echo Running Make
set MAKE=wsl -e make
%MAKE%
set /p DUMMY=Done. Press ENTER to exit...