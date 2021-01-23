/*
Program to change plaintext to Caesar's ciphertext.
Command: ./caesar <key>
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char* String;

bool valid();
int convert();
String getString();

int main(int argc, String argv[])
{
    if (argc == 2 && valid(argv[1]))
    {
        // Get user input
        int n = atoi(argv[1]);
        String plain = getString("plaintext: ");
        printf("ciphertext: ");
        
        // Process and preserve char based on its type
        for (int i = 0; i < strlen(plain); i++)
        {
            // Check if plain[i] is alphabet
            if (isalpha(plain[i]))
            {
                if (isupper(plain[i]))
                {
                    int max = 90;
                    int min = 65;
                    convert(plain[i], n, max, min);
                }
                else
                {
                    int max = 122;
                    int min = 97;
                    convert(plain[i], n, max, min);
                }
            }
            else
            {
                printf("%c", plain[i]);
            }
        } 
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

// Convert plaintext and print cyphertext char
int convert(String prompt, int n, int max, int min)
{
    int ASCII = (int) prompt;
    int cipher = (ASCII + n);
    while (cipher > max)
    {
        cipher = cipher % max + min - 1; 
    }
    printf("%c", cipher);
    return 0;
}

// Check the argument is in digit
bool valid(String prompt)
{
    int counter = 0;
    int j = strlen(prompt);
    for (int i = 0; i < j; i++)
        if (isdigit(prompt[i]))
        {
            counter++;
        }
    if (counter == j && prompt >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

const String getString(const String prompt) 
{
    printf("%s", prompt);
    static char temp[64];
    fgets(temp, sizeof(temp) / sizeof(char), stdin);
    return temp;
}