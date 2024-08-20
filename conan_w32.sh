#!/usr/bin/env bash

rm -rf build_32w
conan install . --build=missing -s build_type=Release -pr:h=conan-profiles/win-32 -of=build_32w && sed -e '1,$s/conan-release/&-w32/' -i build_32w/build/Release/generators/CMakePresets.json
