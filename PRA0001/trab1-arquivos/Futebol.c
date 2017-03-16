#include "Futebol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i, j, incrementador;

void gerarDatabase(long long tamBloco, int numBlocos){
	long long a=0;
	int b=0;
	int IDatual, IDgravacao;
	
	IDatual = consultarControle();
	IDgravacao = IDatual;	
	
	for(b=0;b<numBlocos;b++){
		
		partida *vetorGeral = malloc(sizeof(partida)*tamBloco);
		
		for(a=0;a<tamBloco;a++){
			gerarPartida(vetorGeral, IDgravacao);
			IDgravacao++;
		}
		gravarDatabase(vetorGeral);
		incrementador=0;
		printf("Bloco gravado com sucesso\n");
	}
	
	atualizarControle(IDgravacao);
	
}

void gerarPartida(partida *vetorGeral, int ID){
	
	vetorGeral[incrementador].ID = ID;
	vetorGeral[incrementador].dia = rand()%30+1;
	vetorGeral[incrementador].mes = rand()%12+1;
	vetorGeral[incrementador].ano = rand()%60+1950;
	gerarNomes(vetorGeral);
	vetorGeral[incrementador].golsA = rand()%5;
	vetorGeral[incrementador].golsB = rand()%5;
	vetorGeral[incrementador].publico = (rand()%30000)+1000;

	incrementador++;
}

