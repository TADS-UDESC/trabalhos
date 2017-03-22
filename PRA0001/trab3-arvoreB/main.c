#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "blocao.h"


void gera_registros(Partida *partidas);
void le_todos_registros();
void ordenaopcoes();
void menuArvoreB();
void le_todos_registros_alterado(int escolhaIndex);
FILE *funcaoAbreIndexTXT(int escolhaIndex);


int main() {
    int i;
    
    Partida *partidas;
    partidas  = malloc(N*sizeof(Partida));
    
    do{ 
        
        imprime_menu_principal(); 

        switch(get_opcao()){        
            case '0' : exit(1);
            case '1' : gera_registros(partidas); break; 
            case '2' : le_todos_registros(); break;
            case '3' : ordenaopcoes(); break;
            case '4' : limpa_tudo(); break;
            case '5' : apaga_registro(); break;
            case '6' : menuArvoreB(); break;
            default  : printf("Digite uma opcao Valida:"); getchar(); getchar();
        }    
    } while(1);
    
    return 0;
}

void ordenaopcoes(){
	int opcao =0;
	printf("Digite 1 para ordenar por público;\n 2 para ordenar por ano; \n 3 para ordernar por GolsA; e 4 para ordenar por GolsB:\n");
	scanf("%d", &opcao);
	split_file(opcao);
	intercala(opcao);	
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
    system("clear");       
    if(!arquivo_ler_todos()){
        printf("\n\n");
        printf("Nenhum registros encontrado");
    }
    getchar();  
}

void menuArvoreB(){
	int escolha, escolhaIndex=0, i;
    unsigned long int codigoPartida;
    
    Partida partidaExcluir;
    Partida *partidasLidas;
    partidasLidas  = malloc(N*sizeof(Partida));
    
    printf("Menu da Arvore B com ordem %d\n",M); 
    while(1){ 
        printf("0.sair pro menu principal\n");
        printf("1.ordenar/indexar partir da leitura do arquivo bin\n");
        printf("2.exibir Arvore B com valores de publico\n"); //excluir isso ou melhorar
        printf("3.limpar arvoreB (necessario para novas indexacoes)\n");
        printf("4.mostrar a partir do vetor novo\n");
        printf("5.deletar uma partida\n");
        scanf("%d",&escolha);
        getchar(); 

        switch(escolha){ 
            case 0: 
				break;
            case 1: 
				
				//escolha
				printf("voce deseja ordenar a DB por qual indexador?\n");
				printf("[1] publico / [2] ano / [3] golsA\n");
				scanf("%i", &escolhaIndex);
				
				//ordenacao
				inicio = clock();
				le_todos_registros_alterado(escolhaIndex); 
				fim = clock();
				tempoBloco = (float)(fim-inicio) / CLOCKS_PER_SEC;
				printf("tempo de ordenação na arvore: %f\n", tempoBloco);
				getchar();
				
				//indexacao
				FILE *index;
				index = funcaoAbreIndexTXT(escolhaIndex);
				int qtd;
                printf("\n Quantos registros deseja vizualizar por vez?");
                scanf("%d", &qtd);
				emOrdem(root, index, qtd);
				
				//liberacao
				fclose(index);
				break;
			case 2:
				display(root, 0); 
				break;
			case 3:
				root = NULL;
				//emOrdem(root, index);
				break;
			case 4:
				//essa função pode ser modificada ou usada os mostra paginado antigo
				//mas dai recebendo o vetor novo
				//printaVetorNovo(vetorPartidaNovo);
				break;
			case 5:
				printf("informe o codigo da partida para deletar: "); 
                scanf("%uli",&codigoPartida);
                printf("codigo da partida informado: %u\n", codigoPartida);
                partidaExcluir.codigo = codigoPartida;
                printf("codigo da partida informado: %u\n", partidaExcluir.codigo);
                DelNode(partidaExcluir); 
                break; 
        } 
    }
}

void le_todos_registros_alterado(int escolhaIndex) {
    system("clear");       

    if(!arquivo_ler_todos_alterado(escolhaIndex)) {
        printf("\n");
    }

    getchar();  
}

FILE *funcaoAbreIndexTXT(int escolhaIndex){
	FILE *index;

	switch (escolhaIndex)	{
		case 1:
			index = fopen("indexPublico.txt", "at");
			break;	

		case 2:
			index = fopen("indexAno.txt", "at");
			break;		

		case 3:
			index = fopen("indexGolsA.txt", "at");
			break;

	}

	return index;
}

