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
    int forca;
} jogadores;

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

void atualizarFundosPorResultado(int equipaIndex, dadosdasequipas equipasEDados[NUM_EQUIPAS], int resultado)
{
    float ganho;

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
}


// Função para gerar um calendário de jogos
int** criarCalendario(dadosdasequipas equipasEDados[NUM_EQUIPAS]) 
{
    int equipasnumeros[18] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
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
    for(int i = 0 ; i < 9; i++){
        while(equipasnumeros[equipa1] == 20 || equipasnumeros[equipa1] == equipasnumeros[equipa2])
        {
            equipa1 = rand() % NUM_EQUIPAS;
        }
        while(equipasnumeros[equipa2] == 20 || equipasnumeros[equipa1] == equipasnumeros[equipa2])
        {
            equipa2 = rand() % NUM_EQUIPAS;
        }
        
        jogos[i][0] = equipa1;
        jogos[i][1] = equipa2;
        equipasnumeros[equipa1] = 20;
        equipasnumeros[equipa2] = 20;
    }
    for(int j = 0; j < 9; j++)
    {
        printf(" jogo numero %i : %s vs %s\n", j+1, equipasEDados[jogos[j][0]].equipa, equipasEDados[jogos[j][1]].equipa);
    }


    return jogos;
}

//Funçoes utilizadas durante um jogo
int calcularPoderAtaque(jogadores equipa[NUM_JOGADORES])
{

    int poderAtaque = 0;
    for (int i = 0; i < NUM_JOGADORES; i++) {
        if (strcmp(equipa[i].posicaojogador, "Avancado") == 0 || strcmp(equipa[i].posicaojogador, "Meio-campo") == 0) {
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
            while (getchar() != '\n');
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



int main() 
{
    setlocale(LC_ALL, "Portuguese");

    // cria treinadores para cada equipa
    char treinador[NUM_EQUIPAS][15];
    // cria dados para 18 equipas e jogadores para cada
    dadosdasequipas equipasEDados[NUM_EQUIPAS];
    jogadores jogadoresPorEquipa[NUM_EQUIPAS][NUM_JOGADORES]; // 20 jogadores por equipa
    tabbeladeresultados tabela;

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
                
                //gera um valor aleatorio para o vencimento de cada jogador
                jogadoresPorEquipa[equipaCount][j].vencimento = (rand() % (3000000 - 700000 + 1)) + 700000; // Um valor random entre 700000 e 3000000
            }
        }
        equipaCount++;
    }

    fclose(equipas);

    // Chama a função para mostrar as equipas e captura o índice da equipa selecionada
    int equipaSelecionada = mostrarEquipas(treinador, equipasEDados, jogadoresPorEquipa, NUM_EQUIPAS);

    printf("Primeira Jornada-----------------------------------------\n");
    int** primeirosjogos = criarCalendario(equipasEDados);
    printf("Segunda Jornada------------------------------------------\n");
    int** segundojogos = criarCalendario(equipasEDados);
    printf("Terceira Jornada-----------------------------------------\n");
    int** terceirojogos = criarCalendario(equipasEDados);
    
   /* char continuar;
    do {
        printf("\nDeseja continuar? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');*/

    printf("Primeira Jornada-----------------------------------------------------------------------------------");
    for(int c = 0; c < 9; c++){
         if(primeirosjogos[c][0] == equipaSelecionada){
            int* resultados = simularJogo(equipasEDados, jogadoresPorEquipa, equipaSelecionada, primeirosjogos[c][1]);
            tabela.numerodejogos++;
            tabela.numerodegolos += *resultados;
            tabela.numerodesofridos += *(resultados + 1);
            if(*(resultados+2) == 1){
                tabela.numerodevitorias++;
            }
            else if (*(resultados + 2) == -1) {
                tabela.numerodederrotas++;
            }
            else if (*(resultados + 2) == 0) {
                tabela.numerodeempates++;
            }
         }
         else if (primeirosjogos[c][1] == equipaSelecionada) 
         {
                 int* resultados = simularJogo(equipasEDados, jogadoresPorEquipa, equipaSelecionada, primeirosjogos[c][0]);
                 tabela.numerodejogos++;
                 tabela.numerodegolos += *resultados;
                 tabela.numerodesofridos += *(resultados+1);
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
    printf("Segunda Jornada-----------------------------------------------------------------------------------");
    for (int c = 0; c < 9; c++) {
        if (segundojogos[c][0] == equipaSelecionada) {
            int* resultados = simularJogo(equipasEDados, jogadoresPorEquipa, equipaSelecionada, segundojogos[c][1]);
            tabela.numerodejogos++;
            tabela.numerodegolos += *resultados;
            tabela.numerodesofridos += *(resultados+1);
            if (*(resultados+2) == 1) {
                tabela.numerodevitorias++;
            }
            else if (*(resultados+2) == -1) {
                tabela.numerodederrotas++;
            }
            else if (*(resultados+2) == 0) {
                tabela.numerodeempates++;
            }
        }
        else if (segundojogos[c][1] == equipaSelecionada){ 
                int* resultados = simularJogo(equipasEDados, jogadoresPorEquipa, equipaSelecionada, segundojogos[c][0]);
                tabela.numerodejogos++;
                tabela.numerodegolos += *resultados;
                tabela.numerodesofridos += *(resultados+1);
                if (*(resultados+2) == 1) {
                    tabela.numerodevitorias++;
                }
                else if (*(resultados+2) == -1) {
                    tabela.numerodederrotas++;
                }
                else if (*(resultados+2) == 0) {
                    tabela.numerodeempates++;
                }
        }
    }
    printf("Terceira Jornada-----------------------------------------------------------------------------------");
    for (int c = 0; c < 9; c++) {
        if (terceirojogos[c][0] == equipaSelecionada) {
            int* resultados = simularJogo(equipasEDados, jogadoresPorEquipa, equipaSelecionada, terceirojogos[c][1]);
            tabela.numerodejogos++;
            tabela.numerodegolos += resultados[0];
            tabela.numerodesofridos += resultados[1];
            if (resultados[2] == 1) {
                tabela.numerodevitorias++;
            }
            else if (resultados[2] == -1) {
                tabela.numerodederrotas++;
            }
            else if (resultados[2] == 0) {
                tabela.numerodeempates++;
            }
        }
        else if (terceirojogos[c][1] == equipaSelecionada) {
                int* resultados = simularJogo(equipasEDados, jogadoresPorEquipa, equipaSelecionada, terceirojogos[c][0]);
                tabela.numerodejogos++;
                tabela.numerodegolos += *resultados;
                tabela.numerodesofridos += *(resultados+1);
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
    return 0;
}
