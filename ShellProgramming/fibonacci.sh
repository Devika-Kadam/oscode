#!/bin/bash

echo "Enter the number of terms in the Fibonacci series: "
read num_terms

# Function to generate Fibonacci series
generate_fibonacci() {
    local n=$1
    local a=0
    local b=1
    local count=0

    while [ $count -lt $n ]; do
        echo -n "$a "
        local temp=$((a + b))
        a=$b
        b=$temp
        count=$((count + 1))
    done
}

generate_fibonacci $num_terms
echo  # Print a new line

