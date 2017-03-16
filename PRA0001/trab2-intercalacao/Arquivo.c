#include "Arquivo.h"
#include <time.h>
long QTDREG=0;
long TAMPART = 0;
float tempoBloco, tempoTotal=0;
clock_t inicio, fim;

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
	*ano = rand()%70+1950;
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
	*publico = rand()%30000+1000;
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
    int achou = 0;
	FILE *fp;
    if(  ! ( fp = fopen(ARQUIVO, "rb") ) ) 
	{	
        return achou;
    }
    unsigned long int count = 0;
    Partida *partidas;
    rewind(fp);
    
    int qtd;
    printf("\n Quantos registros deseja vizualizar por vez?");
    scanf("%d", &qtd);
    
	while(!feof(fp))
    {
     	partidas  = malloc(N*sizeof(Partida));
    	
        if (fread(partidas, sizeof(Partida), 1, fp))
        {
            printf("%.7lu\t\t", partidas->codigo);
            printf("%i\t", partidas->dia);
            printf("%i\t", partidas->mes);
            printf("%i\t", partidas->ano);
            printf("## %s \t", partidas->nomeTimeA);
            printf("%i\t", partidas->golsA);
            printf("%i ", partidas->golsB);
            printf("%s ##\t", partidas->nomeTimeB);
			printf("%i\t", partidas->publico);
			printf("%s \t", partidas->local);
            printf("\n");
            achou = 1;
            count++;
            if (count % qtd == 0)
            {
                count = 0;
    			printf("\n Pressione qualquer tecla para continuar ou X para sair");
                if(toupper(getchar()) == 'X') break; 
                system("clear"); 
            }
        }
        free(partidas);
    }
    fclose(fp);
    return achou;
}
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------
//---------------------------------FUNÇÕES DE MANIPULAÇÃO DA DATABASE------------------------
//-------------------------------------------------------------------------------------------
void apaga_registro(){
	
	FILE *fp;
    fp = fopen(ARQUIVO, "rb");
	
    Partida *partidas, *partidaVazia;
    rewind(fp);
    
    
        
    int cod;
	printf("qual o codigo do registro que deseja apagar? ");
	scanf("%i", &cod);
    
	partidas  = malloc(N*sizeof(Partida));
	
    fseek(fp, sizeof(Partida)*cod, SEEK_SET);
    
    printf("deseja apagar a seguinte partida?\n");
	fread(partidas, sizeof(Partida), 1, fp);
    printf("%.7lu\t\t", partidas->codigo);
    printf("%i\t", partidas->dia);
    printf("%i\t", partidas->mes);
    printf("%i\t", partidas->ano);
    printf("## %s \t", partidas->nomeTimeA);
    printf("%i\t", partidas->golsA);
    printf("%i ", partidas->golsB);
    printf("%s ##\t", partidas->nomeTimeB);
	printf("%i\t", partidas->publico);
	printf("%s \t", partidas->local);
    printf("\n");
    
    fclose(fp);
    
    int decisao;
    printf("0. Sim\n");
    printf("1. Nao\n");
    scanf("%i", &decisao);
    
    if(decisao==0){
		char indicador[4] = {"XXX"};
		partidaVazia = malloc(N*sizeof(Partida));
		partidaVazia->codigo = 0;	
		partidaVazia->dia = 0;	
		partidaVazia->mes = 0;	
		partidaVazia->ano = 0;	
		sprintf(partidaVazia->nomeTimeA, "%s", indicador);	
		partidaVazia->golsA = 0;
		partidaVazia->golsB = 0; 
		sprintf(partidaVazia->nomeTimeB, "%s", indicador);	
		partidaVazia->publico = 0;
		sprintf(partidaVazia->local, "%s", indicador);
    
		fp = fopen(ARQUIVO, "r+b");
		fseek(fp, sizeof(Partida)*cod, SEEK_SET);
		fwrite(partidaVazia, sizeof(Partida), 1, fp);
		fclose(fp);
	}
    
    system("clear");
    
    free(partidas);
    free(partidaVazia);
}
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------
//---------------------------------FUNÇÕES DE ORDENAÇÃO DA DATABASE--------------------------
//-------------------------------------------------------------------------------------------
void split_file(int opcao){
	float tempoBloco=0;
	long tamanho =0;
	
	clock_t inicio = clock();
	
	FILE *fp, *fq;
	printf("%d\n", QTDREG);
	TAMPART = QTDREG / 10;
	printf("%d\n", TAMPART);
	int i; 
	char temp_file_name[20];
	Partida *buffer;
		
	if(fp = fopen(ARQUIVO, "rb"))
	{	
				
		buffer = malloc( TAMPART * sizeof( Partida) );	
		for( i=0; i < 10; i++ )
		{
			leRegistros(TAMPART, buffer, fp);
			quicksort(buffer, 0, TAMPART-1, opcao);
			sprintf(temp_file_name, "temp%d.bin", i);
			if( fq = fopen(temp_file_name, "ab") ) 
			{
				fwrite(buffer, sizeof(Partida), TAMPART, fq);
				fclose(fq);
			}
		}
	}
	
	
	fclose(fp);
	clock_t fim = clock();
	tempoBloco = (float)(fim-inicio) / CLOCKS_PER_SEC;
	printf("tempo gasto no split_file: %f segundos\n\n", tempoBloco);
}

