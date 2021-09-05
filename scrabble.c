#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int score = 0;
    // TODO: Compute and return score for string
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] == 'a' || word[i] == 'A')
        {
            score = score + POINTS[0];
        }
        else if (word[i] == 'b' || word[i] == 'B')
        {
            score = score + POINTS[1];
        }
        else if (word[i] == 'c' || word[i] == 'C')
        {
            score = score + POINTS[2];
        }
        else if (word[i] == 'd' || word[i] == 'D')
        {
            score = score + POINTS[3];
        }
        else if (word[i] == 'e' || word[i] == 'E')
        {
            score = score + POINTS[4];
        }
        else if (word[i] == 'f' || word[i] == 'F')
        {
            score = score +POINTS[5];
        }
        else if (word[i] == 'g' || word[i] == 'G')
        {
            score = score + POINTS[6];
        }
        else if (word[i] == 'h' || word[i] == 'H')
        {
            score = score + POINTS[7];
        }
        else if (word[i] == 'i' || word[i] == 'I')
        {
            score = score + POINTS[8];
        }
        else if (word[i] == 'j' || word[i] == 'J')
        {
            score = score + POINTS[9];
        }
        else if (word[i] == 'k' || word[i] == 'K')
        {
            score = score + POINTS[10];
        }
        else if (word[i] == 'l' || word[i] == 'L')
        {
            score = score + POINTS[11];
        }
        else if (word[i] == 'm' || word[i] == 'M')
        {
            score = score + POINTS[12];
        }
        else if (word[i] == 'n' || word[i] == 'N')
        {
            score = score + POINTS[13];
        }
        else if (word[i] == 'o' || word[i] == 'O')
        {
            score = score + POINTS[14];
        }
        else if (word[i] == 'p' || word[i] == 'P')
        {
            score = score + POINTS[15];
        }
        else if (word[i] == 'q' || word[i] == 'Q')
        {
            score = score + POINTS[16];
        }
        else if (word[i] == 'r' || word[i] == 'R')
        {
            score = score + POINTS[17];
        }
        else if (word[i] == 's' || word[i] == 'S')
        {
            score = score + POINTS[18];
        }
        else if (word[i] == 't' || word[i] == 'T')
        {
            score = score + POINTS[19];
        }
        else if (word[i] == 'u' || word[i] == 'U')
        {
            score = score + POINTS[20];
        }
        else if (word[i] == 'v' || word[i] == 'V')
        {
            score = score + POINTS[21];
        }
        else if (word[i] == 'w' || word[i] == 'W')
        {
            score = score + POINTS[22];
        }
        else if (word[i] == 'x' || word[i] == 'X')
        {
            score = score + POINTS[23];
        }
        else if (word[i] == 'y' || word[i] == 'Y')
        {
            score = score + POINTS[24];
        }
        else if (word[i] == 'z' || word[i] == 'Z')
        {
            score = score + POINTS[25];
        }
        else
        {
            score = score + 0;
        }
    }
    return score;
}