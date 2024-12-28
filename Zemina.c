#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// Definição da estrutura de dados
typedef struct
{
	char equipa[15];
	char estadio[30];
	int capacidadeDoEstadio;
	int numerodesocios;
	float fundosdoclube;
	float despesasMensaisdeManutençaodoEstadio;
} dadosdasequipas;

typedef struct
{
	char nome[30];
	int numero;
	float vencimento;
	int datadoIniciodoContrato[3];
	int anosdoContrato;
	char posicaojogador[15];
	int força;
} jogadores;

int main()
{
	// cria treinadores para cada equipa
	char treinador[18][15];
	// cria dados para 18 equipas e jogadores para cada
	dadosdasequipas equipasEDados[18];
	jogadores jogadoresPorEquipa[18][20];

	// Abre o ficheiro "Equipas2"
	FILE* equipas = fopen("Equipas3.txt", "r");
	if (equipas == NULL)
	{
		printf("Não foi possível abrir o ficheiro.\n");
		return 1;
	}

	int equipaCount = 0;
	int jogadorinos = 20;
	char line[50];
	int i = 0;

	// Lê as linhas do arquivo e guarda no local correto
	while (equipaCount < 18)
	{
		// Ler treinador e equipa
		fgets(line, sizeof(line), equipas);
		sscanf(line,"%[^\n]",treinador[equipaCount]);
		fgets(line, sizeof(line), equipas);
		sscanf(line,"%[^\n]",equipasEDados[equipaCount].equipa);
		// Ler 20 jogadores
		for (i; i < jogadorinos; i++)
		{
			fgets(line, sizeof(line), equipas);
			sscanf(line, "%[^;];%d;%[^;];%d",jogadoresPorEquipa[equipaCount][i].nome, &jogadoresPorEquipa[equipaCount][i].numero, jogadoresPorEquipa[equipaCount][i].posicaojogador, &jogadoresPorEquipa[equipaCount][i].força);
		}
		equipaCount++;
		jogadorinos += 20;
	}

	fclose(equipas);
}

//Funçoes utilizadas durante um jogo
int calcularPoderAtaque(jogadores equipa[NUM_JOGADORES]) 
{
	int poderAtaque = 0;
	for (int i = 0; i < NUM_JOGADORES; i++) {
		if (strcmp(equipa[i].posicaojogador, "Avancado") == 0 ||
			strcmp(equipa[i].posicaojogador, "Meio-campo") == 0) {
			poderAtaque += equipa[i].forca;
		}
	}
	return poderAtaque;
}

int calcularPoderDefesa(jogadores equipa[NUM_JOGADORES]) 
{
	int poderDefesa = 0;
	for (int i = 0; i < NUM_JOGADORES; i++) {
		if (strcmp(equipa[i].posicaojogador, "Defesa") == 0 ||
			strcmp(equipa[i].posicaojogador, "Guarda-redes") == 0) {
			poderDefesa += equipa[i].forca;
		}
	}
	return poderDefesa;
}

float gerarFatorAleatorio() 
{
	srand(time(NULL));
	return (rand() % 1001) / 1000.0; // Gera um número entre 0.0 e 1.0
}

const char* determinarLocalPerdaBola() 
{
	int random = rand() % 3;
	switch (random) {
	case 0:
		return "Defesa";
	case 1:
		return "Meio-campo";
	case 2:
		return "Ataque";
	default:
		return "Desconhecido";
	}
}

void gerirAtaque(jogadores equipa[NUM_JOGADORES], jogadores adversarios[NUM_JOGADORES], int tempoRestante) 
{
	int poderAtaque = calcularPoderAtaque(equipa);
	int poderDefesaAdversaria = calcularPoderDefesa(adversarios);
	float fatorAleatorio = gerarFatorAleatorio();

	printf("Poder de Ataque: %d\n", poderAtaque);
	printf("Poder de Defesa do Adversário: %d\n", poderDefesaAdversaria);
	printf("Fator Aleatório: %.2f\n", fatorAleatorio);

	int resultado = (poderAtaque * fatorAleatorio) - poderDefesaAdversaria;

	if (resultado > 0) {
		printf("Ataque bem-sucedido! Gol marcado.\n");
	}
	else {
		const char* localPerda = determinarLocalPerdaBola();
		printf("Ataque falhou. Perda de bola na zona: %s.\n", localPerda);
	}

	printf("Tempo restante do jogo: %d minutos.\n", tempoRestante);
}
