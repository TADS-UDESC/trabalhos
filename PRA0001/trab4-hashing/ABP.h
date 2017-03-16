


typedef struct Partida{
	unsigned long int codigo;
	int dia;
	int mes;
	int ano;
	char nomeTimeA[4];
	int golsA;
	int golsB;
	char nomeTimeB[4];
	int publico;
	char local[20];
	int tamanhoInfo;
}Partida;


typedef struct no{
   void *info;
   Partida fruto;
   int fb;
   struct no *esq, *dir, *pai;
}NoABP;


typedef struct{
   int tamanhoInfo;
   NoABP *raiz;
}ABP;

//unsigned long int colisoes = 0;

void inicializa_ABP(ABP *a, int t);
void insere_ABP(ABP *a, void *info, Partida *fruto, int (*compara_info)(void *, void *) );
void remove_ABP(ABP *a, void *info, int (*compara_info)(void *, void *) );
void limpa_ABP(ABP *a);
int busca_APB(ABP a, void *chave, int (*compara_info)(void *, void *) );
void percurso_pre_ordem(ABP a, void (*mostra_info)(void *) );
void percurso_em_ordem(ABP a, void (*mostra_info)(void *) );
void percurso_pos_ordem(ABP a, void (*mostra_info)(void *) );
void mostra_estrutura(ABP a, void (*mostra_info)(void *) );
int altura(NoABP *n);

void partida_encontrada(NoABP *n);

