from cs50 import get_int

while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

for i in range(height):
    # print {space}
    for j in range(height - i - 1):
        print(' ', end='')

    # print left '#'
    for j in range(i + 1):
        print('#', end='')

    # print two {space}
    print('  ', end='')

    # print right '#'
    for j in range(i + 1):
        print('#', end='')

    # print {\n}
    print()