#!/bin/bash

max=25
min=1

if [ -z "$1" ]; then
    echo "No argument supplied, try './run-day.sh 1'"
elif (( $1 >= $min )) && (( $1 <= $max )); then
    exe="day$1"
    echo "Running day-$1"
    ./build/$1/$exe
else
    echo "There is no advent-door for: $1"
fi
