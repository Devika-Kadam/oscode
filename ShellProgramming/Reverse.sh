#!/bin/bash

echo "Enter a number: "
read number

# Reversing the number
reversed=""
length=${#number}
for (( i=$length-1; i>=0; i-- )); do
    reversed="${reversed}${number:$i:1}"
done

echo "Reversed number: $reversed"
