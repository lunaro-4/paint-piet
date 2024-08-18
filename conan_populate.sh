#!/usr/bin/env bash

rm -rf build_li build_w
conan install . --build=missing -s build_type=Release -pr:h=conan-profiles/linux -of=build_li && sed -e '1,$s/conan-release/&-linux/' -i build_li/build/Release/generators/CMakePresets.json
conan install . --build=missing -s build_type=Release -pr:h=conan-profiles/windows -of=build_w && sed -e '1,$s/conan-release/&-windows/' -i build_w/build/Release/generators/CMakePresets.json