void gerarNomes(partida *vetorGeral){
	int timeA=0, timeB=0;
	while(timeA==timeB){
		timeA = rand()%20;
		timeB = rand()%20;
	}
	
	switch (timeA) {
		case 0:
			vetorGeral[incrementador].nomeTimeA = "CAM";
			vetorGeral[incrementador].local = "Mineirao";
			break;
		case 1:
			vetorGeral[incrementador].nomeTimeA = "COR";
			vetorGeral[incrementador].local = "ArenaTimao";
			break;
		case 2:
			vetorGeral[incrementador].nomeTimeA = "SAN";
			vetorGeral[incrementador].local = "FundodoMar";
			break;
		case 3:
			vetorGeral[incrementador].nomeTimeA = "VIT";
			vetorGeral[incrementador].local = "Barradao";
			break;
		case 4:
			vetorGeral[incrementador].nomeTimeA = "SAO";
			vetorGeral[incrementador].local = "FashionWeek";
			break;
		case 5:
			vetorGeral[incrementador].nomeTimeA = "CRU";
			vetorGeral[incrementador].local = "Mineirao";
			break;
		case 6:
			vetorGeral[incrementador].nomeTimeA = "JEC";
			vetorGeral[incrementador].local = "ArenaJlle";
			break;
		case 7:
			vetorGeral[incrementador].nomeTimeA = "GRE";
			vetorGeral[incrementador].local = "Olimpico";
			break;
		case 8:
			vetorGeral[incrementador].nomeTimeA = "INT";
			vetorGeral[incrementador].local = "BeiraRio";
			break;
		case 9:
			vetorGeral[incrementador].nomeTimeA = "SPO";
			vetorGeral[incrementador].local = "IlhadoRetiro";
			break;
		case 10:
			vetorGeral[incrementador].nomeTimeA = "FLA";
			vetorGeral[incrementador].local = "Maracana";
			break;
		case 11:
			vetorGeral[incrementador].nomeTimeA = "FLU";
			vetorGeral[incrementador].local = "Maracana";
			break;
		case 12:
			vetorGeral[incrementador].nomeTimeA = "GOI";
			vetorGeral[incrementador].local = "SerraDourada";
			break;
		case 13:
			vetorGeral[incrementador].nomeTimeA = "FIG";
			vetorGeral[incrementador].local = "Scarpelli";
			break;
		case 14:
			vetorGeral[incrementador].nomeTimeA = "AVA";
			vetorGeral[incrementador].local = "Mangue";
			break;
		case 15:
			vetorGeral[incrementador].nomeTimeA = "BOT";
			vetorGeral[incrementador].local = "Engenhao";
			break;
		case 16:
			vetorGeral[incrementador].nomeTimeA = "CHA";
			vetorGeral[incrementador].local = "ArenaConda";
			break;
		case 17:
			vetorGeral[incrementador].nomeTimeA = "CAP";
			vetorGeral[incrementador].local = "ArenadaBaixada";
			break;
		case 18:
			vetorGeral[incrementador].nomeTimeA = "PON";
			vetorGeral[incrementador].local = "MoisesLucarelli";
			break;
		case 19:
			vetorGeral[incrementador].nomeTimeA = "PAL";
			vetorGeral[incrementador].local = "Chiqueiro";
			break;
		case 20:
			vetorGeral[incrementador].nomeTimeA = "CFC";
			vetorGeral[incrementador].local = "CoutoPereira";
			break;
	}

	switch (timeB){
		case 0:
			vetorGeral[incrementador].nomeTimeB ="CAM";
			break;
		case 1:
			vetorGeral[incrementador].nomeTimeB ="COR";
			break;
		case 2:
			vetorGeral[incrementador].nomeTimeB ="SAN";
			break;
		case 3:
			vetorGeral[incrementador].nomeTimeB ="VIT";
			break;
		case 4:
			vetorGeral[incrementador].nomeTimeB ="SAO";
			break;
		case 5:
			vetorGeral[incrementador].nomeTimeB ="CRU";
			break;
		case 6:
			vetorGeral[incrementador].nomeTimeB ="JEC";
			break;
		case 7:
			vetorGeral[incrementador].nomeTimeB ="GRE";
			break;
		case 8:
			vetorGeral[incrementador].nomeTimeB ="INT";
			break;
		case 9:
			vetorGeral[incrementador].nomeTimeB ="SPO";
			break;
		case 10:
			vetorGeral[incrementador].nomeTimeB = "FLA";
			break;
		case 11:
			vetorGeral[incrementador].nomeTimeB = "FLU";
			break;
		case 12:
			vetorGeral[incrementador].nomeTimeB = "GOI";
			break;
		case 13:
			vetorGeral[incrementador].nomeTimeB = "FIG";
			break;
		case 14:
			vetorGeral[incrementador].nomeTimeB = "AVA";
			break;
		case 15:
			vetorGeral[incrementador].nomeTimeB = "BOT";
			break;
		case 16:
			vetorGeral[incrementador].nomeTimeB = "CHA";
			break;
		case 17:
			vetorGeral[incrementador].nomeTimeB = "CAP";
			break;
		case 18:
			vetorGeral[incrementador].nomeTimeB = "PON";
			break;
		case 19:
			vetorGeral[incrementador].nomeTimeB = "PAL";
			break;
		case 20:
			vetorGeral[incrementador].nomeTimeB = "CFC";
			break;
	}
}

void gravarDatabase(partida *vetorGeral){
	
	int pa=0;
	
	FILE *DATABASE;
	DATABASE = fopen("DATABASE.bin","ab");
	
	for(pa=0; pa<incrementador; pa++){
				
		fwrite(&vetorGeral[pa].ID, sizeof(int), 1, DATABASE);	
		fwrite(&vetorGeral[pa].dia, sizeof(int), 1, DATABASE);
		fwrite(&vetorGeral[pa].mes, sizeof(int), 1, DATABASE);
		fwrite(&vetorGeral[pa].ano, sizeof(int), 1, DATABASE);
		fwrite(&vetorGeral[pa].nomeTimeA, sizeof(char)*3, 1, DATABASE);
		fwrite(&vetorGeral[pa].golsA, sizeof(int), 1, DATABASE);
		fwrite(&vetorGeral[pa].golsB, sizeof(int), 1, DATABASE);
		fwrite(&vetorGeral[pa].nomeTimeB, sizeof(char)*3, 1, DATABASE);
		fwrite(&vetorGeral[pa].publico, sizeof(int), 1, DATABASE);
		fwrite(&vetorGeral[pa].local, sizeof(char)*15, 1, DATABASE);
		
	}
	
	free(vetorGeral);

	fclose(DATABASE);
		
}

