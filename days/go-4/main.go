package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type bagPair struct {
	beginA int
	endA   int

	beginB int
	endB   int
}

func main() {
	fmt.Println("Starting Day 4")

	puzzlePath := os.Getenv("AOC_PUZZLE_INPUT_PATH")

	input, err := os.OpenFile(puzzlePath, os.O_RDONLY, 0644)
	if err != nil {
		panic(err)
	}
	defer input.Close()

	allPairs := readPairs(input)
	var fullyContains int

	for i, pair := range allPairs {
		// check pair bounds for elfA and elfB
		fmt.Printf("i: %d BA: %d BB: %d EA: %d EB: %d\n",
			i, pair.beginA, pair.beginB, pair.endA, pair.endB)

		if pair.beginA <= pair.beginB && pair.endA >= pair.endB ||
			pair.beginB <= pair.beginA && pair.endB >= pair.endA {
			fullyContains += 1
		}

	}

	totalOverlap := computeOverlapingSections(allPairs)

	fmt.Printf("Fully containing sections: %d\nTotal Overlaping: %d\n",
		fullyContains, totalOverlap)
}

func readPairs(input *os.File) []bagPair {
	scanner := bufio.NewScanner(input)
	var allPairs []bagPair

	for scanner.Scan() {
		line := scanner.Text()
		newPair := bagPair{}

		sections := strings.Split(line, ",")
		for i, section := range sections {
			tmp := strings.Split(section, "-")
			for j, t := range tmp {
				// TODO: Get rid of these ugly if statements
				switch i {
				case 0:
					{
						if j == 0 {
							newPair.beginA, _ = strconv.Atoi(t)
						}
						if j == 1 {
							newPair.endA, _ = strconv.Atoi(t)
						}
					}
				case 1:
					{
						if j == 0 {
							newPair.beginB, _ = strconv.Atoi(t)
						}
						if j == 1 {
							newPair.endB, _ = strconv.Atoi(t)
						}
					}
				}
			}
		}
		allPairs = append(allPairs, newPair)
	}

	return allPairs
}

// TODO: Compute part 2 of day 4
func computeOverlapingSections(allPairs []bagPair) (total int) {

	return
}
