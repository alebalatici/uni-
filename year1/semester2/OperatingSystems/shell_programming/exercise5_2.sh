#Write a bash script that keeps reading strings from the keyboard until the name of a readable 
#regular file is given.
#!/bin/bash
while true; do
        read -p "Enter a file name: " FILENAME
        if [ -f $FILENAME ]; then
                break
        fi
done
exit 0
