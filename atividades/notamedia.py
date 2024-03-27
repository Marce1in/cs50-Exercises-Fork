print("Por favor me dê três notas de um aluno: ")
n1 = float(input(": "))
n2 = float(input(": "))
n3 = float(input(": "))

média_de_aproveitamento = (n1 * 2 + n2 * 3 + n3 * 5) / 10
print("Essa é a média do aluno: " + "%.1f" % média_de_aproveitamento)