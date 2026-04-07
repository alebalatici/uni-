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
        filename=$(echo $FILE | awk -F/ '{print $NF}')
        #echo $filename
        just_name=$(echo $filename | sed -E "s/\..+//")
        #echo $just_name
        nr_char=$(echo $just_name | wc -c)
        if [ $nr_char -gt 0 ]; then
                nr_char=$((nr_char-1))
        fi
        #echo $nr_char
        if [ $nr_char -ge 8 ]; then
                continue
        fi

        echo Full path: $FILE Path: $filename Name: $just_name
        if ! file $FILE | grep -Eq "text"; then
                continue
        fi

        cat $FILE | head -n 10
done
exit 0
