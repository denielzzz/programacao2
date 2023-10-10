#include <stdio.h>
#include <stdlib.h>
#include "libDeck.h"

int verifica_palindromo(char *palavra)
{
    t_cabeca c;
    inicializa(&c);

    insere_inicio(&c, palavra[0]);
    for (int i = 1; palavra[i] != '\0'; i++)
        if (palavra[i] != '\n')
            insere_fim(&c, palavra[i]);

    while(c.inicio != NULL && c.fim != NULL)
    {
        if (c.inicio->letra != c.fim->letra)
            return 0;

        remove_inicio(&c);
        remove_fim(&c);
    }

    return 1;
}

void inicializa(t_cabeca *c)
{
    c->inicio = NULL;
    c->fim = NULL;
}

void insere_inicio(t_cabeca *c, char letra)
{
    t_deck *novo = (t_deck *)malloc(sizeof(t_deck));
    novo->letra = letra;
    novo->prox = c->inicio;
    novo->ant = NULL;
    c->inicio = novo;
}

void insere_fim(t_cabeca *c, char letra)
{
    t_deck *novo = (t_deck *)malloc(sizeof(t_deck));
    novo->letra = letra;
    novo->prox = NULL;
    novo->ant = c->fim;
    c->fim = novo;
}

void remove_inicio(t_cabeca *c)
{
    if (c->inicio != NULL)
    {
        t_deck *aux = c->inicio;
        c->inicio = c->inicio->prox;
        free(aux);
    }
}

void remove_fim(t_cabeca *c)
{
    if (c->fim != NULL)
    {
        t_deck *aux = c->fim;
        c->fim = c->fim->ant;
        free(aux);
    }
}