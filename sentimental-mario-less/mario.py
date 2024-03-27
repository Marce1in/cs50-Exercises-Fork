from cs50 import get_int

# Get the Height of the triangle
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

for i in range(height):
    for j in range(height - i - 1):  # Push the pyramid to the right
        print(end=" ")
    for j in range(i + 1):  # Print the pyramid column by column
        print("#", end="")
    print()  # Start a new column