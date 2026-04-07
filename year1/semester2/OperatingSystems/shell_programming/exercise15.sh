#Calculate the average of all process ids in the system per user. 
#!/bin/bash
if [ $# -eq 0 ]; then
        echo Not enough arguments
        exit 1
fi

if [ ! -f $1 ]; then
        echo $1 is not a file
        exit 1
fi

FILE=$1
sum=0
cnt=0
line=0
while read -r LINE; do
        line=$((line+1))
        if [ $line -eq 1 ]; then
                continue
        fi

        pid=$(echo $LINE | awk '{print $3}')
        number=$(echo $pid | sed -E "s/^0//")
        #echo $number
        sum=$((sum+number))
        cnt=$((cnt+1))

done < $FILE
if [ $cnt -eq 0 ]; then
        echo The file does not containt any process id
else
                echo The average of all process ids is: $((sum/cnt))
fi
exit 0
