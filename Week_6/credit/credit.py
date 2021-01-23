# Program untuk mengecek apakah suatu nomor kartu kredit valid atau tidak
# dan menentukan jenis dari kartu kredit yang dimasukkan dengan menggunakan
# algoritma Luhn.

# Hanya bisa mengidentifikasi kartu kredit berjenis "America Express", "Visa",
# dan "Mastercard".


# Check whether Luhn Algorithm is valid or not
from cs50 import get_string
import math


def valid(prompt, lenght):
    # Declare needed variable
    Sum = 0
    x = 100
    y = 10

    # Take second-to-last digit and times it by 2
    for i in range(lenght):
        evenNum = int(math.floor(((prompt % x) / (x / 10))) * 2)
        x *= 100

        # Pick even[i] digits if even[i] >= 10
        if (evenNum >= 10):
            digit_0 = evenNum % 10
            digit_1 = int(math.floor(evenNum / 10))
            evenNum = 0
        else:
            digit_0 = 0
            digit_1 = 0
            # print()

        # Sum of all digits
        Sum += evenNum + digit_0 + digit_1

    # Take first-to-last digit
    for i in range(lenght):
        oddNum = int(((prompt % y) / (y / 10)))
        y *= 100
        Sum += oddNum

    # Check the last digit of sum
    if (Sum % 10 == 0):
        return True
    else:
        return False


def main():
    # Get user input
    Buffer = get_string("Number: ")
    lenght = len(Buffer)
    ccNum = int(Buffer)

    # Get the first two number of ccNum
    first_two = int(ccNum / (10 ** (lenght - 2)))
    first_one = int(ccNum / (10 ** (lenght - 1)))

    # Process the ccNum into its types
    if (valid(ccNum, lenght)):
        if ((first_two == 34 or first_two == 37) and lenght == 15):
            print("AMEX")
        elif (first_one == 4 and (lenght == 13 or lenght == 16)):
            print("VISA")
        elif (first_two >= 51 and first_two <= 55 and lenght == 16):
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


main()