#!/bin/bash

INPUTDIR=tests_p1
file=trash/difsmain.cpp
g++ -std=c++11 -O3 -Wall $file -lm	
cd $INPUTDIR
for fin in *.in; do
	filename=${fin%.*}
	echo "===========${filename}=========="
	../a.out < ${filename}.in > ${filename}.myout
	diff -b ${filename}.out ${filename}.myout
	read -p "press to cont"
done
