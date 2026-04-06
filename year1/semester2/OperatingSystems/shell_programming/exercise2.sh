#!/bin/bash
#Write a bash script that counts all the lines of code in the C files from the directory given as 
#command-line argument, excluding lines that are empty or contain only spaces. 
if [ $# -eq 0 ]; then
        echo "Not enough arguments"
        exit 1
fi

if [ ! -d $1 ]; then
        echo "$1 is not a directory"
        exit 1
fi

DIR=$1
FILES=$(find $DIR -type f)
total_lines=0
for FILE in $FILES; do
        if echo $FILE | grep -Eq "\.c$"; then
                cnt_lines=$(sed "s/ //g" $FILE | grep -E "." | wc -l)
                total_lines=$((total_lines+cnt_lines))
        fi
done
echo "Total number of lines: $total_lines"
exit 0
