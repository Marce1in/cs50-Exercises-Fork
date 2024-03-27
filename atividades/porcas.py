nome = input("Me dê seu nome: ")

print(f"olá {nome}! Digite quantas porcas, arruelas e parafusos deseja!")

parafuso = int(input("Parafusos: "))
arruelas = int(input("Arruelas: "))
porcas = int(input("Porcas: "))

total = (parafuso * 0.50) + (arruelas * 0.60) + (porcas * 0.75)

print(f"Muito bem {nome}! você deseja:\n" 
    f"{parafuso} parafusos\n"
    f"{arruelas} arruelas\n"
    f"{porcas} porcas\n"
    "Isso dá no total: R$" + "{:.2f}".format(total))
