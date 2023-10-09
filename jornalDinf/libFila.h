typedef struct noticia {
    int idade;
    char *titulo;
    char *texto; 
    struct noticia *prox;
} noticia_t;

typedef struct fila {
    noticia_t *ini;
    noticia_t *fim;
} fila_t;

/* aloca espaco na memoria para a fila e retorna um ponteiro */
fila_t *cria_fila ();

/* aloca espaco na memoria para a noticia e retorna um ponteiro */
noticia_t *cria_noticia ();

/* requisita titulo e texto para a noticia */
void requisita(char *titulo, char *texto);

/* insere uma noticia na fila indicada */
void enqueue (fila_t *fila, noticia_t *noticia);

/* retira a noticia com prioridade da fila e a retorna um ponteiro para ela */
noticia_t *dequeue (fila_t *fila);

/* envelhece as noticias e remove as que estao velhas */
void envelhece_noticias(fila_t *tipo0, fila_t *tipo1);

/* exibe na tela as noticias */
void exibe_noticias(noticia_t *noticia1, noticia_t *noticia2);

/* fecha a edicao e exibe as noticias */
void fecha_edicao(fila_t *tipo0, fila_t *tipo1);

/* desaloca da memoria uma noticia */
void desaloca_noticia(noticia_t **noticia);

/* desaloca toda a fila */
void destroi_fila (fila_t **fila);