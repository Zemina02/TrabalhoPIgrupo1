#define _CRT_SECURE_NO_WARNINGS
#define NUM_EQUIPAS 18
#define NUM_JOGADORES 20
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int numerodejogos;
	int numerodevitorias;
	int numerodeempates;
	int numerodederrotas;
	int numerodegolos;
	int numerodesofridos;
} tabbeladeresultados;

typedef struct {
	char equipa[15];
	char estadio[30];
	int capacidadeDoEstadio;
	int numerodesocios;
	float fundosdoclube;
	float despesasdoestadio;
} dadosdasequipas;

typedef struct {
	char nome[30];
	int numero;
	float vencimento;
	int datadoIniciodoContrato[3];
	int anosdoContrato;
	char posicaojogador[15];
	char posicaoIdeal[15];
	int forca;
} jogadores;

// Função para limpar a tela 
void limparTela() {
#ifdef _WIN32 
	system("cls");
#else system("clear"); 
#endif 
}

//Função para escolher e mostrar a equipa
int mostrarEquipas(char treinador[NUM_EQUIPAS][15], dadosdasequipas equipas[NUM_EQUIPAS], jogadores jogadores[NUM_EQUIPAS][NUM_JOGADORES], int eCount)
{
	// Mostra a Lista das Equipas
	printf("Selecione uma equipa:\n");
	for (int i = 0; i < eCount; i++) {
		printf("%d. %s\n", i + 1, equipas[i].equipa);
	}

	// Pede ao utilizador para escolher e Valida a seleção
	int escolha = 0;
	while (escolha < 1 || escolha > eCount) {
		printf("Digite o numero da equipa que deseja selecionar: ");
		scanf("%d", &escolha);

		if (escolha < 1 || escolha > eCount) {
			printf("Selecao invalida, escolha outra vez.\n");
		}
	}

	// Mostra a equipa que o utilizador escolheu
	int SelecionaIndice = escolha - 1; // Ajustar para indice baseado em zero
	printf("\nDetalhes da equipa selecionada:\n");
	printf("Você escolheu a equipa: %s\n", equipas[SelecionaIndice].equipa);
	printf("Qual o nome do treinador(o teu)?\n");
	scanf("%s", treinador[SelecionaIndice]);
	printf("Treinador: %s\n", treinador[SelecionaIndice]);
	printf("\nJogadores:\n");
	printf("%-30s %-10s %-15s\n", "Nome", "Numero", "Posicaoo"); // cabeçalho
	printf("-------------------------------------------------------\n");

	for (int i = 0; i < NUM_JOGADORES; i++) {
		printf("%-30s %-10d %-15s\n", jogadores[SelecionaIndice][i].nome, jogadores[SelecionaIndice][i].numero, jogadores[SelecionaIndice][i].posicaojogador);
	}

	return SelecionaIndice; // Retorna o índice da equipa selecionada
}

// Função para atualizar os fundos
void atualizarFundos(int equipaIndex, dadosdasequipas equipasEDados[NUM_EQUIPAS], jogadores jogadoresPorEquipa[NUM_EQUIPAS][NUM_JOGADORES]) {
	float totalVencimentos = 0.0;

	// Calcular o total de vencimentos dos jogadores
	for (int i = 0; i < NUM_JOGADORES; i++) {
		totalVencimentos += jogadoresPorEquipa[equipaIndex][i].vencimento;
	}

	// Adicionar as despesas mensais
	float despesasTotais = totalVencimentos + equipasEDados[equipaIndex].despesasdoestadio;

	// Subtrair do fundo do clube
	if (equipasEDados[equipaIndex].fundosdoclube >= despesasTotais) {
		equipasEDados[equipaIndex].fundosdoclube -= despesasTotais;
		printf("Os fundos da equipa %s foram atualizados. Fundos restantes: %.2f\n", equipasEDados[equipaIndex].equipa, equipasEDados[equipaIndex].fundosdoclube);
	}
	else {
		printf("A equipa %s não tem fundos suficientes para cobrir as despesas. Fundos atuais: %.2f\n", equipasEDados[equipaIndex].equipa, equipasEDados[equipaIndex].fundosdoclube);

		// condição de fim de jogo
		if (equipasEDados[equipaIndex].fundosdoclube <= 0) {
			printf("Game Over! A equipa %s ficou sem fundos.\n", equipasEDados[equipaIndex].equipa);
			exit(0); // Sai do programa
		}
	}
}

