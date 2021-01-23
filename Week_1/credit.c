/* Dasprog C- 2019
William Handi Wijaya
0087

Program untuk mengecek apakah suatu nomor kartu kredit valid atau tidak
dan menentukan jenis dari kartu kredit yang dimasukkan dengan menggunakan
algoritma Luhn.

Hanya bisa mengidentifikasi kartu kredit berjenis "America Express", "Visa",
dan "Mastercard".
*/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

long long get_long(void);
bool valid(long long prompt);
int get_lenght(long long l);

int main(void)
{
    // Get user input
    long long ccNum = get_long();
    int lenght = get_lenght(ccNum);

    // Get the first_two number of ccNum
    int first_two = (ccNum / (pow(10, (lenght - 2))));
    int first_one = (ccNum / (pow(10, (lenght - 1))));

    // Process the ccNum into its types
    if (valid(ccNum))
    {
        if ((first_two == 34 || first_two == 37) && lenght == 15)
        {
            printf("AMEX\n");
            return 0;
        }
        if (first_one == 4 && (lenght == 13 || lenght == 16))
        {
            printf("VISA\n");
            return 0;
        }
        if (first_two >= 51 && first_two <= 55 && lenght == 16)
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}

// Get user input
long long get_long(void)
{
	long long x;
	do
	{
		printf("Card Number: ");
		scanf("%lld", &x);
	}
	while (x < 1);
	return x;
}

// Get long lenght
int get_lenght(long long l)
{
    int n = 0;
    char buffer[24];
    sprintf(buffer, "%lld", l);
    while (buffer[n] != '\0')
    {
        n++;
    }
    return n;
}


// Check if luhn algoritm is valid
bool valid(long long prompt)
{
    // Declare needed variable
    int sum = 0;
    long long x = 100;
    long long y = 10;
    int max = 8;
    int result[max];
    int even[max];
    int odd[max];
    int digit_0[max];
    int digit_1[max];
    // Take second-to-last digit and times it by 2 (function)
    for (int i = 0; i < max; i++)
    {
        even[i] = (((prompt % x) / (x / 10)) * 2);
        x *= 100;
        // Pick even[i] digits if >= 10
        if (even[i] >= 10)
        {
            digit_0[i] = even[i] % 10;
            digit_1[i] = even[i] / 10;
            even[i] = 0;
        }
        else
        {
            digit_0[i] = 0;
            digit_1[i] = 0;
        }
        // Sum of all digits
        result[i] = even[i] + digit_0[i] + digit_1[i];
        sum += result[i];
    }
    // Take first-to-last digit
    for (int i = 0; i < max; i++)
    {
        odd[i] = ((prompt % y) / (y / 10));
        y *= 100;
        sum += odd[i];
    }
    // Check the last digit of sum
    int last_digit = sum % 10;
    if (last_digit == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
