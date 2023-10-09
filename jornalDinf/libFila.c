#include <stdio.h>
#include <stdlib.h>
#include "libFila.h"

fila_t *cria_fila ()
{
    fila_t *nova = (fila_t *) malloc(sizeof(fila_t));
    nova->ini = nova->fim = NULL;

    return nova;
}

noticia_t *cria_noticia ()
{
    noticia_t *nova = (noticia_t *) malloc(sizeof(noticia_t));
    nova->idade = 0;
    nova->prox = NULL;
    nova->titulo = (char *) malloc(sizeof(char) * 33);
    nova->texto = (char *) malloc(sizeof(char) * 513);
    requisita(nova->titulo, nova->texto);
    printf("\n");

    return nova;
}

void requisita(char *titulo, char *texto){
    getchar();
    printf("Digite o título: ");
    fgets(titulo, 33, stdin);
    printf("Digite o texto: ");
    fgets(texto, 513, stdin);
}

void envelhece_noticias(fila_t *tipo0, fila_t *tipo1)
{
    noticia_t *aux = tipo0->ini;
    noticia_t *rem;
    while (aux != NULL)
    {
        aux->idade++;
        if(aux->idade > 3)
        {
            rem = aux;
            aux = aux->prox;
            free(rem);
            continue;
        }
        aux = aux->prox;
    }

    aux = tipo1->ini;
    while (aux != NULL)
    {
        aux->idade++;
        if(aux->idade > 3)
        {
            rem = aux;
            aux = aux->prox;
            free(rem);
            continue;
        }
        aux = aux->prox;
    }
}

int eh_valida(noticia_t *noticia)
{
    if(noticia)
        return 1;
    return 0;
}

void exibe_noticias(noticia_t *noticia1, noticia_t *noticia2)
{

        printf("\n=======================================================\n\n");
        if(noticia1 == NULL)
        {
            printf("Esta edição foi pulada por falta de notícias!\n\n");
            printf("=======================================================\n\n");
            return;
        }
        printf("%s\n", noticia1->titulo);
        printf("%s\n", noticia1->texto);

        if(noticia2 == NULL)
        {
            printf("=======================================================\n\n");
            return;
        }
        printf("==\n");
        printf("\n%s\n", noticia2->titulo);
        printf("%s\n", noticia2->texto);
        printf("=======================================================\n\n");
}

void desaloca_noticia(noticia_t **noticia)
{
    free((*noticia)->titulo);
    free((*noticia)->texto);
    free(*noticia);
    *noticia = NULL;
}

void fecha_edicao(fila_t *tipo0, fila_t *tipo1)
{
    noticia_t *aux1, *aux2;
    if(eh_valida(tipo0->ini) && eh_valida(tipo0->ini->prox))
    {
        aux1 = dequeue(tipo0);
        aux2 = dequeue(tipo0);
        exibe_noticias(aux1, aux2);
        desaloca_noticia(&aux1);
        desaloca_noticia(&aux2);
    }
    else if(eh_valida(tipo0->ini) && eh_valida(tipo1->ini))
            {
        aux1 = dequeue(tipo0);
        aux2 = dequeue(tipo1);
        exibe_noticias(aux1, aux2);
        desaloca_noticia(&aux1);
        desaloca_noticia(&aux2);
    }
    else if(eh_valida(tipo1->ini) && eh_valida(tipo1->ini->prox))
    {
        aux1 = dequeue(tipo1);
        aux2 = dequeue(tipo1);
        exibe_noticias(aux1, aux2);
        desaloca_noticia(&aux1);
        desaloca_noticia(&aux2);
    }
    else if(eh_valida(tipo0->ini))
    {
        aux1 = dequeue(tipo0);
        exibe_noticias(aux1, NULL);
        desaloca_noticia(&aux1);
    }
    else if(eh_valida(tipo1->ini))
    {
        aux1 = dequeue(tipo1);
        exibe_noticias(aux1, NULL);
        desaloca_noticia(&aux1);
    }
    else
        exibe_noticias(NULL, NULL);
}

void destroi_fila (fila_t **fila)
{
    noticia_t *aux = (*fila)->ini;
    if(!(aux))
    {
        free(*fila);
        *fila = NULL;
        return;
    }

    while ((*fila)->ini != (*fila)->fim)
    {
        (*fila)->ini = (*fila)->ini->prox;
        desaloca_noticia(&aux);
        aux = (*fila)->ini;
    }

    desaloca_noticia(&aux);
    free(*fila);
    *fila = NULL;
}

void enqueue (fila_t *fila, noticia_t *noticia)
{
    if (fila->ini == NULL)
        fila->ini = fila->fim = noticia;
    else
    {
        fila->fim->prox = noticia;
        fila->fim = noticia;
    }
}

noticia_t *dequeue (fila_t *fila)
{
    noticia_t *aux = fila->ini;

    if (fila->ini == NULL)
        return NULL;
    if(fila->ini == fila->fim)
        fila->ini = fila->fim = NULL;
    else
        fila->ini = fila->ini->prox;

    return aux;
}