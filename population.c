
#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int startSize;

    int endSize;

    // TODO: Prompt for start size

    do
    {

       startSize = get_int("Start size: ");

    }
    while (startSize < 9);

    // TODO: Prompt for end size
    do
    {

       endSize = get_int("End size: ");

    }
    while (endSize < startSize);

    // TODO: Calculate number of years until we reach threshold
    int n = startSize;

    int i = 0;

    do
    {

        n = n + (n / 3) - (n / 4);

        i++;

    }
    while (n < endSize);

    // TODO: Print number of years

    printf("Years: %i\n", i);
}