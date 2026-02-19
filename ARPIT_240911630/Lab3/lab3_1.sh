#1. Write a shell script to find whether a given file is the directory or regular file.
echo "Enter the file name or path"
read file
if [ -e "$file" ]; then

	if [ -d "$file" ] ; then
		echo "$file is a directory"

	elif [ -f "$file" ]; then

	    echo "$file is a regular file"

	else
	 echo "$file exists but its not a regular file nor directory"    	

    fi
else

echo "$file doesnot exists"


fi    
