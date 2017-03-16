typedef struct{
	int ID;
	char *nomeTimeA;
	char *nomeTimeB;
	int golsA;
	int golsB;
	int dia;
	int mes;
	int ano;
	int publico;
	char *local;
}partida;

void gerarDatabase(long long tamBloco, int numBlocos);

void gerarPartida(partida *vetorGeral, int ID);

void gerarNomes(partida *vetorGeral);

void gravarDatabase(partida *vetorGeral);

int consultarControle();

void atualizarControle(int num);

void limpaTudo();

void funcao_recupera_registros(int ini, int fim);
