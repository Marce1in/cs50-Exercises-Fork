#include <cs50.h>
#include <stdio.h>

void Sort(int *sort, int tamanho);

const int TAMANHO_MAX = 10;

int contador = 0;

int main(void)
{
    int sort[TAMANHO_MAX] = {1, 0, 9, 6, 7, 3, 8, 4, 5, 2};

    Sort(sort, TAMANHO_MAX);

    for (int k = 0; k < TAMANHO_MAX; k++)
        {
            printf("(%i) ", sort[k]);
        }
    printf("\n");
}

void Sort(int *sort, int tamanho)
{
    contador++;
    printf("{%i} ", contador);

    if (tamanho < 2){
        return;
    }

    if (sort[0] > sort[1])
    {
        printf("\n");
        for (int k = 0; k < 2; k++)
        {
            printf("(%i) ", sort[k]);
        }
        printf("|| ");


        int tmp = sort[0];
        sort[0] = sort[1];
        sort[1] = tmp;


        for (int k = 0; k < 2; k++)
        {
        printf("[%i] ", sort[k]);
        }
        printf("\n-----------------------------------------------------------------------------------------\n");

        Sort(&sort[1], tamanho - 1);
    }
    if (sort[1] > sort[2] ){
        Sort(&sort[1], tamanho - 1);
    }
    else if (tamanho < TAMANHO_MAX && sort[-1] > sort[0]){
        Sort(&sort[-1], tamanho - 1);
    }
    return;
}
