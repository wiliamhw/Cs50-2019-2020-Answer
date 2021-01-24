/* Dasprog C - 2019
William Handi Wijaya
0087
	 
Program untuk membuat piramid dengan ketinggian tergantung user input.
Input tidak melebihi 8.
*/

#include <stdio.h>

int get_height();

// Make pyramid
int main(void)
{
    int Height = get_height();
    // Untuk tiap baris
    for (int i = 0; i < Height; i++)
    {
    	// Bagian kiri
        for (int j = 0; j < Height - i - 1; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        // Spasi tengah
        printf("  ");
        // Bagian kanan
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }         
        printf("\n");
    }
}

// My Function
int get_height(void)
{
    int x;
    do
    {
        printf("Height: ");
        scanf("%d", &x);
    }
    while (x < 1 || x > 8);
    return x;
}

