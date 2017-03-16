#include "Futebol.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void funcao_menu(int opcao_menu);
void funcao_submenu_database(int opcao_menu);
float blocoGravacao(int tamArquivo);
void funcao_auxiliar_limpar_tela();

long long tamBloco1GB = 20890000;

int main(){
	int opcao_menu=1;
	while(opcao_menu!=0){
		printf("*****Bem vindo ao soft Futebol!*****\n\n");
		printf("    *** MENU *** \n");
		printf("1 - gerar base de dados\n");
		printf("2 - zerar controle e base de dados\n");
		printf("3 - consulta base de dados\n");
		printf("0 - sair do programa\n\n");
		printf("escolha uma das opções do menu: ");
		scanf("%d", &opcao_menu);
		funcao_menu(opcao_menu);
	}
	return 0;
}

void funcao_menu(int opcao_menu){
	int controle, ini, fim;
	switch(opcao_menu){
		case 0:
			printf("\nFIM!\n");
			break; 
		case 1:
			while(opcao_menu!=0){
				printf("1 - gerar base de dados\n");
				printf("	\n");
				printf("	1 - gerar base de dados por número de registros\n");
				printf("	2 - gerar base de dados por tamanho de arquivo\n");
				printf("	0 - voltar ao menu inicial\n\n");
				printf("	escolha uma das opções do menu: ");
				scanf("%d", &opcao_menu);
				funcao_submenu_database(opcao_menu);
			}
			break;
		case 2:
		        limpaTudo();
				printf("dados resetados com sucesso\n");
				funcao_auxiliar_limpar_tela();
			break;
		case 3:
			controle = consultarControle();
			printf("Os indices a serem pesquisados são de 0 a %d\n", controle);
			printf("Digite o indice inicial para pesquisa\n");
			scanf("%d", &ini);
			printf("Digite o indice final para pesquisa\n");
			scanf("%d", &fim);
			printf("\n");
			
			int numRegistros = fim-ini;
			
			funcao_recupera_registros(ini, fim);
			funcao_auxiliar_limpar_tela();
			
			break;
		default :
			printf("Valor invalido!\n");
			funcao_auxiliar_limpar_tela();
	}
}

void funcao_submenu_database(int opcao_menu){
	int  numBlocos, tamArquivo;
	long long tamBloco;
	float tempoTotal=0;
	switch(opcao_menu){
		case 0:
			funcao_auxiliar_limpar_tela();
			break;
			 
		case 1: //GRAVACAO POR BLOCOS DE REGISTROS
			printf("	informe o tamanho do bloco: ");
			scanf("%lli", &tamBloco);
			printf("	informe o numero de blocos para gravar: ");
			scanf("%i", &numBlocos);
			
			int i;
			for(i=0;i<numBlocos;i++){
				float tempoBloco=0;
				clock_t inicio = clock();
				gerarDatabase(tamBloco, 1);
				clock_t fim = clock();
				tempoBloco = (float)(fim-inicio) / CLOCKS_PER_SEC;
				printf("tempo gasto na gravação do bloco: %f segundos\n\n", tempoBloco);
				tempoTotal += tempoBloco;
			}
			
			printf("banco de dados gerado em %f segundos\n\n", tempoTotal);
			funcao_auxiliar_limpar_tela();
			break;
			
		case 2: //GRAVACAO POR TAMANHO DE ARQUIVO GERADO
			printf("	informe o tamanho do arquivo que deseja gerar (em GigaBytes): \n");
			printf("	  (a gravação usa uma paginação de no máximo 8 gigabytes) ");
			scanf("%i", &tamArquivo);
			
			if(tamArquivo<=8){
				tempoTotal += blocoGravacao(tamArquivo);
			} else{
				while(tamArquivo>8){
					tempoTotal += blocoGravacao(tamArquivo);
					tamArquivo = tamArquivo - 8;
				}
				tempoTotal += blocoGravacao(tamArquivo);
			}
			
			printf("banco de dados gerado em %f segundos\n\n", tempoTotal);
			funcao_auxiliar_limpar_tela();
			break;
			
		default :
			printf("Valor invalido!\n");
			funcao_auxiliar_limpar_tela();
	}
	
}

float blocoGravacao(int tamArquivo){
	float tempoBloco=0;
	clock_t inicio = clock();
	gerarDatabase(tamBloco1GB*tamArquivo, 1);
	clock_t fim = clock();
	tempoBloco = (float)(fim-inicio) / CLOCKS_PER_SEC;
	printf("tempo gasto na gravação do bloco: %f segundos\n", tempoBloco);
	return tempoBloco;
}

void funcao_auxiliar_limpar_tela(){
	printf("\naperte enter para voltar ao menu.");
	getchar(); getchar();
	system("clear");
}
