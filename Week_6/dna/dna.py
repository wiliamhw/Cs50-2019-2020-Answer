# https://cs50.harvard.edu/x/2020/psets/6/dna/


import csv
from sys import argv


def main():
    # Get database and test file
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)
    else:
        _csv = argv[1]
        _txt = argv[2]

    # Get DNA sample
    with open(_txt, 'r') as txt_file:
        txt_reader = txt_file.read()

    # Open csv
    with open(_csv, 'r') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')

        # Get STR template (first row) from csv file
        first_row = next(csv_reader)
        first_row.pop(0)
        banyakSTR = len(first_row)

        # Count how many template STR in textfile
        counter = []
        for i in range(banyakSTR):
            hasil = countWord(txt_reader, first_row[i])
            counter.append(hasil)

        # Check equality between DNA sample and database
        for row in csv_reader:
            if same(row, banyakSTR, counter):
                print(row[0])
                return

        # If nothing in the database match the sample
        print("No match")


# Function to check equality of sample and database
def same(csv_row, banyakSTR, counter):

    # Traverse each element of STR template
    for i in range(banyakSTR):
        if int(csv_row[i + 1]) != counter[i]:
            return False

    # If all element is equal
    return True


# Function to count how many 'STR' in textfile
def countWord(In_txt, STR):

    # Initialize needed variable
    STRlen = len(STR)
    TXTlen = len(In_txt)
    j = STRlen
    i, count, Max = [0, 0, 0]

    #  Traverse per letter
    while True:
        if count > Max:
            Max = count

        if j >= TXTlen:
            break

        elif In_txt[i:j] == STR:
            count += 1
            i += STRlen
            j += STRlen

        else:
            count = 0
            i += 1
            j += 1

    return Max


main()