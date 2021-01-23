# https://cs50.harvard.edu/x/2020/psets/6/readability/


from cs50 import get_string


def main():
    # Get Input
    string = get_string("Text: ")

    # Count letter, word, and sentence
    # ['letter', 'word', 'sentence']
    element = [0, 1, 0]
    count_element(string, element)

    # Count index
    L = element[0] / element[1] * 100
    S = element[2] / element[1] * 100
    result = 0.0588 * L - 0.296 * S - 15.8
    index = int(round(result))

    # Print result
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print("Grade", index)


def isEndSign(char):
    if char == '.' or char == '?' or char == '!':
        return True
    else:
        return False


def count_element(string, element):
    lenght = len(string)
    for i in range(lenght):
        # If alpha, letter++
        if string[i].isalpha():
            element[0] += 1

        # If space, word++
        elif string[i] == ' ':
            element[1] += 1

        # If end punctuation, sentence++
        elif isEndSign(string[i]):
            element[2] += 1

        i += 1


main()