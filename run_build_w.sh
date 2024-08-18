#!/usr/bin/env bash

OS=Windows
cmake --preset release-windows
cd build_w/build/Release
source generators/conanbuild.sh
make && cp out/* ../../../out/
