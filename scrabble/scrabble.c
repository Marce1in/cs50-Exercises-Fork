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

    //Print the winner
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
    //Array of chars in the alphabetical order
    char alphab[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //the sum of all points
    int total_points = 0;

    //Uppercase all the letters
    for (int i = 0; word[i] != '\0'; i++)
    {
        word[i] = toupper(word[i]);
    }

    //Sum each point
    for (int i = 0; word[i] != '\0'; i++)
    {
        for (int j = 0; alphab[j] != '\0'; j++)
        {
            if (word[i] == alphab[j])
            {
                total_points = total_points + POINTS[j];
            }
        }
    }
    return total_points;
}
