#!/bin/bash
cd experimental
for f in * ;do
    if [ -f $f ]
    then 
        time ../a.out < ${f} > ${f}.res
    fi
done