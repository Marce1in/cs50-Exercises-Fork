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

if escolha == "I" and x < y:
    print(f"existem todos esse números ímpares entre {x} e {y}: ", end="")
    ímpar = x + 1 if x % 2 == 0 else x + 2
    print(*(i for i in range(ímpar, y, 2)), sep=", ")

elif escolha == "I" and x > y:
    print(f"existem todos esse números ímpares entre {y} e {x}: ", end="")
    ímpar = y + 1 if y % 2 == 0 else y + 2
    print(*(i for i in range(ímpar, x, 2)), sep=", ")

elif escolha == "P" and x < y:
    print(f"existem todos esse números pares entre {x} e {y}: ", end="")
    par = x + 1 if x % 2 != 0 else x + 2
    print(*(i for i in range(par, y, 2)), sep=", ")

else:
    print(f"existem todos esse números pares entre {y} e {x}: ", end="")
    par = y + 1 if y % 2 != 0 else y + 2
    print(*(i for i in range(par, x, 2)), sep=", ")

