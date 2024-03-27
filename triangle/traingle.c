#include <cs50.h>
#include <stdio.h>

string triangle(int a, int b, int c);

int main(void)
{
    int x = 0, y = 0, z = 0;
    x = get_long("x- "), y = get_long("y- "), z = get_long("z- ");
    string sum = triangle(x, y, z);
    printf("%s", sum);
}
string triangle(int a, int b, int c)
{
    if (a > 0 && b > 0 && c > 0 && a + b > c && a + c > b && b + c > a)
    {
        return "VÁLIDO\n";
    }
    else
    {
        return "INVÁLDIDO\n";
    }
}