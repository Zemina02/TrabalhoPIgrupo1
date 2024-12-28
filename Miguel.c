#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

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
	return 0;
}
    // Mostra a Lista das Equipas
    printf("Selecione uma equipa:\n");
    for (int i = 0; i < equipaCount; i++) {
        printf("%d. %s\n", i + 1, equipasEDados[i].equipa);
    }

    // Pede au utilizador para escolher
    int escolha;
    printf("Digite o número da equipa que deseja selecionar: ");
    scanf("%d", &escolha);

    // Validar a Seleção
    if (escolha < 1 || escolha > equipaCount) {
        printf("Seleção inválida.\n");
        return 1;
    }

    // Mostra a Equipa que o Utlilizador escolheu
    int SelecionaIndice = escolha - 1; // Ajustar para indice baseado em zero
    printf("\nDetalhes da equipa selecionada:\n");
    printf("Treinador: %s\n", treinador[SelecionaIndice]);
    printf("Equipa: %s\n", equipasEDados[SelecionaIndice].equipa);
    printf("\nJogadores:\n");
    printf("%-30s %-10s %-15s\n", "Nome", "Número", "Posição"); // cabeçalho
    printf("-------------------------------------------------------\n");

    for (int j = 0; j < 20; j++) {
        printf("%-30s %-10d %-15s\n",
            jogadoresPorEquipa[SelecionaIndice][j].nome,
            jogadoresPorEquipa[SelecionaIndice][j].numero,
            jogadoresPorEquipa[SelecionaIndice][j].posicaojogador);
    }

    return 0;
}
