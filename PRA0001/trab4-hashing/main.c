#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "blocao.h"


void gera_registros(Partida *partidas);
void le_todos_registros();
void imprime_menu_principal();
void imprime_menu_hashing();
void menuHashing();

int main() {
    int i, opcao;
    
    Partida *partidas;
    partidas  = malloc(N*sizeof(Partida));
    
    do{ 
        imprime_menu_principal();
        scanf("%i", &opcao);
        switch(opcao){        
            case 0 : 
				exit(1);
            case 1 : 
				gera_registros(partidas); 
				break; 
            case 2 : 
				menuHashing(); 
				break;
			case 3 :
				limpa_tudo();
				break;
            default  : 
				printf("Digite uma opcao Valida:"); getchar(); getchar();
        }    
    } while(1);
    
    return 0;
}

void menuHashing(){
	int sair, opcao;
	do{ 
		imprime_menu_hashing();
		scanf("%i", &opcao);
		switch(opcao){ 
			case 0 : 
				break;
			case 1 :
				arquivo_ler_todos();
				break;
			case 2 :
				busca_partida();
				break;
			case 3 :	
				mostra_secao_ano();
				break;
			case 4:
				insere_hashing();
				break;
			default  : 
				printf("Digite uma opcao Valida:"); getchar(); getchar();
		}
		printf("[0]voltar ao menu principal \t [1]mostrar menu de hashing\n");
		scanf("%i", &sair);
		if(sair==0){
			break;
		}
	} while(1);
	
}

void imprime_menu_principal(){
    printf("\n CAMPEONATOS BRASILEIROS \n");
    printf("1. Gerar as partidas do campeonato\n");        
    printf("2. Acessar menu de Hashing\n");
    printf("3. Apagar banco de dados e tabela hash\n");
    printf("0. Sair\n");
    printf("\n");     
}

void imprime_menu_hashing(){
	printf("	[MENU DE HASHING]\n");
	printf("	0. sair para o menu principal\n");
    printf("	1. realizar hashing\n");
    printf("	2. realizar busca e remocao\n");
    printf("	3. mostrar secao ano\n");
    printf("	4. inserir partida\n");
}

void gera_registros(Partida *partidas){
    srand(time(NULL));
    int i, quantidade_registros;
    time_t inicio, fim;
	inicio = time(NULL);

    printf("\n Quantos registros (em mil)?: ");
    scanf("%d", &quantidade_registros);
    
    NUMPARTIDAS = quantidade_registros * N;

    for(i=0; i< quantidade_registros; i++){
        printf("\n Gravando...  (%d/%d)", i+1, quantidade_registros );
        randomNPartida(N, partidas);
        gravaNPartida(N, partidas);
    }
    fim = time(NULL);
    printf("\n Registros gerados com sucesso\n");

    getchar();
     
}

void le_todos_registros() {
    if(!arquivo_ler_todos()){
        printf("\n\n");
        printf("Nenhum registros encontrado");
    }
    getchar();  
}

