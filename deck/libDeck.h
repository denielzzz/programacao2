#include <stdio.h>

typedef struct deck
{
    char letra;
    struct deck *prox;
    struct deck *ant;
} t_deck;

typedef struct cabeca
{
    t_deck *inicio;
    t_deck *fim;
} t_cabeca;

int verifica_palindromo(char *palavra);

void inicializa(t_cabeca *c);

void insere_inicio(t_cabeca *c, char letra);

void insere_fim(t_cabeca *c, char letra);

void remove_inicio(t_cabeca *c);

void remove_fim(t_cabeca *c);