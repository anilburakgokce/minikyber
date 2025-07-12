#! /bin/bash

# to be run in code folder

CodeDir=$PWD
OutputDir="$CodeDir/../build"
OutputFileName="minikyber_test"

if [ ! -d $OutputDir ] ; then
mkdir $OutputDir
fi 

gcc $CodeDir/*.c -o $OutputDir/$OutputFileName