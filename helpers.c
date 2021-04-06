#include "helpers.h"
#include "stdio.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through each row and within each pixel, get the average of pixel.rgbtGreen, pixel.rgbtBlue and pixel.rgbtRed values and set each of them to that average

    for (int i = 0; i < height; i++) // iterate through rows
    {
        for (int j = 0; j < width; j++) // iterate through pixels
        {
            RGBTRIPLE pixel = image[i][j];
            // divide by 3.0 and then round in order to get a float that will round up if ending >= .5 (default for dividing integers by integers is rounding down)
            int average = round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // iterate through rows
    {
        for (int j = 0; j < width; j++) // iterate through pixels
        {
            RGBTRIPLE pixel = image[i][j];

            int blue = round(pixel.rgbtBlue * 0.131 + pixel.rgbtGreen * 0.534 + pixel.rgbtRed * 0.272);
            int green = round(pixel.rgbtBlue * 0.168 + pixel.rgbtGreen * 0.686 + pixel.rgbtRed * 0.349);
            int red = round(pixel.rgbtBlue * 0.189 + pixel.rgbtGreen * 0.769 + pixel.rgbtRed * 0.393);

            if (blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = blue;
            }

            if (green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = green;
            }

            if (red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = red;
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // create a reflection by copying left to right from image to new object right to left

    RGBTRIPLE reflection[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < width; j++, k--)
        {
            reflection[i][k] = image[i][j];
        }
    }

    // copy reflection back to image variable

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = reflection[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a blurred copy

    RGBTRIPLE blurred[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // top left
            if (i == 0 && j == 0)
            {
                RGBTRIPLE pixel = image[i][j];
                RGBTRIPLE pixel_r = image[i][j + 1];
                RGBTRIPLE pixel_d = image[i + 1][j];
                RGBTRIPLE pixel_dr = image[i + 1][j + 1];

                blurred[i][j].rgbtRed = round((pixel.rgbtRed + pixel_r.rgbtRed + pixel_d.rgbtRed + pixel_dr.rgbtRed) / 4.0);
                blurred[i][j].rgbtGreen = round((pixel.rgbtGreen + pixel_r.rgbtGreen + pixel_d.rgbtGreen + pixel_dr.rgbtGreen) / 4.0);
                blurred[i][j].rgbtBlue = round((pixel.rgbtBlue + pixel_r.rgbtBlue + pixel_d.rgbtBlue + pixel_dr.rgbtBlue) / 4.0);
            }
            // top right
            else if (i == 0 && j == width - 1)
            {
                RGBTRIPLE pixel_l = image[i][j - 1];
                RGBTRIPLE pixel = image[i][j];
                RGBTRIPLE pixel_dl = image[i + 1][j - 1];
                RGBTRIPLE pixel_d = image[i + 1][j];

                blurred[i][j].rgbtRed = round((pixel_l.rgbtRed + pixel.rgbtRed + pixel_dl.rgbtRed + pixel_d.rgbtRed) / 4.0);
                blurred[i][j].rgbtGreen = round((pixel_l.rgbtGreen + pixel.rgbtGreen + pixel_dl.rgbtGreen + pixel_d.rgbtGreen) / 4.0);
                blurred[i][j].rgbtBlue = round((pixel_l.rgbtBlue + pixel.rgbtBlue + pixel_dl.rgbtBlue + pixel_d.rgbtBlue) / 4.0);
            }
            // top middle
            else if (i == 0)
            {
                RGBTRIPLE pixel_l = image[i][j - 1];
                RGBTRIPLE pixel = image[i][j];
                RGBTRIPLE pixel_r = image[i][j + 1];
                RGBTRIPLE pixel_dl = image[i + 1][j - 1];
                RGBTRIPLE pixel_d = image[i + 1][j];
                RGBTRIPLE pixel_dr = image[i + 1][j + 1];

                blurred[i][j].rgbtRed = round((pixel_l.rgbtRed + pixel.rgbtRed + pixel_r.rgbtRed + pixel_dl.rgbtRed + pixel_d.rgbtRed +
                                               pixel_dr.rgbtRed) / 6.0);
                blurred[i][j].rgbtGreen = round((pixel_l.rgbtGreen + pixel.rgbtGreen + pixel_r.rgbtGreen + pixel_dl.rgbtGreen + pixel_d.rgbtGreen +
                                                 pixel_dr.rgbtGreen) / 6.0);
                blurred[i][j].rgbtBlue = round((pixel_l.rgbtBlue + pixel.rgbtBlue + pixel_r.rgbtBlue + pixel_dl.rgbtBlue + pixel_d.rgbtBlue +
                                                pixel_dr.rgbtBlue) / 6.0);
            }
            // bottom left
            else if (i == height - 1 && j == 0)
            {
                RGBTRIPLE pixel_u = image[i - 1][j];
                RGBTRIPLE pixel_ur = image[i - 1][j + 1];
                RGBTRIPLE pixel = image[i][j];
                RGBTRIPLE pixel_r = image[i][j + 1];

                blurred[i][j].rgbtRed = round((pixel_u.rgbtRed + pixel_ur.rgbtRed + pixel.rgbtRed + pixel_r.rgbtRed) / 4.0);
                blurred[i][j].rgbtGreen = round((pixel_u.rgbtGreen + pixel_ur.rgbtGreen + pixel.rgbtGreen + pixel_r.rgbtGreen) / 4.0);
                blurred[i][j].rgbtBlue = round((pixel_u.rgbtBlue + pixel_ur.rgbtBlue + pixel.rgbtBlue + pixel_r.rgbtBlue) / 4.0);
            }
            // left middle
            else if (j == 0)
            {
                RGBTRIPLE pixel_u = image[i - 1][j];
                RGBTRIPLE pixel_ur = image[i - 1][j + 1];
                RGBTRIPLE pixel = image[i][j];
                RGBTRIPLE pixel_r = image[i][j + 1];
                RGBTRIPLE pixel_d = image[i + 1][j];
                RGBTRIPLE pixel_dr = image[i + 1][j + 1];

                blurred[i][j].rgbtRed = round((pixel_u.rgbtRed + pixel_ur.rgbtRed + pixel.rgbtRed + pixel_r.rgbtRed + pixel_d.rgbtRed +
                                               pixel_dr.rgbtRed) / 6.0);
                blurred[i][j].rgbtGreen = round((pixel_u.rgbtGreen + pixel_ur.rgbtGreen + pixel.rgbtGreen + pixel_r.rgbtGreen + pixel_d.rgbtGreen +
                                                 pixel_dr.rgbtGreen) / 6.0);
                blurred[i][j].rgbtBlue = round((pixel_u.rgbtBlue + pixel_ur.rgbtBlue + pixel.rgbtBlue + pixel_r.rgbtBlue + pixel_d.rgbtBlue +
                                                pixel_dr.rgbtBlue) / 6.0);
            }
            // bottom right
            else if (i == height - 1 && j == width - 1)
            {
                RGBTRIPLE pixel_ul = image[i - 1][j - 1];
                RGBTRIPLE pixel_u = image[i - 1][j];
                RGBTRIPLE pixel_l = image[i][j - 1];
                RGBTRIPLE pixel = image[i][j];

                blurred[i][j].rgbtRed = round((pixel_ul.rgbtRed + pixel_u.rgbtRed + pixel_l.rgbtRed + pixel.rgbtRed) / 4.0);
                blurred[i][j].rgbtGreen = round((pixel_ul.rgbtGreen + pixel_u.rgbtGreen + pixel_l.rgbtGreen + pixel.rgbtGreen) / 4.0);
                blurred[i][j].rgbtBlue = round((pixel_ul.rgbtBlue + pixel_u.rgbtBlue + pixel_l.rgbtBlue + pixel.rgbtBlue) / 4.0);
            }
            // bottom middle
            else if (i == height - 1)
            {
                RGBTRIPLE pixel_ul = image[i - 1][j - 1];
                RGBTRIPLE pixel_u = image[i - 1][j];
                RGBTRIPLE pixel_ur = image[i - 1][j + 1];
                RGBTRIPLE pixel_l = image[i][j - 1];
                RGBTRIPLE pixel = image[i][j];
                RGBTRIPLE pixel_r = image[i][j + 1];

                blurred[i][j].rgbtRed = round((pixel_ul.rgbtRed + pixel_u.rgbtRed + pixel_ur.rgbtRed + pixel_l.rgbtRed + pixel.rgbtRed +
                                               pixel_r.rgbtRed) / 6.0);
                blurred[i][j].rgbtGreen = round((pixel_ul.rgbtGreen + pixel_u.rgbtGreen + pixel_ur.rgbtGreen + pixel_l.rgbtGreen + pixel.rgbtGreen +
                                                 pixel_r.rgbtGreen) / 6.0);
                blurred[i][j].rgbtBlue = round((pixel_ul.rgbtBlue + pixel_u.rgbtBlue + pixel_ur.rgbtBlue + pixel_l.rgbtBlue + pixel.rgbtBlue +
                                                pixel_r.rgbtBlue) / 6.0);
            }
            // right middle
            else if (j == width - 1)
            {
                RGBTRIPLE pixel_ul = image[i - 1][j - 1];
                RGBTRIPLE pixel_u = image[i - 1][j];
                RGBTRIPLE pixel_l = image[i][j - 1];
                RGBTRIPLE pixel = image[i][j];
                RGBTRIPLE pixel_dl = image[i + 1][j - 1];
                RGBTRIPLE pixel_d = image[i + 1][j];

                blurred[i][j].rgbtRed = round((pixel_ul.rgbtRed + pixel_u.rgbtRed + pixel_l.rgbtRed + pixel.rgbtRed + pixel_dl.rgbtRed +
                                               pixel_d.rgbtRed) / 6.0);
                blurred[i][j].rgbtGreen = round((pixel_ul.rgbtGreen + pixel_u.rgbtGreen + pixel_l.rgbtGreen + pixel.rgbtGreen + pixel_dl.rgbtGreen +
                                                 pixel_d.rgbtGreen) / 6.0);
                blurred[i][j].rgbtBlue = round((pixel_ul.rgbtBlue + pixel_u.rgbtBlue + pixel_l.rgbtBlue + pixel.rgbtBlue + pixel_dl.rgbtBlue +
                                                pixel_d.rgbtBlue) / 6.0);
            }
            // middle
            else
            {
                RGBTRIPLE pixel_ul = image[i - 1][j - 1];
                RGBTRIPLE pixel_u = image[i - 1][j];
                RGBTRIPLE pixel_ur = image[i - 1][j + 1];
                RGBTRIPLE pixel_l = image[i][j - 1];
                RGBTRIPLE pixel = image[i][j];
                RGBTRIPLE pixel_r = image[i][j + 1];
                RGBTRIPLE pixel_dl = image[i + 1][j - 1];
                RGBTRIPLE pixel_d = image[i + 1][j];
                RGBTRIPLE pixel_dr = image[i + 1][j + 1];

                blurred[i][j].rgbtRed = round((pixel_ul.rgbtRed + pixel_u.rgbtRed + pixel_ur.rgbtRed + pixel_l.rgbtRed + pixel.rgbtRed +
                                               pixel_r.rgbtRed + pixel_dl.rgbtRed + pixel_d.rgbtRed + pixel_dr.rgbtRed) / 9.0);
                blurred[i][j].rgbtGreen = round((pixel_ul.rgbtGreen + pixel_u.rgbtGreen + pixel_ur.rgbtGreen + pixel_l.rgbtGreen + pixel.rgbtGreen +
                                                 pixel_r.rgbtGreen + pixel_dl.rgbtGreen + pixel_d.rgbtGreen + pixel_dr.rgbtGreen) / 9.0);
                blurred[i][j].rgbtBlue = round((pixel_ul.rgbtBlue + pixel_u.rgbtBlue + pixel_ur.rgbtBlue + pixel_l.rgbtBlue + pixel.rgbtBlue +
                                                pixel_r.rgbtBlue + pixel_dl.rgbtBlue + pixel_d.rgbtBlue + pixel_dr.rgbtBlue) / 9.0);
            }
        }
    }

    // copy blurred version back to image variable

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurred[i][j];
        }
    }

    return;
}
