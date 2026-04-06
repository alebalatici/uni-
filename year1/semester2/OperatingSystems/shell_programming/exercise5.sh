#Write a bash script that keeps reading strings from the keyboard until the name of a readable 
#regular file is given. 
#!/bin/bash
read -p "Enter a file name: " FILENAME
while [ ! -f $FILENAME ]; do
        read -p "Enter a file name: " FILENAME
done
