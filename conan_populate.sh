#!/usr/bin/env bash

CONAN_PRESETS="ConanPresets.json"

rm $CONAN_PRESETS

for KEYWORD in windows linux
do 
	rm -rf build_$KEYWORD
	conan install . --build=missing -s build_type=Release -pr:h=conan-profiles/$KEYWORD -of=build_$KEYWORD && sed -e "1,\$s/conan-release/&-$KEYWORD/" -i build_$KEYWORD/build/Release/generators/CMakePresets.json
done

 sed -e '1,$s/{}/{\n}/'  -e ':a;N;$!ba;s/\n//g' -i $CONAN_PRESETS 
 sed -e '1s/,\( *\){\( *\)"name": "conan-release\(.*\){\(.*\)],/],/'  -i $CONAN_PRESETS
 sed -e '1s/\([{[,}]\)/\1\n/g' -i $CONAN_PRESETS

