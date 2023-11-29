#!/bin/bash

# Function to check if a number is prime
is_prime() {
    local number=$1
    if [ $number -lt 2 ]; then
        return 1 
    fi

    for (( i=2; i*i <= number; i++ )); do
        if [ $((number % i)) -eq 0 ]; then
            return 1 
        fi
    done

    return 0 
}

read -p "Enter a number: " num

if is_prime $num; then
    echo "$num is a prime number."
else
    echo "$num is not a prime number."
fi


