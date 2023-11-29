#!/bin/bash

while true; do
    echo "Choose an arithmetic operation:"
    echo "1. Addition"
    echo "2. Subtraction"
    echo "3. Multiplication"
    echo "4. Division"
    echo "5. Exit"
    read choice

    case $choice in
        1)
            echo "Enter two numbers: "
            read num1
            read num2
            result=$((num1 + num2))
            echo "Result: $result"
            ;;
        2)
            echo "Enter two numbers: "
            read num1
            read num2
            result=$((num1 - num2))
            echo "Result: $result"
            ;;
        3)
            echo "Enter two numbers: "
            read num1
            read num2
            result=$((num1 * num2))
            echo "Result: $result"
            ;;
        4)
            echo "Enter two numbers: "
            read num1
            read num2
            result=$((num1 / num2))
            echo "Result: $result"
            ;;
        5)
            echo "Exiting..."
            exit 0
            ;;
        *)
            echo "Invalid choice. Please choose a valid operation."
            ;;
    esac

    echo "------------------------------------"
done