void atualizarFundosPorResultado(int equipaIndex, dadosdasequipas equipasEDados[NUM_EQUIPAS], int resultado) {
	float ganho;

	// Exibe os fundos atuais antes da atualização
	printf("Fundos atuais da equipa %s: %.2f\n", equipasEDados[equipaIndex].equipa, equipasEDados[equipaIndex].fundosdoclube);

	// Definir os ganhos com base no resultado
	if (resultado == 1) { // Vitória
		ganho = 500000; // Ganho por vitória
		printf("A equipa %s ganhou! Recebeu %.2f.\n", equipasEDados[equipaIndex].equipa, ganho);
	}
	else if (resultado == 0) { // Empate
		ganho = 250000; // Ganho por empate
		printf("A equipa %s empatou! Recebeu %.2f.\n", equipasEDados[equipaIndex].equipa, ganho);
	}
	else { // Derrota
		ganho = 100000; // Ganho por derrota
		printf("A equipa %s perdeu! Recebeu %.2f.\n", equipasEDados[equipaIndex].equipa, ganho);
	}

	// Atualiza os fundos da equipa
	equipasEDados[equipaIndex].fundosdoclube += ganho;

	// Exibe os fundos após a atualização
	printf("Fundos atualizados da equipa %s: %.2f\n", equipasEDados[equipaIndex].equipa, equipasEDados[equipaIndex].fundosdoclube);
}

//Função para comprar jogadores
void comprarJogadores(dadosdasequipas equipasEDados[NUM_EQUIPAS], jogadores jogadoresPorEquipa[NUM_EQUIPAS][NUM_JOGADORES], int equipaSelecionada) {
	int jogadoresComprados = 0;
	bool jogadoresCompradosDeEquipa[NUM_EQUIPAS] = { false }; // Array para rastrear se um jogador foi comprado de cada equipe

	while (jogadoresComprados < 3) {
		printf("\nEscolha uma equipa para comprar um jogador (ou digite 0 para sair):\n");
		for (int i = 0; i < NUM_EQUIPAS; i++) {
			if (i != equipaSelecionada && !jogadoresCompradosDeEquipa[i]) { // Exclui a própria equipe e equipes de onde já comprou
				printf("%d. %s\n", i + 1, equipasEDados[i].equipa);
			}
		}

		int escolhaEquipa;
		printf("Digite o número da equipa que deseja comprar um jogador (0 para sair): ");

		// Verifica se a entrada é um número válido
		while (scanf("%d", &escolhaEquipa) != 1) {
			printf("Caracter inválido. Por favor, insira um número: ");
			while (getchar() != '\n'); // Limpa o buffer de entrada
		}

		if (escolhaEquipa == 0) {
			break; // Sai do loop se o usuário escolher 0
		}

		// Valida a escolha da equipe
		if (escolhaEquipa < 1 || escolhaEquipa > NUM_EQUIPAS || escolhaEquipa - 1 == equipaSelecionada || jogadoresCompradosDeEquipa[escolhaEquipa - 1]) {
			printf("Seleção inválida. Tente novamente.\n");
			continue; // Volta ao início do loop
		}

		int equipaIndex = escolhaEquipa - 1; // Ajusta para índice baseado em zero
		printf("\nJogadores disponíveis na equipa %s:\n", equipasEDados[equipaIndex].equipa);
		printf("%-30s %-10s %-15s %-10s\n", "Nome", "Número", "Posição Ideal", "Força"); // cabeçalho
		printf("----------------------------------------------------------------\n");

		bool jogadorDisponivel = false;
		for (int j = 0; j < NUM_JOGADORES; j++) {
			if (strcmp(jogadoresPorEquipa[equipaIndex][j].posicaojogador, "") != 0) { // Exibe apenas jogadores que estão na equipe
				printf("%-30s %-10d %-15s %-10d\n", jogadoresPorEquipa[equipaIndex][j].nome, jogadoresPorEquipa[equipaIndex][j].numero, jogadoresPorEquipa[equipaIndex][j].posicaojogador, jogadoresPorEquipa[equipaIndex][j].forca);
				jogadorDisponivel = true;
			}
		}

		if (!jogadorDisponivel) {
			printf("Não há jogadores disponíveis na equipa %s.\n", equipasEDados[equipaIndex].equipa);
			continue; // Volta ao início do loop
		}

		while (true) { // Loop para tentar encontrar o jogador
			printf("\nEscolha um jogador para comprar (digite o nome completo): ");
			char nomeJogador[30];
			scanf(" %[^\n]", nomeJogador); // Lê o nome completo do jogador

			bool jogadorEncontrado = false;
			for (int j = 0; j < NUM_JOGADORES; j++) {
				if (strcmp(jogadoresPorEquipa[equipaIndex][j].nome, nomeJogador) == 0) { // Verifica se o nome completo corresponde
					jogadorEncontrado = true;
					printf("\nJogador encontrado: %s, Número: %d, Salário: %.2f, Força: %d\n",
						jogadoresPorEquipa[equipaIndex][j].nome,
						jogadoresPorEquipa[equipaIndex][j].numero,
						jogadoresPorEquipa[equipaIndex][j].vencimento,
						jogadoresPorEquipa[equipaIndex][j].forca);

					// Calcula o valor da transferência
					int mesesRestantes = jogadoresPorEquipa[equipaIndex][j].anosdoContrato * 12; // Supondo que anosdoContrato é o número de anos restantes
					float valorTransferencia = jogadoresPorEquipa[equipaIndex][j].vencimento * 5 * mesesRestantes;

					// Verifica se a equipa compradora tem fundos suficientes
					if (equipasEDados[equipaSelecionada].fundosdoclube >= valorTransferencia) {
						// Realiza a compra
						equipasEDados[equipaSelecionada].fundosdoclube -= valorTransferencia; // Deduz o valor da transferência
						jogadoresPorEquipa[equipaSelecionada][jogadoresComprados] = jogadoresPorEquipa[equipaIndex][j]; // Adiciona o jogador à equipa compradora
						jogadoresPorEquipa[equipaIndex][j].posicaojogador[0] = '\0'; // Remove o jogador da equipa original
						jogadoresPorEquipa[equipaSelecionada][jogadoresComprados].vencimento *= 1.5; // Aumenta o salário do jogador
						jogadoresCompradosDeEquipa[equipaIndex] = true; // Marca que um jogador foi comprado dessa equipe
						jogadoresComprados++;

						printf("Jogador %s comprado com sucesso! Novo salário: %.2f\n", jogadoresPorEquipa[equipaSelecionada][jogadoresComprados - 1].nome, jogadoresPorEquipa[equipaSelecionada][jogadoresComprados - 1].vencimento);
					}
					else {
						printf("Fundos insuficientes para comprar o jogador %s.\n", jogadoresPorEquipa[equipaIndex][j].nome);
					}
					break; // Sai do loop após encontrar e processar o jogador
				}
			}

			if (!jogadorEncontrado) {
				printf("Nenhum jogador encontrado com o nome completo %s. Tente novamente.\n", nomeJogador);
				// Retorna ao início do loop para escolher a equipe novamente
				break; // Sai do loop de busca de jogador
			}
		}

		// Pergunta se o utilizador deseja continuar a procurar
		if (jogadoresComprados < 3) {
			char continuar;
			printf("Deseja continuar a procurar jogadores? (s/n): ");
			scanf(" %c", &continuar);
			if (continuar != 's' && continuar != 'S') {
				break; // Sai do loop se o utilizador não quiser continuar
			}
		}
	}
}

