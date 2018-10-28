#!/bin/bash
# MakeStuff

cd vita/build/
cmake .
make clean
make

cd ../../psp/build
make clean
make