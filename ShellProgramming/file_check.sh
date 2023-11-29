#!/bin/bash

echo "Enter the path to the file: "
read filepath

# Check if the file exists
if [ -e "$filepath" ]; then
    # Get file type
    file_type=$(file -b "$filepath")
    echo "File type: $file_type"

    # Get file permissions
    permissions=$(ls -l "$filepath" | awk '{print $1}')
    echo "Permissions: $permissions"
else
    echo "File not found."
fi

