// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

unsigned int hash(const char word);
void destroy(node *tail);
void counter(node *trav, unsigned int *count);
// Represents trie
node *root;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Make root
    root = calloc(1, sizeof(node));

    // If not enough memory -> stop program
    if (!root)
    {
        unload();
        return false;
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

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // Make traversal node
        node *trav = root;

        // Traverse each char in word[i]
        for (int i = 0; word[i] != '\0'; i++)
        {
            unsigned int index = hash(word[i]);

            // Check the value of children[i];
            if (trav->children[index] == NULL)
            {
                node *n = calloc(1, sizeof(node));

                // If not enough memory -> stop program
                if (!n)
                {
                    unload();
                    return false;
                }

                trav->children[index] = n;
            }
            trav = trav->children[index];
        }
        // Set end of word
        trav->is_word = true;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;

    // Count size from tail
    counter(root, &count);

    return count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *trav = root;

    // Traverse each char in word
    for (int i = 0; word[i] != '\0'; i++)
    {
        unsigned int index = hash(word[i]);
        if (trav->children[index])
        {
            trav = trav->children[index];
        }
        else
        {
            return false;
        }
    }
    if (trav->is_word)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    destroy(root);
    return true;
}

////////////////// Function ///////////////////

void counter(node *trav, unsigned int *count)
{
    if (trav->is_word)
    {
        (*count)++;
        trav->is_word = false;
    }

    // Traverse every leaves and backtrack it
    for (int i = 0; i < N; i++)
    {
        if (trav->children[i])
        {
            counter(trav->children[i], count);
        }
    }

    return;
}

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char word)
{
    if (word == '\'')
    {
        return (N - 1);
    }
    else
    {
        return (tolower(word) - 'a');
    }
}

// Function to free root with recursion
void destroy(node *tail)
{
    if (!tail)
    {
        return;
    }

    // Traverse every leafves and backtrack it
    for (int i = 0; i < N; i++)
    {
        destroy(tail->children[i]);
    }
    free(tail);
}