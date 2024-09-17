#!/bin/bash

Run=$1

rm -rf FileLists/*

# Set the input file
input_file="RunList/${Run}.txt"

# Initialize a counter for file names
counter=0

# Loop through each line in the input file
while IFS= read -r line; do
    # Create a new file with the line's content
    echo "$line" > "FileLists/file_$counter.txt"
   
    # Increment the counter
    counter=$((counter + 1))
done < "$input_file"
