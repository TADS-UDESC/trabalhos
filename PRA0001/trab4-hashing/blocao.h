#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ABP.h"
#include "FilaEncadeada.h"

#define ARQUIVO "fluxo_partida.bin"
#define HASH_TABLE "hash_table.txt"
#define N 1000
#define FLORESTA 1450000
#define SECAOANO FLORESTA/50

ABP vetorFloresta[FLORESTA];
long NUMPARTIDAS=0;
long QTDREG=0;
float totalHashing=0;
clock_t inicioHashing, fimHashing;

//declaracoes de funcoes
void randomIndicadorNomes(char *indicadorTimeA, char *local, char *indicadorTimeB);
void randomAno(int *ano);
void randomCodigo(unsigned long int *m);
void randomDia(int *dia);
void randomMes(int *mes);
void randomPublico(int *publico);
void randomPartida(Partida *partida);
void randomNPartida(int n, Partida *partidas);
void gols(int *gols);
void gravaPartida(Partida *partida);
void gravaNPartida(int n, Partida *partidas);
int arquivo_ler_todos();
void limpa_tudo();
int compara_long_unsigned_int(void *a, void *b);
int escolha_hashing();
int hash_calc(Partida *partidaLida, int escolha);
void busca_partida();
void mostra_secao_ano();
void mostra_partida_abstrato(void *n);

//-------------------------------------------------------------------------------------------
//---------------------------------FUNÇÕES GERADORAS DA DATABASE-----------------------------
//-------------------------------------------------------------------------------------------
void randomCodigo(unsigned long int *m) {
	static int i;
	*m = i++;
}

void randomDia(int *dia){
	*dia = rand()%30+1;
}

void randomMes(int *mes){
	*mes = rand()%12+1;
}

void randomAno(int *ano){
	*ano = rand()%50+1950;
}

void randomIndicadorNomes(char *indicadorTimeA, char *local, char *indicadorTimeB) {
	char indicadores[][4] = {
			"FIG\0", "JEC\0", "AVA\0", "CHA\0", "COR\0", 
			"SAO\0", "SAN\0", "PAL\0", "CAM\0", "CRU\0",
			"GRE\0", "INT\0", "FLA\0", "FLU\0", "BOT\0",
			"CAP\0", "CFC\0", "VIT\0", "SPO\0", "GOI\0"			 
	};
	char locais[][20] = {
			"Scarpelli\0", "ArenaJlle\0", "ressacola\0", "arenaConda\0", "ArenaTimao\0", 
			"FashionWeek\0", "FundodoMar\0", "chiqueiro\0", "Mineirao\0", "Mineirao\0",
			"Olimpico\0", "beiraRio\0", "maracana\0", "maracana\0", "Engenhao\0",
			"ArenaBxada\0", "Coutoreira\0", "Barradao\0", "IlhaRetiro\0", "SerraDrada\0"			 
	};
	int i, j;
	i = rand() % 20;
	j = rand() % 20;
	while(i==j){
		j = rand() % 20;
	}
	sprintf(indicadorTimeA, "%s", indicadores[i]);
	sprintf(local, "%s", locais[i]);
	sprintf(indicadorTimeB, "%s", indicadores[j]);
}

void gols(int *gols){
	*gols = rand()%5;
}

void randomPublico(int *publico){
	*publico = rand()%28999+1000;
}

void randomPartida(Partida *partida) {
	randomCodigo(&partida->codigo);
	randomDia(&partida->dia);
	randomMes(&partida->mes);
	randomAno(&partida->ano);
	randomIndicadorNomes(partida->nomeTimeA, partida->local, partida->nomeTimeB);
	gols(&partida->golsA);
	gols(&partida->golsB);
	randomPublico(&partida->publico);
}

