#!/bin/bash
cd experimental
mkdir result
touch resultados
for f in $(awk 'NF>1{print $NF}' ../outls) ;do
    if [ -f ${f} ]
    then 
        (time ../a.out < ${f} > /dev/zero) 2> ${f}.res
        #echo ${f} >> resultados
        cat ${f}.res | grep real >> result/resultados
    fi
done

