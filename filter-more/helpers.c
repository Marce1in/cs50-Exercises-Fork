#include "helpers.h"
#include <math.h>

void blur_neighbors(int a, int b, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE bmpcopy[height][width]);
void calculate_edges(int a, int b, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE bmpcopy[height][width]);


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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    //Calculate and find the edges of an image pixel by pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            calculate_edges((i - 1), (j - 1), height, width, image, bmpcopy);
        }
    }
    return;
}
void calculate_edges(int a, int b, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE bmpcopy[height][width])
{
    //Create the Gx "kernel"
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    double GxR = 0;
    double GxG = 0;
    double GxB = 0;

    //Create the Gy "kernel"
    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    double GyR = 0;
    double GyG = 0;
    double GyB = 0;

    //Apply the Gx and Gy kernels in the pixel and his neighbors (3x3 grid)
    for (int i = 0 ; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a < 0 || a >= height || b < 0 || b >= width) //If the pixel is going out bounds of the array, the value of the pixel is set do zero
            {
                GxR = (Gx[i][j] * 0) + GxR;
                GxG = (Gx[i][j] * 0) + GxG;
                GxB = (Gx[i][j] * 0) + GxB;

                GyR = (Gy[i][j] * 0) + GyR;
                GyG = (Gy[i][j] * 0) + GyG;
                GyB = (Gy[i][j] * 0) + GyB;
            }
            else
            {
                GxR = (Gx[i][j] * bmpcopy[a][b].rgbtRed) + GxR;
                GxG = (Gx[i][j] * bmpcopy[a][b].rgbtGreen) + GxG;
                GxB = (Gx[i][j] * bmpcopy[a][b].rgbtBlue) + GxB;

                GyR = (Gy[i][j] * bmpcopy[a][b].rgbtRed) + GyR;
                GyG = (Gy[i][j] * bmpcopy[a][b].rgbtGreen) + GyG;
                GyB = (Gy[i][j] * bmpcopy[a][b].rgbtBlue) + GyB;
            }
            b++;
        }
        //Reset the "b" value to his original
        b = b - 3;

        a++;
    }

    //Use the Sobel filter to combine Gx and Gy
    double GR = sqrt((GxR * GxR) + (GyR * GyR));
    double GG = sqrt((GxG * GxG) + (GyG * GyG));
    double GB = sqrt((GxB * GxB) + (GyB * GyB));

    //Verify if the color cap of 255 is meet
    if (GR > 255)
    {
        GR = 255;
    }
    if (GG > 255)
    {
        GG = 255;
    }
    if (GB > 255)
    {
        GB = 255;
    }

    //Change the pixel for his new value
    image[a - 2][b + 1].rgbtRed = round(GR);
    image[a - 2][b + 1].rgbtGreen = round(GG);
    image[a - 2][b + 1].rgbtBlue = round(GB);

    return;
}
