#!/usr/bin/env bash

KEYWORD="linux"
rm -rf build_$KEYWORD
conan install . --build=missing -s build_type=Release -pr:h=conan-profiles/linux -of=build_$KEYWORD && sed -e "1,\$s/conan-release/&-$KEYWORD/" -i build_$KEYWORD/build/Release/generators/CMakePresets.json
KEYWORD="windows"
rm -rf build_$KEYWORD
conan install . --build=missing -s build_type=Release -pr:h=conan-profiles/windows -of=build_$KEYWORD && sed -e "1,\$s/conan-release/&-$KEYWORD/" -i build_$KEYWORD/build/Release/generators/CMakePresets.json
