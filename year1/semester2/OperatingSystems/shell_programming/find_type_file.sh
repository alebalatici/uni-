#!/bin/bash
if [ $# -eq 0 ]; then
        echo Not enough arguments
        exit 1
fi

if [ ! -f $1 ]; then
        echo $1 is not a file
        exit 1
fi

FILE=$1
if [ ! -r $FILE ]; then
        echo $FILE is not a readable file
else
        echo $FILE is a readable file
fi

if [ ! -w $FILE ]; then
        echo $FILE is not a writeable file
else
        echo $FILE is a writeable file
fi

if [ ! -x $FILE ]; then
        echo $FILE is not an executable file
else
        echo $FILE is an executable file
fi
exit 0
