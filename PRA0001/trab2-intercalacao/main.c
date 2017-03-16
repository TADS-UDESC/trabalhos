#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Arquivo.h"
#include "Tela.h"

void gera_registros(Partida *partidas);
void le_todos_registros();
void ordenaopcoes();

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
            case '4' : limpaTudo(); break;
            case '5' : apaga_registro(); break;
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






