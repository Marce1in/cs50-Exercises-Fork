#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Pede para o usuário escolher o tipo de cálculo que deseja
    const int S = get_int("digite:\n1 para soma\n2 para diminuição\n3 para multiplicação\n4 para divisão\n");

    //Soma
    if (S == 1)
    {
    int x = get_int("x = ");

    int y = get_int("y = ");

    printf("Resultado: %i\n", x + y);
    }
    //Subtração
    else if (S == 2)
    {
    int x = get_int("x = ");

    int y = get_int("y = ");

    printf("Resultado: %i\n", x - y);
    }
    //multiplicação
    else if (S == 3)
    {
    int x = get_int("x = ");

    int y = get_int("y = ");

    printf("Resultado: %i\n", x * y);
    }
    //Divisão
    else if (S == 4)
    {
    float x = get_int("x = ");

    float y = get_int("y = ");

    printf("Resultado: %f\n", x / y);
    }
}