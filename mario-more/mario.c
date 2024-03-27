#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;

    //pyramids height selector
    do
    {
        n = get_int("height: ");
    }
    while (n < 1 || n > 8);

    //pyramids maker
    for (int i = 0; i < n; i++)
    {
        //pusher that make the first pyramid right-facing
        for (int j = n; j > i + 1; j--)
        {
            printf(" ");
        }
        //pyramid right-facing "wall"
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        //pyramids gap
        printf("  ");

        //pyramid left-facing "wall"
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        //next line
        printf("\n");
    }
}