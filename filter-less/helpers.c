#include "helpers.h"
#include <math.h>

void blur_neighbors(int a, int b, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE bmpcopy[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Create the average number betwen Red, Green and blue colors
            double rgb_average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            rgb_average = round(rgb_average);
            //Set every color to the average number, putting all pixels in grayscale
            image[i][j].rgbtRed = rgb_average;
            image[i][j].rgbtGreen = rgb_average;
            image[i][j].rgbtBlue = rgb_average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Use a formula to find the sepia equivalent color
            double sepia_R = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            double sepia_G = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            double sepia_B = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            //Round the colors
            sepia_R = round(sepia_R);
            sepia_G = round(sepia_G);
            sepia_B = round(sepia_B);
            //Verify if the color cap of 255 is meet
            if (sepia_R > 255)
            {
                sepia_R = 255;
            }
            if (sepia_G > 255)
            {
                sepia_G = 255;
            }
            if (sepia_B > 255)
            {
                sepia_B = 255;
            }
            //Put the Sepia colors in each pixel
            image[i][j].rgbtRed = sepia_R;
            image[i][j].rgbtGreen = sepia_G;
            image[i][j].rgbtBlue = sepia_B;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //Acess the array in reversed order
            int reverse = (width - 1) - j;
            //Save the values that's going to get swaped
            int reflect_R = image[i][j].rgbtRed;
            int reflect_G = image[i][j].rgbtGreen;
            int reflect_B = image[i][j].rgbtBlue;
            //Swap the start with the end
            image[i][j].rgbtRed = image[i][reverse].rgbtRed;
            image[i][j].rgbtGreen = image[i][reverse].rgbtGreen;
            image[i][j].rgbtBlue = image[i][reverse].rgbtBlue;
            //Swap the end with the start
            image[i][reverse].rgbtRed = reflect_R;
            image[i][reverse].rgbtGreen = reflect_G;
            image[i][reverse].rgbtBlue = reflect_B;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a copy of the image array
    RGBTRIPLE bmpcopy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            bmpcopy[i][j] = image[i][j];
        }
    }
    //Blur each pixel with the average value of his neighbors
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blur_neighbors(i, j, height, width, image, bmpcopy);
        }
    }
    return;
}

void blur_neighbors(int a, int b, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE bmpcopy[height][width])
{
    double rgb_averageR = 0; //Average Red of all neighbors
    double rgb_averageG = 0; //Average Green of all neighbors
    double rgb_averageB = 0; //Average blue of all neighbors

    float neighbors_total = 0; //count how many neighbors exist, ignoring corners and edges

    for (int i = a - 1; i < a + 2; i++)
    {
        for (int j = b - 1; j < b + 2; j++)
        {
            if (i < 0 || i >= height) //Check if i is not going out bounds of the array
            {
                break;
            }
            if (j >= 0 && j < width) //Check if j is not going out bounds of the array
            {
                neighbors_total++;
                //Sum all neighbor pixels
                rgb_averageR = bmpcopy[i][j].rgbtRed + rgb_averageR;
                rgb_averageG = bmpcopy[i][j].rgbtGreen + rgb_averageG;
                rgb_averageB = bmpcopy[i][j].rgbtBlue + rgb_averageB;
            }
        }
    }
    //Find the average and round all RGB values of the neighbors pixels
    image[a][b].rgbtRed = round(rgb_averageR / neighbors_total);
    image[a][b].rgbtGreen = round(rgb_averageG / neighbors_total);
    image[a][b].rgbtBlue = round(rgb_averageB / neighbors_total);

    return;
}