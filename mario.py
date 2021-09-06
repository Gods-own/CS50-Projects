import cs50

height = cs50.get_int("Height: ")

while height < 1 or height > 8:
    height = cs50.get_int("Height: ")

k = height - 1
t = 1

for i in range(height):
    for g in range(height - t):
        print(" ", end="")
    for j in range(height - k):
        print("#", end="")
    k -= 1
    t += 1
    print()