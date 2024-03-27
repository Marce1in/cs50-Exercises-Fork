número = int(input("Me dê um número de 4 digitos: "))
if número < 999 or número > 10000:
    print("Esse número não tem 4 digitos!")
    exit()
resposta = int(número / 100)
print(f"resposta: {resposta}")
