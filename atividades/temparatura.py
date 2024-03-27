def main():
    temperatura = (input('Digite C para celsius, F para Fahrenheit ou K para Kelvin: ')).upper()

    graus = float(input("Por favor me dê quantos graus está a temperatura: "))
    
    if temperatura == "C":
        celsius(graus)
    elif temperatura == "F":
        fahrenheit(graus)
    elif temperatura == "K":
        kelvin(graus)
    else:
        raise Exception("ERRO! Medida incorreta")

def celsius(graus):
    print(f"Convertendo para Fahrenheit fica: {graus * 1.8 + 32}F")
    print(f"Convertendo para Kelvin: {graus + 273.15}K")

def fahrenheit(graus):
    print(f"Convertendo para Celsius fica: {(graus - 32) / 1.8}C")
    print(f"Convertendo para Kelvin fica: {(graus + 459.67) * 5 / 9}K")
    
    
def kelvin(graus):
    print(f"Convertendo para Celsius fica: {graus - 273.15}C")
    print(f"Convertendo para Fahrenheit fica: {(graus - 273.15) * 1.8 + 32}F")
    

if __name__ == "__main__":
    main()