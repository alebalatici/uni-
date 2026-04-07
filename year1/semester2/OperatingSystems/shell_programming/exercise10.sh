#Write a bash script that sorts all files given as command line arguments descending by size. 
#(first check if an argument is a file) 
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
