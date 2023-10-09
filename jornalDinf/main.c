#include <stdio.h>
#include "libFila.h"

int main()
{
    fila_t *tipo0 = cria_fila();
    fila_t *tipo1 = cria_fila();
    int opcao;
    int tipo;

    do
    {
        printf("1 - Cadastrar notícia\n");
        printf("2 - Fechar edição\n");
        printf("3 - Sair\n");
        printf("Digite a opção: ");
        scanf("%d", &opcao);
        if(opcao == 1)
        {
            printf("\nDigite o tipo da notícia: ");
            scanf(" %d", &tipo);
            if (tipo == 0)
                enqueue(tipo0, cria_noticia());
            else
                enqueue(tipo1, cria_noticia());
        }
        if(opcao == 2)
            fecha_edicao(tipo0, tipo1);

    } while (opcao != 3);

    destroi_fila(&tipo0);
    destroi_fila(&tipo1);

    return 0;
}