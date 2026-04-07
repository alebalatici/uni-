#Write a script that receives a directory as a command line argument. The script will delete all 
#the C source files from the directory and will display all other text files sorted alphabetically. 
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
        if file $FILE | grep -Eq "C source"; then
                #echo "Removing $FILE ..."
                rm $FILE
                continue
        fi

        if ! file $FILE | grep -Eq "text"; then
                continue
        fi
        filename=$(echo $FILE | awk -F/ '{print $NF}')
        echo "$filename"

done | sort
exit 0
