#!/usr/bin/env bash

cmake --preset release-linux
cd build_li/build/Release
source generators/conanbuild.sh
make && cp out/* ../../../out/
