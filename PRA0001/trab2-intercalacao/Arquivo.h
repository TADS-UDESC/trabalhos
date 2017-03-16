#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARQUIVO "fluxo_partida.bin"
#define N 1024
#define NUMERO_VIAS 10

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
}Partida;



float randomFloat(float a, float b);
void randomIndicador(char *indicadores);
void randomValor(unsigned long int *v);
void randomData(char *f);
void randomCodigo(unsigned long int *m);
void randomPartida(Partida *partida);
void randomNPartida(int n, Partida *partidas);

void gravaPartida(Partida *partida);
void gravaNPartida(int n, Partida *partidas);

int lePartida(Partida *partida, FILE *fp);
int leNPartida(int n, Partida *partidas, FILE *fp);
int leRegistros(int n, Partida *partidas, FILE *fp);
int leRegistro(Partida *tp, FILE *fp);
void apaga_registro();

int arquivo_ler_todos( );
int compara( Partida *a, Partida *b, int opcao);
void troca_registros(Partida* a, Partida* b);
int particionamento( Partida *vec, int left, int right, char opcao);
void ordenacao(Partida *vec, int left, int right, int opcao);
void split_file(int opcao);
void apaga_arquivos();
void le_inicial( Partida *page, int *pos);
void encontra_menor_na_passada(Partida *page, int *pos,	FILE *fp, int opcao, FILE *pt_INDEX);
void intercala(int opcao);
void limpaTudo();

//coisas novas
void quicksort(Partida *v, int first, int last, int opcao);
void divideOriginal();
void ordenaopcoes();
