#include <stdio.h>

void print_neighbors(int a, int b);

int test_array[5][6];

int main(void)
{

    //Populate the array
    for(int i = 0, k = 10; i < 5; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            test_array[i][j] = k;
            k++;
        }
    }
    //Print the test array
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            printf("[%i]", test_array[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            print_neighbors(i, j);
        }
    }
}
void print_neighbors(int a, int b)
{
    printf("Neighbors of [%i]:\n\n", test_array[a][b]);

    for(int i = a - 1; i < a + 2; i++)
    {
        for(int j = b - 1; j < b + 2; j++)
        {
            if(i < 0 || i >= 5)
            {
                break;
            }
            if(j >= 0 && j < 6)
            {
                printf("[%i]", test_array[i][j]);
            }
        }
        printf("\n");
    }
}