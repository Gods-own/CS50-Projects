import csv
import cs50
import sys


persons = []
file2 = []
good = []


def main():
    if len(sys.argv) < 3:
        print("You need to arguments")

    with open(sys.argv[1]) as file1:
        reader = csv.DictReader(file1)
        for row in reader:
            name = row
            for key, value in name.items():
                if key != "name":
                    name[key] = int(name[key])
            persons.append(name)

    f = open(sys.argv[2], "r")
    file2 = f.read()
    d = 0
    for key, value in persons[d].items():
        if key != "name":
            good.append(maxNo(file2, key))
            d += 1
    f.close()

    print(match(persons, good))


def maxNo(sequence, strdna):
    i = 0
    g = 0
    j = len(strdna)
    f = len(strdna)
    num = []
    while i < len(sequence):
        count = 0
        if sequence[i:j] == strdna:
            count = 1
            g = i
            f = j
            h = len(strdna)
            while g < len(sequence):
                if sequence[(g+h):(h+f)] == strdna:
                    count += 1
                else:
                    break
                h += len(strdna)
        else:
            count = 0
        num.append(count)
        i += 1
        j += 1

    maxstr = num[0]
    l = 0
    for p in range(len(num)):
        if num[l] > maxstr:
            maxstr = num[l]
        l += 1
    return maxstr


def match(persons, good):
    resul = None
    call = 0
    for i in persons:
        e = 0
        for key, value in i.items():
            if key == "name":
                continue
            if i[key] != good[e]:
                if call == len(persons) - 1:
                    resul = "No match"
                call += 1
                break
            elif i[key] == good[e]:
                if e == len(good) - 1:
                    resul = i["name"]
            e += 1
    return resul


if __name__ == "__main__":
    main()