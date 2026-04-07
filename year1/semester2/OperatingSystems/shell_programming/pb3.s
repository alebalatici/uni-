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
for FILE in $FILES; do
        if ! echo $FILE | grep -Eq ".log$"; then
                continue
        fi

        echo Sorting file $FILE ...
        sort $FILE -o $FILE
done
exit 0
