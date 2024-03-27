#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>


int *merge(int *sort, int tamanho);

const int TAMANHO_MAX = 9;
int contador = 0;

int main(void)
{
    int sort[TAMANHO_MAX] = {5, 2, 7, 4, 1, 6, 3, 0, 8};

    int *array = merge(sort, TAMANHO_MAX);

    printf("\n");
    for (int k = 0; k < TAMANHO_MAX; k++)
    {
        printf("(%i) ", *(array + k));
    }
    printf("\n");

    printf("%i\n", contador);

    free(array);

}

int *merge(int *sort, int tamanho)
{
    int *array_ordenada = malloc(sizeof(int) * tamanho);
    contador++;

    if (tamanho <= 1){
        *array_ordenada = *sort;
        return array_ordenada;
    }

    int *metade_esquerda = merge(sort, tamanho / 2); //Esquerda
    int *metade_direita = merge(sort + tamanho / 2, tamanho / 2); //Direita

    int next_E = 0;
    int next_D = 0;

    for (int i = 0; true; i++)
    {
        if (i + 2 == tamanho)
        {
            if (metade_esquerda[next_E] > metade_direita[next_D])
            {
                array_ordenada[i] = metade_direita[next_D];
                array_ordenada[i + 1] = metade_esquerda[next_E];
            }
            else
            {
                array_ordenada[i] = metade_esquerda[next_E];
                array_ordenada[i + 1] = metade_direita[next_D];
            }
            break;
        }

        else if (metade_esquerda[next_E] > metade_direita[next_D])
        {
            array_ordenada[i] = metade_direita[next_D];
            next_D++;
        }
        else
        {
            array_ordenada[i] = metade_esquerda[next_E];
            next_E++;
        }
    }

    free(metade_esquerda);
    free(metade_direita);

    return array_ordenada;
}