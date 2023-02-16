#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 50
#define LINE_COUNT 1000

typedef struct SectionPair
{
    // Sections of elf A
    uint8_t beginA;
    uint8_t endA;

    // Sections of elf B
    uint8_t beginB;
    uint8_t endB;
} SectionPair_t;

void getSectionPairs(char *buffer, SectionPair_t currentPair)
{
    int digitCount = 0, sectionNumberIndex = 1;
    char newNumberBuffer[BUFFER_SIZE];
    memset(newNumberBuffer, 0, sizeof(newNumberBuffer));

    for(int j = 0; buffer[j+1] != '\n'; j++)
    {

        if((buffer[j] == '-') || (buffer[j] == ','))
        {
            // TODO: Input reads '-' and ',' so converted numbers are wrong!
            switch(sectionNumberIndex)
            {
                case 1:
                    strncpy(newNumberBuffer, buffer, digitCount - 1);
                    printf("B-A: %s", newNumberBuffer);
                    currentPair.beginA = atoi(newNumberBuffer);
                    memset(newNumberBuffer, 0, sizeof(newNumberBuffer));
                    sectionNumberIndex = 2;
                    break;
                case 2:
                    strncpy(newNumberBuffer, &buffer[j+1], digitCount - 1);
                    printf("\tE-A: %s", newNumberBuffer);
                    currentPair.endA = atoi(newNumberBuffer);
                    memset(newNumberBuffer, 0, sizeof(newNumberBuffer));
                    sectionNumberIndex = 3;
                    break;
                case 3:
                    strncpy(newNumberBuffer, &buffer[j+1], digitCount - 1);
                    printf("\tB-B: %s", newNumberBuffer);
                    currentPair.beginB = atoi(newNumberBuffer);
                    memset(newNumberBuffer, 0, sizeof(newNumberBuffer));
                    sectionNumberIndex = 4;
                    break;
                case 4:
                    strncpy(newNumberBuffer, &buffer[j+1], digitCount - 1);
                    printf("\tE-B: %s\n", newNumberBuffer);
                    currentPair.endB = atoi(newNumberBuffer);
                    memset(newNumberBuffer, 0, sizeof(newNumberBuffer));                        
                    sectionNumberIndex = 1;
                    break;
                default:
                    fprintf(stderr, "Error section numbers!\n");
                    exit(1);
                    break;
            }
            digitCount = 0;
        }
    }
}

int main(int argc, char **argv)
{
    /* File IO */
    FILE *fp = fopen("puzzle-inputs/4/input.txt", "r");
    if (!fp)
    {
        fprintf(stderr, "Error opening file '%s'\n", "input.txt");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));

    SectionPair_t allPairs[LINE_COUNT];

    int index = 0;

    while (fgets(buffer, BUFFER_SIZE, fp))
    {
        getSectionPairs(buffer, allPairs[index]);
        index++;
    }
    /*
    for(int i = 0; i < index; i++)
    {
        printf("%d - SectionA from %d to %d\n"
                "SectionB from %d to %d\n",
                i,
                allPairs[i].beginA,
                allPairs[i].endA,
                allPairs[i].beginB,
                allPairs[i].endB);
    }
    */
    fclose(fp);

    return 0;
}