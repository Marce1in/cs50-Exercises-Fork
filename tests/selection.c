#include <cs50.h>
#include <stdio.h>

void selection(int *sort);

const int TAMANHO_MAX = 8;

int main(void)
{
    int sort[TAMANHO_MAX] = {5, 2, 7, 4, 1, 6, 3, 0};

    selection(sort);

    printf("\n");
    for (int k = 0; k < TAMANHO_MAX; k++)
    {
        printf("(%i) ", sort[k]);
    }
    printf("\n");

}

void selection(int sort[])
{
    for (int i = 0; i < TAMANHO_MAX; i++)
    {
        int sort_num = i;

        for (int j = i; j < TAMANHO_MAX; j++)
        {
            if(sort[sort_num] > sort[j])
            {
                sort_num = j;
            }
        }
        int tmp = sort[i];
        sort[i] = sort[sort_num];
        sort[sort_num] = tmp;
}