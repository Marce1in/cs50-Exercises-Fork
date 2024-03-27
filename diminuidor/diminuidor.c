#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    //pega uma frase do usuário
    string frase = get_string("O texto para diminuir, senhor? ");

    //pega o quanto o usuário quer diminuir a frase
    int diminui = get_int("Até quanto deseja diminuir, senhor? ");

    //Cria uma array de chars vazia com o tamanho que o usuário quer diminuir a frase
    char frase_diminuída[diminui];

    //Diminuí a frase
    for (int começo = 0, fim = 0; começo != fim; começo++)
    {
        frase_diminuída[começo] = frase[começo];
    }

    frase_diminuída[diminui] = '\0';

    //Printa a frase diminuída
    printf("Sua frase está aqui, senhor: %s \n", frase_diminuída);
}