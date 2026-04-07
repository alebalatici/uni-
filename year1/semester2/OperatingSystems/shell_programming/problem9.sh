#!/bin/bash
if [ $# -eq 0 ]; then
        echo Not enough arguments
        exit 1
fi

for ARG in $*; do
        if [ ! -f $ARG ]; then
                echo $ARG is not a file
                continue
        fi

        while read -r LINIE; do
                echo $LINIE
        done < $ARG | sort | uniq -c | sort -nr | head -n 1
done | sort -nr
exit 0
