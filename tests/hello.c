#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int TAMANHO_MÁXIMO = 38; //Maior nome brasileiro "Charlingtonglaevionbeecheknavare"

int main(void)
{
    printf("Qual teu nome? ");

    char* nome = malloc(sizeof(char) * TAMANHO_MÁXIMO  + 1);
    if (nome == NULL)
    {
        printf("Memória insuficiente");
        return 1;
    }

    fgets(nome, TAMANHO_MÁXIMO, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    if(strcmp(nome, "jailson") == 0)
    {
        printf("Que delícia cara\n");
    }
    else
    {
        printf("Salve, %s!\n", nome);
    }

    free(nome);
    return 0;
}