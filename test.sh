#!/bin/env bash

make tests

MAKE_TEST_OUTP=`make test`
N_OF_ERRORS=$(echo "$MAKE_TEST_OUTP" | grep "Errors:"  | sed 's/^\(.*\)://' | sed -z 's/ //g' | awk '{print}' ORS=' ' | sed 's/ / + /')

# echo "$MAKE_TEST_OUTP"
if [ $((N_OF_ERRORS)) -ge 1 ]
then 
	valgrind out/tests all
else
	echo "$MAKE_TEST_OUTP"
fi

