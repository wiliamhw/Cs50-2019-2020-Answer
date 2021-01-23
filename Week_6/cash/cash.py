# https://cs50.harvard.edu/x/2020/psets/6/cash/


# Function to get change from user input
def get_change():
    while True:
        change = int(input("Change owed: "))
        if change > 0:
            break
    return change


# Function to count item
def count_item(cents):
    count = 0

    while (cents - 25 >= 0):
        count += 1
        cents -= 25

    while (cents - 10 >= 0):
        count += 1
        cents -= 10

    while (cents - 5 >= 0):
        count += 1
        cents -= 5

    while (cents - 1 >= 0):
        count += 1
        cents -= 1

    return count


def main():
    # Get change
    dollars = get_change()
    cents = int(round(dollars * 100))

    # Decide which cents to use
    counter = count_item(cents)

    # Print amount of cents
    print(f"{counter}")


main()