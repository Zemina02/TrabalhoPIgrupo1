#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// Defini��o da estrutura de dados
typedef struct
{
	char equipa[15];
	char estadio[30];
	int capacidadeDoEstadio;
	int numerodesocios;
	float fundosdoclube;
	float despesasMensaisdeManuten�aodoEstadio;
} dadosdasequipas;

typedef struct
{
	char nome[30];
	int numero;
	float vencimento;
	int datadoIniciodoContrato[3];
	int anosdoContrato;
	char posicaojogador[15];
	int for�a;
} jogadores;

int main()
{
	// cria treinadores para cada equipa
	char treinador[18][15];
	// cria dados para 18 equipas e jogadores para cada
	dadosdasequipas equipasEDados[18];
	jogadores jogadores[360];

	// Abre o ficheiro "Equipas2"
	FILE* equipas = fopen("Equipas.txt", "r");
	if (equipas == NULL)
	{
		printf("N�o foi poss�vel abrir o ficheiro.\n");
		return 1;
	}
	// L� as linhas do arquivo e guarda no local correto
	int equipaCount = 0;
	int jogadorinos = 20;
	char line[50];
	int i = 0;

		// Ler treinador e equipa
		if (equipaCount < 18) 
		{
			fgets(line, sizeof(line), equipas);
			sscanf(line, "%[^\n]", treinador[equipaCount]);
			fgets(line, sizeof(line), equipas);
			sscanf(line, "%[^\n]", equipasEDados[equipaCount].equipa);
			// Ler 20 jogadores
			for (i; i < jogadorinos; i++)
			{
				fgets(line, sizeof(line), equipas);
				sscanf(line, "%[^;];%d;%[^;];%d",
					jogadores[i].nome,
					&jogadores[i].numero,
					jogadores[i].posicaojogador,
					&jogadores[i].for�a);
			}
			equipaCount++;
			jogadorinos += 20;
			i += 20;
		}

	fclose(equipas);
	
	printf("%s", treinador[0]);
	return 0;
}
