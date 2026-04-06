#!/bin/bash
if [ $# -eq 0 ]; then
        echo Not enough arguments
        exit 1
fi

if [ ! -f $1 ]; then
        echo $1 not a file
        exit 1
fi
FILE=$1
content=$(awk '{print $1","$10}' $FILE | sort)
regex="^[0-9]+$"
prev_user=""
prev_sum=0
for LINE in $content; do
        #echo $LINE
        name=$(echo $LINE | awk -F, '{print $1}')
        time=$(echo $LINE | awk -F, '{print $2}')
        hours_unmodif=$(echo $time | awk -F: '{print $1}')
        minutes_unmodif=$(echo $time | awk -F: '{print $2}')

        hours=$(echo $hours_unmodif | sed "s/(//")
        minutes=$(echo $minutes_unmodif | sed "s/)//")

        if [[ $hours == "" ]]; then
                hours=0
        fi
        if [[ $minutes == "" ]]; then
                minutes=0
        fi

        if echo $hours | grep -Eq "\+"; then
                days=$(echo $hours | awk -F+ '{print $1}')
                hours=$(echo $hours | awk -F+ '{print $2}')
                hours=$((days*24+hours))
        fi

         if ! echo $hours | grep -Eq $regex; then
                hours=0
        fi

        if ! echo $minutes | grep -Eq $regex; then
                minutes=0
        fi

        hours=$(echo $hours | sed "s/^0//")
        minutes=$(echo $minutes | sed "s/^0//")

        if [ "$prev_user" != "$name" ]; then
                if [ ! -z "$prev_user" ]; then
                        echo Name: $prev_user Total: $prev_sum
                fi
                prev_user=$name
                prev_sum=$((hours*60+minutes))

        else
                prev_sum=$((prev_sum+hours*60+minutes))
        fi
        #echo "Name: $name Hours: $hours Minutes: $minutes"
done

#echo $prev_user
exit 0
