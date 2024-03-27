import sys

print("Irei calcular a perímetro de um forma geométrica")

lados = int(input("Porfavor me dê o número de lados: "))
sys.exit("Valor inválido!") if lados < 3 or lados > 5 else None

formas = {3: "TRIÂNGULO", 4: "QUADRADO", 5: "PENTÁGONO"}

print(f"Sua forma é: {formas[lados]}")

valores = []

for i in range(lados):
    valor = int(input(f"Me dê o valor do °{i + 1} lado: "))
    valores.append(valor)

perímetro = 0

for i in valores:
    perímetro += i
    
print(f"Esse é o seu perímetro: {perímetro}")    

    
