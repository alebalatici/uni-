#!/bin/bash
if [ $# -eq 0 ]; then
        echo Not enough arguments
        exit 1
fi

read -p "Enter a file name for the output included libraries: " FILENAME

fullname="$FILENAME.txt"
if [ -f $fullname ]; then
        echo "Found $fullname"
        echo "Deleting the previous content of $fullname ..."
        > $fullname
fi

for ARG in $*; do
        if [ ! -f $ARG ]; then
                echo $ARG is not a file
                continue
        fi

        if ! file $ARG | grep -Eq "C source"; then
                echo $ARG is not a C file
                continue
        fi

        while read -r LINE; do
                if echo $LINE | grep -Eq "^#include"; then
                        echo $LINE >> "$FILENAME.txt"
                        echo "Wrote $LINE to $FILENAME.txt"
                fi
        done < $ARG

done
exit 0
