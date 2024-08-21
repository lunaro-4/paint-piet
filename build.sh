#!/usr/bin/env bash


if [ $# -lt 1 ]
then 
	echo "You should specify build type!"
	echo "Vaible build types are: \"linux\", \"windows\""
	exit 1
fi

if [ $1 = "linux" ]
then
	KEYWORD="linux"
elif [ $1 = "windows" ]
then
	KEYWORD="windows"
else
	echo "Invalid build type!"
	echo "Vaible build types are: \"linux\", \"windows\""
	exit 1
fi



BUILD_PATH="build_$KEYWORD/build/Release"


source $BUILD_PATH/generators/conanbuild.sh
BUILD_TYPE=$2 cmake --preset release-$KEYWORD
cd $BUILD_PATH
rm -rf out/*
BUILD_TYPE=$2 make && cp out/* ../../../out/
