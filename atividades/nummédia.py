def troca(x,y,z):
    temp = x
    x = y
    y = temp
    
    print(f"X: {x}, Y: {y}, Z: {z}")
    
    
def media(x,y,z):
    media = (x + y + z) / 3
    print(f"Média: {media}")
    
    
def maior(x,y,z):
    lista = [x,y,z]
    maior = 0
    for i in range(3):
        maior

        if maior < lista[i]:
            maior = lista[i]

    print(f"Esse é o maior número entre eles: {maior}")
    
    
print("Me dê três número")
x = int(input("x: "))
y = int(input("y: "))
z = int(input("z: "))

print("Vamos lá \n" 
      "digite 1 para trocar os números\n"
      "digite 2 para ver a média entre eles\n"
      "digite 3 para encontrar o maior\n")

escolha = int(input(": "))

if escolha == 1:
    troca(x,y,z)
elif escolha == 2:
    media(x,y,z)
elif escolha == 3:
    maior(x,y,z)
else:
    raise Exception("ERRO! opçâo inválida!")

