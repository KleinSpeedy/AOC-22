#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 10

void getElvCaloriesRanking(int *elves, int elvCount)
{
    int *ptr_highest = &elves[0];
    int *ptr_second = &elves[0];
    int *ptr_third = &elves[0];

    for(int i = 0; i < elvCount; i++)
    {
        if(elves[i] > *ptr_highest || 
            elves[i] > *ptr_second ||
            elves[i] > *ptr_third)   
        {
            if(elves[i] > *ptr_highest)
                ptr_highest = &elves[i];
            
            if((elves[i] > *ptr_second) && (elves[i] < *ptr_highest))
            {
                ptr_third = ptr_second;
                ptr_second = &elves[i];
            }
        }
    }

    int totalTopThree = *ptr_highest + *ptr_second + *ptr_third;

    printf("Total: %d\n"
    "1: %d\n"
    "2: %d\n"
    "3: %d\n",
    totalTopThree,
    *ptr_highest,
    *ptr_second,
    *ptr_third);
}

int main(int argc, char **argv)
{ 
    /* File IO */
    FILE *fp = fopen("puzzle-inputs/1/input.txt", "r");
    if(!fp)
    {
        fprintf(stderr, "Error opening file '%s'\n", "input.txt");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    memset(buffer,0,sizeof(buffer));

    int elvCount = 0;
    int calories = 0;
    int temp = 0;
    int *allElves = NULL;
    int *tempPtr = NULL;

    while(fgets(buffer, BUFFER_SIZE ,fp))
    {
        temp = atoi(buffer);
        calories += temp;

        /* check for linux or windows */
        if((strcmp(buffer, "\n") == 0) || (strcmp(buffer, "\r\n") == 0))
        {
            tempPtr = (int *)realloc(allElves, sizeof(int) * (elvCount + 1));

            if(!tempPtr)
            {
                fprintf(stderr, "Out of memory!\n");
                exit(1);
            }

            allElves = tempPtr;
            allElves[elvCount] = calories;
            elvCount++;
            calories = 0;
        }
    }

    getElvCaloriesRanking(allElves, elvCount);

    free(allElves);
    fclose(fp);

    return 0;
}