#!/bin/bash

# Check if the build directory exists
if [ -d "build" ]; then
  echo "Removing existing build directory..."
  rm -rf "build"
fi

cmake -S . -B build
cmake --build build
cd build
ctest