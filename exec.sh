#!/bin/bash

INPUTDIR=tests_p1


cd $INPUTDIR
for fin in *.in; do
	filename=${fin%.*}
	echo "===========${filename}=========="
	if test -f "${filename}.import"; then
		java -Dimport=${filename}.import -Din=${filename}.in -Dout=${filename}.outhyp -cp ../po-uuilib/po-uuilib.jar:../m19-app/m19-app.jar:../m19-core/m19-core.jar m19.app.App	
	else
		java -Din=${filename}.in -Dout=${filename}.outhyp -cp ../po-uuilib/po-uuilib.jar:../m19-app/m19-app.jar:../m19-core/m19-core.jar m19.app.App
	fi

	diff -b ${filename}.out ${filename}.outhyp
done