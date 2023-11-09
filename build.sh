#!/bin/bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=~/.local/share/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
