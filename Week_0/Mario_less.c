/* Dasprog C - 2019
William Handi Wijaya
0087

Program untuk membuat setengah piramid dengan ketinggian tergantung user input.
*/

#include <stdio.h>

int get_height();

// Make pyramid
int main()
{
    int Height = get_height();
    // Set height limit
    // Untuk tiap baris
    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Height - i - 1; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}   

// Get user input
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

