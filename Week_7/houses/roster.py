import sys
from cs50 import SQL

#  Get command line argument
if len(sys.argv) != 2:
    print("Usage: import.py house_name")
    exit(1)
else:

    # Open database
    db = SQL("sqlite:///students.db")

    # Get value
    data = db.execute("SELECT * FROM students \
            WHERE house = ? \
            ORDER BY last, first", sys.argv[1])

    # Print value
    for value in data:
        print(value['first'], end=' ')

        if value['middle'] is not None:
            print(value['middle'], end=' ')

        print(f"{value['last']}, born {value['birth']}")