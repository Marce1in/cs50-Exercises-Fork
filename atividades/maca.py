print("Digite quantas maçãs o senhor comprou: ")
quantia = int(input(": "))
valor = 0.0
if quantia >= 12.0:
    valor = quantia * 0.25
else:
    valor = quantia * 0.30
    
print("Esse é o valor total: R$" + "{:.2f}".format(valor))