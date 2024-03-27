// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1430;

// Hash table
node *table[N];

// Keep track of how many words are in the dictionary
unsigned int total_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int location = hash(word);

    for (node *tmp = table[location]; tmp != NULL; tmp = tmp->next) //Run trought all the linked list searching for the word
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //Multiply the ASCII value of the first 2 chars with the lenght of the word
    long hash_index = (tolower(word[0]) * tolower(word[1]) * strlen(word)) % N;
    return hash_index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r"); //Open the dictionary file
    if (file == NULL) //If fopen fails
    {
        return false;
    }

    node *n = malloc(sizeof(node)); //create a node
    if (n == NULL) //If Malloc fails
    {
        fclose(file);
        return false;
    }


    while (fgets(n->word, (LENGTH + 2), file) != NULL) //Fill the hash table with words
    {
        n->word[strcspn(n->word, "\n")] = '\0'; //adjust the array to iliminate the '\n' character
        int location = hash(n->word); //Find the proper location to put the word in the hash table

        //Insert the word in the hash table
        if (table[location] == NULL)
        {
            n->next = NULL;
            table[location] = n;
        }
        else
        {
            n->next = table[location];
            table[location] = n;
        }

        n = malloc(sizeof(node)); //Create a node
        if (n == NULL) //If Malloc fails
        {
            fclose(file);
            return false;
        }
        //Update how many words are loaded
        total_size++;
    }

    if (ferror(file)) //Check if fgets got an error reading the file
    {
        free(n);
        fclose(file);
        return false;
    }
    else
    {
        free(n);
        fclose(file);
        return true;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return total_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) //Free all the linked lists
    {
        node *list = table[i];
        while (list != NULL) //Go to the next node and free the old one
        {
            node *tmp = list->next;
            free(list);
            list = tmp;
        }
    }
    return true;
}
