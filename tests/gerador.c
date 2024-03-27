#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <time.h>

int d4(void);
int d6(void);
int d8(void);
int d10(void);
int d12(void);
int d20(void);

int main(void)
{
    string sujeito[8] = {
        "inocente curioso",
        "criminoso",
        "pessoa influente",
        "bando cultista",
        "cultista independente",
        "ex-agente da Ordo Realitas",
        "item amaldiçoado",
        "criatura paranormal"
    };
    string ação[10] = {
        "invocou uma criatura de propósito",
        "incovou uma criatura sem querer",
        "está sequestrando inocentes",
        "está assassinando inocentes",
        "está usando um ritual ou item amaldiçoado para cometer crimes",
        "está recrutando cultistas",
        "está pesquisando um ritual perigoso",
        "está coletando itens amaldiçoados",
        "matou um agente da Ordo Realitas",
        "está manipulando um agente da Ordo Realitas"
    };
    string local[20] = {
        "escola",
        "hospital",
        "vilarejo",
        "fazenda",
        "mata fechada",
        "becos de metrópole",
        "arranha-céu",
        "grande loja de departamento",
        "esgoto",
        "zona industrial da cidade",
        "shopping center",
        "orfanato",
        "museu",
        "cemitério",
        "delegacia ou base militar",
        "mansão",
        "antiga sede da Ordo Realitas",
        "navio",
        "ilha remota",
        "caverna"
    };
    string aliado[4] = {
        "civil alheio ao paranormal",
        "civil exposto ao paranormal",
        "antigo conhecido de um dos agentes",
        "outro agente da ordo realitas",
    };
    string objeto[6] = {
        "equipamento",
        "ingrediente para um ritual poderoso",
        "equipamento com modificações",
        "artefato com grande valor para a Ordem",
        "item amaldiçoado",
        "explosivo"
    };
    string evento[12] = {
        "o aparecimento de uma criatura paranormal de grande poder",
        "a chegada de reforços inimigos",
        "uma doença paranormal afetando o aliado",
        "civis se revoltando contra eles",
        "a revelação de que o aliado era um vilão",
        "a revelação de que as ações do inimigo era justificadas",
        "perda de seus equipamentos",
        "ter que proteger um civil",
        "perda de comunicação com a Ordo Realitas e acesso ao sistema de crédito",
        "agentes da lei os importunando",
        "um desastre",
        "o aparecimento de um antigo inimigo"
    };

    printf("Um(a) %s %s em um(a) %s.\n"
    "Durante a investigação, o grupo terá a ajuda de um(a) %s\n"
    "e poderá encontrar um %s.\n"
    "Porém, em determinado momento os agentes serão\n"
    "surpreendidos por %s.\n",
    sujeito[d8()], ação[d10()], local[d20()],
    aliado[d4()], objeto[d6()], evento[d12()]);

}
int d4(void)
{
    srand(time(NULL) * 4);
    int dado = (random() / ((double) RAND_MAX + 1)) * 4;
    printf("Rolagem do D4: %i\n", dado);
    return dado;
}
int d6(void)
{
    srand(time(NULL) * 6);
    int dado = (random() / ((double) RAND_MAX + 1)) * 6;
    printf("Rolagem do D6: %i\n", dado);
    return dado;
}
int d8(void)
{
    srand(time(NULL) * 8);
    int dado = (random() / ((double) RAND_MAX + 1)) * 8;
    printf("Rolagem do D8: %i\n", dado);
    return dado;
}
int d10(void)
{
    srand(time(NULL) * 10);
    int dado = (random() / ((double) RAND_MAX + 1)) * 10;
    printf("Rolagem do D10: %i\n", dado);
    return dado;
}
int d12(void)
{
    srand(time(NULL) * 12);
    int dado = (random() / ((double) RAND_MAX + 1)) * 12;
    printf("Rolagem do D12:%i\n", dado);
    return dado;
}
int d20(void)
{
    srand(time(NULL) * 20);
    int dado = (random() / ((double) RAND_MAX + 1)) * 20;
    printf("Rolagem do D20: %i\n", dado);
    return dado;
}
