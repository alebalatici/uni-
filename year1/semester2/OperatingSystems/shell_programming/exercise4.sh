#Write a bash script that receives any number of command line arguments and prints on the 
#screen, for each argument, if it is a file, a directory, a number or something else. 
#Will say 01, 02 ... are natural numbers
#!/bin/bash
if [ $# -eq 0 ]; then
        echo Not enough arguments
        exit 1
fi

number_regex="^[0-9]+$"
for ARG in $*; do
        if [ -f $ARG ]; then
                echo $ARG is a file
        elif [ -d $ARG ]; then
                echo $ARG is a directory
        elif [[ "$ARG" =~ $number_regex ]]; then
                echo $ARG is a natural number
        else
                echo $ARG is something else
        fi
done
exit 0
