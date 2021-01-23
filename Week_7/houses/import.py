from cs50 import SQL
import csv
import sys

#  Get command line argument
if len(sys.argv) != 2:
    print("Usage: import.py csv_file")
    exit(1)
else:

    # Open database
    db = SQL("sqlite:///students.db")

    # Emptying databasee
    db.execute("DELETE FROM students")
    db.execute("UPDATE sqlite_sequence SET seq = 0 WHERE name = 'students'")

    # Open CSV file
    with open(sys.argv[1], 'r') as F_in:

        # Create reader
        reader = csv.DictReader(F_in, delimiter=",")

        # Transfer file
        for row in reader:
            full = row['name'].split()

            # Parsing name
            first = full[0]
            if len(full) == 2:
                middle = None
                last = full[1]
            else:
                middle = full[1]
                last = full[2]

            # Inserting file
            db.execute("INSERT INTO students (first, middle, last, house, birth) \
                        VALUES(? ,? ,? , ?, ?)",
                        first, middle, last, row["house"], row["birth"])