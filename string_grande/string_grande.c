#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //string gigante para organizar
    string frase = "'Nome' BATATA 'Marcelo' ROPA 'Idade' ENTERNO '17' LEKLEKLEK 'Nascimento' UIUIUIUI '27/05/2022' MFAOPIFNMA][][== [ 'Cor favorita' FOOOO 'Roxo'";
    string frase_organi[10];
    int k = 0;

    for (int i = 0; frase[i] != '&' + 1; i++)
    {
        if (frase[i] == '&' + 1)
        {
            i++;
            for (int j = i; frase[j] != '&' + 1; j++)
            {
                frase_organi[k] = frase[j];
            }
        }
        k++;
    }
}