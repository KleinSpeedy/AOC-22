#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 5
#define LINE_COUNT 2500

enum GameResult
{
    Lose = 0,
    Draw = 3,
    Wins = 6
};

int calculateStrategyScore_Pick(char *oponentPick, char *strategyPick, int rounds)
{
    uint8_t oponent = 0, strategy = 0, roundScore = 0;
    enum GameResult outcome;
    int totalScore = 0;

    for (int i = 0; i < rounds; i++)
    {
        oponent = oponentPick[i] - 'A' + 1;
        strategy = strategyPick[i] - 'X' + 1;

        /* A,X Rock | B,Y Paper | C,Z Scissors
         * A vs X => Draw | B vs X => Lose | C vs X => Wins
         * A vs Y => Wins | B vs Y => Draw | C vs Y => Lose
         * A vs Z => Lose | B vs Z => Wins | C vs Z => Draw
         */
        if (oponent == strategy)
            outcome = Draw;
        else
        {
            if ((oponent == 1 && strategy == 3) ||
                (oponent == 2 && strategy == 1) ||
                (oponent == 3 && strategy == 2))
            {
                outcome = Lose;
            }
            else
            {
                outcome = Wins;
            }
        }

        roundScore = outcome + strategy;
        totalScore += roundScore;
    }

    return totalScore;
}

int calculateStrategyScore_Result(char *oponentPick, char *strategyPick, int rounds)
{
    uint8_t oponent = 0, strategy = 0, roundScore = 0;
    enum GameResult outcome;
    int results[3] = {Lose, Draw, Wins};

    int totalScore = 0;

    for (int i = 0; i < rounds; i++)
    {
        oponent = oponentPick[i] - 'A' + 1;
        strategy = strategyPick[i] - 'X' + 1;

        /* A,X Rock | B,Y Paper | C,Z Scissors
         * A vs X => Draw | B vs X => Lose | C vs X => Wins
         * A vs Y => Wins | B vs Y => Draw | C vs Y => Lose
         * A vs Z => Lose | B vs Z => Wins | C vs Z => Draw
         */
        // Desired result
        outcome = results[strategy - 1];
        
        if(outcome == Draw)
            strategy = oponent;
        else
        {
            if(outcome == Wins)
            {
                switch(oponent)
                {
                case 1:
                    strategy = 2;
                    break;
                case 2:
                    strategy = 3;
                    break;
                case 3:
                    strategy = 1;
                    break;
                default:
                    fprintf(stderr, "Error in rounds calculation!\n");
                    break;
                }
            }
            else
            {
                switch(oponent)
                {
                case 1:
                    strategy = 3;
                    break;
                case 2:
                    strategy = 1;
                    break;
                case 3:
                    strategy = 2;
                    break;
                default:
                    fprintf(stderr, "Error in rounds calculation!\n");
                    break;
                }
            }
        }

        roundScore = outcome + strategy;
        totalScore += roundScore;
    }

    return totalScore;
}

int main(int argc, char **argv)
{
    /* File IO */
    FILE *fp = fopen("puzzle-inputs/2/input.txt", "r");
    if (!fp)
    {
        fprintf(stderr, "Error opening file '%s'\n", "input.txt");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));

    char oponentPick[LINE_COUNT];
    memset(oponentPick, 0, sizeof(oponentPick));

    char strategyPick[LINE_COUNT];
    memset(strategyPick, 0, sizeof(strategyPick));

    int index = 0;

    while (fgets(buffer, BUFFER_SIZE, fp))
    {
        oponentPick[index] = buffer[0];
        strategyPick[index] = buffer[2];
        index++;
    }

    int totalScorePick = calculateStrategyScore_Pick(oponentPick, strategyPick, index);
    int totalScoreResult = calculateStrategyScore_Result(oponentPick, strategyPick, index);

    printf("TotalScore_Pick: %d\n"
           "TotalScore_Result: %d\n",
           totalScorePick,
           totalScoreResult);

    fclose(fp);

    return 0;
}