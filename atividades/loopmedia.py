print("Me dê 2 notas de um aluno")
while(True):
    n1 = float(input(": "))
    n2 = float(input(": "))
    
    print(f"Essa é a média: {(n1 + n2) / 2}")
    
    escolha = int(input("digite 1 para continuar o programa e 2 para parar: "))
    
    if escolha == 2:
        break
