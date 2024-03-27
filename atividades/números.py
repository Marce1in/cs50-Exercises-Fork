def a():
    print("Me Dê quatro números inteiros para eu somar")
    a = int(input("a: "))
    b = int(input("b: "))
    c = int(input("c: "))
    d = int(input("d: "))
    print(f"Esse é o resultado: {a + b + c + d}")
a()

def b():
    a = 10
    b = 20
    
    temp = 20
    b = a
    a = temp
    
    print(f"a: {a}")
    print(f"b: {b}")
b()

def c():
    print("Por favor me dê três notas de alunos:")
    a = int(input())
    b = int(input())
    c = int(input())
    média = (a + b + c) / 3
    print("Essa é a nota média entre elas: " + "%.2f" % média)
c()