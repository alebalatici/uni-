#Write a script that receives as command line arguments pairs consisting of a filename and a 
#word. For each pair, check if the given word appears at least 3 times in the file and print a 
#corresponding message. 
#!/bin/bash
if [ $# -eq 0 ]; then
        echo Not enough arguments
        exit 1
fi

while [ $# -gt 0 ]; do
        filename=$1
        shift

        if [ $# -eq 0 ]; then
                echo Odd number of arguments: Pair $filename - unfinished
                break
        fi

        word=$1
        shift

        if [ ! -f $filename ]; then
                echo $filename is not a file
                continue
        fi

        nr_ap=$(grep -Eo "$word" $filename | wc -l)
        if [ $nr_ap -ge 3 ]; then
                echo $word appears in $filename $nr_ap times, therefore more than 3 times
        else
                echo $word does not appear in $filename at least 3 times
        fi
done
exit 0
