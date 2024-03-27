print("porfavor, me dê sua idade e seu peso:")
idade = int(input("idade: "))
peso = int(input("peso: "))

if idade <= 12:
    print("Infantil")
    
elif idade <= 16:
    if peso <= 40:
        print("juvenil leve")
    else:
        print("juvenil pesado")
        
elif idade <= 24:
    if peso <= 45:
        print("Senior leve")
    elif peso <= 60:
        print("Senior médio")
    else:
        print("Senior pesado")
        
else:
    print("veterano")