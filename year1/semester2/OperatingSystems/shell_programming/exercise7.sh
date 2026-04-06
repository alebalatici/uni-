#Write a bash script that calculates the sum of the sizes (in bytes) of all regular files in a folder 
#given as a parameter.
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
sum=0
for FILE in $FILES; do
        size=$(du -b $FILE | awk '{print $1}')
        #echo $size
        sum=$((sum+size))
done
echo The sum of the sizes in bytes of all regular files in $DIR is $sum
exit 0
