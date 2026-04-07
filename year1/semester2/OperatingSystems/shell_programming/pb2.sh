#!/bin/bash
if [ $# -eq 0 ]; then
        echo Not enough arguments
        exit 1
fi

if [ ! -d $1 ]; then
        echo $1 is not a directory
        exit 1
fi

DIR=$1
FILES=$(find $DIR -type f)
files_found=0
for FILE in $FILES; do
        if ! echo $FILE | grep -Eq ".c$"; then
                continue
        fi

        lines=$(cat $FILE | wc -l)
        if [ $lines -gt 500 ]; then
                files_found=$((files_found+1))
                if [ $files_found -le 2 ]; then
                        echo $FILE
                fi
        fi
done
exit 0
