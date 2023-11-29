#!/bin/bash

echo "Enter a string: "
read input_string

# Reversing the string
reversed_string=""
length=${#input_string}
for (( i=$length-1; i>=0; i-- )); do
    reversed_string="${reversed_string}${input_string:$i:1}"
done

echo "Reversed string: $reversed_string"
