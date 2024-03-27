def comparar_número(num):

    if num > 10:
        print("Esse valor é maior que 10!")
    elif num < 10:
        print("Esse valor NÃO é maior que 10")
    else:
        print("Esse valor é 10")
        
    if num >= 0:
        print("Esse valor é também positivo!")
    else:
        print("Esse valor é também negativo!")
        
    return
    

número = int(input("Por favor me dê um número: "))
senha = input("Por favor insira sua senha de acesso: ")

if senha == "SENAC":
    print("Acesso permitido")
    comparar_número(número)
else:
    print("Acesso negado")
