// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 10000

// Loaded flag
bool loaded = false;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    // Ref: https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
    unsigned int sum = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        sum = (sum << 2) ^ tolower(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Insert word to new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }
        else
        {
            strcpy(n->word, word);
            n->next = NULL;
        }

        // Insert new node to linked list
        unsigned int index = hash(word);
        if (hashtable[index])
        {
            n->next = hashtable[index]->next;
            hashtable[index]->next = n;
        }
        else
        {
            hashtable[index] = n;
        }
    }

    // Close dictionary
    loaded = true;
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        int count = 0;
        for (int i = 0; i < N; i++)
        {
            if (hashtable[i])
            {
                node *tmp = hashtable[i];
                while (tmp)
                {
                    count++;
                    tmp = tmp->next;
                }
            }
        }
        return count;
    }
    else return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    unsigned int index = hash(word);
    node *trav = hashtable[index];
    while (trav)
    {
        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
        }
        else
        {
            trav = trav->next;
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *trav = hashtable[i];
        while (trav)
        {
            node *tmp = trav;
            trav = trav->next;
            free(tmp);
        }
    }
    return true;
}