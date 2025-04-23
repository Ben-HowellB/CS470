#!/bin/bash

# Get the current date and time in format YYYY-MM-DD_HH-MM-SS
main_dir=$(date +"%Y-%m-%d_%H-%M-%S")

echo "Creating main directory: $main_dir"
mkdir "$main_dir"

# Array of 10 programming languages
languages=("Python" "Java" "C" "C++" "JavaScript" "Ruby" "Go" "Rust" "Swift" "Kotlin")

# Loop to create subdirectories and files
for i in $(seq 1 10)
do
    if [ "$i" -eq 10 ]; then
        sub_num=110
        file_num=510
    else
        sub_num=$((100 + i))  # 101 to 109
        file_num=$((500 + i)) # 501 to 509
    fi

    sub_dir="file$sub_num"
    file_name="tuser$file_num.txt"

    mkdir "$main_dir/$sub_dir"
    echo "Writing ${languages[$((i - 1))]} to $main_dir/$sub_dir/$file_name"
    echo "${languages[$((i - 1))]}" > "$main_dir/$sub_dir/$file_name"
done
