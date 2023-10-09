#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct 
{
  char *rotulo;
  char *tipo;
  char *categorias;
} atributo;

void exibe_atributos(atributo *infos, int tamanho)
{
    if (infos == 0)
    {
        printf("O arquivo ARFF fornecido � inv�lido!\n");
        exit(0);
    }

    printf("==== ATRIBUTOS DO ARQUIVO ====\n");
    for(int i = 0; i < tamanho; i++)
    {
        printf("-> Atributo #%d\n", i+1);
        printf("R�tulo: %s\n", infos[i].rotulo);
        printf("Tipo: %s\n", infos[i].tipo);
        if (infos[i].categorias) printf("Categorias: %s\n", infos[i].categorias);
        if (i < tamanho-1) printf("------------------------------\n");
    }
    printf("===============================\n");
}

int conta_atributos(FILE *arff)
{
  int cont = 0;
  char linha[1025];
  fgets(linha, 1024, arff);
  while(!feof(arff))
  {
    if(strstr(linha, "@attribute"))
      cont++;

    fgets(linha, 1024, arff);
  }
  rewind(arff);

  return cont;
}

atributo* processa_atributos(FILE *arff)
{
  atributo *infos;
  char linha[1025], *token;
  int i = 0;
  // aloca o vetor de atributos
  if(!(infos = (atributo*) malloc(sizeof(atributo) * conta_atributos(arff)))){
    fprintf(stderr, "Erro ao alocar memoria!\n");
    exit(4);
  }
  // le o arquivo e armazena os atributos
  fgets(linha, 1024, arff);
  while(!feof(arff))
  {
    if(strstr(linha, "@attribute"))
    {
      if(!(token = strtok(linha, " ")))
      {
        fprintf(stderr, "Erro ao ler o arquivo!\n");
        exit(5);
      }
      
      if(!(token = strtok(NULL, " ")))
      {
        fprintf(stderr, "Erro ao ler o arquivo!\n");
        exit(6);
      }
      infos[i].rotulo = strdup(token);
      if(!(token = strtok(NULL, " ")))
      {
        fprintf(stderr, "Erro ao ler o arquivo!\n");
        exit(7);
      }
      infos[i].tipo = strdup(token);

      if(strstr(infos[i].tipo, "{"))
      {
        infos[i].categorias = strdup(infos[i].tipo);
        free(infos[i].tipo);
        infos[i].tipo = strdup("categoric");
      }
      else
        infos[i].categorias = 0;
    
      i++;
    }
    
    fgets(linha, 1024, arff);
  }
  rewind(arff);

  return infos;
}

// desaloca os atributos do strdup
int desaloca_atributos(atributo *infos, int tamanho)
{
  for(int i = 0; i < tamanho; i++)
  {
    free(infos[i].rotulo);
    free(infos[i].tipo);
    if (infos[i].categorias) free(infos[i].categorias);
  }
  free(infos);

  return 0;
}

int main(int argc, char **argv)
{
  int opt;
  char exibicao = 0;
  char *entrada = 0;
  FILE *arff;
  atributo *infos;

  while ((opt = getopt(argc, argv, "pi:")) != -1) 
  {
    switch (opt) 
    {
    case 'i':
      entrada = strdup(optarg);
      break;
    case 'p':
      exibicao = 1;
      break;
    default:
      fprintf(stderr, "Forma de uso: ./arff -i <arq_in> [-p]\n");
      exit(1);
    }
  }

  if ( ! entrada ) 
  {
    fprintf(stderr, "Forma de uso: ./arff -i <arq_in> [-p]\n");
    exit(2);
  }


  if(!(arff = fopen(entrada, "r")))
  {
    fprintf(stderr, "Erro ao abrir o arquivo %s\n", entrada);
    exit(3);
  }

  infos = processa_atributos(arff);

  if (exibicao)
    exibe_atributos(infos, conta_atributos(arff));

  desaloca_atributos(infos, conta_atributos(arff));
  free(entrada);
 
  fclose(arff);

  return 0 ;
}