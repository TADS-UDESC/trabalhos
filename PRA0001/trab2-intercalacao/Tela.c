#include "Tela.h"

char get_opcao()
{   
    printf("Escolha uma opcao: ");    
    return getchar();          
}

void imprime_menu_principal()
{
    system("clear");   
    printf("\n CAMPEONATOS BRASILEIROS \n");
    printf("1. Gerar registros.\n");        
    printf("2. Le todos os registros.\n");
    printf("3. ordena\n");      
    printf("4. limpa tudo\n");
    printf("5. apaga registro\n");
    printf("0. Sair\n");
    printf("\n");     
     
}

