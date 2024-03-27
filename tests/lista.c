// Implements a list of numbers with linked list
#include <stdio.h>
#include <stdlib.h>

// Represents a node
typedef struct node
{
    int number;
    struct node *next;
}
node;

char ordem(void);
node *lista_crescente(int tamanho, node *p);
node *lista_decrescente(int tamanho);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("ERRO! MÉTODO DE USO: ./lista [TAMANHO DA LISTA]\n");
        return 1;
    }

    int tamanho_da_lista = atoi(argv[1]);

    if (tamanho_da_lista < 0)
    {
        printf("ERRO! O TAMANHO DE LISTA DEVE SER UM NÚMERO INTEIRO MAIOR QUE ZERO\n");
        return 2;
    }

    //Seleciona um tipo de ordem e cria a lista
    node *lista = malloc(sizeof(node));
    char input = ordem();

    if (input == '+')
    {
        lista = lista_crescente(tamanho_da_lista, lista);
    }
    else if (input == '-')
    {
        lista = lista_decrescente(tamanho_da_lista);
    }
    else
    {
        printf("ERRO! INPUT INVÁLIDO\n");
        return 3;
    }

    // Print a lista
    for (node *tmp = lista; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }

    // Free a lista
    while (lista != NULL)
    {
        node *tmp = lista->next;
        free(lista);
        lista = tmp;
    }
    return 0;
}

//Pergunta para o usuário se a ordem da lista será crescente ou decrescente
char ordem(void)
{
    char input;
    //Explica ao usuário oque ele deve fazer
    printf("Escolha a ordem da lista\n"
    "Digite '+' para a lista ser crescente\n"
    "Digite '-' para a lista ser decrescente\n\n");

    //Recebe o input do usuário
    printf("Ordem: ");
    scanf("%c", &input);

    return input;
}

node *lista_crescente(int tamanho, node *p)
{
    node *n = malloc(sizeof(node));
    if (tamanho != 1)
    {
        n->next = p;
        n->number = tamanho;
        n = lista_crescente(tamanho - 1, n);
    }
    else
    {
        n->next = p;
        n->number = tamanho;
    }
    return n;
}

node *lista_decrescente(int tamanho)
{
    node *n = malloc(sizeof(node));

    if (tamanho > 1)
    {
        n->next = lista_decrescente(tamanho - 1);
        n->number = tamanho;
    }
    else
    {
        n->next = NULL;
        n->number = tamanho;
    }
    return n;
}