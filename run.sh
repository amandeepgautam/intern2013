#initialize directory structure
BINDIR=bin
OBJDIR=obj
if [ ! -d "$BINDIR" ]; then
	mkdir "$BINDIR"
fi
if [ ! -d "$OBJDIR" ]; then
	mkdir "$OBJDIR"
fi
clear
clear
clear
make

if [ $? -eq 0 ]; then
	make TYPE=$1 INP_FILE=$2 OUT_FILE=$3 run 
else
	echo ******Make failed********
fi

#Example: ./run.sh 0 dataset/input
