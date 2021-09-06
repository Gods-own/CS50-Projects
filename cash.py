import cs50

dollars = cs50.get_float("Change owed: ")

while dollars < 0:
    dollars = cs50.get_float("Change owed: ")

cents = round(dollars * 100)

coins = 0

while cents > 0:
    if cents >= 25:
        cents = cents - 25
    elif cents >= 10:
        cents = cents - 10
    elif cents >= 5:
        cents = cents - 5
    else:
        cents = cents - 1
    coins += 1

print(coins)