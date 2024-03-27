#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string key);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    //check if is really a single command-line
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    bool checker = only_digits(argv[1]);
    //check if the key is false
    if (checker == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //converts the key to a integer
    int key = atoi(argv[1]);
    //gets a text to encrypt from the user
    string pltext = get_string("plaintext: ");

    //take every char and send to the "rotate" function
    for (int i = 0; pltext[i] != '\0'; i++)
    {
        pltext[i] = rotate(pltext[i], key);
    }

    //print the cryted text
    printf("ciphertext: %s\n", pltext);

}
//check if the command-line (aka key) is valid
bool only_digits(string key)
{
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (isalpha(key[i]) || isspace(key[i]) || ispunct(key[i]))
        {
            return false;
        }
    }
    return true;
}
//rotate an char if the char is alphabetical
char rotate(char c, int n)
{
    //the latter that's goin to rotate
    char s = 0;
    //rotate the lowercase letters
    if (isalpha(c) && islower(c))
    {
        c = c - 97;
        s = (c + n) % 26;
        return s + 97;
    }
    //rotate the uppercase letters
    else if (isalpha(c) && isupper(c))
    {
        c = c - 65;
        s = (c + n) % 26;
        return s + 65;
    }
    //if is not a letter return the same character
    else
    {
        return c;
    }
}