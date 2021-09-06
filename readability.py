import cs50


def main():

    text = cs50.get_string("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    L = (letters/words) * 100
    S = (sentences/words) * 100

    grade = round(0.0588 * L - 0.296 * S - 15.8)

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def count_letters(text):
    letter = 0
    for char in text:
        if char.isalpha():
            letter += 1
        else:
            letter += 0
    return letter


def count_words(text):
    word = 0
    for char in text:
        if char == " ":
            word += 1
        else:
            word += 0
    return word + 1


def count_sentences(text):
    sentence = 0
    for char in text:
        if char == "." or char == "?" or char == "!":
            sentence += 1
        else:
            sentence += 0
    return sentence


if __name__ == "__main__":
    main()
