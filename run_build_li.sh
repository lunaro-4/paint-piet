#!/usr/bin/env bash

BUILD_PATH="build_li/build/Release"

source $BUILD_PATH/generators/conanbuild.sh
cmake --preset release-linux
cd $BUILD_PATH
make && cp out/* ../../../out/
