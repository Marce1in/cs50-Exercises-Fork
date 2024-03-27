from cs50 import get_float


def main():
    # Get the dollars value rejecting negative values
    while True:
        dollars = get_float("How many dollars, sir? ")
        if dollars > -1.0:
            break

    # Calculate how many coins the customer is gonna need
    coins = Exchange(dollars)
    print(coins.quarters() + coins.dimes() + coins.nickels() + coins.pennies())


class Exchange:
    def __init__(self, dollars):
        self.dollars = dollars

    # Calculate the number of quarters to give the customer
    def quarters(self):
        quarters = 0
        while self.dollars >= 0.25:
            self.dollars -= 0.25
            quarters += 1
        self.dollars = round(self.dollars, 2)
        return quarters

    # Calculate the number of dimes to give the customer
    def dimes(self):
        dimes = 0
        while self.dollars >= 0.10:
            self.dollars -= 0.10
            dimes += 1
        self.dollars = round(self.dollars, 2)
        return dimes

    # Calculate the number of nickels to give the customer
    def nickels(self):
        nickels = 0
        while self.dollars >= 0.05:
            self.dollars -= 0.05
            nickels += 1
        self.dollars = round(self.dollars, 2)
        return nickels

    # Calculate the number of pennies to give the customer
    def pennies(self):
        pennies = 0
        while self.dollars >= 0.01:
            self.dollars -= 0.01
            pennies += 1
        self.dollars = round(self.dollars, 2)
        return pennies


main()