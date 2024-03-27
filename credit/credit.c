#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Número do cartão de crédito
    long crednum;
    //As sobras/resto do resultado da divisão do crednum por 10
    int sobra;
    //Faz e verifica se o resultado da soma das sobras divididas por 10 dá resto 0
    int verificador = 0;
    //Contador que altera se o número vai ser dobrado e somado ou apenas somado
    int i = 0;

    crednum = get_long("you'r credit card, sir? ");
    //Crednum reserva para os usos após o calculo
    long num = crednum;

    if (crednum >= 4000000000000 && crednum <= 5600000000000000)
    {
        while (crednum > 0)
        {
            //Separa cada digito
            sobra = crednum % 10;
            crednum = crednum - sobra;
            crednum = crednum / 10;
            //Soma metade dos digitos
            if (i == 0)
            {
                i++;
                verificador = sobra + verificador;
            }
            //Dobra e soma a outra metade dos digitos
            else
            {
                i--;
                sobra = sobra * 2;
                if (sobra >= 10)
                {
                    sobra = sobra % 10;
                    verificador = verificador + sobra + 1;
                }
                else
                {
                    verificador = verificador + sobra;
                }
            }
        }
        //Tenta transformar o resultado da somas em 0
        verificador = verificador % 10;
        if (verificador == 0)
        {
            //Dimínui o crednum até os dois últimos digitos para a identificação da empresa do cartão
            for (i = 50; i < num; i++)
            {
                sobra = num % 10;
                num = num - sobra;
                num = num / 10;
            }
            if (num >= 40 && num <= 49)
            {
                printf("VISA\n");
            }
            else if (num >= 51 && num <= 55)
            {
                printf("MASTERCARD\n");
            }
            else if (num == 34 || num == 37)
            {
                printf("AMEX\n");
            }
            //Se os dois primeiros digitos não forem de nenhuma empresa
            else
            {
                printf("INVALID\n");
            }
        }
        //Se o resultado da soma dos restos não for divisível por 10
        else
        {
            printf("INVALID\n");
        }
    }
    //Se a quantidade de dígitos do cartão for muito grande ou muito pequeno para ser considerado um cartão válido
    else
    {
        printf("INVALID\n");
    }
}