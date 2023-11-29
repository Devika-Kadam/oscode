
#!/bin/bash

echo "Enter a number: "
read num
reverse=0
temp=$num

# reversing the number
while [ $temp -gt 0 ]
do
    remainder=$(( $temp % 10 ))
    reverse=$(( $reverse * 10 + $remainder ))
    temp=$(( $temp / 10 ))
done

# checking if the number is palindrome or not
if [ $num -eq $reverse ]
then
    echo "$num is a palindrome number"
else
    echo "$num is not a palindrome number"
fi

echo "Reverse of $num is $reverse"
