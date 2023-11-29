#!/bin/bash

# Function to calculate factorial
calculate_factorial() {
    local num=$1
    if [ $num -eq 0 ]; then
        factorial=1
    else
        factorial=1
        for ((i=1; i<=$num; i++)); do
            factorial=$((factorial * i))
        done
    fi
}

echo "Enter a number: "
read input_number

calculate_factorial $input_number

echo "Factorial of $input_number is: $factorial"

