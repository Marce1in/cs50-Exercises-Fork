#Explica para o usuário oque ele precisa fazer
print("Me dê dois número para invertê-los")

#Coleta os dados requisitados
x = int(input("x: "))
y = int(input("y: "))

#Cria uma variável temporária para auxiliar o processo
temp = x
x = y
y = temp

#Retorna o resultado
print(f"invertidos com sucesso! x: {x}, y: {y}")