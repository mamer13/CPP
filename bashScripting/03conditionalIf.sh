#!/bin/bash
read -p "Enter a number: " num

if [ $num -gt 0 ]; then
    echo "Positive number"
elif [ $num -lt 0 ]; then
    echo "Negative number"
else
    echo "Zero"
fi

read -p "Enter a name: " name
if [ "$name" = "Mohamed" ]; then  # Compare string equality
  echo "Correct name"               # Print message if equal
fi

