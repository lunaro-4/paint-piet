#!/usr/bin/env bash

BUILD_TYPE=$1
./conan_populate.sh
./build.sh $BUILD_TYPE || exit 1
cd build_$BUILD_TYPE/build/Release
python3 -m compiledb make && cp compile_commands.json ../../.. 
