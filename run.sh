#!/bin/bash
#Sample command: ./run.sh {Type of graph format} {location of input file} {the name of the output file} {file containing ground truth}. 
#The following will serve as an example: ./run.sh 0 dataset/network_1000.txt output/community_1000.txt
#initialize directory structure
BINDIR=bin
OBJDIR=obj
OUTPUT=output
if [ ! -d "$BINDIR" ]; then
	mkdir "$BINDIR"
fi
if [ ! -d "$OBJDIR" ]; then
	mkdir "$OBJDIR"
fi
if [ ! -d "$OUTPUT" ]; then
	mkdir "$OUTPUT"
fi
clear
make
if [ $? -eq 0 ]; then
	make TYPE=${1} INP_FILE=${2} OUT_FILE=${3} GRD_TRUTH=${4} run 
else
	echo ******Make failed********
fi

#Example: ./run.sh 0 dataset/input
