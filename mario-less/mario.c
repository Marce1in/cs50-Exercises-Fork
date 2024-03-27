#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;

    //pyramid height selector
    do
    {
        n = get_int("height: ");
    }
    while (n < 1 || n > 8);

    //pyramid maker
    for (int i = 0; i < n; i++)
    {
        //pusher that makes pyramid right-facing
        for (int j = n; j > i + 1; j--)
        {
            printf(" ");
        }
        //pyramid "wall"
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}