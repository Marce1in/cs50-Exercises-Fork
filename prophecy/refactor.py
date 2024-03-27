from cs50 import SQL
import csv

# Open the new file
db = SQL("sqlite:///students.db")

def main():
    # Open the file and iterate over him filling the new file
    with open("students.csv") as old_db_file:
        old_db = csv.DictReader(old_db_file)

        for row in old_db:
            Fill_Students_Table(row)

            if row["house"] not in Houses_Already_In:
                Houses_Already_In.append(row["house"])
                Fill_Houses_Table(row)

        # Reset the file pointer
        old_db_file.seek(0)
        old_db = csv.DictReader(old_db_file)

        for rows in old_db:
            Fill_Assignments(rows)


def Fill_Students_Table(row):
    db.execute("INSERT INTO students (id, student) VALUES (?, ?)",
    row["id"], row["student_name"])


#Keep track what houses are already in the new database
Houses_Already_In = []
House_id = 1

def Fill_Houses_Table(row):
    global House_id

    db.execute("INSERT INTO houses (id, house, head) VALUES(?, ?, ?)",
    House_id, row["house"], row["head"])

    House_id += 1


# Assign a house for a student based on the old database
def Fill_Assignments(row):
    house_index = Houses_Already_In.index(row["house"]) + 1

    db.execute("INSERT INTO assignments (id_student, id_house) VALUES (?, ?)",
    row["id"], house_index)

main()
