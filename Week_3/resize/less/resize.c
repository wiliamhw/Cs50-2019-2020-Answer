/* Dasprog C - 2019
William Handi Wijaya
0087

Program untuk memperbesar suatu gambar berformat bmp.
*/

#include <stdio.h>
#include <stdlib.h>

// Masukan header yang berisi custom data type dan struct
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize size infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    int n = atoi(argv[1]);

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_old;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_old = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_old;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_old = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Resize canvas
    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine padding for scanlines
    int old_padding = (4 - (bi_old.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Change image size
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);

    // Change file size
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE temp[bi.biWidth];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi_old.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi_old.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            for (int k = 0; k < n; k++)
            {
                temp[(j * n) + k] = triple;
            }
        }

        // skip over infile padding, if any
        fseek(inptr, old_padding, SEEK_CUR);

        for (int k = 0; k < n; k++)
        {
            fwrite(temp, sizeof(RGBTRIPLE), bi.biWidth, outptr);
            for (int a = 0; a < padding; a++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
