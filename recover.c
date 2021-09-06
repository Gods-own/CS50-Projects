#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");


    int i = 0;
    char filename[8];
    BYTE buffer[BLOCK];

    while (fread(buffer, sizeof(BYTE), BLOCK, infile))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            sprintf(filename, "%03i.jpg", i);
            FILE *outfile = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), BLOCK, outfile);
            fclose(outfile);
            i++;
        }
        else if (i != 0)
        {
            FILE *outfile = fopen(filename, "a");
            fwrite(buffer, sizeof(BYTE), BLOCK, outfile);
            fclose(outfile);
        }

    }

    fclose(infile);

}