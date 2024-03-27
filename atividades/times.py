print("Porfavor me dê dois time e o número de gols")
timeA = str(input("Me dê um time: "))
golsA = int(input("Me dê os número de gols: "))

timeB = str(input("Me dê outro time: "))
golsB = int(input("Me dê o número de gols: "))

if golsA > golsB:
    print(f"Time {timeA} é o vencedor!")
elif golsB > golsA:
    print(f"Time {timeB} é o vencedor!")
else:
    print("Empate")
