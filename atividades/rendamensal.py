renda = float(input("porfavor insira sua renda mensal em R$: "))
gastos = {"Saúde": [0.0, 0.10], 
          "Educação": [0.0, 0.25], 
          "Alimentação": [0.0, 0.30], 
          "Vestuário": [0.0, 0.10], 
          "Lazer": [0.0, 0.05], 
          "Outros": [0.0, 0.20]}

for gasto in gastos:
    print(f"{gasto}: R$ ", end="")
    gastos[gasto][0] = renda * gastos[gasto][1]
    print("%.2f" % gastos[gasto][0])