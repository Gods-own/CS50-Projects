#include <math.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string ciper_text(string text1);

int main(int argc, string argv[])
{
    int k;
    int p;
    int c;

    if (argc == 2)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");

                return 1;
            }
        }

        k = atoi(argv[1]);

        string text = get_string("plaintext: ");

        printf("ciphertext: ");

       for (int j = 0, q = strlen(text); j < q; j++)
       {
           if (isupper(text[j]))
           {
               p = text[j] - 65;
               c = ((p + k) % 26) + 65;
           }
           else if(islower(text[j]))
           {
               p = text[j] - 97;
               c = ((p + k) % 26) + 97;
           }
           else
           {
               p = text[j] - 0;
               c = p;
           }

        //  printf("%i\n", alpha);

           printf("%c", c);
        }

        printf("\n");

    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}











