#!/bin/bash
# MakeStuff

cd vita/build/
echo -e "\n-----------------Compiling for vita--------------------------\n"
cmake .
make clean
make
curl -T NCESPSV.vpk ftp://$1:1337/ux0:/

cd ../../psp/build
echo -e "\n-----------------Compiling for psp---------------------------\n"
make clean
make
cd ../
curl -T "gfx/test.png" ftp://$1:1337/ux0:/pspemu/PSP/GAME/NCESPSP/gfx/
curl -T "build/EBOOT.PBP" ftp://$1:1337/ux0:/pspemu/PSP/GAME/NCESPSP/