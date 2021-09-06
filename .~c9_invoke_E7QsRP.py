import csv
import cs50
import sys


def main():
    if len(sys.argv) < 3:
        print("You need to arguments")

    persons = []
    file2 = []

    with open(sys.argv[1]) as file1:
        reader = csv.DictReader(file1)
        for row in reader:
            name = row
            name["AGATC"] = int(name["AGATC"])
            name["TTTTTTCT"] = int(name["TTTTTTCT"])
            name["AATG"] = int(name["AATG"])
            name["TCTAG"] = int(name["TCTAG"])
            name["GATA"] = int(name["GATA"])
            name["TATC"] = int(name["TATC"])
            name["GAAA"] = int(name["GAAA"])
            name["TCTG"] = int(name["TCTG"])
            persons.append(name)


    f = open(sys.argv[2], "r")
    sequence = f.read()


def maxNo(sequence, strdna):
    i = 0
    j = 1
    while i < len(file2):
        sequence[i:j]


main()







