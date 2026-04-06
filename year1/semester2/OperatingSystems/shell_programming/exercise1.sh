#!/bin/bash
#Write a bash script that counts all the C files from a given directory and all of its subdirectories. 
#Does not work for file names with spaces
if [  $# -eq 0 ]; then
        echo "Not enough arguments"
        exit 1
fi

if [ ! -d $1 ]; then
        echo "$1 not a  directory"
        exit 1
fi

DIR=$1
count=0
FILES=$(find $DIR -type f)
for FILE in $FILES; do
        #if file $FILE | grep -Eq "C source"; then
        #       count=$((count+1))
        if echo $FILE | grep -Eq "\.c$"; then
                count=$((count+1))
        fi
done
echo $count
exit 0
