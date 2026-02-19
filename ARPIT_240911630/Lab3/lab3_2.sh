#Write a shell script to list all files (only file names) containing the input pattern
#(string) in the folder entered by the user.
echo "Enter the folder Path"

read folder

echo "Enter the pattern to search"

read pattern


if [ -d "$folder" ]; then


	echo "Files Containing the pattern '$pattern' are:"

	grep -rl --include="*" "$pattern" "$folder"

else
    
    echo "The folder '$folder'	does not exist."


 fi  