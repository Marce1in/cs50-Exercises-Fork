# Comparador de nomes
nome = input("Qual teu nome? ")

if nome == "jailson":
    print("Que delícia cara")
else:
    print(f"Salve, {nome}!")


# Comparador de números
while True:
    try:
        x = int(input("me de um número please: "))
        y = int(input("me de outro número please: "))
        break
    except ValueError:
        print("Isso não é um número!!")

if  x > y:
    print(f"{x} é maior que {y}")
elif y > x:
    print(f"{x} é menor que {y}")
else:
    print(f"{x} é igual a {y}")


# Verificador de par ou ímpar
while True:
    try:
        x = int(input("me de um número please: "))
        break
    except ValueError:
        print("Isso não é um número!!")

if x % 2 == 0:
    print(f"{x} é um número par")
else:
    print(f"{x} é um número impar")


# Encontra todos os números entre x e y
while True:
    try:
        x = int(input("Digite um número: "))
        y = int(input("Digite outro número: "))
        break
    except ValueError:
        print("Isso não é um número irmão!")

print(f"existem todos esse números entre {x} e {y}: ", end="")
for i in range(x + 1 , y):
    print(i, end=" ")
print()


# Encontra todos os númeors ímpares ou pares entre x e y
while True:
    try:
        x = int(input("Digite um número: "))
        y = int(input("Digite outro número: "))
        break
    except ValueError:
        print("Isso não é um número irmão!")

while True:
    escolha = input(f"Digite 'I' para encontrar todos os números Ímpares entre {x} e {y}\n"
                    f"Ou Digite 'P' para encontrar todos os números Pares entre {x} e {y}: ").upper()

    if escolha not in ["I", "P"]:
        print("\nErro! Dígito errado, use apenas 'I' ou 'P'\n")
        continue
    break

if escolha == "I":
    print(f"existem todos esse números ímpares entre {x} e {y}: ", end="")
    print([i for i in range(x + 1, y) if i % 2 != 0])
    print()
else:
    print(f"existem todos esse números pares entre {x} e {y}: ", end="")
    for i in range(x + 1 , y):
        if i % 2 == 0:
            print(i, end=" ")
    print()


# Mesma coisa, mas com estilo
while True:
    try:
        x = int(input("Digite um número: "))
        y = int(input("Digite outro número: "))
        break
    except ValueError:
        print("Isso não é um número irmão!")

while True:
    escolha = input(f"Digite 'I' para encontrar todos os números Ímpares entre {x} e {y}\n"
                    f"Ou Digite 'P' para encontrar todos os números Pares entre {x} e {y}: ").upper()

    if escolha not in ["I", "P"]:
        print("\nErro! Dígito errado, use apenas 'I' ou 'P'\n")
        continue
    break

if x > y:
    x, y = y, x

if escolha == "I":
    print(f"existem todos esse números ímpares entre {x} e {y}: ", end="")
    print(*(i for i in range(x + 1, y) if i % 2 != 0))
else:
    print(f"existem todos esse números pares entre {x} e {y}: ", end="")
    pares = x + 1 if x % 2 != 0 else x + 2 #Ultra eficente
    for i in range(pares , y, 2):
        print(i, end=" ")
    print()

# Vários métodos de fazer a mesma coisa, encontrar os números pares

for i in range(x + 1 , y): #O clássico, fácil de ler mas meio grande
    if i % 2 == 0:
        print(i, end=" ")

print([i for i in range(x + 1, y) if i % 2 != 0]) #Bem mais compacto,
                                                  #porém cria uma lista sem necessidade

print(*(i for i in range(x + 1, y) if i % 2 != 0)) #Ainda compacto,
                                                   #não cria uma lista, apenas gera o desejado

pares = x + 1 if x % 2 != 0 else x + 2 #É relativamente fácil de ler e tem o dobro de eficiência
for i in range(pares , y, 2):
    print(i, end=" ")


pares = x + 1 if x % 2 != 0 else x + 2 #É ainda relativamente fácil de ler e ainda tem o dobro de eficiência
print(*(i for i in range(pares, y, 2)))#E é mais compacto ainda, porem pode ser complicado debbugar

# Programa simples que printa um triangulo invertido
tamanho = int(input("Me da um tamanho aew bro: "))

for i in range(tamanho):
    for j in range(tamanho - i - 1):
        print(end=" ")
    for k in range(i + 1):
        print("#", end="")
    print()

# Faz o mesmo que o de cima, mas usando um gerador
tamanho = int(input("Me da um tamanho aew bro: ")) + 1

for i in range(tamanho):
    print(*(" " for j in range(tamanho - i - 1)), sep="", end="")
    print(*("#" for k in range(i)), sep="")

# Programa um pouco diferente, mas com a mesma filosofia, cria dois triangulos invertidos
tamanho = int(input("Me da um tamanho aew bro: "))

for i in range(tamanho):
    for j in range(tamanho - i - 1):
        print(" ", end="")
    for j in range(i + 1):
        print("k", end="")
    print("  ", end="")
    for j in range(i + 1):
        print("k", end="")
    print()

# Faz o mesmo que o de cima, mas usando um gerador
tamanho = int(input("Me da um tamanho aew bro: ")) + 1

for i in range(tamanho):
    print(*(" " for j in range(tamanho - i - 1)), sep="", end="")
    print(*("#" for j in range(i)), sep="", end="  ")
    print(*("#" for j in range(i)), sep="")

# Programa pika q a IA fez
class Exchange:
    def coins(self, cents):
        coins = 0
        values = [25, 10, 5, 1]
        for value in values:
            while cents >= value:
                cents = cents - value
                coins += 1
        return coins

exchange = Exchange()
cents = int(input("Enter the number of cents to exchange: "))
total_coins = exchange.coins(cents)
print(f"Total number of coins: {total_coins}")