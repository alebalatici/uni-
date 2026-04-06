#Write a bash script that sorts the file given as command line arguments in ascending order 
#according to their file size in bytes. 
#!/bin/bash
if [ $# -eq 0 ]; then
        echo Not enough arguments
        exit 1
fi

for ARG in $*; do
        if [ ! -f $ARG ]; then
                echo $ARG is not a file
                continue
        fi

        du -b $ARG
done | sort -nr
exit 0
