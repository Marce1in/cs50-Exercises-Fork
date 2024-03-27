print("Vamos calcular o seu peso ideal!")
altura = float(input("Digite sua altura: "))
genero = str(input("Digite seu gênero biológico: ")).lower()

nomes_masculinos = ["homem", "masculino", "m"]
nomes_femininos = ["mulher", "feminino", "f"]

if genero in nomes_masculinos:
    peso_ideal = (72.7 * altura) - 58
elif genero in nomes_femininos:
    peso_ideal = (62.1 * altura) - 44.7
else:
    raise Exception("ERRO! gênero inválido!")

print(f"Esse é o seu peso ideal: {peso_ideal}")
    
