#!/usr/bin/env bash

./build.sh "-t linux $1"
./build.sh "-t windows $1"

if [ $OS ] 
then
	cp build_windows/build/Release/Makefile .
else
	cp build_linux/build/Release/Makefile .
fi
sed -e '1,$s/{\(.*\)\n^\(.*\)\n/{\2'

