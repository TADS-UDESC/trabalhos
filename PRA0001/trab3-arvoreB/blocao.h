#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//arquivo.h
#define ARQUIVO "fluxo_partida.bin"
#define N 1024
#define NUMERO_VIAS 10
#define M 4

long NUMPARTIDAS=0;
long QTDREG=0;
long TAMPART = 0;
int contadorVetor=0;
int contadorVetorB=0;
unsigned long int countOrdem = 0;
float tempoBloco=0, tempoTotal=0;
clock_t inicio, fim;

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

struct node{ 
    int n; 
    Partida vetorPartidasNode[M-1];
    struct node *p[M];   
}*root=NULL; 

enum KeyStatus { Duplicate,SearchFailure,Success,InsertIt,LessKeys };

Partida *vetorPartidaNovo;

//declaracoes de funcoes
char get_opcao();
void imprime_menu_principal();
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
void quicksort(Partida *v, int first, int last, int opcao);
void divideOriginal();
void ordenaopcoes();
void insert(Partida partida, int escolhaIndex);
enum KeyStatus ins(struct node *ptr, Partida partida, Partida *partidaAcima, struct node **newnode, int escolhaIndex);
int searchPos(Partida partida, Partida *vetorPartidas, int n, int escolhaIndex);
void display(struct node *ptr, int blanks);
void emOrdem(struct node *noRecebido, FILE *index, int qtd);
void printaVetorNovo(Partida *vetorPartidaNovo);
int searchPosID(Partida partida, Partida *vetorPartidas, int n);
enum KeyStatus del(struct node *ptr, Partida partidaInformada);
void DelNode(Partida partidaInformada);
int arquivo_ler_todos_alterado(int escolhaIndex);


//implementacao da funcoes
char get_opcao(){   
    printf("Escolha uma opcao: ");    
    return getchar();          
}