void randomNPartida(int n, Partida *partidas) {
	int i;
	Partida partida;
	QTDREG += N;
	int IDatual, IDgravacao;
		
	for(i=0; i<n; i++) {
		randomPartida(&partida);
		partidas[i] = partida;
	} 
}
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------
//---------------------------------FUNÇÕES DE GRAVAÇÃO E LEITURA-----------------------------
//-------------------------------------------------------------------------------------------
void gravaPartida(Partida *partida) {
	FILE *fp;
	if(fp = fopen(ARQUIVO, "ab")) {
		fwrite(partida, sizeof(Partida), 1, fp);
	}
	fclose(fp);
}

void gravaNPartida(int n, Partida *partidas) {
	FILE *fp;
	if(fp = fopen(ARQUIVO, "ab")) {
		fwrite(partidas, sizeof(Partida), n, fp);
	}
	fclose(fp);
}

int arquivo_ler_todos( ){
    int achou=0, i, escolha=9;
    unsigned long int hash, cont=0;
    	
	FILE *fp, *hash_table;
    if(!( fp = fopen(ARQUIVO, "rb"))){	
        return achou;
    }
    rewind(fp);
    if(!( hash_table = fopen(HASH_TABLE, "wt"))){	
        return achou;
    }
    rewind(hash_table);
    
    
    //------inicializa todas árvores------------------------------------------
    for(i=0;i<FLORESTA;i++){
		inicializa_ABP(&vetorFloresta[i], sizeof(int));
	}
	//------------------------------------------------------------------------
    
    //----------------------define o tipo de hashing--------------------------
    escolha = escolha_hashing();
    //------------------------------------------------------------------------
    
    //------le do .bin, hashea e joga na FLORESTA, partida por partida--------
    Partida *uma_partida;
    
    inicioHashing = clock();
    while(!feof(fp)){
     	uma_partida  = malloc(sizeof(Partida));
    	if (fread(uma_partida, sizeof(Partida), 1, fp)){
  			hash = hash_calc(uma_partida, escolha);
			insere_ABP(&vetorFloresta[hash], &uma_partida->codigo, uma_partida, compara_long_unsigned_int);
			fprintf(hash_table, "%.7lu \t %.7lu\n", hash, uma_partida->codigo);
        }
        free(uma_partida);
        hash = 0;
        cont++;
    }
    fimHashing = clock();
    totalHashing = (float)(fimHashing-inicioHashing)/CLOCKS_PER_SEC;
	printf("Hashing levou: %f\n", totalHashing);
    
    fclose(fp);
    fclose(hash_table);
    //------------------------------------------------------------------------
    
    busca_partida(); //precisa ficar isso aqui?
       
    return achou;
}

