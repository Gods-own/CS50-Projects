#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int averageValue;

    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, m = width; j < m; j++)
        {

            averageValue = round(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen
            + (float)image[i][j].rgbtRed) / 3);

            image[i][j].rgbtBlue = averageValue;
            image[i][j].rgbtGreen = averageValue;
            image[i][j].rgbtRed = averageValue;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;

    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, m = width; j < m; j++)
        {
            sepiaRed = round((0.393 * (float)image[i][j].rgbtRed) + (0.769 *  (float)image[i][j].rgbtGreen) + (0.189 * (float)image[i][j].rgbtBlue));
            sepiaGreen = round((0.349 *  (float)image[i][j].rgbtRed) + (0.686 * (float)image[i][j].rgbtGreen) + (0.168 * (float)image[i][j].rgbtBlue));
            sepiaBlue = round((0.272 *  (float)image[i][j].rgbtRed) + (0.534 * (float)image[i][j].rgbtGreen) + (0.131 * (float)image[i][j].rgbtBlue));

            if (sepiaRed > 255 && sepiaBlue > 255)
            {
                sepiaRed = 255;
                sepiaBlue = 255;
            }
            else if (sepiaRed > 255 && sepiaGreen > 255)
            {
                sepiaRed = 255;
                sepiaGreen = 255;
            }
            else if (sepiaBlue > 255 && sepiaGreen > 255)
            {
                sepiaGreen = 255;
                sepiaBlue = 255;
            }
            else if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            else if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            else if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])

