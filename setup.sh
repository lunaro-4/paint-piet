#!/usr/bin/env bash

pip install conan
conan profile detect 
conan install . --output-folder=build --build=missing

