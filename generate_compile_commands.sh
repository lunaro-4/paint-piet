#!/usr/bin/env bash

./conan_populate.sh
./run_build_li.sh
cd build_li/build/Release
python3 -m compiledb make && cp compile_commands.json ../../.. 