int consultarControle(){
    int ID, num;
	FILE *CONTROLE;
	CONTROLE = fopen ("CONTROLE.txt", "rt+");
 	fscanf(CONTROLE, "%d", &ID);
	fclose(CONTROLE);
	num = ID;
  return num;
}

void atualizarControle(int num){
	FILE *CONTROLE;
	CONTROLE = fopen ("CONTROLE.txt", "wt+");
 	fprintf(CONTROLE, "%d", num);
	fclose(CONTROLE);
}

void limpaTudo(){
	FILE *CONTROLE;
	CONTROLE = fopen ("CONTROLE.txt", "wt+");
 	fprintf(CONTROLE, "%d", 0);
	fclose(CONTROLE);
	
	remove("DATABASE.bin");
	FILE *DATABASE;
	DATABASE = fopen("DATABASE.bin","ab");
	fclose(DATABASE);
	
}

void funcao_recupera_registros(int ini, int fim){
	FILE *pt_arquivo;
	pt_arquivo = fopen("DATABASE.bin","rb");
	
	partida *vetorPartida = malloc(sizeof(partida)+1);
	partida *aux = malloc(sizeof(partida)+1);
	
	rewind(pt_arquivo);
	
	int i;
	for(i=0;i<fim;i++){
		if(i<ini){
			fflush(stdin);
			fread(&aux[0].ID, sizeof(int), 1, pt_arquivo);
			fread(&aux[0].dia, sizeof(int), 1, pt_arquivo);
			fread(&aux[0].mes, sizeof(int), 1, pt_arquivo);
			fread(&aux[0].ano, sizeof(int), 1, pt_arquivo);
			fread(&aux[0].nomeTimeA, sizeof(char)*3, 1, pt_arquivo);
			fread(&aux[0].golsA, sizeof(int), 1, pt_arquivo);
			fread(&aux[0].golsB, sizeof(int), 1, pt_arquivo);
			fread(&aux[0].nomeTimeB, sizeof(char)*3, 1, pt_arquivo);
			fread(&aux[0].publico, sizeof(int), 1, pt_arquivo);
			fread(&aux[0].local, sizeof(char)*15, 1, pt_arquivo);
			
		} else{
			fflush(stdin);
			fread(&vetorPartida[0].ID, sizeof(int), 1, pt_arquivo);
			fread(&vetorPartida[0].dia, sizeof(int), 1, pt_arquivo);
			fread(&vetorPartida[0].mes, sizeof(int), 1, pt_arquivo);
			fread(&vetorPartida[0].ano, sizeof(int), 1, pt_arquivo);
			fread(&vetorPartida[0].nomeTimeA, sizeof(char)*3, 1, pt_arquivo);
			fread(&vetorPartida[0].golsA, sizeof(int), 1, pt_arquivo);
			fread(&vetorPartida[0].golsB, sizeof(int), 1, pt_arquivo);
			fread(&vetorPartida[0].nomeTimeB, sizeof(char)*3, 1, pt_arquivo);
			fread(&vetorPartida[0].publico, sizeof(int), 1, pt_arquivo);
			fread(&vetorPartida[0].local, sizeof(char)*15, 1, pt_arquivo);
			
			printf("%i\t%i\t%i\t%i\t%s\t%i\t%i\t%s\t%i\t%s\n", 
					vetorPartida[0].ID,vetorPartida[0].dia, vetorPartida[0].mes, 
					vetorPartida[0].ano, vetorPartida[0].nomeTimeA, vetorPartida[0].golsA,
					vetorPartida[0].golsB, vetorPartida[0].nomeTimeB, vetorPartida[0].publico,
					vetorPartida[0].local);
		}
 	}
 	free(aux);
 	free(vetorPartida);	
	fclose(pt_arquivo);
}

