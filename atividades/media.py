
print("Por favor me dê três notas de um aluno: ")
n1 = float(input(": "))
n2 = float(input(": "))
n3 = float(input(": "))
média_dos_exercícios = float(input("Agora me dê a média dos exercícios: "))
média_de_aproveitamento = (n1 + n2 * 2 + n3 * 3 + média_dos_exercícios) / 7
print("Essa é média do aproveitamento: " + "%.1f" % média_de_aproveitamento)

if média_de_aproveitamento >= 9.0:
    print("O aluno tirou nota A")
elif média_de_aproveitamento >= 7.5:
    print("O aluno tirou nota B")
elif média_de_aproveitamento >= 6.0:
    print("O aluno tirou nota C")
else:
    print("O aluno tirou nota D")