// Função para gerar um calendário de jogos
int** criarCalendario(dadosdasequipas equipasEDados[NUM_EQUIPAS])
{
	int equipasnumeros[18] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17 };
	int** jogos = malloc(9 * sizeof(int*));
	for (int i = 0; i < 9; i++) {
		jogos[i] = malloc(2 * sizeof(int));
	}
	if (jogos == NULL) {
		printf("Erro ao alocar memória para jogos.\n");
		exit(1);
	}
	int equipa1 = rand() % NUM_EQUIPAS;
	int equipa2 = rand() % NUM_EQUIPAS;

	printf("\nCalendario de Jogos:\n");
	for (int i = 0; i < 9; i++) {
		while (equipasnumeros[equipa1] == 20 || equipasnumeros[equipa1] == equipasnumeros[equipa2])
		{
			equipa1 = rand() % NUM_EQUIPAS;
		}
		while (equipasnumeros[equipa2] == 20 || equipasnumeros[equipa1] == equipasnumeros[equipa2])
		{
			equipa2 = rand() % NUM_EQUIPAS;
		}

		jogos[i][0] = equipa1;
		jogos[i][1] = equipa2;
		equipasnumeros[equipa1] = 20;
		equipasnumeros[equipa2] = 20;
	}
	for (int j = 0; j < 9; j++)
	{
		printf(" jogo numero %i : %s vs %s\n", j + 1, equipasEDados[jogos[j][0]].equipa, equipasEDados[jogos[j][1]].equipa);
	}


	return jogos;
}


int gerarFatorAleatorio()
{
	return rand() % 6; // Gera um número entre 0 e 5
}

int gerarFatorContraatake(char posicao[10])
{
	int num = 0;
	if (strcmp(posicao, "Defesa") == 0) { num = 0; }
	else if (strcmp(posicao, "Meio-campo") == 0) { num = 1; }
	else if (strcmp(posicao, "Ataque") == 0) { num = 2; }

	switch (num) {
	case 0:
		return rand() % 16; // Gera um número entre 0 e 15
	case 1:
		return rand() % 11; // Gera um número entre 0 e 10 
	case 2:
		return rand() % 6; // Gera um número entre 0 e 5
	}
}

