#!/bin/bash
python filegenerator.py
echo "exec"
./execExperimental.sh
python cleaning.py