print("Porfavor insira o preço e a quantidade de produtos que foram comprados")

valor = float(input("Preço: "))
quantia = float(input("Quantidade: "))

if valor < 0 or quantia < 0:
    raise Exception("VALOR INVÁLIDO")

total = valor * quantia

print("Esse é o total: R$" + "{:.2f}".format(total))