char* determinarLocalPerdaBola()
{
	int random = rand() % 3;
	switch (random) {
	case 0:
		return "Defesa";
	case 1:
		return "Meio-campo";
	case 2:
		return "Ataque";
	}
}

int gerirAtaque(jogadores equipa[NUM_JOGADORES], jogadores adversarios[NUM_JOGADORES], int tempoRestante, bool Suprise, char* position) {
	int poderAtaque = calcularPoderAtaque(equipa);
	int poderDefesaAdversaria = calcularPoderDefesa(adversarios);
	int fatorAleatorio = gerarFatorAleatorio();
	if (Suprise == true)
	{
		fatorAleatorio = gerarFatorContraatake(position);
	}

	printf("Poder de Ataque: %d\n", poderAtaque);
	printf("Poder de Defesa do Adversario: %d\n", poderDefesaAdversaria);
	printf("Fator Aleatorio: %d\n", fatorAleatorio);

	int resultado = (poderAtaque + fatorAleatorio) - poderDefesaAdversaria;

	if (resultado > 0) {
		return 1; // Ataque bem-sucedido
	}
	else {
		return 0; // Ataque falhou
	}
}

// Função para resetar as posições dos jogadores de uma equipa específica
void resetarPosicoes(jogadores jogadoresPorEquipa[NUM_EQUIPAS][NUM_JOGADORES], int equipaSelecionada) {
	for (int j = 0; j < NUM_JOGADORES; j++) {
		// Armazena a posição atual em posicaoIdeal antes de resetar
		strcpy(jogadoresPorEquipa[equipaSelecionada][j].posicaoIdeal, jogadoresPorEquipa[equipaSelecionada][j].posicaojogador);
		strcpy(jogadoresPorEquipa[equipaSelecionada][j].posicaojogador, ""); // Reseta a posição para uma string vazia
	}
}

void posicionarJogadores(jogadores jogadoresPorEquipa[NUM_EQUIPAS][NUM_JOGADORES], int equipaSelecionada, const char* posicao, int quantidade) {
	for (int i = 0; i < quantidade; i++) {
		printf("Escolha o jogador para %s %d:\n", posicao, i + 1);

		// Mostra os jogadores disponíveis para a posição
		printf("\nJogadores disponíveis:\n");
		printf("%-30s %-15s\n", "Nome", "Posição Ideal");
		printf("-----------------------------------------------\n");
		for (int j = 0; j < NUM_JOGADORES; j++) {
			// Exibe apenas jogadores que não estão posicionados
			if (strcmp(jogadoresPorEquipa[equipaSelecionada][j].posicaojogador, "") == 0) {
				printf("%-30s %-15s\n", jogadoresPorEquipa[equipaSelecionada][j].nome, jogadoresPorEquipa[equipaSelecionada][j].posicaoIdeal);
			}
		}

		// Mensagem para o utilizador
		printf("\nNome: ");
		char nomeJogador[30];
		scanf(" %[^\n]", nomeJogador); // Lê o nome do jogador

		// Extrai o primeiro nome
		char primeiroNome[30];
		sscanf(nomeJogador, "%s", primeiroNome); // Pega apenas o primeiro nome

		// Converte o primeiro nome para minúsculas
		for (int k = 0; primeiroNome[k]; k++) {
			primeiroNome[k] = tolower(primeiroNome[k]);
		}

		bool encontrado = false;
		for (int j = 0; j < NUM_JOGADORES; j++) {
			// Extrai o primeiro nome do jogador na lista e converte para minúsculas
			char nomeDoJogador[30];
			sscanf(jogadoresPorEquipa[equipaSelecionada][j].nome, "%s", nomeDoJogador);
			for (int k = 0; nomeDoJogador[k]; k++) {
				nomeDoJogador[k] = tolower(nomeDoJogador[k]);
			}

			if (strcmp(nomeDoJogador, primeiroNome) == 0) {
				// Verifica se o jogador já foi posicionado
				if (strcmp(jogadoresPorEquipa[equipaSelecionada][j].posicaojogador, "") == 0) {
					strcpy(jogadoresPorEquipa[equipaSelecionada][j].posicaojogador, posicao);
					encontrado = true;
				}
				else {
					printf("Jogador %s já está posicionado. Tente novamente.\n", primeiroNome);
					encontrado = true; // O jogador foi encontrado, mas já está posicionado
				}
				break;
			}
		}
		if (!encontrado) {
			printf("Jogador %s não encontrado. Tente novamente.\n", primeiroNome);
			i--; // Decrementa o contador para permitir nova tentativa
		}
	}
}

