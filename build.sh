#!/usr/bin/env bash

function valid_os() {
	FOUND=0;
	for i in linux windows
	do
		if [ $1 = $i ]
		then 
			FOUND=1
			return 1
		fi
	done
	return 0
}

function is_valid_argumtn_value() {
	if [ ${1:0:1} = '-' ]; then
		return 0;
	fi
	return 1
}

UI_FILE_PATH="src/gui/paint-piet.ui"


DO_CMAKE=1;
OS_TARGET=

while :; do
    case $1 in
        -t|--target) 
			if [ "$2" ]; then 
				OS_TARGET="$2"
				shift
			else
				die '-t or --target requires operating system name '
			fi
			;;
        -m|--make) 
			is_valid_argumtn_value $2
			if [ $? -eq 0 ]; then
				die 'invalid argument for --make'
			fi
			MAKE_TARGET=$2
			shift
			;;
        -s|--skip-cmake) 
			DO_CMAKE=0
			;;
		-l|--libraries-included)
			BUILD_TARGET="MONO"
			shift
			;;
		-u|--ui-trmplate)
			is_valid_argumtn_value $2
			if [ $? -eq 0 ]; then
				die 'invalid argument for --ui-template'
			fi
			UI_FILE_PATH=$2
			shift
			;;
        *) break
    esac
    shift
done


if [ -z "$OS_TARGET" ]
then 
	echo "You should specify build type!"
	echo "Vaible build types are: \"linux\", \"windows\""
	exit 1
fi


valid_os $OS_TARGET

if [ $? ]; then
	echo "Building for $OS_TARGET"
else
	echo "Invalid build type!"
	echo "Vaible build types are: \"linux\", \"windows\""
	exit 1
fi

BUILD_PATH="build_$OS_TARGET/build/Release"

set -e

source $BUILD_PATH/generators/conanbuild.sh
if [ $DO_CMAKE -eq 1 ]
then
	BUILD_TYPE=$BUILD_TYPE cmake --preset conan-release-$OS_TARGET 
fi
cd $BUILD_PATH 
rm -rf out/* 
BUILD_TYPE=$BUILD_TYPE make $MAKE_TARGET && cp  out/* ../../../out/ && cp Makefile ../../..
