#Consider a file containing a username on each line. Generate a comma-separated string with 
#email addresses of the users that exist. The email address will be obtained by appending 
#"@scs.ubbcluj.ro" at the end of each username. Make sure the generated string does NOT 
#end in a comma. 
#!/bin/bash
if [ $# -eq 0 ]; then
        echo Not enough arguments
        exit 1
fi

if [ ! -f $1 ]; then
        echo $1 is not a file
        exit 1
fi

domain="@scs.ubbcluj.ro"
text=""
while read -r NAME; do
        #echo $NAME
        email="${NAME}${domain}"
        text="${text}, ${email}"

done < $1
text=$(echo $text | sed -E "s/^, //")
echo $text
exit 0
