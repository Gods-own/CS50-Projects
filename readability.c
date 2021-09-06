#include <math.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_letters(string text1);
int count_words(string text2);
int count_sentences(string text3);

int main(void)
{
    string text = get_string("Text: ");

    int letter1 =  count_letters(text);

    int words1 = count_words(text);

    int sentence1 = count_sentences(text);

    float L = (float)letter1 / (float)words1 * 100;

    float S = (float)sentence1 / (float)words1 * 100;

    //formula for calculating the readability of a text

    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

//function to count number of letters in a string

int count_letters(string text1)
{
    int letters = 0;

    for (int i = 0, n = strlen(text1); i < n; i++)
    {
        if (isalpha(text1[i]))
        {
            letters = letters + 1;
        }
        else
        {
            letters = letters + 0;
        }
    }

    return letters;
}

//function to count number of words in a string

int count_words(string text2)
{
    int words = 0;

    for (int j = 0, l = strlen(text2); j < l; j++)
    {
        if (isspace(text2[j]))
        {
            words = words + 1;
        }
        else
        {
            words = words + 0;
        }
    }

    return words + 1;
}

//function to count number of sentences in a string

int count_sentences(string text3)
{
    int sentences = 0;

    for (int k = 0, m = strlen(text3); k < m; k++)
    {
        if (text3[k] == '.' || text3[k] == '?' || text3[k] == '!')
        {
            sentences = sentences + 1;
        }
        else
        {
            sentences = sentences + 0;
        }
    }

    return sentences;
}