{
    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, m = width * 0.5; j < m; j++)
        {
            RGBTRIPLE empty = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = empty;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE empty[height][width];
    int averageBlue;
    int averageRed;
    int averageGreen;
    float blue;
    float red;
    float green;

    for (int k = 0, l = height; k < l; k++)
    {
        for (int p = 0, h = width; p < h; p++)
        {
            empty[k][p] = image[k][p];
        }
    }

    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, m = width; j < m; j++)
        {
            if (i == 0 && j == 0)
            {
                blue = empty[i][j].rgbtBlue +  empty[i][j + 1].rgbtBlue + empty[i + 1][j].rgbtBlue +  empty[i + 1][j + 1].rgbtBlue;

                red = empty[i][j].rgbtRed + empty[i][j + 1].rgbtRed +  empty[i + 1][j].rgbtRed +  empty[i + 1][j + 1].rgbtRed;

                green = empty[i][j].rgbtGreen +  empty[i][j + 1].rgbtGreen +  empty[i + 1][j].rgbtGreen +  empty[i + 1][j + 1].rgbtGreen;

                averageBlue = round(blue / 4);
                averageRed = round(red / 4);
                averageGreen = round(green / 4);

            }
            else if (i == 0 && j == (m -  1))
            {
                blue = empty[i][j - 1].rgbtBlue +  empty[i][j].rgbtBlue + empty[i + 1][j - 1].rgbtBlue +  empty[i + 1][j].rgbtBlue;

                red = empty[i][j - 1].rgbtRed + empty[i][j].rgbtRed +  empty[i + 1][j - 1].rgbtRed +  empty[i + 1][j].rgbtRed;

                green = empty[i][j - 1].rgbtGreen +  empty[i][j].rgbtGreen +  empty[i + 1][j - 1].rgbtGreen +  empty[i + 1][j].rgbtGreen;

                averageBlue = round(blue / 4);
                averageRed = round(red / 4);
                averageGreen = round(green / 4);

            }
            else if (i == (n - 1) && j == 0)
            {
                blue = empty[i - 1][j].rgbtBlue + empty[i - 1][j + 1].rgbtBlue + empty[i][j].rgbtBlue
                       + empty[i][j + 1].rgbtBlue;

                red = empty[i - 1][j].rgbtRed + empty[i-1][j + 1].rgbtRed +  empty[i][j].rgbtRed
                      + image[i][j + 1].rgbtRed;

                green = empty[i-1][j].rgbtGreen + empty[i-1][j + 1].rgbtGreen + empty[i][j].rgbtGreen
                        + empty[i][j + 1].rgbtGreen;


                averageBlue = round(blue / 4);
                averageRed = round(red / 4);
                averageGreen = round(green / 4);
            }
            else if (i == (n - 1) && j == (m - 1))
            {
                blue = empty[i - 1][j - 1].rgbtBlue + empty[i - 1][j].rgbtBlue + empty[i][j - 1].rgbtBlue +  empty[i][j].rgbtBlue;

                red = empty[i - 1][j - 1].rgbtRed + empty[i - 1][j].rgbtRed +  empty[i][j - 1].rgbtRed
                      + empty[i][j].rgbtRed;

                green = empty[i - 1][j - 1].rgbtGreen + empty[i - 1][j].rgbtGreen + empty[i][j - 1].rgbtGreen
                        + empty[i][j].rgbtGreen;

                averageBlue = round(blue / 4);
                averageRed = round(red / 4);
                averageGreen = round(green / 4);
            }
            else if (i == 0 && j > 0)
            {
                blue = empty[i][j - 1].rgbtBlue +  empty[i][j].rgbtBlue +  empty[i][j + 1].rgbtBlue +  empty[i + 1][j - 1].rgbtBlue
                       + empty[i + 1][j].rgbtBlue +  empty[i + 1][j + 1].rgbtBlue;

                red = empty[i][j - 1].rgbtRed +  empty[i][j].rgbtRed+  empty[i][j + 1].rgbtRed +  empty[i + 1][j - 1].rgbtRed
                      + empty[i + 1][j].rgbtRed +  empty[i + 1][j + 1].rgbtRed;

                green = empty[i][j - 1].rgbtGreen +  empty[i][j].rgbtGreen+  empty[i][j + 1].rgbtGreen +  empty[i + 1][j - 1].rgbtGreen
                        + empty[i + 1][j].rgbtGreen +  empty[i + 1][j + 1].rgbtGreen;

                averageBlue = round(blue / 6);
                averageRed = round(red / 6);
                averageGreen = round(green / 6);
            }
            else if (i == (n - 1) && j > 0)
            {
                blue = empty[i - 1][j - 1].rgbtBlue + empty[i-1][j].rgbtBlue + empty[i - 1][j + 1].rgbtBlue +  empty[i][j - 1].rgbtBlue
                       + empty[i][j].rgbtBlue + empty[i][j + 1].rgbtBlue;

                red = empty[i - 1][j - 1].rgbtRed + empty[i - 1][j].rgbtRed + empty[i-1][j + 1].rgbtRed +  empty[i][j - 1].rgbtRed
                      + empty[i][j].rgbtRed +  empty[i][j + 1].rgbtRed;

                green = empty[i - 1][j - 1].rgbtGreen + empty[i - 1][j].rgbtGreen + empty[i-1][j + 1].rgbtGreen +  empty[i][j - 1].rgbtGreen
                        +  empty[i][j].rgbtGreen + empty[i][j + 1].rgbtGreen;

                averageBlue = round(blue / 6);
                averageRed = round(red / 6);
                averageGreen = round(green / 6);
            }
            else if (i > 0 && j == 0)
            {
                blue = empty[i - 1][j].rgbtBlue + empty[i - 1][j + 1].rgbtBlue +  empty[i][j].rgbtBlue
                       + empty[i][j + 1].rgbtBlue + empty[i + 1][j].rgbtBlue +  empty[i + 1][j + 1].rgbtBlue;

                red =  empty[i - 1][j].rgbtRed + empty[i - 1][j + 1].rgbtRed + empty[i][j].rgbtRed+  empty[i][j + 1].rgbtRed
                       + empty[i + 1][j].rgbtRed +  empty[i + 1][j + 1].rgbtRed;

                green = empty[i - 1][j].rgbtGreen + empty[i - 1][j + 1].rgbtGreen + empty[i][j].rgbtGreen
                        + empty[i][j + 1].rgbtGreen + empty[i + 1][j].rgbtGreen +  empty[i + 1][j + 1].rgbtGreen;

                averageBlue = round(blue / 6);
                averageRed = round(red / 6);
                averageGreen = round(green / 6);

            }
            else if (i > 0 && j == (m - 1))
            {
                blue = empty[i - 1][j - 1].rgbtBlue + empty[i - 1][j].rgbtBlue + empty[i][j - 1].rgbtBlue +  empty[i][j].rgbtBlue
                       +  empty[i + 1][j - 1].rgbtBlue +  empty[i + 1][j].rgbtBlue;

                red = empty[i - 1][j - 1].rgbtRed + empty[i - 1][j].rgbtRed + empty[i][j - 1].rgbtRed +  empty[i][j].rgbtRed
                      +  empty[i + 1][j - 1].rgbtRed +  empty[i + 1][j].rgbtRed;

                green = empty[i - 1][j - 1].rgbtGreen + empty[i - 1][j].rgbtGreen + empty[i][j - 1].rgbtGreen +  empty[i][j].rgbtGreen
                        +  empty[i + 1][j - 1].rgbtGreen +  empty[i + 1][j].rgbtGreen;

                averageBlue = round(blue / 6);
                averageRed = round(red / 6);
                averageGreen = round(green / 6);
            }
            else if (i>0 && j>0)
            {
                blue = empty[i - 1][j - 1].rgbtBlue + empty[i - 1][j].rgbtBlue + empty[i - 1][j + 1].rgbtBlue +  empty[i][j - 1].rgbtBlue +  empty[i][j].rgbtBlue
                       +  empty[i][j + 1].rgbtBlue +  empty[i + 1][j - 1].rgbtBlue +  empty[i + 1][j].rgbtBlue +  empty[i + 1][j + 1].rgbtBlue;

                red = empty[i - 1][j - 1].rgbtRed + empty[i - 1][j].rgbtRed + empty[i-1][j + 1].rgbtRed +  empty[i][j - 1].rgbtRed +  empty[i][j].rgbtRed
                      +  empty[i][j + 1].rgbtRed +  empty[i + 1][j - 1].rgbtRed +  empty[i + 1][j].rgbtRed +  empty[i + 1][j + 1].rgbtRed;

                green = empty[i-1][j - 1].rgbtGreen + empty[i-1][j].rgbtGreen + empty[i-1][j + 1].rgbtGreen +  empty[i][j - 1].rgbtGreen +  empty[i][j].rgbtGreen
                        +  empty[i][j + 1].rgbtGreen +  empty[i + 1][j -1].rgbtGreen +  empty[i + 1][j].rgbtGreen +  empty[i + 1][j + 1].rgbtGreen;

                averageBlue = round(blue / 9);
                averageRed = round(red / 9);
                averageGreen = round(green / 9);

            }

            image[i][j].rgbtBlue = averageBlue;
            image[i][j].rgbtRed = averageRed;
            image[i][j].rgbtGreen = averageGreen;

        }
    }
    return;
}
