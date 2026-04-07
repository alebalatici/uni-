#!/bin/bash
if [ $# -eq 0 ]; then
        echo Not enough arguments
        exit 1
fi

regex="^[0-9]+$"
while [ ! $# -eq 0 ]; do
        file=$1
        shift
        if [ $# -eq 0 ]; then
                echo Uncompleted triplet: $file - -
                continue
        fi

        word=$1
        shift
        if [ $# -eq 0 ]; then
                echo Uncompleted triplet: $file $word -
                continue
        fi

        number=$1
        shift

        if [ ! -f $file ]; then
                echo $file is not a file
                continue
        fi

        if ! [[ "$number" =~ $regex ]]; then
                echo $number is not a number
                continue
        fi

        number=$(echo $number | sed -E "s/^0+//")
        echo Triplet: $file $word $number
        while read -r LINE; do
                nr_ap=$(echo $LINE | grep -E -o "$word" | wc -l)
                if [ $nr_ap -eq $number ]; then
                        echo $LINE
                fi
        done < $file
done
exit 0
