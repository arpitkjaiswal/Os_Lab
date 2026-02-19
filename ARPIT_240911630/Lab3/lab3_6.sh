echo "Enter the filename"

read filename

if [ -f "$filename" ]; then
	sed -i '2~2d' "$filename"
    echo "All even-numbered lines deleted from $filename"
else
	echo "File does not exist"
fi
