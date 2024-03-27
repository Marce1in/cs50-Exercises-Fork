print("Por favor insira quantos litros seus carro consome por quilômetros (km/l), quantos quilômetros falta para seu destino e qual é o custo da gasolina atual")

km = float(input("km: "))
kml = float(input("km/l: "))
custo = float(input("custo de um litro de gasolina: "))

consumo_da_viagem = km / kml
custo_viagem = consumo_da_viagem * custo

print(f"Isso é consumo total: {consumo_da_viagem}")
print(f"Isto é o custo total de viagem: R$ {custo_viagem}")
