#!/bin/bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/home/leonardo/.vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
