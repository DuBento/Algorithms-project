#!/bin/bash
rm -r experimental
mkdir experimental
python filegenerator.py
echo "exec"
ls -lt experimental > outls
./execExperimental.sh
python cleaning.py