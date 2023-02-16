#!/bin/bash

max=25
min=1

if [ -z "$1" ]; then
    echo "No argument supplied, try './run-day.sh 1'"
elif (( $1 >= $min )) && (( $1 <= $max )); then
    if (( $1 >= 4 )); then
        export AOC_PUZZLE_INPUT_PATH="./puzzle-inputs/$1/input.txt"
        echo "Running Day-$1 with Input: $AOC_PUZZLE_INPUT_PATH"
        go run ./days/go-$1/main.go
    else
        exe="day$1"
        echo "Running day-$1"
        ./build/days/$1/$exe
    fi
else
    echo "There is no advent-door for: $1"
fi
