@echo off

if exist build (
    echo Removing existing build directory...
    rmdir /s /q build
)

cmake -S . -B build
cmake --build build
cd build
ctest