/* Dasprog C - 2019
William Handi Wijaya
0087
     
Program untuk menghitung banyak koin yang diberikan dalam kembalian.
Digunakan input berupa mata uang dollar dan kembalian dalam koin cent.
*/

#include <stdio.h>
#include <math.h>

float get_change_amount();

int main(void)
{
    // Get change
    float dollars = get_change_amount();
    int cents = round(dollars * 100);
    int count = 0;
    // Deciding which cents to be used
    // 25 cent coin
    while (cents - 25 >= 0)
    {
        count++;
        cents = cents - 25;
    }
    // 10 cent coin
    while (cents - 10 >= 0)
    {
        count++;
        cents = cents - 10;
    }
    // 5 cent coin
    while (cents - 5 >= 0)
    {
        count++;
        cents = cents - 5;
    }
    // 1 cent coin
    while (cents - 1 >= 0)
    {
        count++;
        cents = cents - 1;
    }
    // Print how many coins is used
    printf("%i\n", count);
    return 0;
}
    
// Define get_change_amount
float get_change_amount(void)
{
    float x;
    do
    {
    	printf("Change: ");
    	scanf("%f", &x);
    }
    while (x <= 0);
    return x;
}

