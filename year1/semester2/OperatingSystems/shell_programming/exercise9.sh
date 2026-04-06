#Write a script that reads filenames until the word "stop" is entered. For each filename, check if 
#it is a text file and if it is, print the number of words on the first line.(Hint: test command to 
#check if regular file; file command to check if text file) 
#!/bin/bash
while true; do
        read -p "Enter a file name: " FILENAME
        if [ $FILENAME = "stop" ]; then
                break
        fi

        if [ ! -f $FILENAME ]; then
                echo $FILENAME is not a file
                continue
        fi

        if ! file $FILENAME | grep -Eq "text"; then
                echo $FILENAME is not a text file
                continue
        fi

        line=$(cat $FILENAME | head -n 1)
        number=$(echo $line | wc -w)
        echo The number of words on the first line is: $number
done
exit 0
