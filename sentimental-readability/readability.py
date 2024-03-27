from cs50 import get_string


def main():
    text = get_string("Your text, sir? ")

    word_sum = count_words(text)
    # Avarage number of letter per 100 words
    l = count_letters(text) / word_sum * 100
    # Avarage number of setences per 100 words
    s = count_setences(text) / word_sum * 100
    # Get the index with the formula and round the number for get the grade
    index = int(round(0.0588 * l - 0.296 * s - 15.8))

    # Print the right Grade
    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


# Functions that count all the Letters, Setences and words in the text

def count_letters(text):
    letter_counter = 0
    for i in text:
        if i.isalpha():
            letter_counter += 1
    return letter_counter


def count_words(text):
    words_counter = 1
    for i in text:
        if i.isspace():
            words_counter += 1
    return words_counter


def count_setences(text):
    setences_counter = 0
    for i in text:
        if i in [".", "?", "!"]:
            setences_counter += 1
    return setences_counter


# Call main
main()