void limpa_tudo() {
	QTDREG = 0;
	remove("fluxo_partida.bin");
	remove("hash_table.txt");
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
//---------------------------------FUNÇÕES DE HASHING--------------------------------------
//-------------------------------------------------------------------------------------------
void insere_hashing(){
	int hash = escolha_hashing();
	Partida *partidaNova;
    partidaNova  = malloc(sizeof(Partida));
	randomNPartida(1, partidaNova);
    printf("codigo da nova partida: %lu\n", partidaNova->codigo);
    gravaNPartida(1, partidaNova);
    hash = hash_calc(partidaNova, hash);
	insere_ABP(&vetorFloresta[hash], &partidaNova->codigo, partidaNova, compara_long_unsigned_int);
}

int escolha_hashing(){
	int escolha, sair;
	
	do{ 
		printf("\n");
		printf("	[MENU DE ESCOLHA DO TIPO DE HASHING]\n");
		printf("	0. hashing por codigo\n");
		printf("	1. hashing por ano\n");
		printf("	2. retornar\n");
		scanf("%i", &escolha);
		switch(escolha){        
			case 0 : 
				return 0;
			case 1 : 
				return 1;
			case 2 : 
				break;
			default  : 
				printf("Digite uma escolha Valida:"); getchar(); getchar();
		}
		printf("[0]retornar ao Menu de Hashing \t [1]repetir Menu\n");
		scanf("%i", &sair);
		if(sair==0){
			break;
		}      
    } while(1);
}

int hash_calc(Partida *partidaLida, int escolha){
	int hash=0;
	switch(escolha){        
		case 0 :
			hash = (partidaLida->codigo+(partidaLida->codigo%11))%(FLORESTA);
			return hash;
		case 1 : 
			hash = ((partidaLida->ano-1950)*SECAOANO)+(partidaLida->publico-1000);
			return hash; 
	}
}

void busca_partida(){
	int ano=0, publico=0;
	unsigned long int hash, hash_busca, busca;
	
	int escolha, sair;

	do{ 
		printf("\n");
		printf("	[MENU DE BUSCA (deve operar de acordo com ultimo hashing)]\n");
		printf("	0. busca por codigo\n");
		printf("	1. busca por ano e publico\n");
		printf("	2. cancelar\n");
		scanf("%i", &escolha);
		switch(escolha){        
			case 0 : 
				printf("Digite um codigo: \n");
				scanf("%lu", &busca);
				hash_busca = (busca+(busca%11))%(FLORESTA);
				printf("hash de %lu: %lu\n", busca, hash_busca);
				if(busca_APB(vetorFloresta[hash_busca], &busca, compara_long_unsigned_int)){
					printf("%lu encontrado!!\n\n", busca);
					printf("composicao da árvore que contém o codigo: \n");
					percurso_em_ordem(vetorFloresta[hash_busca], mostra_partida_abstrato);
					printf("	0. excluir\n");
					printf("	1. continuar\n");
					scanf("%i", &escolha);
					if (escolha == 0){
						remove_ABP(&vetorFloresta[hash_busca], &busca, compara_long_unsigned_int);
						printf("partida excluida\n");
					}
				} else{
					printf("%lu nao encontrado!!\n\n", busca);
				}
				
				break;
			case 1 : 
				while(ano<1950 || ano>1999){
					printf("Digite o ano da partida (1950->1999): \n");
					scanf("%i", &ano);
				}
				while(publico<1000 || publico>29999){
					printf("Digite o publico da partida (1000->29999): \n");
					scanf("%i", &publico);
				}
				hash = ((ano-1950)*SECAOANO)+(publico-1000);
				printf("hash da partida: %lu\n", hash);
				
				percurso_em_ordem(vetorFloresta[hash], mostra_partida_abstrato);
				
				break;
			case 2 :
				break;
			default  : 
				printf("Digite uma escolha Valida:"); getchar(); getchar();
		} 
		
		printf("[0]retornar ao Menu de Hashing \t [1]repetir Menu de busca\n");
		scanf("%i", &sair);
		if(sair==0){
			break;
		}  
    } while(1);
	
}


void mostra_secao_ano(){
	int escolha_ano=0, parar=9;
	long unsigned int secao_ano=0, i=0;
	printf("qual ano deve ser verificado? ");
	scanf("%i", &escolha_ano);
	escolha_ano = escolha_ano -1950;
	secao_ano = SECAOANO*escolha_ano;
	for(i=secao_ano;i<secao_ano+SECAOANO;i++){
		if(vetorFloresta[i].raiz!=NULL){
			printf("árvore %lu contém os seguintes códigos de partidas: \n", i);
			percurso_em_ordem(vetorFloresta[i], mostra_partida_abstrato);
			printf("[0]parar \t [1]continuar\n");
			scanf("%i", &parar);
			if(parar==0){
				break;
			}
		}
	}
}

void mostra_partida_abstrato(void *n){
	NoABP *no_partida_recebida = (NoABP *) n;
	partida_encontrada(no_partida_recebida);
}

int compara_long_unsigned_int(void *a, void *b){
    long unsigned int *pa = (long unsigned int *) a;
    long unsigned int *pb = (long unsigned int *) b;
    
    if(*pa > *pb)
       return 1;

    if(*pa < *pb)
       return -1;

    return 0;

}

/*
inicioHashing = clock();
fimHashing = clock();
totalHashing = (float)(fimHashing-inicioHashing)/CLOCKS_PER_SEC;
printf("Hashing levou: %f\n", totalHashing);

*/ 