int escolherTatica(jogadores jogadoresPorEquipa[NUM_EQUIPAS][NUM_JOGADORES], dadosdasequipas equipasEDados[NUM_EQUIPAS], int equipaSelecionada) {
	// Resetar as posições dos jogadores da equipa do utilizador
	resetarPosicoes(jogadoresPorEquipa, equipaSelecionada);

	int taticasEscolhida;
	printf("\nEscolha a tática:\n");
	printf("\n1. 4-3-3\n");
	printf("\n2. 4-4-2\n");
	printf("\n3. 5-3-2\n");
	printf("\n4. 4-5-1\n");
	printf("\nDigite o número da tática que deseja escolher: ");

	// Verifica se a entrada é um número válido
	if (scanf("%d", &taticasEscolhida) != 1) {
		// Limpa o buffer de entrada
		while (getchar() != '\n');
		printf("\nCaracter inválido. Por favor, insira um número.\n");
		return -1; // Retorna -1 para indicar erro
	}

	int defesas = 0, meio_campo = 0, avancados = 0;

	// Definindo as posições com base na tática escolhida
	switch (taticasEscolhida) {
	case 1: // 4-3-3
		defesas = 4; meio_campo = 3; avancados = 3;
		break;
	case 2: // 4-4-2
		defesas = 4; meio_campo = 4; avancados = 2;
		break;
	case 3: // 5-3-2
		defesas = 5; meio_campo = 3; avancados = 2;
		break;
	case 4: // 4-5-1
		defesas = 4; meio_campo = 5; avancados = 1;
		break;
	default:
		printf("Tática inválida. Por favor, escolha 1, 2, 3 ou 4.\n");
		return -1; // Retorna -1 para indicar erro
	}

	// Mostra os jogadores disponíveis e suas posições ideais
	printf("\nJogadores disponíveis para posicionamento:\n");
	printf("%-30s %-15s\n", "Nome", "Posição Ideal"); // cabeçalho alterado
	printf("-------------------------------------------------------------\n");

	for (int i = 0; i < NUM_JOGADORES; i++) {
		// Exibe apenas jogadores que não estão posicionados
		if (strcmp(jogadoresPorEquipa[equipaSelecionada][i].posicaojogador, "") == 0) {
			printf("%-30s %-15s\n", jogadoresPorEquipa[equipaSelecionada][i].nome, jogadoresPorEquipa[equipaSelecionada][i].posicaoIdeal); // Exibe a posição ideal
		}
	}

	// Escolher o guarda-redes
	printf("Escolha o guarda-redes:\n");
	posicionarJogadores(jogadoresPorEquipa, equipaSelecionada, "Guarda-redes", 1);

	// Posiciona os jogadores de acordo com a tática escolhida
	printf("Formação escolhida: %d-%d-%d\n", defesas, meio_campo, avancados);
	posicionarJogadores(jogadoresPorEquipa, equipaSelecionada, "Defesa", defesas);
	posicionarJogadores(jogadoresPorEquipa, equipaSelecionada, "Meio-campo", meio_campo);
	posicionarJogadores(jogadoresPorEquipa, equipaSelecionada, "Avançado", avancados);

	// Calcular e exibir o poder de ataque e defesa
	int poderAtaque = calcularPoderAtaque(jogadoresPorEquipa[equipaSelecionada]);
	int poderDefesa = calcularPoderDefesa(jogadoresPorEquipa[equipaSelecionada]);

	printf("\nPoder de Ataque da equipa %s: %d\n", equipasEDados[equipaSelecionada].equipa, poderAtaque);
	printf("Poder de Defesa da equipa %s: %d\n", equipasEDados[equipaSelecionada].equipa, poderDefesa);

	return 0; // Retorna 0 para indicar sucesso
}

// Função para perguntar ao usuário se deseja mudar a tática
int perguntarMudancaTatica() {
	char resposta;
	printf("Deseja mudar a tática? (s/n): ");
	scanf(" %c", &resposta);
	return (resposta == 's' || resposta == 'S') ? 1 : 0; // Retorna 1 se sim, 0 se não
}

