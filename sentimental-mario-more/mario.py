from cs50 import get_int

# Get the Height of the triangle
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

for i in range(height):
    for j in range(height - i - 1):  # Push the first pyramid to the right
        print(end=" ")
    for j in range(i + 1):  # Print the first Pyramid column
        print("#", end="")
    print(end="  ")  # Separate the Pyramids
    for j in range(i + 1):  # Print the second Pyramid column
        print("#", end="")
    print()  # Start a new column