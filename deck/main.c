#include <stdio.h>
#include "libDeck.h"

int main()
{
    char palavra[100];
    fgets(palavra, 100, stdin);

    if(verifica_palindromo(palavra))
        printf("é palidromo\n");
    else
        printf("não é palindromo\n");

    return 0;
}