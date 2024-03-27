print("Digite *1* se o senhor quer Álcool ou *2* se Gasolina")
tipo = int(input(": "))

if tipo not in [1,2]:
    raise Exception("ERRO! Produto inválido")
    
escolhas = ["Álcool", "Gasolina"]

print(f"Digite quantos litros de {escolhas[tipo]} você comprou: ")
quantia = int(input(": "))

valor = 0.0

if tipo == 1:
    if quantia > 25:
        valor = quantia * 4.78
    else:
        valor = quantia * 5.10

else:
    if quantia > 25:
        valor = quantia * 4.18    
    else:
        valor = quantia * 4.30

    
print("Esse é o valor total: R$" + "{:.2f}".format(valor))