

echo "Enter the file extension (e.g. .txt , .text):"
read ext

echo "Enter the destination folder name:"
read dest

if [ ! -d "$dest" ]; then
    mkdir "$dest"
    echo "Created folder: $dest"
fi


for file in *"$ext"; do
    if [ -f "$file" ]; then
        mv "$file" "$dest"
        echo "Moved: $file -> $dest/"
    fi
done
