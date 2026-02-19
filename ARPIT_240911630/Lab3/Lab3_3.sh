#Write a shell script to replace all files with .txt extension with .text in the current di-
#rectory. This has to be done recursively i.e if the current folder contains a folder
#“OS” with abc.txt then it has to be changed to abc.text ( Hint: use find, mv )


find . -type f -name "*.txt" | while read file; do

	new_name="${file%.txt}.text"


	mv "$file" "$new_name"


	echo "Renamed: $file -? $new_name"

done