//Função para simular jogo
int* simularJogo(dadosdasequipas equipasEDados[NUM_EQUIPAS], jogadores jogadoresPorEquipa[NUM_EQUIPAS][NUM_JOGADORES], int equipaSelecionada, int equipaAdversaria) {

	printf("\nSimulando jogo entre %s e %s...\n", equipasEDados[equipaSelecionada].equipa, equipasEDados[equipaAdversaria].equipa);

	int golosEquipa = 0;
	int golosAdversario = 0;
	int posseDeBola = equipaSelecionada;

	// Simulação de 90 minutos de jogo
	for (int tempo = 9; tempo <= 90; tempo += 9) {
		printf("\nMinuto: %d\n", tempo);

		if (posseDeBola == equipaSelecionada) {
			printf("Bola da tua equipa\n");
			int resultadoAtaque = gerirAtaque(jogadoresPorEquipa[equipaSelecionada], jogadoresPorEquipa[equipaAdversaria], 90 - tempo, false, "Meio-Campo");
			if (resultadoAtaque > 0) {
				printf("Ataque bem-sucedido! Golo marcado.\n");
				golosEquipa++;
				posseDeBola = equipaAdversaria;
			}
			else {
				char* localPerda = determinarLocalPerdaBola();
				printf("Ataque falhou. Perda de bola na zona: %s. CONTRA_ATAQUE\n", localPerda);
				int resultadoDefesa = gerirAtaque(jogadoresPorEquipa[equipaAdversaria], jogadoresPorEquipa[equipaSelecionada], 90 - tempo, true, localPerda);
				if (resultadoDefesa > 0) {
					golosAdversario++;
				}
			}
		}
		else if (posseDeBola == equipaAdversaria) {
			printf("Bola dos oponentes\n");
			int resultadoAtaque = gerirAtaque(jogadoresPorEquipa[equipaAdversaria], jogadoresPorEquipa[equipaSelecionada], 90 - tempo, false, "Meio-Campo");
			if (resultadoAtaque > 0) {
				printf("Ataque bem-sucedido! Golo marcado.\n");
				golosAdversario++;
				posseDeBola = equipaSelecionada;
			}
			else {
				char* localPerda = determinarLocalPerdaBola();
				printf("Ataque falhou. Perda de bola na zona: %s. CONTRA_ATAQUE\n", localPerda);
				int resultadoDefesa = gerirAtaque(jogadoresPorEquipa[equipaSelecionada], jogadoresPorEquipa[equipaAdversaria], 90 - tempo, true, localPerda);
				if (resultadoDefesa > 0) {
					golosEquipa++;
				}
			}
		}

		// Intervalo
		if (tempo == 45) {
			printf("\nIntervalo! Pressione Enter para continuar o jogo...\n");
			printf("Deseja trocar a tática? (s/n): ");
			char resposta;
			scanf(" %c", &resposta);
			if (resposta == 's' || resposta == 'S') {
				int resultadoEscolha;
				do {
					resultadoEscolha = escolherTatica(jogadoresPorEquipa, equipasEDados, equipaSelecionada);
					if (resultadoEscolha != 0) {
						printf("Caracter inválido. Tente novamente.\n");
					}
				} while (resultadoEscolha != 0); // Continua pedindo até que a escolha seja válida
			}
			printf("Pressione Enter para continuar o jogo...\n");
			while (getchar() != '\n'); // Limpa o buffer
			getchar(); // Espera pelo Enter
		}
	}

	printf("\nResultado Final: %s %d - %d %s\n", equipasEDados[equipaSelecionada].equipa, golosEquipa, golosAdversario, equipasEDados[equipaAdversaria].equipa);

	// Determinar vencedor e atualizar fundos
	int* resultadoegolos = malloc(3 * sizeof(int));
	if (resultadoegolos == NULL) {
		printf("Erro ao alocar memória para jogos.\n");
		exit(1);
	}
	resultadoegolos[0] = golosEquipa;
	resultadoegolos[1] = golosAdversario;

	if (golosEquipa > golosAdversario) {
		printf("A equipa %s venceu!\n", equipasEDados[equipaSelecionada].equipa);
		resultadoegolos[2] = 1; // Vitória
	}
	else if (golosEquipa < golosAdversario) {
		printf("A equipa %s venceu!\n", equipasEDados[equipaAdversaria].equipa);
		resultadoegolos[2] = -1; // Derrota
	}
	else {
		printf("O jogo terminou em empate!\n");
		resultadoegolos[2] = 0; // Empate
	}
	// Atualiza os fundos da equipa com base no resultado
	atualizarFundosPorResultado(equipaSelecionada, equipasEDados, resultadoegolos[2]);

	free(resultadoegolos); // Libere a memória alocada
	return resultadoegolos;
}

int calcularPoderAtaque(jogadores equipa[NUM_JOGADORES]) {
	int poderAtaque = 0;
	for (int i = 0; i < NUM_JOGADORES; i++) {
		if (strcmp(equipa[i].posicaojogador, "Avancado") == 0 || strcmp(equipa[i].posicaojogador, "Meio-campo") == 0) {
			poderAtaque += equipa[i].forca;
		}
	}
	return poderAtaque;
}

int calcularPoderDefesa(jogadores equipa[NUM_JOGADORES]) {
	int poderDefesa = 0;
	for (int i = 0; i < NUM_JOGADORES; i++) {
		if (strcmp(equipa[i].posicaojogador, "Defesa") == 0 || strcmp(equipa[i].posicaojogador, "Guarda-redes") == 0) {
			poderDefesa += equipa[i].forca;
		}
	}
	return poderDefesa;
}


