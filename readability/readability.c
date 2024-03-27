#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //The text
    string text;
    //The sum of the letters
    int letsum;
    //The sum of the words
    int wordsum;
    //The sum of the sentences
    int sensum;
    //Get the text
    text = get_string("Your text, sir? \n");

    letsum = count_letters(text);

    wordsum = count_words(text);

    sensum = count_sentences(text);

    //Avarage number of letter per 100 words
    double l = (float) letsum / (float) wordsum * 100;
    //Avarage number of sentences per 100 words
    double s = (float) sensum / (float) wordsum * 100;
    //calculate the index with the formula and round the number for get the grade
    int index = (int) round(0.0588 * l - 0.296 * s - 15.8);
    //Print the right grade
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
//count the total letters of the text
int count_letters(string text)
{
    //counter
    int i = 0;
    //Sum of all the letters of the text
    int letsum = 0;
    //Count all the letters of the text
    while (text[i] != '\0')
    {

        if (isalpha(text[i]))
        {
            letsum++;
            i++;
        }
        else
        {
            i++;
        }

    }
    return letsum;
}
//count the total words of the text
int count_words(string text)
{
    //counter
    int i = 0;
    //Sum of all the words of the text
    int wordsum = 1;
    //Count all the words of the text
    while (text[i] != '\0')
    {

        if (isspace(text[i]))
        {
            wordsum++;
            i++;
        }
        else
        {
            i++;
        }

    }
    return wordsum;
}
//count the total sentences of the text
int count_sentences(string text)
{
    //counter
    int i = 0;
    //Sum of all the sentences of the text
    int sensum = 0;
    //Count all the sentences of the text
    while (text[i] != '\0')
    {

        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sensum++;
            i++;
        }
        else
        {
            i++;
        }

    }
    return sensum;
}