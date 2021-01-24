/*
Program to change plaintext to Vigenere's ciphertext.
Command: ./caesar <key>
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef char* String;

bool valid(String prompt);
int shift(char c);
int convert(char input, int max, int min, int key);

int main(int argc, String argv[])
{
    String inKey = NULL;
    printf("Insert key: ");
    scanf("%s", inKey);
    
    if (valid(inKey))
    {
        // Get user input
        String input = NULL;
        printf("plaintext: ");
        scanf("%s", input);
        
        printf("ciphertext: ");
        
        // Print based on char type
        int j = 0;
        for (int i = 0; i < strlen(input); i++)
        {
            if (isalpha(*(input + i)))
            {
                // Keyword counter
                int key =  shift(*(inKey + i));
                if (isupper(*(input + i)))
                {
                    int max = 90;
                    int min = 65;
                    convert(*(input + i), max, min, key);
                }
                else
                {
                    int max = 122;
                    int min = 97;
                    convert(*(input + i), max, min, key);
                }
                // Add keyword counter by 1 every alphabet converted
                j++;
                while (j >= strlen(argv[1]))
                {
                    j = j - strlen(argv[1]);
                }
            }
            else
            {
                printf("%c", input[i]);
            }
        }
        // End program
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage : ./vigenere keyword\n");
        return 1;
    }
}

// Define converter
int convert(char input, int max, int min, int key)
{
    int n = (int) input;
    n = n + key;
    while (n > max)
        n = n - max + min -1;
    printf("%c",n);
    return 0;
}

// Shift char to number
int shift(char c)
{
    int ASCII = (int) c;
    if (ASCII >= 'A' && ASCII <= 'Z')
    {
        ASCII = ASCII - 65;
        return ASCII;
    }
    else
    {
        ASCII = ASCII - 97;
        return ASCII;
    }
}


// Check input is all alphabet
bool valid(String prompt)
{
    int j = strlen(prompt);
    int counter = 0;
    for (int i = 0; i < j; i++)
    {
        if (isalpha(*(prompt + i)))
        {
            counter++;
        }
    }
    if (counter == j)
    {
        return true;
    }
    else
    {
        return false;
    }
}
