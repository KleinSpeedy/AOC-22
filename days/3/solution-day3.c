#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 100
#define ELF_COUNT 300

#define CHECK_ALLOC(x) if(!x){fprintf(stderr,"Error malloc!\n"); exit(1);}

typedef struct elf
{
    int rucksackSize;
    char *rucksack;

    char *compartmentA;
    char *compartmentB;
} Elf_t;

/* -----Functions----- */

void deleteAllElves(Elf_t *allElves)
{
    for(int i = 0; i < ELF_COUNT; i++)
    {
        free(allElves[i].compartmentA);
        free(allElves[i].compartmentB);
        free(allElves[i].rucksack);
    }
}

void createNewElf(Elf_t *elf, char *content)
{
    int size = 0;
    char *compA, *compB, *rucksack;

    elf->rucksackSize = strlen(content);
    size = elf->rucksackSize / 2;

    compA = (char *)calloc(1, (sizeof(char) * size));
    compB = (char *)calloc(1, (sizeof(char) * size));
    rucksack = (char *)calloc(1, (sizeof(char) * elf->rucksackSize));
    
    CHECK_ALLOC(compA);
    CHECK_ALLOC(compB);
    CHECK_ALLOC(rucksack);

    strncpy(rucksack, content, elf->rucksackSize);
    strncpy(compA, content, size);
    strncpy(compB, &content[size], size);
    
    elf->compartmentA = compA;
    elf->compartmentB = compB;
    elf->rucksack = rucksack;
}

char findMatchingItem(int substringSize, char *compA, char *compB)
{
    char matchingItem;
    for(int i = 0; i < substringSize; i++)
    {
        for(int j = 0; j < substringSize; j++)
        {
            if(compA[i] == compB[j])
            {
                matchingItem = compA[i];
                return matchingItem;
            }
        }
    }

    fprintf(stderr, "Didnt find matching item!\n");
    exit(1);
}

int calculateItemsPrioritySum(Elf_t *allElves)
{
    int totalPrioritiesSum = 0;
    char matchingItem;

    for(int i = 0; i < ELF_COUNT; i++)
    {
        matchingItem = findMatchingItem(
                (allElves[i].rucksackSize / 2),
                allElves[i].compartmentA,
                allElves[i].compartmentB);

        if(matchingItem >= 97)
            totalPrioritiesSum += matchingItem - 'a' + 1;
        else
            totalPrioritiesSum += matchingItem - 'A' + 27;
    }

    return totalPrioritiesSum;
}

char findMatchingGroupItem(Elf_t *elfOne, Elf_t *elfTwo, Elf_t *elfThree)
{
    char itemElfOne, itemElfTwo, itemElfThree;
    
    for(int i = 0; i < elfOne->rucksackSize; i++)
    {
        itemElfOne = elfOne->rucksack[i];
        for(int j = 0; j < elfTwo->rucksackSize; j++)
        {
            itemElfTwo = elfTwo->rucksack[j];
            for(int k = 0; k < elfThree->rucksackSize; k++)
            {
                itemElfThree = elfThree->rucksack[k];
                if((itemElfOne == itemElfTwo) && (itemElfOne == itemElfThree))
                {
                    return itemElfOne;
                }
            }
        }
    }

    fprintf(stderr, "Could not find matching group item!\n");
    exit(1);
}

int calculateGroupPrioritySum(Elf_t *allElves)
{
    char matchingGroupItem;
    int totalGroupPrioritySum = 0;

    for(int i = 0; i < ELF_COUNT; i+=3)
    {
        matchingGroupItem = findMatchingGroupItem(&allElves[i],&allElves[i+1],&allElves[i+2]);
        if(matchingGroupItem >= 97)
            totalGroupPrioritySum += matchingGroupItem - 'a' + 1;
        else
            totalGroupPrioritySum += matchingGroupItem - 'A' + 27;
    }
    return totalGroupPrioritySum;
}

int main(int argc, char **argv)
{
    /* File IO */
    FILE *fp = fopen("puzzle-inputs/3/input.txt", "r");
    if (!fp)
    {
        fprintf(stderr, "Error opening file '%s'\n", "input.txt");
        return 1;
    }

    int index = 0;

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));

    Elf_t allElves[ELF_COUNT];

    while (fgets(buffer, BUFFER_SIZE, fp))
    {
        createNewElf(&allElves[index], buffer);
        index++;
    }

    int totalPrioritiesSum = calculateItemsPrioritySum(allElves);
    int totalGroupPrioritySum = calculateGroupPrioritySum(allElves);

    printf("Priorities Sum: %d\n"
            "Group Priorities Sum: %d\n",
            totalPrioritiesSum,
            totalGroupPrioritySum);

    deleteAllElves(allElves);
    fclose(fp);

    return 0;
}