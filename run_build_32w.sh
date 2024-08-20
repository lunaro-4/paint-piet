#!/usr/bin/env bash

BUILD_PATH="build_32w/build/Release"
OS=Windows
source $BUILD_PATH/generators/conanbuild.sh
cmake --preset release-windows
cd $BUILD_PATH
make && cp out/* ../../../out/
