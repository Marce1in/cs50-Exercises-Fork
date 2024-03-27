#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool checker(string key);
bool abc_check(char abc[]);
char encryption(char letter, string key);

int main(int argc, string argv[])
{
    //Check if the program has received only one command
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //Check if the program has 26 letters, all alphabetical and all different from each one
    if (checker(argv[1]) == false)
    {
        printf("Key must contain 26 different characters.\n");
        return 1;
    }
    //gets a text to encrypt from the user
    string pltext = get_string("plaintext: ");

    //encrypts the text using the key as base
    for (int i = 0; pltext[i] != ''; i++)
    {
        pltext[i] = encryption(pltext[i], argv[1]);
    }

    //print the crypted text
    printf("ciphertext: %s\n", pltext);
}
bool checker(string key)
{
    //Verify if the string have 26 letters in total
    if (strlen(key) != 26)
    {
        return false;
    }
    //Verify if all the string letters are alphabetical
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            return false;
        }
    }
    //Verify if the string contain each letter exactly once
    if (abc_check(key) == false)
    {
        return false;
    }

    return true;
}
//Make the verification if the string contains each letter exactly once
bool abc_check(char abc[])
{
    //Array of chars in the alphabetical order
    char alphaa[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //counter
    int k = 0;

    //Uppercase all the letters (globally)
    for (int i = 0; abc[i] != '\0'; i++)
    {
        abc[i] = toupper(abc[i]);
    }

    //check every letter
    for (int i = 0; abc[i] != '\0'; i++)
    {
        for (int j = 0; alphaa[j] != '\0'; j++)
        {
            if (abc[i] == alphaa[j])
            {
                alphaa[j] = '0';
                k++;
            }
        }
    }
    //if has any duplicate letters "k" will never hit 26
    if (k == 26)
    {
        return true;
    }
    return false;
}
//Encrypt the text
char encryption(char letter, string key)
{
    //Array of chars in the alphabetical order
    char alphab[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //Shuffle the letters using the key as a base
    for (int i = 0; alphab[i] != '\0'; i++)
    {
        //if the letter is uppercase
        if (letter == alphab[i])
        {
            letter = key[i];
            return letter;
        }
        //if the letter is lowercase
        else if (letter == alphab[i] + 32)
        {
            letter = key[i];
            letter = tolower(letter);
            return letter;
        }
    }
    //if is not a letter
    return letter;
}