#include <cs50.h>
#include <stdio.h>

void bubble(int *sort);

const int TAMANHO_MAX = 8;

int main(void)
{
    int sort[TAMANHO_MAX] = {5, 2, 7, 4, 1, 6, 3, 0};

    bubble(sort);

    printf("\n");
    for (int k = 0; k < TAMANHO_MAX; k++)
        {
            printf("(%i) ", sort[k]);
        }
    printf("\n");
}

void bubble(int *sort)
{
    for (int i = 0; i < TAMANHO_MAX; i++)
    {
        bool swap_detector = false;

        for (int j = 0; j < TAMANHO_MAX - i; j++)
        {
            if (sort[j] > sort[j + 1] && (j + 1) < (TAMANHO_MAX - i))
            {
                int tmp = sort[j];
                sort[j] = sort[j + 1];
                sort[j + 1] = tmp;
                swap_detector = true;
            }
        }

        if (swap_detector == false){
            break;
        }
    }
}
