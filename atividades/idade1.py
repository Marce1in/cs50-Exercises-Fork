escolha = int(input("digite 1 calcular a idade ou 2 para cancelar: "))

while(escolha != 2):
    
    ano_ref = int(input("Me dê o ano de referência: "))
    ano_nasc = int(input("Me dê o seu ano de nascimento: "))
    
    print(f"Essa é a sua idade: {ano_ref - ano_nasc}")
    
    escolha = int(input("digite 1 calcular a idade ou 2 para cancelar: "))