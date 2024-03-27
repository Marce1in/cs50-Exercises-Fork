ano_ref = int(input("Me dê o ano de referência: "))

while(True):
    ano_nasc = int(input("Me dê o seu ano de nascimento: "))
    
    print(f"Essa é a sua idade: {ano_ref - ano_nasc}")
    
    escolha = int(input("digite 1 para parar, 2 para continuar: "))
    
    if escolha == 1:
        break