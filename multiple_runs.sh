#!/bin/bash
#Sample command: ./multiple_run.sh {type of input graph representation} {location of input file} {output location(it will be prefixed by depth.)}
# For example: ./multiple_run.sh 0 dataset/test output/.
# Note that in the above example output file created will be output/1;output/2....

DEPTH=1
while [ ${DEPTH} -lt 20 ]; do
	#modify global.h for different depths.
	sed -i -e "s/#define DEPTH [0-9]*/#define DEPTH ${DEPTH}/g" ./src/global.h
	OUTFILLE=${3}${DEPTH}
	./run.sh ${1} ${2} ${OUTFILLE}
	let DEPTH=DEPTH+1
done
