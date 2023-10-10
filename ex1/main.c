#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *poema, caractere;
    int posicao, tamanho;
    FILE *arquivo;

    if(!(arquivo = fopen("poema.bin", "rb")))
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fseek(arquivo, 0, SEEK_END);
    tamanho = ftell(arquivo) / 5;
    poema = (char *) malloc(tamanho * sizeof(char));
    rewind(arquivo);

    fread(&posicao, sizeof(int), 1, arquivo);
    fread(&caractere, sizeof(char), 1, arquivo);
    while(!feof(arquivo))
    {
        poema[posicao] = caractere;
        fread(&posicao, sizeof(int), 1, arquivo);
        fread(&caractere, sizeof(char), 1, arquivo);
    }

    for(int i = 0; i < tamanho; i++)
        printf("%c", poema[i]);

    free(poema);
    fclose(arquivo);

    return 0;
}