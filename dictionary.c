// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 2000;

// Hash table
node *table[N];

//Keeping track of the number of words loaded
int i = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int indexed = hash(word);

    node *cursor = table[indexed];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    //Adapted from https://github.com/hexangel616/CS50
    //www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;
    while ((c = tolower(*word++)))
    {
        // << is the left shift operator
        // http://www.fredosaurus.com/notes-cpp/expressions/bitops.html
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *diction = fopen(dictionary, "r");


    if (diction != NULL)
    {
        char word[LENGTH + 1];
        while (fscanf(diction, "%s", word) != EOF)
        {
            node *newNode = malloc(sizeof(node));

            if (newNode == NULL)
            {
                return false;
            }

            strcpy(newNode->word, word);

            int hashIndex = hash(word);

            newNode->next = table[hashIndex];

            table[hashIndex] = newNode;

            i++;
        }

        fclose(diction);
    }

    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return i;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int j = 0; j < N; j++)
    {
        node *cursor = table[j];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