int main() {
	setlocale(LC_ALL, "Portuguese");

	// Cria treinadores para cada equipa
	char treinador[NUM_EQUIPAS][15];
	// Cria dados para 18 equipas e jogadores para cada
	dadosdasequipas equipasEDados[NUM_EQUIPAS];
	jogadores jogadoresPorEquipa[NUM_EQUIPAS][NUM_JOGADORES]; // 20 jogadores por equipa
	tabbeladeresultados tabela = { 0 }; // Inicializa todos os membros com zero

	// Abre o ficheiro "Equipas.txt"
	FILE* equipas = fopen("Equipas.txt", "r");
	if (equipas == NULL) {
		printf("Não foi possível abrir o ficheiro.\n");
		return 1;
	}

	// Lê as linhas do arquivo e guarda no local correto
	int equipaCount = 0;
	char line[50];

	// Ler treinador e equipa
	while (equipaCount < NUM_EQUIPAS && fgets(line, sizeof(line), equipas) != NULL) {
		sscanf(line, "%[^\n]", treinador[equipaCount]);

		if (fgets(line, sizeof(line), equipas) != NULL) {
			sscanf(line, "%[^\n]", equipasEDados[equipaCount].equipa);
		}

		equipasEDados[equipaCount].fundosdoclube = 100000000.0; // 100 milhões
		equipasEDados[equipaCount].despesasdoestadio = 100000.0; // 100 mil

		// Ler 20 jogadores
		for (int j = 0; j < NUM_JOGADORES; j++) {
			if (fgets(line, sizeof(line), equipas) != NULL) {
				sscanf(line, "%[^;];%d;%[^;];%d", jogadoresPorEquipa[equipaCount][j].nome, &jogadoresPorEquipa[equipaCount][j].numero, jogadoresPorEquipa[equipaCount][j].posicaojogador, &jogadoresPorEquipa[equipaCount][j].forca);

				// Gera um valor aleatório para o vencimento de cada jogador
				jogadoresPorEquipa[equipaCount][j].vencimento = (rand() % (3000000 - 700000 + 1)) + 700000; // Um valor random entre 700000 e 3000000
			}
		}
		equipaCount++;
	}

	fclose(equipas);

	// Chama a função para mostrar as equipas e captura o índice da equipa selecionada
	int equipaSelecionada = mostrarEquipas(treinador, equipasEDados, jogadoresPorEquipa, NUM_EQUIPAS);

	while (true) {
		// Criar as jornadas automaticamente após a seleção da equipa
		printf("Pressione Enter para criar o calendário de jogos...\n");
		getchar(); // Espera pelo input do utilizador
		getchar(); // Captura o Enter
		limparTela();

		// Criar as jornadas automaticamente após a seleção da equipa
		int** primeirosjogos = criarCalendario(equipasEDados);
		printf("Primeira Jornada-----------------------------------------\n");

		int** segundojogos = criarCalendario(equipasEDados);
		printf("Segunda Jornada------------------------------------------\n");

		int** terceirojogos = criarCalendario(equipasEDados);
		printf("Terceira Jornada-----------------------------------------\n");

		// Escolher a tática antes de simular o jogo
		int resultadoEscolha;
		do {
			resultadoEscolha = escolherTatica(jogadoresPorEquipa, equipasEDados, equipaSelecionada);
			if (resultadoEscolha != 0) {
				printf("Caracter inválido. Tente novamente.\n");
			}
		} while (resultadoEscolha != 0); // Continua pedindo até que a escolha seja válida
		limparTela();

		// Simular jogos para a primeira jornada
		printf("\nPrimeira Jornada-----------------------------------------------------------------------------------");
		for (int c = 0; c < 9; c++) {
			if (primeirosjogos[c][0] == equipaSelecionada) {
				int* resultados = simularJogo(equipasEDados, jogadoresPorEquipa, equipaSelecionada, primeirosjogos[c][1]);
				tabela.numerodejogos++;
				tabela.numerodegolos += *resultados;
				tabela.numerodesofridos += *(resultados + 1);
				if (*(resultados + 2) == 1) {
					tabela.numerodevitorias++;
				}
				else if (*(resultados + 2) == -1) {
					tabela.numerodederrotas++;
				}
				else if (*(resultados + 2) == 0) {
					tabela.numerodeempates++;
				}
			}
			else if (primeirosjogos[c][1] == equipaSelecionada) {
				int* resultados = simularJogo(equipasEDados, jogadoresPorEquipa, equipaSelecionada, primeirosjogos[c][0]);
				tabela.numerodejogos++;
				tabela.numerodegolos += *resultados;
				tabela.numerodesofridos += *(resultados + 1);
				if (*(resultados + 2) == 1) {
					tabela.numerodevitorias++;
				}
				else if (*(resultados + 2) == -1) {
					tabela.numerodederrotas++;
				}
				else if (*(resultados + 2) == 0) {
					tabela.numerodeempates++;
				}
			}
		}

		// Simular jogos para a segunda jornada
		printf("\nSegunda Jornada------------------------------------------------------");
		for (int c = 0; c < 9; c++) {
			if (segundojogos[c][0] == equipaSelecionada) {
				if (perguntarMudancaTatica()) {
					escolherTatica(jogadoresPorEquipa, equipasEDados, equipaSelecionada);
				}
				int* resultados = simularJogo(equipasEDados, jogadoresPorEquipa, equipaSelecionada, segundojogos[c][1]);
				tabela.numerodejogos++;
				tabela.numerodegolos += *resultados;
				tabela.numerodesofridos += *(resultados + 1);
				if (*(resultados + 2) == 1) {
					tabela.numerodevitorias++;
				}
				else if (*(resultados + 2) == -1) {
					tabela.numerodederrotas++;
				}
				else if (*(resultados + 2) == 0) {
					tabela.numerodeempates++;
				}
			}
			else if (segundojogos[c][1] == equipaSelecionada) {
				if (perguntarMudancaTatica()) {
					escolherTatica(jogadoresPorEquipa, equipasEDados, equipaSelecionada);
				}
				int* resultados = simularJogo(equipasEDados, jogadoresPorEquipa, equipaSelecionada, segundojogos[c][0]);
				tabela.numerodejogos++;
				tabela.numerodegolos += *resultados;
				tabela.numerodesofridos += *(resultados + 1);
				if (*(resultados + 2) == 1) {
					tabela.numerodevitorias++;
				}
				else if (*(resultados + 2) == -1) {
					tabela.numerodederrotas++;
				}
				else if (*(resultados + 2) == 0) {
					tabela.numerodeempates++;
				}
			}
		}

		// Simular jogos para a terceira jornada
		printf("\nTerceira Jornada------------------------------------------------------");
		for (int c = 0; c < 9; c++) {
			if (terceirojogos[c][0] == equipaSelecionada) {
				if (perguntarMudancaTatica()) {
					escolherTatica(jogadoresPorEquipa, equipasEDados, equipaSelecionada);
				}
				int* resultados = simularJogo(equipasEDados, jogadoresPorEquipa, equipaSelecionada, terceirojogos[c][1]);
				tabela.numerodejogos++;
				tabela.numerodegolos += *resultados;
				tabela.numerodesofridos += *(resultados + 1);
				if (*(resultados + 2) == 1) {
					tabela.numerodevitorias++;
				}
				else if (*(resultados + 2) == -1) {
					tabela.numerodederrotas++;
				}
				else if (*(resultados + 2) == 0) {
					tabela.numerodeempates++;
				}
			}
			else if (terceirojogos[c][1] == equipaSelecionada) {
				if (perguntarMudancaTatica()) {
					escolherTatica(jogadoresPorEquipa, equipasEDados, equipaSelecionada);
				}
				int* resultados = simularJogo(equipasEDados, jogadoresPorEquipa, equipaSelecionada, terceirojogos[c][0]);
				tabela.numerodejogos++;
				tabela.numerodegolos += *resultados;
				tabela.numerodesofridos += *(resultados + 1);
				if (*(resultados + 2) == 1) {
					tabela.numerodevitorias++;
				}
				else if (*(resultados + 2) == -1) {
					tabela.numerodederrotas++;
				}
				else if (*(resultados + 2) == 0) {
					tabela.numerodeempates++;
				}
			}
		}

		// Atualizar fundos após a terceira jornada
		atualizarFundos(equipaSelecionada, equipasEDados, jogadoresPorEquipa);

		// Permitir ao usuário comprar jogadores após a terceira jornada
		comprarJogadores(equipasEDados, jogadoresPorEquipa, equipaSelecionada);



		// Pergunta ao jogador se deseja criar um novo calendário ou sair
		char opcao;
		printf("\nDeseja criar um novo calendário? (s/n): ");
		scanf(" %c", &opcao);

		if (opcao == 's' || opcao == 'S') {
			// Reinicia a tabela e continua o loop
			tabela = (tabbeladeresultados){ 0 }; // Reseta a tabela
			printf("Criando um novo calendário...\n");
			// O jogador não precisa escolher a equipe novamente
		}
		else {
			printf("Saindo do jogo. Obrigado por jogar!\n");
			exit(0); // Sai do programa
		}
	}

	return 0;
}

