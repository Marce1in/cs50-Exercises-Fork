#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int sort[10] = {1, 0, 9, 6, 7, 3, 8, 4, 5, 2};
    int d_mudança = 0;
    int t_mudança = 0;

    typedef struct
    {
        int número;
        int local;
    }
    sortNL;
    sortNL sort_num;
    sort_num.número = 0;

    for (int i = 0; i < 10; i++)
    {
        sort_num.número = 0;
        sort_num.local = 0;

        for (int j = i; j < 10; j++)
        {
            if(sort_num.número > sort[j]) //Encontra o menor
            {
                sort_num.número = sort[j];
                sort_num.local = j;
            }
            t_mudança++;
        }
        sort[sort_num.local] = sort[i];
        sort[i] = sort_num.número;
        d_mudança++;
        for (int k = 0; k < 10; k++)
        {
            printf("(%i) ", sort[k]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Número de  mudanças dentro: %i\n", d_mudança);
    printf("Número de  mudanças total: %i\n", t_mudança);
}

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int sort[10] = {1, 0, 9, 6, 7, 3, 8, 4, 5, 2};
    int d_mudança = 0;
    int t_mudança = 0;

    for (int i = 0; i < 10; i++)
    {
        int sort_num = sort[i];

        for (int j = 0; j < 10; j++)
        {
            if(sort[i] < sort[j])
            {
                sort[i] = sort[j];
                sort[j] = sort_num;
                for (int k = 0; k < 10; k++)
                {
                    printf("(%i) ", sort[k]);
                }
                printf("\n");
                d_mudança++;
            }
        t_mudança++;
        }
    }
    printf("Número de  mudanças dentro: %i\n", d_mudança);
    printf("Número de  mudanças total: %i\n", t_mudança);
}
