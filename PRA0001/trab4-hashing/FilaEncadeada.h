#define ERRO_FILA_VAZIA -1

typedef struct ele{
   void *info;
   struct ele *proximo;
}Elemento;

typedef struct {
     int tamanhoInfo;
     Elemento *inicio, *fim;
}FilaEncadeada;

void inicializaFila(FilaEncadeada *f, int tamanho);
int inserir(FilaEncadeada *f, void *info);
int remover(FilaEncadeada *f, void *info);
int filaVazia(FilaEncadeada f);
void limpaFila(FilaEncadeada *f);
void mostraFila(FilaEncadeada f, void (*mostraInfo)(void *) );
