#!/bin/bash

INPUTDIR=tests_p1

g++ -Wall main.cpp

cd $INPUTDIR
for fin in *.in; do
	filename=${fin%.*}
	echo "===========${filename}=========="
	../a.out < ${filename}.in > ${filename}.myout
	diff -b ${filename}.out ${filename}.outhyp
done