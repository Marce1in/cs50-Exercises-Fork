print("Me dê dois números")

x = int(input(": "))
y = int(input(": "))

print("Muito bem! Agora seleciona que tipo de operação deseja:\n" +
      "Digite 1 para Adição\n" +
      "Digite 2 para Subtração\n" +
      "Digite 3 para Multiplicação\n")

escolha = int(input(": "))

operadores = {1: eval("x+y"),
              2: eval("x-y"),
              3: eval("x*y")}

if escolha not in [1, 2, 3]:
    print("Operação INVÁLIDA")
else:
    print(f"Esse é o resultado: {operadores[escolha]}")