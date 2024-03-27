from cs50 import get_string

card = get_string("What is your card sir? ")
# Check if there's only numbers
if not card.isdigit():
    print("INVALID")
    exit()

# Chech if the lenght is correct
card_length = len(card)
if card_length not in [13, 14, 15, 16]:
    print("INVALID")
    exit()

# Sum and multiply the digits using Luhn's algorithm
total_sum = 0
for i in range(card_length - 2, -1, -2):
    num = (ord(card[i]) - 48) * 2
    if num >= 10:
        num %= 10
        total_sum += num + 1
    else:
        total_sum += num

for i in range(card_length - 1, -1, -2):
    num = ord(card[i]) - 48
    total_sum += num

# Check if the Sum in valid
if total_sum % 10 != 0:
    print("INVALID")
    exit()

# Search for what company is the credit card
if card[0:2] in ["34", "37"]:
    print("AMEX")
elif card[0:2] in ["51", "52", "53", "54", "55"]:
    print("MASTERCARD")
elif card[0] in ["4"]:
    print("VISA")
else:
    print("INVALID")