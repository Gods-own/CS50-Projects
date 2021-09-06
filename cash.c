#include <cs50.h>

#include <math.h>

#include <stdio.h>


int main(void)
{
  float dollars;

  do
  {
      dollars = get_float("Change owed: ");

  }
  while (dollars <= 0);

  int cents = round(dollars * 100);

  int coins = 0;

  while (cents > 0)
  {

    if (cents >= 25)
    {
       cents = cents - 25;
    }
    else if (cents >= 10)
    {
        cents = cents - 10;
    }
    else if (cents >= 5)
    {
        cents = cents - 5;
    }
    else
    {
         cents = cents - 1;
    }

    coins++;
  }

  printf("%i\n", coins);
}