#5. Write a program to copy all the files (having file extension input by the user) in the
#current folder to the new folder input by the user. ex: user enter .text TEXT then all
#files with .text should be moved to TEXT folder. This should be done only at single
#level. i.e if the current folder contains a folder name ABC which has .txt files then
#these files should not be copied to TEXT.

echo "Enter the file extension  (e.g. .txt , .text):"
read ext

echo "Enter the destination folder name"
read dest

if [ ! -d "$dest" ]; then
	mkdir "$dest"
	echo "Created folder: $dest"
fi

for file in *"$ext"; do


	if [-f "$file" ]; then

	    cp "$file" "$dest"
	    echo "Copied: $file -> $dest /"

	    fi
done	     