void imprime_menu_principal(){
    system("clear");   
    printf("\n CAMPEONATOS BRASILEIROS \n");
    printf("1. Gerar os registros do campeonato.\n");        
    printf("2. Ler todos os registros do campeonato.\n");
    printf("3. Ordenar os registros\n");      
    printf("4. Limpar todos os regristros\n");
    printf("5. Apagar um registro\n");
    printf("6. Acessar menu de ArvoreB\n");
    printf("0. Sair\n");
    printf("\n");     
     
}

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
    if(!( fp = fopen(ARQUIVO, "rb"))){	
        return achou;
    }
    unsigned long int count = 0;
    Partida *partidas;
    rewind(fp);
    
    int qtd;
    printf("\n Quantos registros deseja vizualizar por vez?");
    scanf("%d", &qtd);
    
	while(!feof(fp)){
     	partidas  = malloc(N*sizeof(Partida));
    	
        if (fread(partidas, sizeof(Partida), 1, fp)){
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
            if (count % qtd == 0){
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
		
	if(fp = fopen(ARQUIVO, "rb")){				
		buffer = malloc( TAMPART * sizeof( Partida) );	
		for( i=0; i < 10; i++ ){
			leRegistros(TAMPART, buffer, fp);
			quicksort(buffer, 0, TAMPART-1, opcao);
			sprintf(temp_file_name, "temp%d.bin", i);
			if( fq = fopen(temp_file_name, "ab") ) {
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

	if(! ( fp = fopen(ARQUIVO, "wb") ) ) {
        printf("Erro ao abrir arquivo ordenado");      
    }
	page = malloc(NUMERO_VIAS*sizeof(Partida));
	
	for(i=0;i<NUMERO_VIAS;i++) {
		pos[i] = 0;
		page[i].codigo = 0;
    }
	i = 0;
	t = NUMERO_VIAS * TAMPART; 
	do {
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
	for(i=0 ; i< NUMERO_VIAS ; i++) {
		if(pos[i] < TAMPART) {
			if(k == 0) {k++; min = i; continue;}
			if(compara(&page[i], &page[min], opcao) ) {
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
		if(pos[i] < TAMPART){
			sprintf(temp_file_name, "temp%d.bin", i);
			if(fp = fopen(temp_file_name, "rb") ) {
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

 	fp = fopen("fluxo_partida.bin", "wb");
	printf("\nRegistros deletados com sucesso\n");
	}
}

void limpa_tudo() {

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


//-------------------------------------------------------------------------------------------
//---------------------------------FUNÇÕES DE ORDENAÇÃO POR ARVORE-B-------------------------
//-------------------------------------------------------------------------------------------
void insert(Partida partida, int escolhaIndex){ 
    struct node *newnode; 
	Partida partidaAcima;
    enum KeyStatus value;
    value = ins(root, partida, &partidaAcima, &newnode, escolhaIndex); 
    if (value == Duplicate) 
        printf("partida já existe na árvore\n"); 
    if (value == InsertIt){ 
        struct node *uproot = root; 
        root=malloc(sizeof(struct node)); 
        root->n = 1; 
        root->vetorPartidasNode[0] = partidaAcima; 
        root->p[0] = uproot; 
        root->p[1] = newnode; 
    }
}

enum KeyStatus ins(struct node *ptr, Partida partida, Partida *partidaAcima, struct node **newnode, int escolhaIndex){ 
    struct node *newPtr, *lastPtr; 
    int pos, i, n, splitPos; 
    Partida novaPartida, ultimaPartida; 								
    enum KeyStatus value; 
    if (ptr == NULL){ 
        *newnode = NULL; 
		*partidaAcima = partida;										   
        return InsertIt; 
    } 
    n = ptr->n; 
    pos = searchPos(partida, ptr->vetorPartidasNode, n, escolhaIndex);
    if (pos < n && partida.publico == ptr->vetorPartidasNode[pos].publico)
        return Duplicate; 
    value = ins(ptr->p[pos], partida, &novaPartida, &newPtr, escolhaIndex); 			   
    if (value != InsertIt) 
        return value; 
  
    if (n < M - 1){ 
        pos = searchPos(novaPartida, ptr->vetorPartidasNode, n, escolhaIndex); 
  
        for (i=n; i>pos; i--){ 
			ptr->vetorPartidasNode[i] = ptr->vetorPartidasNode[i-1]; 
            ptr->p[i+1] = ptr->p[i]; 
        } 
  
        ptr->vetorPartidasNode[pos] = novaPartida; 
        ptr->p[pos+1] = newPtr; 
        ++ptr->n; 
        return Success; 
    }
  
    if (pos == M - 1){ 
		ultimaPartida = novaPartida;
        lastPtr = newPtr; 
    } else{
		ultimaPartida = ptr->vetorPartidasNode[M-2];				
        lastPtr = ptr->p[M-1]; 
        for (i=M-2; i>pos; i--){ 
            ptr->vetorPartidasNode[i] = ptr->vetorPartidasNode[i-1]; 
            ptr->p[i+1] = ptr->p[i]; 
        } 
        ptr->vetorPartidasNode[pos] = novaPartida; 
        ptr->p[pos+1] = newPtr; 
    } 
    splitPos = (M - 1)/2; 
	(*partidaAcima) = ptr->vetorPartidasNode[splitPos];	

    (*newnode)=malloc(sizeof(struct node));
    ptr->n = splitPos; 
    (*newnode)->n = M-1-splitPos;
    for (i=0; i < (*newnode)->n; i++){ 
        (*newnode)->p[i] = ptr->p[i + splitPos + 1]; 
        if(i < (*newnode)->n - 1) 
            (*newnode)->vetorPartidasNode[i] = ptr->vetorPartidasNode[i + splitPos + 1]; 
        else 
            (*newnode)->vetorPartidasNode[i] = ultimaPartida; 
    } 
    (*newnode)->p[(*newnode)->n] = lastPtr; 
    return InsertIt; 
}

int searchPos(Partida partida, Partida *vetorPartidas, int n, int escolhaIndex){ 
    int pos=0;
    
    switch (escolhaIndex){
		case 1:
			while (pos < n && partida.publico >= vetorPartidas[pos].publico){
				pos++; 
			}
			break;	
		case 2:
			while (pos < n && partida.ano >= vetorPartidas[pos].ano){
				pos++; 
			}
			break;		
		case 3:
			while (pos < n && partida.golsA >= vetorPartidas[pos].golsA){
				pos++; 
			}
			break;
	}
    return pos; 
}

void display(struct node *ptr, int blanks){ 
    if (ptr){ 
        int i; 
        for(i=1;i<=blanks;i++) 
            printf(" "); 
        for (i=0; i < ptr->n; i++) 
            printf("%d ",ptr->vetorPartidasNode[i].publico); 
        printf("\n"); 
        for (i=0; i <= ptr->n; i++) 
            display(ptr->p[i], blanks+10); 
    }
}

void emOrdem(struct node *noRecebido, FILE *index, int qtd){
	int i=0;
	for(i=0;i<M;i++){
		if(noRecebido->p[i]!=NULL){ 							
			emOrdem(noRecebido->p[i], index, qtd); 							
		}
		if(i < noRecebido->n){
			countOrdem ++;
			fprintf(index, "%i\n", noRecebido->vetorPartidasNode[i].codigo);
			printf("%.7lu\t\t", noRecebido->vetorPartidasNode[i].codigo);
			printf("%i\t", noRecebido->vetorPartidasNode[i].dia);
			printf("%i\t", noRecebido->vetorPartidasNode[i].mes);
			printf("%i\t", noRecebido->vetorPartidasNode[i].ano);
			printf("## %s \t", noRecebido->vetorPartidasNode[i].nomeTimeA);
			printf("%i\t", noRecebido->vetorPartidasNode[i].golsA);
			printf("%i ", noRecebido->vetorPartidasNode[i].golsB);
			printf("%s ##\t", noRecebido->vetorPartidasNode[i].nomeTimeB);
			printf("%i\t", noRecebido->vetorPartidasNode[i].publico);
			printf("%s \t", noRecebido->vetorPartidasNode[i].local);
			printf("\n");	
		} else{
			break;
		}
		if (countOrdem % qtd == 0){
            countOrdem = 0;
    		printf("\n Pressione qualquer tecla para continuar ou X para sair");
            if(toupper(getchar()) == 'X') break; 
            system("clear"); 
        }
	}
}

void printaVetorNovo(Partida *vetorPartidaNovo){
	int i;
	for(i=0;i<20;i++){
		printf("%li\t%i\t%i\t%i\n", vetorPartidaNovo[i].codigo, vetorPartidaNovo[i].publico,
								    vetorPartidaNovo[i].ano, vetorPartidaNovo[i].golsA);
	}
}

int searchPosID(Partida partida, Partida *vetorPartidas, int n){ 
    printf("em searchposID, codigo: %u\n", partida.codigo); 

    int pos=0; 
    while (pos < n && partida.codigo >= vetorPartidas[pos].codigo) 
        pos++; 
    return pos; 
}

void DelNode(Partida partidaInformada){ 
    printf("em delnode, codigo: %u\n", partidaInformada.codigo); 
    struct node *uproot; 
    enum KeyStatus value; 
    value = del(root,partidaInformada); 
    switch (value){ 
    case SearchFailure: 
        printf("partidaInformada de codigo: %u não existe\n", partidaInformada.codigo); 
        break; 
    case LessKeys: 
        uproot = root; 
        root = root->p[0]; 
        free(uproot); 
        break; 
    }
}

enum KeyStatus del(struct node *ptr, Partida partidaInformada){ 
    printf("em del, codigo: %u\n", partidaInformada.codigo); 
    int pos, i, pivot, n ,min; 
    Partida *vetorPartidas; 
    enum KeyStatus value; 
    struct node **p,*lptr,*rptr; 

    if (ptr == NULL){
		printf("search failure 1\n");
        return SearchFailure; 
   }
   
    n=ptr->n; 
    vetorPartidas = ptr->vetorPartidasNode; 
    p = ptr->p; 
    min = (M - 1)/2;
    pos = searchPosID(partidaInformada, vetorPartidas, n);
    printf("passou o primeiro searchPos\n"); 

    if (p[0] == NULL){ 
        //if (pos == n || partidaInformada.codigo < vetorPartidas[pos].codigo) {
        //    printf("search failure 2\n");
        //    return SearchFailure; 
        //}  
        for (i=pos+1; i < n; i++){ 
            vetorPartidas[i-1] = vetorPartidas[i]; 
            p[i] = p[i+1]; 
        } 
        return  --ptr->n >= (ptr==root ? 1 : min) ? Success : LessKeys; 
    }

    if (pos < n && partidaInformada.codigo == vetorPartidas[pos].codigo) { 
        struct node *qp = p[pos], *qp1; 
        int nkey; 
        while(1){ 
            nkey = qp->n; 
            qp1 = qp->p[nkey]; 
            if (qp1 == NULL) 
                break; 
            qp = qp1; 
        } 
        vetorPartidas[pos] = qp->vetorPartidasNode[nkey-1]; 
        qp->vetorPartidasNode[nkey - 1] = partidaInformada; 
    } 
    value = del(p[pos], partidaInformada); 
    if (value != LessKeys) 
        return value; 

    if (pos > 0 && p[pos-1]->n > min){ 
        pivot = pos - 1; 
        lptr = p[pivot]; 
        rptr = p[pos]; 
       
        rptr->p[rptr->n + 1] = rptr->p[rptr->n]; 
        for (i=rptr->n; i>0; i--){ 
            rptr->vetorPartidasNode[i] = rptr->vetorPartidasNode[i-1]; 
            rptr->p[i] = rptr->p[i-1]; 
        } 
        rptr->n++; 
        rptr->vetorPartidasNode[0] = vetorPartidas[pivot]; 
        rptr->p[0] = lptr->p[lptr->n]; 
        vetorPartidas[pivot] = lptr->vetorPartidasNode[--lptr->n]; 
        return Success; 
    }
    if (pos<n && p[pos+1]->n > min){ 
        pivot = pos; 
        lptr = p[pivot]; 
        rptr = p[pivot+1]; 
        
        lptr->vetorPartidasNode[lptr->n] = vetorPartidas[pivot]; 
        lptr->p[lptr->n + 1] = rptr->p[0]; 
        vetorPartidas[pivot] = rptr->vetorPartidasNode[0]; 
        lptr->n++; 
        rptr->n--; 
        for (i=0; i < rptr->n; i++){ 
            rptr->vetorPartidasNode[i] = rptr->vetorPartidasNode[i+1]; 
            rptr->p[i] = rptr->p[i+1]; 
        }
        rptr->p[rptr->n] = rptr->p[rptr->n + 1]; 
        return Success; 
    } 

    if(pos == n) 
        pivot = pos-1; 
    else 
        pivot = pos; 

    lptr = p[pivot]; 
    rptr = p[pivot+1]; 
    lptr->vetorPartidasNode[lptr->n] = vetorPartidas[pivot]; 
    lptr->p[lptr->n + 1] = rptr->p[0]; 
    for (i=0; i < rptr->n; i++){ 
        lptr->vetorPartidasNode[lptr->n + 1 + i] = rptr->vetorPartidasNode[i]; 
        lptr->p[lptr->n + 2 + i] = rptr->p[i+1]; 
    } 
    lptr->n = lptr->n + rptr->n +1; 
    free(rptr); 
    for (i=pos+1; i < n; i++){ 
        vetorPartidas[i-1] = vetorPartidas[i]; 
        p[i] = p[i+1]; 
    } 
    return  --ptr->n >= (ptr == root ? 1 : min) ? Success : LessKeys; 
}

int arquivo_ler_todos_alterado(int escolhaIndex){
	countOrdem = 0;
    int achou = 0, i;
	FILE *fp;
   	time_t inicioFread=0, fimFread=0, inicioInsert=0, fimInsert=0;
   	float totalFread=0, totalInsert=0;

	
    if(  ! ( fp = fopen(ARQUIVO, "rb") ) ){	
        return achou;
    }
    unsigned long int count = 0;
    Partida *partidasLidas;
    partidasLidas = malloc(NUMPARTIDAS*sizeof(Partida));
    rewind(fp);
    
    inicioFread = clock();
	while(!feof(fp)){
    	fread(partidasLidas, sizeof(Partida), NUMPARTIDAS, fp);
    }
    fimFread = clock();
    totalFread = (float)(fimFread-inicioFread)/CLOCKS_PER_SEC;
    
    inicioInsert = clock();
    for(i=0;i<NUMPARTIDAS;i++){
		insert(*partidasLidas, escolhaIndex);
		partidasLidas++;
    }
    fimInsert = clock();
	totalInsert = (float)(fimInsert-inicioInsert)/CLOCKS_PER_SEC;
				
    
    printf("fread levou: %f\n", totalFread);
    printf("insert levou: %f\n", totalInsert);
    fclose(fp);
    
    return achou;
}
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
