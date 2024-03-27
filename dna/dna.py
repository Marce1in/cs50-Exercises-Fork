import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("ERROR! usage: [(CSV FILE) (DNA SEQUENCE)])")
        exit(1)

    # Read database file into a variable
    try:
        database_file = open(sys.argv[1], "r")
        database = csv.DictReader(database_file)
    except FileNotFoundError:
        print("ERROR! invalid file")
        exit(2)

    # Read DNA sequence file into a variable
    try:
        dna_file = open(sys.argv[2], "r")
        dna_sequence = dna_file.read()
    except FileNotFoundError:
        print("ERROR! invalid file")
        exit(3)

    # Find longest match of each STR in DNA sequence
    STR_keys = list(database.fieldnames)
    del STR_keys[0]

    STR_match_list = [longest_match(dna_sequence, key) for key in STR_keys]

    # Check database for matching profiles
    No_match = True

    for person in database:
        STR_person_list = [int(person[key]) for key in STR_keys]

        if STR_person_list == STR_match_list:
            print(person["name"])
            No_match = False

    print("No match") if No_match == True else None

    database_file.close()
    dna_file.close()
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables

    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
