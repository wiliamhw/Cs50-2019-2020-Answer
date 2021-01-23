#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t BYTE;

bool isjpg(BYTE buffer[]);

int main(int argc, char *argv[])
{
    // If command-line argument != 1
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // Remember filename
    char *infile = argv[1];

    // If file can't be opened for reading
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s file.\n", infile);
        return 2;
    }

    // Declare needed variabel
    BYTE buffer[512];
    int counter = 0;
    char filename[8];
    bool opened = false;
    FILE *outfile = NULL;

    // While not EOF
    while (fread(&buffer, sizeof(BYTE) * 1, 512, inptr) == 512)
    {
        // If start of a new JPEG is found
        if (isjpg(buffer))
        {
            // If already found JPEG
            if (opened)
            {
                fclose(outfile);
                opened = false;
            }

            // Start JPEG
            sprintf(filename, "%03i.jpg", counter);
            outfile = fopen(filename, "w");
            opened = true;
            counter++;
        }

        // Default -> write data
        if (opened)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, outfile);
        }
        else
        {
            continue;
        }
    }
    fclose(outfile);

    return 0;
}

bool isjpg(BYTE buffer[])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    else
    {
        return false;
    }
}