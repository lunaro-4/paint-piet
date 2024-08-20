#!/usr/bin/env bash

OS=Windows
cmake --preset release-w32
cd build_32w/build/Release
source generators/conanbuild.sh
make && cp out/* ../../../out/