void quicksort(Partida *vec, int first, int last, int opcao){
    int pivot, j, i;
    Partida temp;
    if(first<last){
        pivot=first;
        i=first;
        j=last;	
		switch (opcao){
			case 1:
				while(i<j){
             		while(vec[i].publico<=vec[pivot].publico&&i<last)
                		i++;
             		while(vec[j].publico>vec[pivot].publico)
                		j--;
             		if(i<j){
                		temp=vec[i];
                		vec[i]=vec[j];
                		vec[j]=temp;
             		}
         		}	
			break;
			case 2:
				while(i<j){
             		while(vec[i].ano<=vec[pivot].ano&&i<last)
                		i++;
             		while(vec[j].ano>vec[pivot].ano)
                		j--;
             		if(i<j){
                		temp=vec[i];
                		vec[i]=vec[j];
                		vec[j]=temp;
             		}
         		}	
			break;
			case 3:
				while(i<j){
             		while(vec[i].golsA<=vec[pivot].golsA&&i<last)
                		i++;
             		while(vec[j].golsA>vec[pivot].golsA)
                		j--;
             		if(i<j){
                		temp=vec[i];
                		vec[i]=vec[j];
                		vec[j]=temp;
             		}
         		}	
			break;
			case 4:
				while(i<j){
             		while(vec[i].golsB<=vec[pivot].golsB&&i<last)
                		i++;
             		while(vec[j].golsB>vec[pivot].golsB)
                		j--;
             		if(i<j){
                		temp=vec[i];
                		vec[i]=vec[j];
                		vec[j]=temp;
             		}
         		}	
			break;
		}
        temp=vec[pivot];
        vec[pivot]=vec[j];
        vec[j]=temp;
        quicksort(vec,first,j-1, opcao);
        quicksort(vec,j+1,last, opcao);
    }
}

int leRegistro(Partida *tp, FILE *fp) {
    int x = fread(tp, sizeof(Partida), 1, fp);
    if(x == 1)
        return 1;
    else
        return 0;
}

int leRegistros(int n, Partida *partidas, FILE *fp) {
    int x = fread(partidas, sizeof(Partida), n, fp); 
    if(x == n)
        return 1;
    else
        return 0;
}

void intercala(int opcao){
	float tempoBloco=0;
	clock_t inicio = clock();
	Partida *page;
	
	int pos[NUMERO_VIAS], i;
	long t;
	FILE *fp;
	
	FILE *pt_INDEX;
	switch (opcao){
		case 1:
			pt_INDEX = fopen("indexPublico.txt", "at");
		break;	
		case 2:
			pt_INDEX = fopen("indexAno.txt", "at");
		break;
		
		case 3:
			pt_INDEX = fopen("indexGolsA.txt", "at");
		break;
		
		case 4:
			pt_INDEX = fopen("indexGolsB.txt", "at");
		break;
	}

	if(! ( fp = fopen(ARQUIVO, "wb") ) ) 
	{
        printf("Erro ao abrir arquivo ordenado");      
    }
	page = malloc(NUMERO_VIAS*sizeof(Partida));
	
	for(i=0;i<NUMERO_VIAS;i++) {
		pos[i] = 0;
		page[i].codigo = 0;
    }
	i = 0;
	t = NUMERO_VIAS * TAMPART; 
	do 
	{
		le_inicial(page,pos);
		encontra_menor_na_passada(page, pos, fp, opcao, pt_INDEX);
	} while(++i < t);
	
	fclose(fp);
	fclose(pt_INDEX);
	apaga_arquivos();
	
	clock_t fim = clock();
	tempoBloco = (float)(fim-inicio) / CLOCKS_PER_SEC;
	printf("tempo gasto no intercala: %f segundos\n\n", tempoBloco);
}

void encontra_menor_na_passada(Partida *page, int *pos,	FILE *fp, int opcao, FILE *pt_INDEX){
	int min, i, k;
	k = 0;
	for(i=0 ; i< NUMERO_VIAS ; i++) 
	{
		if(pos[i] < TAMPART) {
			if(k == 0) {k++; min = i; continue;}
			if(compara(&page[i], &page[min], opcao) ) 
			{
				min = i;
			}
		}
	}
	
	int cod = page[min].codigo;
	fprintf(pt_INDEX, "%i\n", cod);
	
    fwrite(&page[min], sizeof(Partida), 1, fp);
	pos[min]++;	
}

int compara( Partida *a, Partida *b, int opcao)  {
	switch (opcao){
		case 1:
			return ( a->publico < b->publico );
		break;
		case 2:
			return ( a->ano < b->ano );
		break;
		case 3:
			return ( a->golsA < b->golsA );
		break;
		case 4:
			return ( a->golsB < b->golsB );
		break;
	}
	return 1;    
}

void le_inicial( Partida *page, int *pos){
	int i;	
	FILE *fp;
	char temp_file_name[20];
	
	for( i=0; i<NUMERO_VIAS; i++) {	
		if(pos[i] < TAMPART)
		{
			sprintf(temp_file_name, "temp%d.bin", i);
			if(fp = fopen(temp_file_name, "rb") ) 
			{
				fseek(fp, pos[i]*sizeof(Partida), SEEK_SET);
				leRegistro(&page[i], fp);
				fclose(fp);	
			}
		}
	}
}

void apaga_arquivos(){
	int i;
	FILE *fp;
	char temp_file_name[20];
	
	for(i=0; i<NUMERO_VIAS; i++) {
		sprintf(temp_file_name, "temp%d.bin", i);
		if(fp = fopen(temp_file_name, "rb")) {
			fclose(fp);
			remove(temp_file_name);	
		}		
	}
}

void limpaTudo(){
	QTDREG = 0;
	TAMPART = 0;
	remove("fluxo_partida.bin");
	remove("indexPublico.txt");
	remove("indexAno.txt");
	remove("indexGolsA.txt");
	remove("indexGolsB.txt");
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

