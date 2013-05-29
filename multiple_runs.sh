#!/bin/bash
DEPTH=1
while [ ${DEPTH} -lt 20 ]; do
	#modify global.h for different depths.
	sed -i -e "s/#define DEPTH [0-9]*/#define DEPTH ${DEPTH}/g" ./src/global.h
	OUTFILLE=${3}${DEPTH}
	./run.sh ${1} ${2} ${OUTFILLE}
	let DEPTH=DEPTH+1
done
